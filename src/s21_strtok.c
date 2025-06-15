#include "misc.h"
#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *memo = "";

  if (str == S21_NULL) str = memo;

  if (s21_strlen(str) == 0 || str == S21_NULL || memo == S21_NULL)
    return S21_NULL;

  if (s21_strlen(delim) == 0) return str;

  // Удалить разделители в начале строки
  while (is_char_in_set(*str, delim)) str++;

  char *result = str;

  for (; *str != '\0'; str++) {
    // взяли один чар из строки
    if (is_char_in_set(*str, delim)) {
      // ставим вместо этого чара конец строки
      *str = '\0';
      // сместить указатель за символ разделитель
      str++;
      break;
    }
  }
  // запоминаем указатель str в static memo
  memo = str;

  return s21_strlen(result) ? result : S21_NULL;
}