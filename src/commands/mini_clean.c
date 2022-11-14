#include <stdio.h>
#include <stdlib.h>

#include "../mini_lib.h"

int main(int argc, char **argv) {
  if(argc != 2) 
    return EXIT_FAILURE;

  MYFILE *f;
  char *filename;

  filename = argv[1];
  f = mini_fopen(filename, 'w');
  mini_fclose(f);
  mini_exit();
  return EXIT_SUCCESS;
}