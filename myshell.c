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
#include <sys/times.h>
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
        if (execvp(args[0], args)){
            fprintf(stderr, 
            "%s has failed to execute\n", args[0]);
        }
    }
    else
    {
        int status;
        wait(&status);
        if(!WIFEXITED(status)){
            fprintf(stderr, 
            "The shell has encountered an error with the previous command");
        }
    }
    return 0;
}


/**
 * attempts to change the current working directory
 * takes a string as the new directory path
 * prints an error if a change in directory failed
 * returns the error status
 */
int cd(char* new_dir){
    int status = chdir(new_dir);
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
    if ((args[0] = strtok(in, " \n\t()<|&;")) == NULL){
        return 0;
    }
    int i = 0;
    while( i<CMD_NUM && (args[++i] = strtok(NULL, " ")) != NULL){

    }
    args[i] = NULL;
    //returns the number of strings originally in in
    return i;
}



/**
 * removes the first item of the passed array
 * by copying values backwards by one
 * used to get rid of the time argument
 * returns 0
 */
int remove_time_arg(char* args[]){
    int i = 0;
    if (!strcmp(args[0], "time")){
        while(i < CMD_NUM - 1){
            args[i] = args[i+1];
            i++;
        }
    }
    return i;
}

/**updates the input stream to the given filename if possible
 * returns 1 if not
 */
FILE * update_stream(char * args[]){
    int i = 0;
    char * filename = NULL;
    //const char *mode = 'w';
    FILE * file;
    while (i < CMD_NUM && args[i+1]){
        if((args[i][0] - '>' == 0) || !strcmp(args[i], ">>")){
            printf("file cmd found\n");
            filename = args[i+1];
            if (!strcmp(args[i], ">>")){
                //mode = 'a';
            }
            file = freopen(filename, mode, stdout);
            args[i] = NULL;
            args[i+1]=NULL;
        }
        i++;
    }
    if (!file){
        fclose(file);
    }
    return file;
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
    arg_count = read_input(args, in);

    //check to see if time is the first argument
    //start a timer
    int time = remove_time_arg(args);
    clock_t start = clock();

    //EXIT
    if (!strcmp(args[0], "exit")){  
        exit(0);
    }

    //Change directory
    if(!strcmp(args[0], "cd")){
        if (arg_count < 2 || args[1] == NULL){
            printf("Please provide a directory name\n");
        }else{
            status = cd(args[1]);
        }
    }

    //System Calls
    else{
        //check for file names
        //FILE * file = update_stream(args);
        status = unix_cmd(args);
        //fclose(file);

        
    }
    //TIME
    clock_t end = clock();
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    if (time){
        printf("program ran in %2f seconds", elapsed);
    }
}

/**attempts to get user input from stdin
 * calls an appropriate shell/system command, or prints an error
 */
int main(int argc, char ** argv){
    //get input from the user
    char in[LEN];
    int i = 0;
    while (i < 3){
        printf(">>");
        i++;
        if(fgets(in, LEN,stdin) == NULL){
            fprintf(stderr, "failed to read input");
        }else{
            run(in);
        }
    }
    return 0;
}

