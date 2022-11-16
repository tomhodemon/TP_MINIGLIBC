#include "mini_lib.h"
#include <stdio.h>

#include <stdlib.h>
#include <errno.h>
#include <limits.h>

ssize_t getdelim(char **lineptr, size_t *n, int delim, MYFILE *stream) {
    char *cur_pos, *new_lineptr;
    size_t new_lineptr_len;
    int c;

    if (lineptr == NULL || n == NULL || stream == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (*lineptr == NULL) {
        *n = 128; /* init len */
        if ((*lineptr = (char *)malloc(*n)) == NULL) {
            errno = ENOMEM;
            return -1;
        }
    }

    cur_pos = *lineptr;
    for (;;) {
        c = mini_fgetc(stream);

        if ((c == EOF && cur_pos == *lineptr))
            return -1;

        if (c == EOF)
            break;

        if ((*lineptr + *n - cur_pos) < 2) {
            if (SSIZE_MAX / 2 < *n) {
#ifdef EOVERFLOW
                errno = EOVERFLOW;
#else
                errno = ERANGE; /* no EOVERFLOW defined */
#endif
                return -1;
            }
            new_lineptr_len = *n * 2;

            if ((new_lineptr = (char *)realloc(*lineptr, new_lineptr_len)) == NULL) {
                errno = ENOMEM;
                return -1;
            }
            cur_pos = new_lineptr + (cur_pos - *lineptr);
            *lineptr = new_lineptr;
            *n = new_lineptr_len;
        }

        *cur_pos++ = (char)c;

        if (c == delim)
            break;
    }

    *cur_pos = '\0';
    return (ssize_t)(cur_pos - *lineptr);
}

ssize_t getline(char **lineptr, size_t *n, MYFILE *stream) {
    return getdelim(lineptr, n, '\n', stream);
}

int main(int argc, char **argv) {
  if(argc != 3) {
    mini_perror("[ERROR] nombre d'arguments incorrect: ");
    mini_exit();
  }

  char *filename = argv[2];
  MYFILE *f = mini_fopen(filename, 'r');
  if(f == NULL) {
    mini_perror("[ERROR] probleme lors de l'ouverture du fichier: ");
    mini_exit();
  }

  char b[2048];
  getline(b, 2048, f);

  return 0;
}