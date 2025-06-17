#ifndef S21_STRING_PLUS
#define S21_STRING_PLUS
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* !!!  НЕ ЗАБЫТЬ УБРАТЬ  !!! */

typedef unsigned long int s21_size_t;
#define S21_NULL (void *)0

s21_size_t s21_strlen(const char *str);

char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);

void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *restrict dest,                     // авва
                 const void *restrict src, s21_size_t n); // авав
void *s21_memmove(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strcat(char *dest, const char *src);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
int s21_strcmp(const char *str1, const char *str2);
char *s21_strcpy(char *dest, const char *src);
char *s21_strchr(const char *str, int c);
// Выполняет поиск первого вхождения символа c (беззнаковый тип)
// в первых n байтах строки, на которую указывает аргумент str.

s21_size_t s21_strspn(const char *s, const char *accept);
char *s21_strpbrk(const char *s, const char *accept);

int s21_sprintf(char *str, const char *format, ...);
int s21_sscanf(const char *str, const char *format, ...);

void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);

// Макросы для определения операционной системы
#ifdef __apple__
// Сообщения для macOS
#elif defined(__linux__)
// Сообщения для Linux
#else
#error "Unsupported operating system"
#endif

// Дополнительно
#define S21_BUFFER_MAX 512

typedef struct
{
  int minus;         // Выровнять по левому краю в пределах заданной ширины. Умолч. по
                     // правому краю
  int plus;          // Указывать знак +/- для чисел. Умолч. знак выводится только для
                     // отрицательных чисел
  int space;         // Резервирует пробел перед выводом
  int grid;          // Для спецификаторов o,x,X,e,E,f,g,G
  int zero;          // Заполнить пробелы символом 0 если указан спецификатор ширины
  int width;         // Ширина поля для вывода числа
  int accurancy;     // точность (количество знаков) после запятой.
  int length;        // тип переменной double (%lf, %Lf, %ld)
  int notation;      // Система счисления. 10 - десятичная 16 - шестнадцатеричная
  int space_to_sign; // Резервирует один символ для знака в виде пробела.
                     // заданы minus || plus. **Избыточно?
  int dot;           // Наличие точки в формате вывода (точность числа, количество знаков
                     // после зпт). **Перекликается с accurancy %.0f ?
  int upper_case;    // Спецификаторы в верхнем регистре. G,E,F,X
  int g;             // Если указан спецификатор g
  int e;             // вывод числа в экспоненицальной системе
} Specifiers;

#endif