#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
/**
 * support exit
 * cd
 * ls, nano, pwd, ls -l,wc
 * time
 * 
 */

#define LEN 1024
int main(int argc, char ** argv){
    char * tokens = get_input();
     while (tokens!= NULL){
        printf("%s",tokens);
        tokens = strtok(NULL,  " ()<>|&;");
    }
}

char* get_input(){
    char buffer[LEN];
    fgets(buffer, LEN, stdin);
    char * tokens = strtok(buffer, " ()<>|&;");
    return tokens;
}

/**
 * The following exit, cd
 */

