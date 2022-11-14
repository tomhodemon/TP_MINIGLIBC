#include <unistd.h>
#include <stdio.h>
#include "mini_lib.h"

malloc_element *malloc_list;

void print_malloc_list(void) {
  printf("[MALLOC_LIST] head: %p - size: %d (free space: %d)\n", malloc_list, get_size_malloc_list(), get_number_free_space_malloc_list()); 
  malloc_element *current = malloc_list;
  while(current != NULL) {
    printf("\taddr: %p | buff_addr: %p | size: %d | status: %d | next_addr: %p\n", current, current->buffer, current->size, current->status, current->next_malloc);
    current = current->next_malloc;
  }
}

int get_size_malloc_list(void) {
  malloc_element *current = malloc_list;
  int count = 0;
  while(current != NULL) {
    current = current->next_malloc;
    count++;
  }
  return count;
}

int get_number_free_space_malloc_list(void) {
  int count = 0;
  malloc_element *current_malloc_element = malloc_list;
  while(current_malloc_element != NULL) {
    if(current_malloc_element->status == 0) count++;
    current_malloc_element = current_malloc_element->next_malloc;
  }
  return count;
}

int get_size_myfiles_list(MYFILES_ELEMENT *ll) {
  MYFILES_ELEMENT *current = ll;
  int count = 0;
  while(current != NULL) {
    current = current->next_file;
    count++;
  }
  return count;
}

void print_myfiles_list(MYFILES_ELEMENT *ll) {
  printf("[MYFILES_LIST] head: %p - size: %d\n", ll, get_size_myfiles_list(ll)); 
  MYFILES_ELEMENT *current = ll;
  while(current != NULL) {
    printf("\taddr: %p | next_addr: %p\n", current, current->next_file);
    current = current->next_file;
  }
  printf("\n");
}

void test_mini_memory() {
  printf("############## TEST_MINI_MEMORY ##############\n\n");

  void *e1 = mini_calloc(4, sizeof(char));
  mini_calloc(4, sizeof(char));
  mini_calloc(4, sizeof(char));

  print_malloc_list();

  mini_free(e1);
  print_malloc_list();

  mini_calloc(3, sizeof(char)); // doit etre le premier element de la liste chainee
  print_malloc_list();

  mini_calloc(5, sizeof(char));
  print_malloc_list();

  mini_exit();
}

void test_mini_string() {
  printf("############## TEST_MINI_STRING ##############\n\n");

  // mini_printf("aaa");
  // mini_printf("bbb\n");
  // mini_printf("\nccc");

  mini_perror("error: \n");
  //MYFILE *f = mini_fopen("./none", 'r');
  mini_exit();
  // debug
  exit(0);
}