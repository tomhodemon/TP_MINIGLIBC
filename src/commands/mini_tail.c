#include "mini_lib.h"


int mini_atoi(const char *s) {
  int a = 0;
  for (int i = 0  ; i<mini_strlen(s); i++) {
      a = (int)(s[i] - 48) + a * 10;
  }
  return a;
}

int main(int argc, char **argv) {
  if(argc != 4)
    return 1;

  char *opt = argv[1];
  if(mini_strcmp(opt, "-n") != 0) {
    printf("opt non valide");
    return 1;
  }

  char *filename = argv[3];
  MYFILE *f = mini_fopen(filename, 'r');
  if(f == NULL) {
    printf("probleme ouverture de fichier");
    return 1;
  }

  int n = mini_atoi(argv[2]);
 
  int current_number_line = 0;
  int BUF_SIZE = 1024;
  char *buffer = (char*) mini_calloc(1,BUF_SIZE);
  int count;

  while((count = mini_fread(buffer, sizeof(char), BUF_SIZE, f)) != 0) {
    for(int i=0; i<strlen(buffer); i++) {
      if(buffer[i] == '\n') current_number_line++;
      if(current_number_line == n) {
        char *partial = (char*) mini_calloc(1,BUF_SIZE);
        strncpy(partial, buffer, i);
        mini_printf(partial); 
        mini_free(partial);
        mini_exit();
      }
      
    }
   mini_printf(buffer); 
  }
  
  mini_free(buffer);
  mini_fclose(f);
  return 0;
}