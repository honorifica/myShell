#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include"infor_print.c"
#include"commandSplit.c"
#include"checkValid.c"
#include"sigCommPerform.c"

int main(){
    while(1){    
        /*initialize*/
        char* command=(char*)malloc(sizeof(char)*1024);
        memset(command, '\0' , 1024);
        size_t length;
        /*information show*/
        infor_print();
        /*command grabber*/
        getline(&command, &length, stdin);
        //printf("\033[33m%s",command );
        if(command[0]=='\n')continue;
        if(strcmp(command, "exit\n")==0)
            exit(1);
        char** commSplitted= NULL;
        /*command valid verify*/
        if(checkValid(command)==0)
            continue;
        commSplitted = commandSplit(command);
        if(sizeof(commSplitted)==0) continue;
        if(sigCommPerform(commSplitted)==0) break;
        free(command);
    }
}