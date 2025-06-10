#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

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
  {
    char *str = "some text here";
    char *fnd = "text";
    printf("Haystack: '%s' Needle: '%s' strstr: '%s'\n", str, fnd,
           strstr(str, fnd));
    printf("Haystack: '%s' Needle: '%s' s21str: '%s'\n\n", str, fnd,
           s21_strstr(str, fnd));
  }

  {
    char *str = "some text here";
    char *fnd = "";
    printf("Haystack: '%s' Needle: '%s' strstr: '%s'\n", str, fnd,
           strstr(str, fnd));
    printf("Haystack: '%s' Needle: '%s' s21str: '%s'\n\n", str, fnd,
           s21_strstr(str, fnd));
  }

  {
    char *str = "";
    char *fnd = "text";
    printf("Haystack: '%s' Needle: '%s' strstr: '%s'\n", str, fnd,
           strstr(str, fnd));
    printf("Haystack: '%s' Needle: '%s' s21str: '%s'\n\n", str, fnd,
           s21_strstr(str, fnd));
  }

  {
    char *str = "";
    char *fnd = "";
    printf("Haystack: '%s' Needle: '%s' strstr: '%s'\n", str, fnd,
           strstr(str, fnd));
    printf("Haystack: '%s' Needle: '%s' s21str: '%s'\n\n", str, fnd,
           s21_strstr(str, fnd));
  }

  {
    char *str = "some text here";
    char *fnd = "12";

    printf("Haystack: '%s' Needle: '%s' strstr: '%s'\n", str, fnd,
           strstr(str, fnd));
    printf("Haystack: '%s' Needle: '%s' s21str: '%s'\n\n", str, fnd,
           s21_strstr(str, fnd));
  }
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
  // printf("%g\n", 12345.1234567);//0.1234 Округление до 0.00004 отсекает, выше
  // плюсует предыдущий разряд 0.12345 > 0.1235 printf("%G\n", 12345.1234567);
  // printf("%.0f\n", 1.12345);

  printf("\nEnd\n");
  return 0;
}

/*

            // проверить оригинальный strstr возвращает ли он NULL
    // Проверка на пустую подстроку (или NULL)
    if (needle == NULL || *needle == '\0') {
        return NULL; // По договоренности strstr часто возвращает haystack в
   этом случае,
                     // но NULL часто безопаснее и яснее. Стандарт допускает UB
   для NULL.
    }
    // Проверка на NULL haystack
    if (haystack == NULL) {
        return NULL; // Стандарт допускает UB для NULL haystack.
    }

    for (const char *p = haystack; *p != '\0'; p++) {
        const char *haystack_tmp = p;
        const char *needle_tmp = needle;
        while (*haystack_tmp != '\0' && *needle_tmp != '\0' && *haystack_tmp ==
   *needle_tmp) {
            ++haystack_tmp;
            ++needle_tmp;
        }
        if (*needle_tmp == '\0') {
            // Возвращаем указатель на начало совпадения в haystack.
            // Приводим const char* к char*, так как это ожидает оригинальная
   функция strstr
            // (хотя это потенциально опасно, если вызывающий код будет изменять
   строку). return (char *)p;
        }
        // Если дошли до конца haystack, прекращаем поиск
        if (*haystack_tmp == '\0') {
            break;
        }
    }
    return NULL;

*/