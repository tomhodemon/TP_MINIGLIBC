#include <stdlib.h>
#include <stdio.h>

#include "../mini_lib.h"

int main(int argc, char **argv) {
  if(argc != 2)
    return EXIT_FAILURE;

  MYFILE *f = NULL;
  char *fname;
  int count = 0;
  char* buffer; 

  fname = argv[1]; 
  f = mini_fopen(fname, 'r'); // voir qui gere l'erreur
  buffer = (char*) mini_calloc(1, BUF_SIZE);

  while((count = mini_fread(buffer, sizeof(char), BUF_SIZE, f)) != 0) {
    mini_printf(buffer);
  }

  mini_fclose(f);
  mini_free(buffer);
  mini_exit();
  return EXIT_SUCCESS;
}