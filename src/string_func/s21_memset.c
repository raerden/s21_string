#include "../s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
  // Заполлняем передаваемым значением
  if (n != 0) {
    unsigned char *s = (unsigned char *)str;
    const unsigned char value = (unsigned char)c;

    while (n--) {
      *s++ = value;
    }
  }
  return str;
}