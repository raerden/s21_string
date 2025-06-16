#include "s21_string.h"

#include <check.h>
#include <stdlib.h>
#include <string.h>

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

// отправляет форматированный вывод в строку, на которую указывает str.
/*
str − Это С-строка, которую функция обрабатывает в качестве источника для
извлечения данных; format − это С-строка, содержащая один или несколько
следующих элементов: пробельный символ, непробельный символ и спецификаторы
формата. Спецификатор формата для печатающих функций следует прототипу:
%[флаги][ширина][.точность][длина]спецификатор.
*/

// допишет к строке заданное число
// позже добавить сюда опции форматирования (выравнивание, дорисовка нулей и тд)
void int_to_str(char **str, int num) {
  char symbols[] = "0123456789";
  while (num > 0) {
    **str = symbols[num % 10];
    //  *str = '1';
    num = num / 10;
    (*str)++;
  }
}

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
        // printf("Found d-spec. Is = %d\n", num);
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

  s21_sprintf(str, format, 10);

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