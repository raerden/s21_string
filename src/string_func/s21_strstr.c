#include "../s21_string.h"

// Находит первое вхождение всей строки needle (не включая завершающий нулевой
// символ), которая появляется в строке haystack
char *s21_strstr(const char *haystack, const char *needle) {
  if (*needle == '\0') return (char *)haystack;

  char *result = S21_NULL;

  for (const char *p = haystack; *p != '\0'; p++) {
    const char *haystack_tmp = p;
    const char *needle_tmp = needle;
    // while до конца строки и оба чара совпадают
    while (*haystack_tmp != '\0' && *needle_tmp != '\0' &&
           *haystack_tmp == *needle_tmp) {
      haystack_tmp++;
      needle_tmp++;
    }
    // while промотал needle_tmp до конца. Значит совпадение
    if (*needle_tmp == '\0') {
      // возвращаем указатель на начало подстроки
      result = (char *)p;
      break;
    }
  }

  return result;
}