#include "../mini_lib.h"

int main(int argc, char **argv) {
  if(argc != 2) {
    mini_perror("[ERROR] nombre d'arguments incorrect: ");
    mini_exit();
  }

  MYFILE *f = NULL;
  char *fname;
  int count = 0;
  char* buffer; 

  fname = argv[1]; 
  f = mini_fopen(fname, 'r'); 
  if(f == NULL) {
    mini_perror("[ERROR] probleme lors de l'ouverture du fichier: ");
    mini_exit();
  }
  buffer = (char*) mini_calloc(1, BUF_SIZE);

  while((count = mini_fread(buffer, sizeof(char), BUF_SIZE, f)) != 0) {
    mini_printf(buffer);
  }

  mini_fclose(f);
  mini_free(buffer);
  mini_exit();
}