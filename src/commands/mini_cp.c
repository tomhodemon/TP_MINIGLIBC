#include "../mini_lib.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define IOBUFFER_SIZE 3

int main(int argc, char **argv) {
  if(argc != 3)
    return EXIT_FAILURE;

  char *src, *dest;
  MYFILE *fsrc, *fdest;
  char *buffer;
  int count = 0;

  src = argv[1];
  dest = argv[2];
  fsrc = mini_fopen(src, 'r'); // check qui gere l'erreur (si le ficher n'existe pas)
  fdest = mini_fopen(dest, 'w');
  buffer = (char*) mini_calloc(1, IOBUFFER_SIZE);

  while((count = mini_fread(buffer, sizeof(char), IOBUFFER_SIZE, fsrc)) != 0) {
    mini_fwrite(buffer, sizeof(char), count, fdest);
  }

  mini_fclose(fsrc);
  mini_fclose(fdest);
  mini_free(buffer);
  return EXIT_SUCCESS;
}