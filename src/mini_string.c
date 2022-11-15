#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include "mini_lib.h"

char *buffer = NULL;
int BUF_SIZE = 1024;
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
  if(mini_strlen(s1) != mini_strlen(s2)) return 1;
  while(*s1 != *s2) return 1;
  return 0;
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
  mini_free(buffer);
}

int mini_scanf(char *buffer, int size_buffer) {
  return read(STDIN_FILENO, buffer, size_buffer); 
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