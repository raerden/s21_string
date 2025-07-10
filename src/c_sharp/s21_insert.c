#include "../s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *result = S21_NULL;

  if (src && str) {
    s21_size_t src_len = s21_strlen(src);
    s21_size_t str_len = s21_strlen(str);
    if (start_index <= src_len) {
      result = (char *)malloc(src_len + str_len + 1);
      if (result) {
        s21_memcpy(result, src, start_index);
        s21_memcpy(result + start_index, str, str_len);
        s21_memcpy(result + start_index + str_len, src + start_index,
                   src_len - start_index + 1);
      }
    }
  }
  return (void *)result;
}