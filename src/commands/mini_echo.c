#include "../mini_lib.h"
#include <stdio.h>

int main(int argc, char **argv) {
  if(argc != 2) {
    mini_perror("[ERROR] nombre d'arguments incorrect: ");
    mini_exit();
  }

  char *s = argv[1];
  mini_printf(s);

  mini_exit();
}