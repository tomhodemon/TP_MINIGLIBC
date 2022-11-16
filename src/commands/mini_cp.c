#include "../mini_lib.h"
#include <locale.h>

int main(int argc, char **argv) {
  if(argc != 3) {
    mini_perror("[ERROR] nombre d'arguments incorrect: ");
    mini_exit();
  }

  char *src, *dest;
  MYFILE *fsrc, *fdest;
  char *buffer;
  int count = 0;

  src = argv[1];
  dest = argv[2];
  fsrc = mini_fopen(src, 'r');
  
  fdest = mini_fopen(dest, 'w');

  if(fsrc == NULL || fdest == NULL) {
    mini_perror("[ERROR] probleme lors de l'ouverture du fichier: ");
    mini_exit();
  }

  buffer = (char*) mini_calloc(1, IOBUFFER_SIZE);

  while((count = mini_fread(buffer, sizeof(char), IOBUFFER_SIZE, fsrc)) != 0) {
    mini_fwrite(buffer, sizeof(char), count, fdest);
  }

  mini_fclose(fsrc);
  mini_fclose(fdest);
  mini_free(buffer);
  mini_exit();
}