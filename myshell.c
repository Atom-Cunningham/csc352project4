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

#define LEN 128
int main(int argc, char ** argv){
    get_input();
}

char* get_input(){
    char buffer[LEN];
    fgets(buffer, LEN, stdin);
    printf("%s",strtok(buffer, " ()<>|&;"));
    return buffer;
}

/**
 * The following exit, cd
 */

