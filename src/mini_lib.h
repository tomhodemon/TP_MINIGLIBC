#ifndef MINI_LIB_FILE
#define MINI_LIB_FILE

typedef struct malloc_element{
  void* buffer;
  int size;
  int status;
  struct malloc_element *next_malloc;
} malloc_element;


typedef struct{
  int fd;
  void *buffer_read;
  void *buffer_write; 
  int ind_read;
  int ind_write;
} MYFILE;

typedef struct MYFILES_ELEMENT{
  MYFILE *file;
  struct MYFILES_ELEMENT *next_file;
} MYFILES_ELEMENT;

// gestion de la memoire
extern malloc_element* malloc_list;

extern void* mini_calloc(int, int);
extern void mini_free(void*);
extern void mini_exit(void);
extern void mini_perror(char*);

// gestion des chaines de caracteres
extern char *buffer;
extern int BUF_SIZE;
extern int ind;

extern void mini_printf(char*);
extern int mini_strcpy(char*, const char*);
extern char* mini_strncpy(char*, const char*, int);
extern int mini_strlen(const char*);
extern int mini_strcmp(const char*, const char*);
extern int mini_scanf(char*, int);
extern void mini_perror(char*);
extern void mini_itoa(int, char*);
extern int mini_atoi(const char *s);
extern int mini_getline(char*, int, MYFILE*);


// gestion des Entrees/Sorties
extern int IOBUFFER_SIZE;

extern MYFILE *mini_fopen(char*, char);
extern int mini_fread(void*,int, int, MYFILE*); // faire erreurs
extern int mini_fwrite(void*,int, int, MYFILE*); // faire erreurs (si file descriptor est correct pour ecriture)
extern int mini_fflush(MYFILE*);
extern int mini_fgetc(MYFILE *);
extern int mini_getchar(void);
extern int mini_fputc(MYFILE*, char);
extern int mini_fclose(MYFILE*);
void _register_new_file(MYFILE *);

// linked_list
extern MYFILES_ELEMENT *myfiles_list;

extern void _registrer_new_file(MYFILE*);
extern void delete_element_myfiles_list(MYFILE*);

// debug
extern int get_number_free_space_malloc_list(void);
extern int get_size_malloc_list(void);
extern void print_malloc_list(void);
extern void print_myfiles_list(void);
extern int get_size_myfiles_list(void);

extern void test_mini_memory(void);
extern void test_mini_string(void);
extern void test_mini_io(void);
extern void test_mini_touch(void);

#endif