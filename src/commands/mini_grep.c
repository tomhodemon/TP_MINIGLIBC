#include "mini_lib.h"
#include <stdio.h>

int main(int argc, char **argv) {
  
  if(argc != 3) 
    return 1;

  char *filename = argv[2];
  MYFILE *f = mini_fopen(filename, 'r');
  if(f == NULL) {
    printf("probleme ouverture de fichier");
    return 1;
  }

  int BUF_SIZE = 1024;
  char *buffer = (char*) mini_calloc(1,BUF_SIZE);
  int count;
  int st_line = 0;

  while((count = mini_fread(buffer, sizeof(char), BUF_SIZE, f)) != 0) {
   
  }


  return 0;
}