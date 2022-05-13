#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include"normalExcute.c"
#include"redirectExcute.c"
#include"pipeExcute.c"
int sigCommPerform(char** commSplitted){
    int arrplace=-1;
    int linePlace=-1;
    for(int i=0;commSplitted[i];i++){
        //printf("\033[35m%s ", commSplitted[i]),fflush(stdout);
        if(commSplitted[i][0]=='>') {
            arrplace  = i;
        }
        if(commSplitted[i][0]=='|'){
            linePlace=i;
            break;
        }
    }
    //printf("\n");
    if(arrplace==-1 && linePlace ==-1){
        normalExcute(commSplitted);
        free(commSplitted);
        return 1;
    }else if (arrplace!=-1 && linePlace == -1){
        redirectExcute(commSplitted, arrplace);
        free(commSplitted);
        return 1;
    }else if(linePlace!=-1){
        pipeExcute(commSplitted, linePlace);
        return 1;
    }
}