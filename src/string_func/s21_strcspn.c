#include "../s21_string.h"

// Вычисляет длину начального сегмента str1, который полностью состоит из
// символов, не входящих в str2 Иначе говоря, выполняет поиск первого вхождения
// в строку str1 любого из символов строки str2, возвращает количество символов
// до найденного первого вхождения
s21_size_t s21_strcspn(const char* str1, const char* str2) {
  s21_size_t len1 = s21_strlen(str1);
  s21_size_t len2 = s21_strlen(str2);
  bool found = false;
  s21_size_t i = 0;
  while ((i < len1) && (found == false)) {
    for (s21_size_t j = 0; (j < len2) && (found == false); j++)
      if (str1[i] == str2[j]) found = true;
    if (!found) i++;
  }
  s21_size_t res = len1;
  if (found) res = i;

  return res;
}