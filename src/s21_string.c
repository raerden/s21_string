#include "s21_string.h"

#include <check.h>
#include <stdlib.h>
#include <string.h>

// START_TEST(strlen1) {
//   char *str = "Hello world";
//   ck_assert_int_eq(strlen(str), s21_strlen(str));
// }

int s21_sprintf(char *str, const char *format, ...) {
  // char allspec[] = "cdieEfgGosuxXpn%";
  char *src = str;  // запомнить указатель на начало строки

  va_list arguments;
  va_start(arguments, format);

  while (*format) {
    if (*format == '%') {
    } else {
      *str = *format;
      str++;
    }

    format++;
  }

  *str = '\0';
  return str - src;
}

void print_numbers(int count, ...) {
  va_list args;
  va_start(args, count);  // Инициализация va_list

  for (int i = 0; i < count; i++) {
    int num = va_arg(args, int);  // Получение следующего аргумента типа int
    printf("%d ", num);
  }

  printf("\n%d ", va_arg(args, int));  // вышли за предел переданных аргументов.
                                       // Выведет мусор из памяти

  va_end(args);  // Очистка va_list
  printf("\n");
}

// остановился на 18:30

int main() {
  const char *haystack = NULL;
  const char *needle = "test";
  // Стандарт strstr для пустой needle часто возвращает haystack.
  // Наша реализация возвращает NULL.
  const char *expected = NULL;  // Ожидаем NULL

  printf("%s\n", strstr(haystack, needle));
  // printf("%s\n", s21_strstr(haystack, needle));

  // printf("%ld\n", s21_strlen(str));
  // printf("%ld\n", s21_strlen(fnd));
  // printf("strstr: %s\n", strstr(str,fnd));
  // printf("s21_strstr: %s\n", s21_strstr(str,fnd));
  // printf("after: %s\n", str);

  // char allspec[] = "cdieEfgGosuxXpn%";
  // printf("%ld", s21_strlen(allspec));

  // print_numbers(3, 10, 20, 30, 56); // Вызов функции с тремя аргументами
  // print_numbers(2, 100, 200);   // Вызов функции с двумя аргументами

  // int d = -10;

  // printf("%4d\n", d);
  // printf("%010d\n", d);
  // printf("%+010d\n", d);
  // printf("%+10d\n", d);
  // printf("%-10d\n", d);
  // printf("%- 10d\n", d);
  // printf("%g\n", 12345.1234567);//0.1234 Округление до 0.00004 отсекает,
  // выше плюсует предыдущий разряд 0.12345 > 0.1235 printf("%G\n",
  // 12345.1234567); printf("%.0f\n", 1.12345);

  printf("\nEnd\n");
  return 0;
}
