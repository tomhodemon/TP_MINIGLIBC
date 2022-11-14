#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mini_lib.h"

malloc_element* malloc_list = NULL;
char *buffer;

void* mini_calloc(int number_element, int size_element) {
  if(number_element < 0 || size_element < 0) {
    mini_perror("Error argument in mini_calloc");
    mini_exit();
  }
  int size = number_element*size_element;

  malloc_element *new_malloc_element = sbrk(sizeof(malloc_element));
  new_malloc_element->buffer = sbrk(size);
  if((int)new_malloc_element->buffer == -1) {
    mini_perror("Error sbrk in mini_calloc");
    mini_exit();
  }
  mini_bzero(new_malloc_element->buffer, number_element, size_element);
  new_malloc_element->size = size;
  new_malloc_element->status = 1;
  new_malloc_element->next_malloc = NULL;

  if(malloc_list == NULL) {
    malloc_list = new_malloc_element;
  } else {    
    malloc_element *current = malloc_list;
    while(!(current->next_malloc == NULL || (current->size >= size && current->status == 0))) {
      current = current->next_malloc;
    }
    if(current->next_malloc == NULL) {
      current->next_malloc = new_malloc_element;
    } else {
      current->buffer = new_malloc_element->buffer;
      current->size = size;
      current->status = 1;
    }
  }
  return new_malloc_element->buffer;
}

void mini_free(void* e) {
  if(e == NULL) return;
  malloc_element *current_malloc_element = malloc_list;
  while(current_malloc_element != NULL && (void*)current_malloc_element->buffer != e) {
    current_malloc_element = current_malloc_element->next_malloc;
  }
  current_malloc_element->status = 0;
  return; 
}

void mini_exit(void) {
  // gestion des Entrees/Sorties
  MYFILES_ELEMENT *current_file = myfiles_list;
  while(current_file) {
    mini_fflush(current_file->file);
    current_file = current_file->next_file;
  }
  // gestion des chaines de caracteres
  write(STDOUT_FILENO, buffer, ind);

  // gestion de la memoire
  _exit(0);
}

void mini_bzero(void *s, int number_element, int size_element) {
  for(int i=0; i<number_element; i++) {
    s = (void *)'\0';
    s += size_element;
  }
}
