#include <stdlib.h>
#include <stdio.h>

#include "../mini_lib.h"

int main(int argc, char **argv) {
  if(argc != 2)
    return EXIT_FAILURE;

  MYFILE *f; 
  char *filename;
  int word_count, line_count, res, i, fla;
  char *buffer;


  buffer = (char*) mini_calloc(1, IOBUFFER_SIZE);
  filename = argv[1];
  word_count = line_count = 0;
  res = -1;
  f = mini_fopen(filename,  'r');

  fla=0;

  while(res!=0) {
    res = mini_fread(buffer, sizeof(char), IOBUFFER_SIZE-1, f); 
    for(i=0; i<res; i++){
      if (((buffer[i] == ' ') && !(buffer[i+1] == ' ')))
        word_count++;
      else if(!(buffer[i] == ' ') && !(buffer[i] == '\n') && (i+1) == res)
        word_count++;
      else if(buffer[i] == '\n' && !(buffer[i+1] == '\n') && !(buffer[i+1] == ' '))
        word_count++;
      // else if (buffer[i] == '\n' && !(buffer[i-1] == ' ') && !(buffer[i-1] == '\n') && !(buffer[i+1] == ' ')) {
      //   word_count++;
      // }
    }
  }

  mini_fclose(f);
  printf("wc: %d\t%s\n", word_count, argv[1]);

  mini_exit();
  return EXIT_SUCCESS;
}