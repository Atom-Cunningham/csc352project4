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
        args[i] = strtok(NULL, " \n\t()<>|&;");
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
    char * str;
    printf("running\n");
    arg_count = read_input(args, in);
    str[5] = args[0];
    printf("args[0]: %s\n", args[0]);
    printf("strcmp(%s, exit) == %d", str, strcmp(str, "exit"));
    if (!strcmp(str, "exit\0")){  
        exit(0);
    }
    str[4] = args[0];
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

