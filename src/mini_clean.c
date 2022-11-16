#include "mini_lib.h"
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv) {
  if(argc != 2) {
    mini_perror("[ERROR] nombre d'arguments incorrect: ");
    mini_exit();
  }

  int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC | O_NONBLOCK | O_NOCTTY);
  if(fd == -1) {
    mini_perror("[ERROR] probleme lors de l'ouverture du fichier: ");
    mini_exit();
  }

  close(fd);
  mini_exit();
}