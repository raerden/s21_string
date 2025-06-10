#include "s21_string.h"

// Возвращает длину строки без учета нуль символа
size_t s21_strlen(const char *str) {
  size_t len = 0;
  while (*str) {
    len++;
    str++;
  }
  return len;
}