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

char *s21_strtok(char *str, const char *delim) {
  static int step = 1;
  printf("%d: ---------------------- \n", step++);
  printf("str: '%s'\n", str);

  static char *memo;

  if (str == NULL) {
    str = memo;
    printf("memo: |%s|\n", memo);
  }

  if (strlen(str) == 0) return NULL;

  // удалить разделители в начале строки
  int i = 0;

  // char str[] = "! This is a test.";
  // const char delim[] = " ,!.";

  // while (str[i] != *delim)

  // char *temp = str;
  // for (const char *p = delim; *p != '\0'; p++) {
  //   while (*p == *temp) {
  //     temp++;
  //   }
  // }
  // str = temp;
  printf("clean delim: |%s|\n", str);

  int len = 0;
  for (char *p = str; *p != '\0'; p++) {
    // взяли один чар из строки
    const char *d = delim;
    // проверяем его на все разделители по очереди
    while (*d != '\0') {
      // если чар равен разделителю
      if (*p == *d) {
        // ставим чару конец строки
        *p = '\0';
        // мемо запоминаем на позиции +1 от этого чара
        memo = p + 1;
        printf("save: |%s| len:%d\n", memo, len);
        return str;
      }
      d++;
    }
    len++;
  }

  return str;
}

int main() {
  printf("\n");
  char str[] = "! This is a test.";
  char delim[] = " ,!.";

  char *temp = str;
  int check = 1;
  while (check && *temp != '\0') {
    for (char *d = delim; *d != '\0'; d++) {
      while (*temp == *d) {
        temp++;
      }
    }
    check = 0;
  }
  printf("%s", temp);

  printf("\n");
  return 0;

  // char str[] = "Hello,  world!! This is a test.";
  // const char delim[] = " ,!.";

  // char *s21_token = s21_strtok(str, delim);
  // int step = 1;
  // while (s21_token != NULL) {
  //   printf("Token: '%s'\n", s21_token);
  //   s21_token = s21_strtok(NULL, delim);
  //   step++;
  //   if (step == 18) break;
  // }

  // printf("\n");

  // char str2[] = "Hello,  world!!! This is a test.";
  // char *token = strtok(str2, delim);

  // while (token != NULL) {
  //   printf("Token: '%s'\n", token);
  //   token = strtok(
  //       NULL, delim);  // Последующие вызовы с NULL для продолжения разбиения
  // }

  // printf("%s\n", strstr(haystack, needle));
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
