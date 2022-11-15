#include <fcntl.h>
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "mini_lib.h"

int IOBUFFER_SIZE = 2048;

MYFILES_ELEMENT *myfiles_list = NULL;

void _register_new_file(MYFILE *file) {
  MYFILES_ELEMENT *new_file = (MYFILES_ELEMENT*) mini_calloc(1, sizeof(MYFILES_ELEMENT));
  new_file->file = file;
  if(myfiles_list == NULL) {
    new_file->next_file = NULL;
  } else {
    new_file->next_file = myfiles_list;
  }
  myfiles_list = new_file;
  
  return;
}

MYFILE *mini_fopen(char* file, char mode) {
  MYFILE *new_file = (MYFILE*) mini_calloc(1, sizeof(MYFILE));
  new_file->buffer_read = NULL;
  new_file->buffer_write = NULL;
  new_file->ind_read = -1;
  new_file->ind_write = -1;
  switch (mode) {
  case 'r':
    new_file->fd = open(file, O_RDONLY);
    break;
  case 'w':
    new_file->fd = open(file, O_WRONLY | O_CREAT | O_TRUNC | O_NONBLOCK | O_NOCTTY);
    break;
  case 'b':
    new_file->fd = open(file, O_RDWR | O_CREAT | O_NONBLOCK | O_NOCTTY);
    break;
  case 'a':
    new_file->fd = open(file, O_WRONLY | O_CREAT | O_APPEND);
    break;
  default: 
    mini_perror("[ERROR] indefined flag: ");
    return NULL;
  }
  _register_new_file(new_file);
  return new_file->fd == -1 ? NULL : new_file;
}

int mini_fread(void* buffer,int size_element, int number_element, MYFILE* file) {
  int count;
  int bytes_read = 0;
  if(file->ind_read == -1) {
    file->buffer_read = mini_calloc(1, IOBUFFER_SIZE); 
    file->ind_read = 0; 
    count = read(file->fd, file->buffer_read, IOBUFFER_SIZE); 
    if(!count)
      return 0;
   }
  
  while(number_element-- && *((char*)file->buffer_read + file->ind_read) != '\0') {
    *((char*)buffer++) = *((char*)file->buffer_read + file->ind_read);
    file->ind_read++;bytes_read++;
    if(file->ind_read == IOBUFFER_SIZE) {
      read(file->fd, file->buffer_read, IOBUFFER_SIZE); 
      file->ind_read = 0;
    }
  }
  *((char*)buffer++) = '\0';

  return bytes_read;
}

int mini_fwrite(void* buffer,int size_element, int number_element, MYFILE* file) {
  int bytes_wrote = 0;
  if(file->ind_write== -1) {
    file->buffer_write = mini_calloc(1, IOBUFFER_SIZE); 
    file->ind_write = 0;
  }

  while(number_element--) {
    *((char*)file->buffer_write + file->ind_write) = *(char*)buffer++;
    file->ind_write++;
    if(file->ind_write == IOBUFFER_SIZE) {
      write(file->fd, file->buffer_write, file->ind_write);
      bytes_wrote += file->ind_write;
      file->ind_write = 0; 
    }
  }
  return bytes_wrote += file->ind_write;
}

int mini_fflush(MYFILE* file) {
  if(file == NULL) 
    return -1;
  return write(file->fd, file->buffer_write, file->ind_write);
}

int mini_fgetc(MYFILE *file) {
  char c; 
  if(file == NULL) 
    return -1;
  if (mini_fread(&c, 1, sizeof(char), file) == 0)
		return -1;
	return c;
}

int mini_getchar(void) {
  char c; 
  if (read(STDIN_FILENO, &c, sizeof(char)) == -1)
		return -1;
	return c;
}

int mini_fputc(MYFILE* file, char c) {
  if(file == NULL) 
    return -1;
  return mini_fwrite(&c, 1, sizeof(char), file);
}

int mini_fclose(MYFILE *file) {
  if(file == NULL) {
    mini_exit();
  }
  mini_fflush(file);
  delete_element_myfiles_list(file);
  if(close(file->fd) == -1) {
    return -1;
  }
  return 0;
}

void test_mini_io() {
  mini_printf("############## TEST_MINI_IO ##############\n\n");

  MYFILE *f1 = mini_fopen("./file.txt", 'w');
  MYFILE *f2 = mini_fopen("./file2.txt", 'r');

  mini_fputc(f1, 'r');
  mini_fclose(f1);
  mini_fclose(f2);
  mini_exit();
  // printf("head: %p\tnumber_file: %d\n", myfiles_list->head, myfiles_list->number_file);

  
  // int number_element = 2;
  // void *buffer = mini_calloc(number_element + 1, sizeof(char));

  // mini_fread(buffer, sizeof(char), number_element, f);
  // mini_fread(buffer, sizeof(char), number_element, f);
  // assert(mini_fread(buffer, sizeof(char), number_element, f) == 2);
  // mini_printf((char*)buffer);

  
  // mini_free(f->buffer_read);
  // mini_free(f->buffer_write);

  // mini_free(f);

  // FILE *fp; 
  // fp = fopen("./file.txt", "a");
  // char *b_ = "hello";
  // fwrite(b_, sizeof(char), 2, fp);
  // printf("\n");
  // fflush(fp);
  // fclose(fp);

 
  mini_printf("\n");
}