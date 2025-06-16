#include "s21_string.h"

#include <check.h>
#include <stdlib.h>
#include <string.h>

// Проба функции с вариативными аргументами
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

// допишет к строке заданное число
// позже добавить сюда опции форматирования (выравнивание, дорисовка нулей и тд)
void int_to_str(char **str, int num) {
  char symbols[] = "0123456789";
  // максимальное число unsigned long int = 18446744073709551615 - 20 символов.
  char buffer[22] = {0};
  char *ptr = buffer;
  while (num > 0) {
    *ptr = symbols[num % 10];
    num = num / 10;
    ptr++;
  }
  ptr = '\0';
  int len = s21_strlen(buffer);
  for (int i = len - 1; i >= 0; i--) {
    **str = buffer[i];
    (*str)++;
  }
}

// отправляет форматированный вывод в строку, на которую указывает str.
/*
str − Это С-строка, которую функция обрабатывает в качестве источника для
извлечения данных; format − это С-строка, содержащая один или несколько
следующих элементов: пробельный символ, непробельный символ и спецификаторы
формата. Спецификатор формата для печатающих функций следует прототипу:
%[флаги][ширина][.точность][длина]спецификатор.
*/
int s21_sprintf(char *str, const char *format, ...) {
  char allspec[] = "cdieEfgGosuxXpn%";
  char *save_str_pointer = str;  // запомнить указатель на начало строки

  va_list arguments;
  // указываем название аргумента, после которого пойдут вариативные аргументы
  va_start(arguments, format);

  while (*format) {
    if (*format == '%') {
      // начало определения спецификатора
      // движемся по строке пока не найдем одиз из спецификаторов
      while (*format != 'd' && *format != '\0') *format++;
      // обнаружен спецификатор целого числа.
      // Получаем его из вариативного аргумента как int

      if (*format == 'd') {
        int num = va_arg(arguments, int);
        //  отпечатать int как строку в str
        int_to_str(&str, num);
      }

    } else {
      *str = *format;
      str++;
    }

    format++;
  }

  va_end(arguments);  // Очистка va_list

  *str = '\0';
  return str - save_str_pointer;
}

int main() {
  printf("\n");

  char str[256];
  char *format = "Hello %d world";

  s21_sprintf(str, format, 102567);

  printf("%s\n", str);

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

/*

  // char haystack[] = "hello world";
  // char needle[] = "wo";
  // printf("%s\n", strstr(haystack, needle));
  // printf("%s\n", s21_strstr(haystack, needle));

  // printf("%ld\n", s21_strlen(str));
  // printf("%ld\n", s21_strlen(fnd));
  // printf("strstr: %s\n", strstr(str, fnd));
  // printf("s21_strstr: %s\n", s21_strstr(str, fnd));
  // printf("after: %s\n", str);
*/