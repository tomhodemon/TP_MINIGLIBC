#include "../mini_lib.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
  if(argc != 2)
    return EXIT_FAILURE;

  MYFILE *f;
  
  f = mini_fopen(argv[1], 'i');
  if(f == NULL) {
    // mini_perror("error");
    return EXIT_FAILURE;
  }
  mini_fclose(f);
  return EXIT_SUCCESS;
}