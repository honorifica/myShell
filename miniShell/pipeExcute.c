#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>
int pipeExcute(char** commandSplitted, int linePlace){
    /*initialize*/
    char command[128];
    memset(command, '\0', 128 );
    int storingPlace=0;
    int arrPlace=-1;
    char* sigSplittedCom[16];
    /*get array place*/
    for(int i=0;i<linePlace;i++){
        sigSplittedCom[i] = commandSplitted[i];
        if(commandSplitted[i][0]=='>'){
            arrPlace=i;
        }
    }
    FILE *output;//->file to store current result
    if(arrPlace!=-1){
        /**
         * For redirect command.
         * The place behind the arrPlace is the file which the result need to be stored
         * which was already formed by redirectExcute
         * Simply need to open it and stored it to temp file "former"
         * which can be used in the continued command as file argument
         **/
        redirectExcute(sigSplittedCom, arrPlace);
        FILE* result =fopen(sigSplittedCom[arrPlace+1], "r");
        char bridge;
        output = fopen("former", "w");
        while(1){
            bridge= fgetc(result);
            if(bridge==-1) break;
            fputc(bridge, output);
            fflush(output);
        }
    } else if(arrPlace==-1){
        /**
         * for command which are not redirect
         * restore the splitted command to a whole one
         * use popen() to excute the command
         * and store the result in the temp file "current"
         * then restore the result to file "former" 
         * which its path can be used in the continued command as input
         **/
        /*get line place*/
        for(int i=0;i<linePlace;i++){
            for(int j=0;commandSplitted[i][j];j++){
                command[storingPlace++]=commandSplitted[i][j];
            }
            command[storingPlace++]=' ';
        }
        //printf("\033[35m%s\n", command),fflush(stdout);
        /*get current result*/
        char bridge;
        FILE* result = popen(command, "r");
        output = fopen("current", "w");
        while(1)
        {
            bridge = fgetc(result);
            if(bridge==-1) break;
            //printf("\033[35m%c", bridge),fflush(stdout);
            fputc(bridge, output);
            fflush(output); 
        }
        fclose(output);
        pclose(result);
        /*store as former result*/
        FILE* former=fopen("former", "w");
        output = fopen("current", "r");
        while(1 && output)
        {
            bridge = fgetc(output);
            if(bridge==-1) break;
            fputc(bridge, former);
            fflush(former); 
        }
        fclose(former);
        if(output) fclose(output);
    }
    /*needed result filepath generate*/
    char filePath[256];
    memset(filePath, '\0', 256);
    if(arrPlace==-1){
        getcwd(filePath, 256);
        strcat(filePath,"/former");
    } else {
        getcwd(filePath, 256);
        if(commandSplitted[arrPlace+1][0]!='>')
            strcat(filePath, "/");
        strcat(filePath, commandSplitted[arrPlace+1]);
    }
    /*form next splitted command*/
    char** newSplittedComm = (char**)malloc(sizeof(char*)*128);
    for(int i=0;i<128;i++){
        newSplittedComm[i]=NULL;
    }
    storingPlace=0;
    int lineFoundFlag=0;
    int arrFoundFlag=0;
    for(int i=linePlace+1;commandSplitted[i];){
        if(commandSplitted[i][0]=='|' && lineFoundFlag==0){
            newSplittedComm[storingPlace++] = filePath;
            lineFoundFlag=1;
        }
        if(commandSplitted[i][0]=='>' &&   arrFoundFlag==0){
            newSplittedComm[storingPlace++] = filePath;
            arrFoundFlag=1;
        }
        newSplittedComm[storingPlace++] = commandSplitted[i++];
    }
    if(lineFoundFlag==0 && arrFoundFlag == 0) 
        newSplittedComm[storingPlace]=filePath;
    /*get new pipe '|' place*/
    int newLinePlace=-1;
    for(int i=0;newSplittedComm[i];i++){
        if(newSplittedComm[i][0]=='|'){
            newLinePlace = i;
            break;
        }
    }
    /*next excute*/
    free(commandSplitted);
    if(newLinePlace!=-1){
        pipeExcute(newSplittedComm, newLinePlace);
        return 1;
    }
    else{
        sigCommPerform(newSplittedComm);
        remove("current");
        remove("former");
        return 1;
    }
}