#include "../mini_lib.h"
#include <stdio.h>

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
		int len_word = mini_strlen(word);
		if(len_word <= mini_strlen(line)) {
			int i = 0;
			while(line[i] != '\0') {
				if(line[i] != '\n') {
					int c=0;
					while(word[c]!='\0' && line[i+c]!='\0' && word[c] == line[i+c]) c++;
					if(c == len_word) mini_printf(line), mini_printf("\n");
				}
				i++;
			}
		}
  }
	mini_fclose(f);
	mini_exit();
}