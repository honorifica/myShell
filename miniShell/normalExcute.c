#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>
int  normalExcute(char** commSplitted){
    //printf("\033[35m%s\033[0m", commSplitted[0]);
    if(strcmp(commSplitted[0] , "cd")==0){
        if(commSplitted[1]) {
            if(chdir(commSplitted[1])!=0){
                char currentDIr[256];
                getcwd(currentDIr, 256);
                strcat(currentDIr, commSplitted[1]);
                chdir(currentDIr);
            }
        }
        return 1;
    }
    int amount = 0;
    while(commSplitted[amount])amount++;

    pid_t pid =  fork();
    if(pid>0) wait(NULL);
    else if(pid<0) {
        fprintf(stderr, "excute process fork failed");
        exit(0);
    }
    else {
        char ecvFile1[32];
        char ecvFile2[32];
        memset(ecvFile1, '\0', 32);
        memset(ecvFile2, '\0', 32);
        strcat(ecvFile1, "/bin/");
        strcat(ecvFile2, "/usr/bin/");
        strcat(ecvFile1, commSplitted[0]);
        strcat(ecvFile2, commSplitted[0]);
        if(execv(ecvFile1, commSplitted )==-1)
            execv(ecvFile2, commSplitted );
        exit(1);
    }
}

