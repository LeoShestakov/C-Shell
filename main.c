#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

char *** processInput(char *line);

int main() {
	while(1){
		char curdir [100];
		getcwd(curdir, 100);

		printf("*SCOOP* [%s] $ ", curdir);
		char input[100];
		fgets(input, 100, stdin);
		input[strlen(input) - 1] = NULL;
		char *** newInput = processInput(input);

		int x = 0;
		while(newInput[x] != 0){
			pid_t pid;
			time_t t;
			int status;
			
			if(!strcmp(newInput[x][0], "cd")){
				chdir(newInput[x][1]);
			}
			else if(! strcmp(newInput[x][0], "exit")){
				return 0;
			}
			
			else {
				int n;
				int redirect;
				int rIndex;
				int redirect2;
				int rIndex2;
				int stdin_fd = STDIN_FILENO;
			
				for (n = 0; newInput[x][n] != 0; n++) {
					if (!strcmp(newInput[x][n], ">")) {
						rIndex = n;
						redirect = 1;
					}
				}
				for (n = 0; newInput[x][n] != 0; n++) {
					if (!strcmp(newInput[x][n], "<")) {
						rIndex2 = n;
						redirect2 = 1;
					}
				}
				
				pid = fork();
				if (pid > 0){
					pid = wait(&status);
				}
				else if (pid == 0){
					if (redirect) {
						int fd = open(newInput[x][rIndex + 1], O_RDWR|O_CREAT|O_TRUNC, 0755);
						int desc = dup(STDOUT_FILENO);
						dup2(fd, 1);
						close(fd);
						close(desc);
						newInput[x][rIndex] = NULL;
						execvp(newInput[x][rIndex - 1], newInput[x]);
					}
					if (redirect2) {
						int fd = open(newInput[x][rIndex2 + 1], O_RDONLY);
						dup2(fd, STDIN_FILENO);
						newInput[x][rIndex2] = NULL;
						execvp(newInput[x][0], newInput[x]);
					}
					else {
						execvp(newInput[x][0], newInput[x]);
					}
				}
			}
		free(newInput[x]);
		x++;
		}
	free(newInput);
	}
}

char *** processInput(char *line){
    int current = 0;
    int size = 0;
    char*** input = malloc(0);
    int x = 0;
    while(line){
		input[x] = realloc(input[x], sizeof(char*)*current + sizeof(char*) + 10);
		input[x][current] = strsep(&line, " ");
		//printf("%s\n", input[x][current]);
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
