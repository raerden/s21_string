#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  //   if (src == S21_NULL || s21_strlen(src) == 0) return S21_NULL;
  if (src == S21_NULL) return S21_NULL;

  const char *work = src;
  // пустой trim_chars - удалить пробелы и "\n\t\v\f\r"
  if (trim_chars == S21_NULL || s21_strlen(trim_chars) == 0) {
    trim_chars = " \n\r\t\v\f";
  }

  // printf("len=%ld\n", s21_strlen(work));
  while (is_char_in_set(*work, trim_chars)) {
    work++;
  }
  // printf("len=%ld\n", s21_strlen(work));
  // printf("src='%s'\n", work);

  size_t len = s21_strlen(work);
  while (len > 0 && is_char_in_set(work[len - 1], trim_chars)) {
    len--;
  }

  // printf("len=%ld\n", len);
  // printf("work[%s]\n", work);

  char *buffer_pointer = S21_NULL;
  char *buffer = malloc((len + 1) * sizeof(char));
  if (buffer != S21_NULL) {
    buffer_pointer = buffer;
    while (*work != '\0' && len > 0) {
      *buffer = *work;
      buffer++;
      work++;
      len--;
    }
    *buffer = '\0';

    // printf("[%s]\n", buffer_pointer);
  }
  return buffer_pointer;
}