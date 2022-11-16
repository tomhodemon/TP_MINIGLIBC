#include "../mini_lib.h"
#include <stdio.h>

int mini_getline(char *line, int size, MYFILE *f) {
    char c; int i = 0;
    while((c = (char)mini_fgetc(f))!=-1 && c!='\n' && i<size) *(line+i) = c, i++;
    *(line+i) = '\0';
    return i;
}

int main(int argc, char **argv) {
  if(argc != 3) {
    mini_perror("[ERROR] nombre d'arguments incorrect: ");
    mini_exit();
  }

char word[100];
    mini_strcpy(word, argv[1]);
  char *filename = argv[2];
  MYFILE *f = mini_fopen(filename, 'r');
  if(f == NULL) {
    mini_perror("[ERROR] probleme lors de l'ouverture du fichier: ");
    mini_exit();
  }

  char line[2048]; int res = -1;
  while((res = mini_getline(line, 2048, f)) != 0) {
  }
    mini_fclose(f);
    return 0;
}