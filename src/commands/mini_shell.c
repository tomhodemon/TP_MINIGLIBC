#include <unistd.h>
#include<sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../mini_lib.h"

int main(int argc, char **argv) {
  
  while(1) {
    printf("\nme@term #\n");
    char b[2048];

    char *commandArgs = NULL;
    char *commandName = NULL;
    int c =  mini_scanf(b, 2048);
    b[c-1] = '\0';
   
    int i =0;
    while(b[i] != '\0' && b[i] != ' ') {
      i++;
    }
    printf("count: %d | len b: %lu | %lu\n", c, strlen(b), i);

    commandName = (char*) mini_calloc(i, sizeof(char));
    commandArgs = (char*) mini_calloc(strlen(b)-i, sizeof(char));

    mini_strncpy(commandName, b, i);
    mini_strcpy(commandArgs, b+(i+1));

    printf("commandName: %s | %d\n", commandName, mini_strlen(commandName));
    printf("commandArgs: %s | %d\n", commandArgs, mini_strlen(commandArgs));
    

    if(fork() == 0) {
      char *args[] = {commandName, commandArgs, NULL};
      execvp(commandName, args);
      exit(0);
    } else {
      wait(NULL);
    }
  }
  return 0;
}