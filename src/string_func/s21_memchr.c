#include "../s21_string.h"

void* s21_memchr(const void* str, int c, s21_size_t n) {
  void* symbol = S21_NULL;

  const unsigned char* p = str;
  unsigned char ch = (unsigned char)c;
  for (s21_size_t i = 0; i < n; i++) {
    if (p[i] == ch) {
      symbol = (void*)(p + i);
      break;
    }
  }
  return symbol;
}