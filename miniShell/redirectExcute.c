#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>
FILE* redirectExcute(char** commSplitted, int arrPlace){
    FILE* output;
    FILE* result;
    if(strcmp(commSplitted[0],"exit")==0)
        return 0;
    if(commSplitted[arrPlace][0]=='>'){
        //output redirection
        char  command[128];
        memset(command, '\0', 128);
        int commPlace=0;
        for(int i=0;i<arrPlace;i++){
            for(int j=0;commSplitted[i][j];j++){
                command[commPlace++] = commSplitted[i][j];
            }
            command[commPlace++] = ' ';
        }
        if(commSplitted[arrPlace+1]){
            output = fopen(commSplitted[arrPlace+1], "w+");
            if(output){
                //printf("\033[35m%s\n", command),fflush(stdout);
                result = popen(command, "r");
                char bridge;
                while(1)
                {
                    bridge = fgetc(result);
                    if(bridge==-1) break;
                    //printf("\033[33m%c", bridge);
                    fputc(bridge, output);
                    fflush(output); 
                }
                fclose(output);
                pclose(result);
            }
        }
    }
    return output;
}