#include <stdlib.h>
#include <stdio.h>

#include "../mini_lib.h"

int mini_atoi(const char *s) {
  int a = 0;
  for (int i = 0  ; i<mini_strlen(s); i++) {
      a = (int)(s[i] - 48) + a * 10;
  }
  return a;
}

int line_count(char *filename) {
  MYFILE *f = mini_fopen(filename, 'r');
  if(f == NULL) {
    printf("probleme ouverture de fichier");
    return 1;
  }

  int line_count = 0;
  char *b = (char*) mini_calloc(1, BUF_SIZE);
  int res = -1;

  while(res!=0) {
    res = mini_fread(b, sizeof(char), BUF_SIZE, f);
    for(int i=0; i<res; i++)
      if(b[i] == '\n') line_count++;
  }
  mini_free(b);
  mini_fclose(f);
  return line_count;
}

int main(int argc, char **argv) {
  if(argc != 4)
    return 1;

  char *opt = argv[1];
  if(mini_strcmp(opt, "-n") != 0) {
    printf("opt non valide");
    return 1;
  }

  int n = mini_atoi(argv[2]);

  char *filename = argv[3];

  int number_line = line_count(filename);

  MYFILE *f = mini_fopen(filename, 'r');
  if(f == NULL) {
    printf("probleme ouverture de fichier");
    return 1;
  }

  int hook_line = number_line - n + 1;
  if(hook_line < 0) hook_line = 0;  

  char *b = (char*) mini_calloc(1, BUF_SIZE);
  int res = -1;
  int i;

  while(res!=0) {
  res = mini_fread(b, sizeof(char), BUF_SIZE, f);
    for(i=0; i<res; i++) {
      if(b[i] == '\n') hook_line--;
      if(hook_line == 0) break;
    }
    if(hook_line == 0) break;
  }

  mini_printf(b+i);
  while((res = mini_fread(b, sizeof(char), BUF_SIZE, f)) != 0) {
    mini_printf(b);
  }

  mini_fclose(f);  
  mini_free(b);  
  mini_exit();
  return 0;
}