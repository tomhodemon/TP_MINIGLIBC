#include "../mini_lib.h"
#include <locale.h>

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
  MYFILE *f = mini_fopen(filename, 'r');
  if(f == NULL) {
    mini_perror("[ERROR] probleme lors de l'ouverture du fichier: ");
    mini_exit();
  }

  int n = mini_atoi(argv[2]);
 
  int current_number_line = 0;
  char *buffer = (char*) mini_calloc(1,BUF_SIZE);
  int count;

  while((count = mini_fread(buffer, sizeof(char), BUF_SIZE, f)) != 0) {
    for(int i=0; i<mini_strlen(buffer); i++) {
      if(buffer[i] == '\n') current_number_line++;
      if(current_number_line == n) {
        char *partial = (char*) mini_calloc(1, BUF_SIZE);
        mini_strncpy(partial, buffer, i+1);
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