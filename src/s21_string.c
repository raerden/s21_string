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

void *test(const char *src) {
  // создаю новую область памяти равной размеру переданной строки
  char *new_str = malloc((strlen(src) + 1) * sizeof(char));
  if (!new_str) return NULL;
  // запоминаю начальный указатель
  char *save_begin_pointer = new_str;

  // посимвольно копирую через указатели переданную строку в новую
  // заменить на strcpy - будет еще короче
  /*
  char *new_str = malloc((strlen(src) + 1) * sizeof(char));
  if (new_str) strcpy(new_str, src);
  return new_str;
  */
  for (const char *p = src; *p != '\0'; p++) {
    *new_str = *p;
    new_str++;
  }
  *new_str = '\0';

  // У меня подгарает, как можно возвращать если функция void?
  //  но все же передаю результат.
  return save_begin_pointer;
}

char *s21_strtok(char *str, const char *delim) {
  static int step = 1;
  printf("  %d: ---------------------- \n", step++);
  printf("str  : |%s|\n", str);

  static char *memo = "";

  if (str == S21_NULL) {
    str = memo;
    printf("memo : |%s|\n", memo);
  }

  if (s21_strlen(str) == 0 || str == S21_NULL || memo == S21_NULL)
    return S21_NULL;

  if (strlen(delim) == 0) delim = " \n\r\t\v\f";

  // удалить разделители в начале строки
  while (is_char_in_set(*str, delim)) str++;

  // // удалить разделители в конце строки
  // int len = s21_strlen(str);
  // for (int i = len - 1; i >= 0; i--) {
  //   if (is_char_in_set(str[i], delim))
  //     str[i] = '\0';
  //   else
  //     break;
  //   // printf("(%c)", str[i]);
  // }

  int len = strlen(str);
  printf("cldel: |%s|[%d]\n", str, len);

  char *p = str;
  for (; *p != '\0' && len > 0; p++) {
    // взяли один чар из строки
    if (is_char_in_set(*p, delim)) {
      // ставим конец строки вместо этого чара
      *p = '\0';
      // мемо запоминаем на позиции +1 от этого чара
      // memo = p + 1;
      break;
    }
  }
  memo = p + 1;

  // int len = s21_strlen(str);
  //  const char *d = delim;
  //  // проверяем его на все разделители по очереди
  //  while (*d != '\0') {
  //    // если чар равен разделителю
  //    if (*p == *d) {
  //      // ставим чару конец строки
  //      *p = '\0';
  //      // мемо запоминаем на позиции +1 от этого чара
  //      memo = p + 1;
  //      // printf("save: |%s| len:%d\n", memo, len);
  //      return str;
  //    }
  //    d++;
  //  }
  //  len++;
  // }

  return str;
}

int main() {
  printf("\n");

  // char str[] = ". Hello,  world! !! This is a test";
  char str[] = ".Hello test..";
  char delim[] = " ,!.";

  char *s21_token = s21_strtok(str, delim);
  int step = 1;
  while (s21_token != NULL) {
    printf("Token: '%s'\n", s21_token);
    s21_token = s21_strtok(NULL, delim);
    step++;
    if (step == 8) break;
  }

  printf("\n");

  // char *token = strtok(str, delim);

  // while (token != NULL) {
  //   printf("Token: '%s'\n", token);
  //   token = strtok(
  //       NULL, delim);  // Последующие вызовы с NULL для продолжения
  //       разбиения
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
