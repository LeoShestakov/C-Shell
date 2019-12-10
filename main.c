#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>

char ** processInput(char *line);

int main() {
  while(1){
    char curdir [100];
    getcwd(curdir, 100);

    printf("%s $ ", curdir);
    char input[100];
    fgets(input, 100, stdin);
    input[strlen(input) - 1] = NULL;
    char ** newInput = processInput(input);


    pid_t pid;
    time_t t;
    int status;
    pid = fork();

    if(!strcmp(newInput[0], "cd")){
      chdir(newInput[1]);
      pid = wait(&status);
    }
    else if(! strcmp(newInput[0], "exit")){
        exit(0);
    }
    else if (pid > 0){
        pid = wait(&status);
    }
    else if (pid == 0){
        printf("NORMAL EXEC");
        execvp(newInput[0], newInput);
    }
  }
}

char ** processInput(char *line){
    int current = 0;
    int size = 0;
    char** input = malloc(0);
    while(line){
      input = realloc(input, sizeof(char*)*current + sizeof(char*));
      input[current] = strsep(&line, " ");
      current++;
    }
    input[current] = 0;
    return input;
}
