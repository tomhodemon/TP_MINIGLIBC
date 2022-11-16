#include "../mini_lib.h"
#include <locale.h>
#include <stdio.h>

int main(int argc, char **argv) {
  if(argc != 2) {
    mini_perror("[ERROR] nombre d'arguments incorrect: ");
    mini_exit();
  }

  char *filename = argv[1];
  MYFILE *f = mini_fopen(filename,  'r');
  if(f == NULL) {
    mini_perror("[ERROR] probleme lors de l'ouverture du fichier: ");
    mini_exit();
  }
 
  char c; int word_count = 0; int in_word = 0;
  while((c = (char)mini_fgetc(f)) != -1 && (c == ' ' || c == '\n')) ;

  while(c != -1) {
    if(c != ' ' && c != '\n') in_word = 1;
    else if(in_word) in_word = 0, word_count++;
    c = (char)mini_fgetc(f);
  }
  if(in_word) word_count++;

  mini_fclose(f);
  char word_count_string[2048];
  mini_itoa(word_count, word_count_string);
  mini_printf("\twc: ");
  mini_printf(word_count_string);
  mini_printf("\t");
  mini_printf(filename);
  mini_exit();
}