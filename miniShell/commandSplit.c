#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
char** commandSplit(char *command){
    char*  adjustedCommand=(char*)malloc(sizeof(char)*1024);
    int commPlace=0;
    int adjustPlace=0;
    int amount=0;
    int type=-1;
    while(command[commPlace]!='\n'){
        if(command[commPlace]=='|' || command[commPlace]=='&'  || command[commPlace]=='\t' || command[commPlace]=='>'){
            if(command[commPlace-1]!=' '){
                amount++;
                adjustedCommand[adjustPlace++]=' ';
            }
            adjustedCommand[adjustPlace++] = command[commPlace++];
            if(command[commPlace]!=' '){
                adjustedCommand[adjustPlace++]=' ';
                amount++;
            }
        } else if(command[commPlace]=='<') 
            command[commPlace++]==' ';
        else{
            if(command[commPlace]==' ')  amount++;
            adjustedCommand[adjustPlace++] = command[commPlace++];
        }
    }
    amount++;
    char**  commSplitted=(char**)malloc(sizeof(char*)*1024);
    int temp=0;
    commSplitted[temp++] = strtok(adjustedCommand," ");
    while(commSplitted[temp++]=strtok(NULL," ")) continue;
    return commSplitted;
}