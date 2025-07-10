#include "../s21_string.h"

char* s21_strrchr(const char* str, int c) {
  char* res = S21_NULL;
  while (*str) {
    if (*str == (char)c) {
      res = (char*)str;
    }
    str++;
  }
  return res;
}