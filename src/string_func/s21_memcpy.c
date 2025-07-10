#include "../s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  void *result = dest;

  if (dest == S21_NULL || src == S21_NULL) {
    result = S21_NULL;
  } else {
    char *ch_dest = (char *)dest;
    const char *ch_src = (char *)src;
    for (s21_size_t i = 0; i < n; i++) {
      ch_dest[i] = ch_src[i];
    }
  }

  return result;
}