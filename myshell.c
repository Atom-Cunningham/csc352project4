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
#define CMD_NUM 25

int cd(char* new_dir){
    int status = chdir(new_dir);

    //TODO remove prints
    char cwd[256];
    char * newCurrent = getcwd(cwd, sizeof(cwd));
    printf("%s\n",newCurrent);

    if (status != 0){
        printf("cannot find directory %s", new_dir);
    }
    return status;

}

//gets the input and splits it
int read_input(char* args[], char* in){
    //make sure there is at least one arg
    if ((args[0] = strtok(in, " \n\t()<>|&;")) == NULL){
        return 0;
    }
    int i = 0;
    while( i<CMD_NUM && (args[++i] = strtok(NULL, "\n\t ")) != NULL){
        printf("%s\n",args[i]); //sanity check
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
    
    //EXIT
    if (!strcmp(args[0], "exit")){  
        printf("exiting");
        exit(0);
        }
    return 0;

    //CD
    if(!strcmp(args[0], "cd")){
        printf("cding\n");
        if (arg_count < 2){
            printf("Please provide a directory name\n");
        }else{

        }
    }
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

