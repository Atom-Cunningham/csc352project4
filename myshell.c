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
#define CMD_NUM 5

//gets the input and splits it
int read_input(char* args[], char* in){
    //assigns args[i] to the address of each string in in
    
    args[0] = strtok(in," ()<>|&;");
    //make sure there is at least one arg
    if (args[0] == NULL){
        return 0;
    }
    int i = 1;
    while(i < CMD_NUM){

        //assign strtok(in) to args[i]
        //replace old in
        args[i] = strtok(NULL, " ()<>|&;");
        if(args[i] == NULL){
            return i;
        }
        printf("%s\n",args[i]); //sanity check
        i++;
    }
    //returns the number of strings originally in in
    return i;
}


int run(char * in){
    int arg_count;
    char * args[CMD_NUM];
    printf("running\n");
    arg_count = read_input(args, in);
    printf("args[0]: %s\n", args[0]);
    printf("strcmp(%s, exit) == %d", args[0], strcmp(args[0], "exit"));
    if (!strcmp(args[0], "exit")){  
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
        i++;
    }
    return 0;
}

