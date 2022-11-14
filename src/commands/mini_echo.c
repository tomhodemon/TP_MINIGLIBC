#include <stdlib.h>
#include <stdio.h>

#include "../mini_lib.h"

int main(int argc, char **argv) {
  if(argc != 2)
    return EXIT_FAILURE;

  char *s = argv[1];

  mini_printf(s);
  mini_exit();
  return EXIT_SUCCESS;
}