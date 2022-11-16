#include "../mini_lib.h"
#include <locale.h>

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
 
  int word_count = 0, res = -1, i;
  char *buffer = (char*) mini_calloc(1, IOBUFFER_SIZE);

  while(res!=0) {
    res = mini_fread(buffer, sizeof(char), IOBUFFER_SIZE, f); 
    for(i=0; i<res; i++){
      if (((buffer[i] == ' ') && !(buffer[i+1] == ' ')))
        word_count++;
      else if(!(buffer[i] == ' ') && !(buffer[i] == '\n') && (i+1) == res)
        word_count++;
      else if(buffer[i] == '\n' && !(buffer[i+1] == '\n') && !(buffer[i+1] == ' '))
        word_count++;
    }
  }

  mini_fclose(f);
  mini_free(buffer);

  char word_count_string[2048];
  mini_itoa(word_count, word_count_string);
  mini_printf("\twc: ");
  mini_printf(word_count_string);
  mini_printf("\t");
  mini_printf(filename);

  mini_exit();
}