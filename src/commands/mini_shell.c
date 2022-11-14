#include <unistd.h>
#include<sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../mini_lib.h"


char* mini_strncpy(char* destination, const char* source, int num)
{
    // return if no memory is allocated to the destination
    if (destination == NULL) {
        return NULL;
    }
 
    // take a pointer pointing to the beginning of the destination string
    char* ptr = destination;
 
    // copy first `num` characters of C-string pointed by source
    // into the array pointed by destination
    while (*source && num--)
    {
        *destination = *source;
        destination++;
        source++;
    }
 
    // null terminate destination string
    *destination = '\0';
 
    // the destination is returned by standard `strncpy()`
    return ptr;
}

int main(int argc, char **argv) {
  
  while(1) {
    printf("\n####### NEW ######\n");
    char b[2048];
    char commandName[2048];
    char commandArgs[2048];
    scanf("%s", b);
    int i =0;
    while(b[i] != '\0' && b[i] != ' '&& b[i] != '\n') {
      i++;
    }
    strncpy(commandName, b, i);
    strcpy(commandArgs, b+(++i));
    // scanf("%s", b);
    
    // if(strcmp(commandName, "./cat") == 0) {
    //   if(fork() == 0) {
    //     printf("in fork");
    //     char *args[] = {"./cat", "file.txt", NULL};
    //     execvp("./cat", args);
    //     exit(0);
    //   }
    // }
    if(fork() == 0) {
      printf("commandName: %s | %d", commandName, strlen(commandName));
      char *args[] = {"./cat", "file.txt", NULL};
      execvp("./cat", args);
      exit(0);
    } else {
      wait(NULL);
    }
  }
  return 0;
}