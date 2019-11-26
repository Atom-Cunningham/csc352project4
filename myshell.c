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
#define LEN 255
#define EXIT "exit"
#define CD "cd"
#define TIME "time"

//gets the input and splits it
int read_input(char* args[], char* in){
    //assigns args[i] to the address of each string in in
    int i = 0;
    args[0] = strtok(in," ()<>|&;");

    //make sure there is at least one arg
    if (args[0] == NULL){
        return 0;
    }
    while((args[++i] = strtok(in, " ()<>|&;")) != NULL){
        printf("%s\n",args[i]); //sanity check
    }
    //returns the number of strings originally in in
    return i;
}


int run(char * in){
    int arg_count;
    char * args[5];
    printf("running\n");
    printf("args[0]: %s\n", args[0]);
    if (strcmp(args[0], EXIT) == 0){  
        exit(0);
    }
    return 0;
}

int main(int argc, char ** argv){
    //get input from the user
    char in[LEN];
    int i = 0;
    while (i < 3){
        if(fgets(in, LEN,stdin) == NULL){
            fprintf(stderr, "failed to read input");
        }
        run(in);
    }
    return 0;
}

