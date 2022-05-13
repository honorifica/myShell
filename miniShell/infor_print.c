#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
void infor_print(){
    char* userName = getlogin();
    char* hostName = (char*)malloc(sizeof(char)*256);
    gethostname(hostName, 256);
    char workSpace[256];   
    getcwd(workSpace,256);   
    int uid = getuid();
    char userLevel;
    if(uid==0) userLevel = '#';
    else userLevel='$';
    printf("\033[1m\033[32m%s@%s\033[37m:\033[31m%s\033[37m%c\033[0m ",userName, hostName,workSpace, userLevel);
}