#include <fcntl.h>
#include <unistd.h>
#include "mini_lib.h"

int main(int argc, char **argv) {
  if(argc != 2) {
    mini_perror("[ERROR] nombre d'arguments incorrect: ");
    mini_exit();
  }

  int fd = open(argv[1], O_RDONLY | O_CREAT | O_NONBLOCK | O_NOCTTY);
  if(fd == -1) {
    mini_perror("[ERROR] le fichier n'a pas pu etre cree: ");
    mini_exit();
  }
  close(fd);
  mini_exit();
}