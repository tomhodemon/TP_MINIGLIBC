#include <locale.h>
#include "mini_lib.h"

int line_count(char *filename) {
  MYFILE *f = mini_fopen(filename, 'r');
  if(f == NULL) {
    mini_perror("[ERROR] probleme lors de l'ouverture du fichier: ");
    mini_exit();
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
  if(argc != 4) {
    mini_perror("[ERROR] nombre d'arguments incorrect: ");
    mini_exit();
  }

  char *opt = argv[1];
  if(mini_strcmp(opt, "-n") != 0) {
    mini_perror("[ERROR] option non valide: ");
    mini_exit();
  }

  char *filename = argv[3];
  int number_line = line_count(filename);
  MYFILE *f = mini_fopen(filename, 'r');
  if(f == NULL) {
    mini_perror("[ERROR] probleme lors de l'ouverture du fichier: ");
    mini_exit();
  }

  char *b = (char*) mini_calloc(1, BUF_SIZE);
  int res = -1;

  int n = mini_atoi(argv[2]);
  if(n > 0) {
    int hook_line = number_line - n + 1;
    if(hook_line > 0) {
      int i;
      while(res != 0) {
        res = mini_fread(b, sizeof(char), BUF_SIZE, f);
        for(i=0; i<res; i++) {
          if(b[i] == '\n') hook_line--;
          if(hook_line == 0) break;
        }
        if(hook_line == 0) break;
      }
      mini_printf(b+i+1);
      while((res = mini_fread(b, sizeof(char), BUF_SIZE, f)) != 0) mini_printf(b);
    } else {
      while((res = mini_fread(b, sizeof(char), BUF_SIZE, f)) != 0) mini_printf(b);
    }
  }
  
  mini_fclose(f);  
  mini_free(b);  
  mini_exit();
  return 0;
}