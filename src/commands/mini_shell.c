
#include  <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include "../mini_lib.h"

void parse_args(char *line, char **argv) {
  while (*line != '\0') {
    while(*line == ' ' || *line == '\t' || *line == '\n')
      *line++ = '\0';
    *argv++ = line;
    while(*line != '\0' && *line != ' ' && *line != '\t' && *line != '\n') 
      line++;
  }
  *argv = '\0';
}

void  execute(char **args) {
  pid_t pid;
  int status;
  if ((pid = fork()) < 0) {
      mini_perror("*** ERROR: forking child process failed: ");
      mini_exit();
  }
  else if(pid == 0) {
      if(execvp(*args, args) < 0) {
        mini_perror("*** ERROR: exec failed: ");
        mini_exit();
      }
  }
  else {
    while(wait(&status) != pid) ;
    mini_printf("\n");
  }
}
     
int main(int argc, char **argv) {
  char  prompt[1024];
  char  *args[64];
     
  while (1) {
    printf("me@term # ");
    gets(prompt);
    parse_args(prompt, args);
    if (mini_strcmp(args[0], "exit") == 0)
          mini_exit();
    execute(args);
  }
}