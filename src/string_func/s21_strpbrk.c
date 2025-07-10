#include "../s21_string.h"

// Находит первый символ в строке str1, который соответствует любому символу,
// указанному в str2
char* s21_strpbrk(const char* str1, const char* str2) {
  char* found_char = S21_NULL;

  s21_size_t chars_to_1st_match = s21_strcspn(str1, str2);
  if (chars_to_1st_match != s21_strlen(str1))
    found_char = (char*)(&str1[chars_to_1st_match]);
  // используем приведение типа, т.к. str1 указывает на константу, а вернуть
  // нужно просто указатель

  return found_char;
}