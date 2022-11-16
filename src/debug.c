#include <stdio.h>
#include "mini_lib.h"

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

int get_size_myfiles_list(void) {
  MYFILES_ELEMENT *current = myfiles_list;
  int count = 0;
  while(current != NULL) {
    current = current->next_file;
    count++;
  }
  return count;
}

void print_myfiles_list(void) {
  printf("[MYFILES_LIST] head: %p - size: %d\n", myfiles_list, get_size_myfiles_list()); 
  MYFILES_ELEMENT *current = myfiles_list;
  while(current != NULL) {
    printf("\taddr: %p | next_addr: %p\n", current, current->next_file);
    current = current->next_file;
  }
  printf("\n");
}

void test_mini_memory() {
  printf("############## TEST_MINI_MEMORY ##############\n\n");

  void *e1 = mini_calloc(4, sizeof(char));
  void *e2 = mini_calloc(4, sizeof(char));
  void *e3 = mini_calloc(4, sizeof(char));

  print_malloc_list();

  mini_free(e1);
  print_malloc_list();

  void *e4 = mini_calloc(3, sizeof(char)); // doit etre le premier element de la liste chainee
  print_malloc_list();

  void *e5 = mini_calloc(5, sizeof(char));
  print_malloc_list();

   mini_free(e2);
   mini_free(e3);
   mini_free(e4);
   mini_free(e5);
   mini_printf("\n");
}

void test_mini_string() {
  printf("############## TEST_MINI_STRING ##############\n\n");

  mini_printf("\n\t[mini_printf\n");
  mini_printf("aaa");
  mini_printf("bbb\n");
  mini_printf("\nccc");

  mini_printf("\n\t[mini_scanf]\n");
  char b[2048];
  mini_printf("prompt: \n");
  int c = mini_scanf(b, 2048 - 1);
  *((char*)b+c) = '\0';

  mini_printf(b);
  mini_printf("\n");

  mini_printf("\n\t[mini_perror]\n");
  mini_perror("[ERROR] error: ");

  mini_printf("\n\t[mini_strcmp]\n");
  char s1[] = "hello";
  char s2[] = "hello";
  char s3[] = "pashello";
  printf("on compare %s et %s: %d <-- resultat mini_strcmp\n", s1, s2, mini_strcmp(s1, s2));
  printf("on compare %s et %s: %d <-- resultat mini_strcmp\n", s1, s3, mini_strcmp(s1, s3));

  mini_printf("\n\t[mini_strcpy]\n");
  char s4[30]; 
  char s5[] = "chaine s5";
  mini_strcpy(s4, s5);
  printf("on copie %s dans s4: %s <-- s4 apres mini_strcpy\n", s5, s4);
  
  mini_printf("\n\t[mini_strlen]\n");
  char s6[] = "une chaine";
  printf("resultat de mini_strlen pour '%s': %d\n", s6, mini_strlen(s6));
}

void test_mini_io() {
  mini_printf("############## TEST_MINI_IO ##############\n\n");

  mini_printf("\t[mini_fopen]\n");
  MYFILE *f1 = mini_fopen("./file.txt", 'b');
  if(f1 == NULL) {
    mini_perror("[ERROR] probleme lors de l'ouverture du fichier: ");
    mini_exit();
  }

  mini_printf("\n\t[mini_write]\n");
  char b[] = "Hello World!\n";
  mini_fwrite(b, 1, sizeof(b)-1, f1);
  mini_printf("on mini_fwrite 'Hello World!' dans f1\n");
  mini_fclose(f1);
 
  
  f1 = mini_fopen("./file.txt", 'r');
  if(f1 == NULL) {
    mini_perror("[ERROR] probleme lors de l'ouverture du fichier: ");
    mini_exit();
  }

  mini_printf("\n\t[mini_fread]\n");
  void *br = (void*) mini_calloc(1, 30); 
  mini_fread(br, 1, 4, f1);
  *((char*)br+4) = '\n';
  mini_printf("on recupere 4 caracteres de f1: "); mini_printf(br);


  mini_printf("\n\t[mini_fclose]\n");
  mini_fclose(f1);
  
  MYFILE *f2= mini_fopen("./file2.txt", 'b');
  if(f2 == NULL) {
    mini_perror("[ERROR] probleme lors de l'ouverture du fichier: ");
    mini_exit();
  }

  mini_printf("\n\t[mini_fputc]\n");
  mini_fputc(f2, 'c');
  mini_printf("on mini_fputc le caractere 'c' dans f2\n");

  mini_printf("\n\t[mini_fgetc]\n");
  char c[2];
  c[0] = (char)mini_fgetc(f2);
  c[1] = '\0';
  mini_printf("resultat de mini_fgetc sur f2: "); mini_printf(c); mini_printf("\n");

  mini_fclose(f2);
  mini_free(br);
}