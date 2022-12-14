#include <unistd.h>
#include <sys/wait.h>
#include <locale.h>
#include "mini_lib.h"

void parse_args(char *prompt, char **args) {
  int len_prompt = mini_strlen(prompt);
  prompt[len_prompt-1] = '\0';
  while (*prompt != '\0') {
    while(*prompt == ' ' || *prompt == '\t' || *prompt == '\n')
      *prompt++ = '\0';
    *args++ = prompt;
    while(*prompt != '\0' && *prompt != ' ' && *prompt != '\t' && *prompt != '\n') 
      prompt++;
  }
  *args = (char*)'\0';
  return;
}

void  execute(char **args) {
  pid_t pid;
  int status;
  if ((pid = fork()) < 0) {
      mini_perror("*** ERROR: forking child process failed: ");
      mini_exit();
  }
  else if(pid == 0) {
    if(!mini_strcmp("cat", *args)) {
      if(execvp("./mini_cat", args) < 0) {
        mini_perror("*** ERROR: exec failed: ");
        mini_exit();
      }
    } else if(!mini_strcmp("wc", *args)) {
      if(execvp("./wc", args) < 0) {
        mini_perror("*** ERROR: exec failed: ");
        mini_exit();
      }
    } else if(!mini_strcmp("echo", *args)) {
      if(execvp("./mini_echo", args) < 0) {
        mini_perror("*** ERROR: exec failed: ");
        mini_exit();
      }
    } else if(!mini_strcmp("clean", *args)) {
      if(execvp("./mini_clean", args) < 0) {
        mini_perror("*** ERROR: exec failed: ");
        mini_exit();
      }
    } else if(!mini_strcmp("cp", *args)) {
      if(execvp("./mini_cp", args) < 0) {
        mini_perror("*** ERROR: exec failed: ");
        mini_exit();
      }
    } else if(!mini_strcmp("tail", *args)) {
      if(execvp("./mini_tail", args) < 0) {
        mini_perror("*** ERROR: exec failed: ");
        mini_exit();
      }
    } else if(!mini_strcmp("head", *args)) {
      if(execvp("./mini_head", args) < 0) {
        mini_perror("*** ERROR: exec failed: ");
        mini_exit();
      }
    } else if(!mini_strcmp("touch", *args)) {
      if(execvp("./mini_touch", args) < 0) {
        mini_perror("*** ERROR: exec failed: ");
        mini_exit();
      }
    } else {
      if(execvp(*args, args) < 0) {
        mini_perror("[ERROR] commande inconnue: ");
        mini_exit();
      }
    }  
  }
  else {
    while(wait(&status) != pid) ;
    mini_printf("\n");
  }
}
     
int main(int argc, char **argv) {
  char prompt[BUF_SIZE];
  char *args[64];
  int c; 
  while (1) {
    mini_printf("me@term $ \n");
    c = mini_scanf(prompt, BUF_SIZE);
    *((char*)prompt+c) = '\0';
    if(mini_strlen(prompt) >= 1){
      parse_args(prompt, args);
      if (mini_strcmp(args[0], "exit") == 0)
        mini_exit();
      execute(args);
    }
  }
}
