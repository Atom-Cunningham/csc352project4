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
char* get_input();

//gets the input and splits it
char* get_input(){
    char buffer[LEN];
    fgets(buffer, LEN, stdin);
    char * tokens = strtok(buffer, " ()<>|&;");
    return tokens;
}

//broken
int count_tokens(char tokens[]){
    int count = 0;
    while (tokens!= NULL){
        printf("%s ",tokens);
        count++;
        tokens = strtok(NULL,  " ()<>|&;");
    }
    return count;
}

int run(char * args){

}

int main(int argc, char ** argv){
    //get input from the user
    char * tokens = get_input();

    int count = count_tokens(tokens);
    printf("\ntoken count %d \n", count);
}

