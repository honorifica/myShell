int checkValid(char* command){
    int place=0;
    int flag=0;
    while(command[place] ){
        if(command[place]!=' ' && command[place]!='\n' && command[place] !='\t' )
            flag =1;
            break;
    }
    return flag;
}