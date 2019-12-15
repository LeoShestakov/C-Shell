#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>


char *** processInput(char *line);

int main() {
  while(1){
    char curdir [100];
    getcwd(curdir, 100);

    printf("SCOOP [%s] $ ", curdir);
    char input[100];
    fgets(input, 100, stdin);
    input[strlen(input) - 1] = NULL;
    char *** newInput = processInput(input);

    int x = 0;
    while(newInput[x] != 0){
      pid_t pid;
      time_t t;
      int status;
      pid = fork();
      if(!strcmp(newInput[x][0], "cd")){
        chdir(newInput[x][1]);
        pid = wait(&status);
      }
      else if(! strcmp(newInput[x][0], "exit")){
          exit(0);
      }
      else if (pid > 0){
          pid = wait(&status);
      }
      else if (pid == 0){
          printf("NORMAL EXEC\n");
          execvp(newInput[x][0], newInput[x]);
      }
      x++;
    }
  }
 //printf("test");
  //processInput("hello buddy this is ; a test ; of our function");
}

char *** processInput(char *line){
    int current = 0;
    int size = 0;
    char*** input = malloc(0);
    int x = 0;
    while(line){
      input[x] = realloc(input[x], sizeof(char*)*current + sizeof(char*) + 10);
      input[x][current] = strsep(&line, " ");
      printf("%s\n", input[x][current]);
      if (!strcmp(input[x][current],";")){
        input[x][current] = NULL;
        x++;
        current = 0;
      } 
	  else {
        current++;
      }
    }
    input[x][current] = 0;
    input[x + 1] = 0;
    return input;
}
