#include <errno.h>
#include <locale.h>
#include <unistd.h>
#include "mini_lib.h"

int BUF_SIZE = 1024;
char *buffer = NULL;
int ind = -1;

int mini_strlen(const char* s) {
  int i = 0;
  for(; *s!='\0'; s++, i++);
  return i;
}

int mini_strcpy(char *dest, const char *src) {
  int count = 0;
  for(;*src != '\0'; dest++, src++, count++)
    *dest = *src;
  *dest = '\0';
  return count;
}

char* mini_strncpy(char* dest, const char* src, int n) {
  if (dest == NULL) return NULL;

  char* ptr = dest;

  while (*src && n--) {
    *dest = *src;
    dest++;
    src++;
  }
  *dest = '\0';
  return ptr;
}

int mini_strcmp(const char* s1, const char* s2) {
  for( ; *s1 == *s2 ; s2++ , s1++)
    if(*s1 == '\0') return 0;
  return *s1 - *s2;
}

void mini_printf(char* s) {
  if(buffer == NULL) {
    buffer = (char*) mini_calloc(BUF_SIZE, sizeof(char));
    ind = 0;
  }
  while(*s) {
    mini_strcpy(buffer + ind, s);
    ind++;
    if (ind == BUF_SIZE || *s == '\n') {
      write(STDOUT_FILENO, buffer, ind);
      
      ind = 0;
    }
    s++;
  }
}

int mini_scanf(char *b, int size_buffer) {
  return read(STDIN_FILENO, b, size_buffer-1); 
}

void mini_perror(char *message) {
  char s[2];
  mini_itoa(errno, s);
  int message_len = mini_strlen(message);
  char *error = (char*) mini_calloc(1, message_len+1);
  mini_strcpy(error, message);
  *(error + message_len - 1) = *s;
  *(error + message_len) = '\0';
  mini_printf(error);
  mini_printf("\n");
  mini_free(error);
  return;
 }

void rev(char *s) {
  int i, j;
  char c;
  for (i = 0, j = mini_strlen(s)-1; i<j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

void mini_itoa(int n, char *s) {
  int i, sign;
  if ((sign = n) < 0)
    n = -n;
  i = 0;
  do{
    s[i++] = n % 10 + '0';
  } while ((n /= 10) > 0);

  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';
  rev(s);
}

int mini_atoi(const char *s) {
  int a = 0;
  for (int i = 0  ; i<mini_strlen(s); i++) {
    a = (int)(s[i] - 48) + a * 10;
  }
  return a;
}

int mini_getline(char *line, int size, MYFILE *f) {
  char c; int i = 0;
  while((c = (char)mini_fgetc(f))!=-1 && c!='\n' && i<size) *(line+i) = c, i++;
  if(i==0 && c=='\n') i++, *(line) = c;
  *(line+i) = '\0';
  return i;
}