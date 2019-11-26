/**
 * Adam Cunningham
 * NetID Laser
 * csc352 project 4
 * 
 * this is a basic shell
 * It can perform built in commands such as 
 * cd, exit, and time
 * It can also run any unix command that is not built
 * into the shell
 * 
 */
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define LEN 255
#define CMD_NUM 25

/**
 * attempts to launch a program using the given arguments
 * calls fork and waits
 * prints an error message if necessary
 */
int unix_cmd(char* args[]){
    if(fork()==0){
        execvp(args[0], args);
    }
    else
    {
        int status;
        wait(&status);
    }
    return status;
}

/**
 * attempts to change the current working directory
 * takes a string as the new directory path
 * prints an error if a change in directory failed
 * returns the error status
 */
int cd(char* new_dir){
    int status = chdir(new_dir);

    /**
    //TODO remove prints
    char cwd[256];
    char * newCurrent = getcwd(cwd, sizeof(cwd));
    printf("%s\n",newCurrent);
    */
    if (status != 0){
        printf("cannot find directory %s\n", new_dir);
    }
    return status;
}

/**
 * takes an array of strings, and an input string from stdin
 * replaces whitespace and specified charaters with '\0'
 * copies the pointers to the passed in array of strings
 * returns the count of the number of arguments given
 */
int read_input(char* args[], char* in){
    //make sure there is at least one arg
    if ((args[0] = strtok(in, " \n\t()<>|&;")) == NULL){
        return 0;
    }
    int i = 0;
    while( i<CMD_NUM && (args[++i] = strtok(NULL, " ")) != NULL){
        printf("%s\n",args[i]); //sanity check
    }
    args[i] = NULL;
    //returns the number of strings originally in in
    return i;
}

/**
 * takes the input stream from fread
 * parses it for arguments
 * checks the first argument against built in commands
 * then tries to run it as a unix command
 * returns an error status
 */
int run(char * in){
    int arg_count;
    int status;
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

    //Change directory
    if(!strcmp(args[0], "cd")){
        printf("cding\n");
        if (arg_count < 2 || args[1] == NULL){
            printf("Please provide a directory name\n");
        }else{
            status = cd(args[1]);
        }
    }

    //System Calls
    else{
        status = unix_cmd(args);
            //pwd is NULL if bad, else pointer
        if(( !strcmp(args[0], "pwd") && status == NULL)
            //ls is 1 or 2 on bad return
        ||  (!strcmp(args[0], "ls")  && status >  0)
            //if not pwd, non-zero is usually bad
        ||  ( strcmp(args[0], "pwd") && status >  0)
        {
            fprintf(stderr, "invalid unix cmd");
        }
        
    }

    //TIME
    return status;
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

