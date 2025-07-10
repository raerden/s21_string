#include "../s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  Specifiers specs = {0};
  va_list args;
  va_start(args, format);
  char *p_format = (char *)format;
  char *save_str_pointer = str;
  s21_memset(str, 0, s21_strlen(str));

  while (*p_format) {
    if (*p_format != '%') {
      *str = *p_format;
      str++;
      p_format++;
    } else if (*(p_format + 1) == '%') {
      *str = '%';
      str++;
      p_format += 2;
    } else {
      specifiers_parser(&specs, &p_format, &args);

      switch (specs.spec_char) {
        case 'c':
        case 's':
          str = print_str(str, &specs, &args);
          break;

        case 'd':
        case 'u':
          str = print_int(str, &specs, &args);
          break;

        case 'e':  // Научная нотация (мантисса/экспонента)
        case 'E':  // Научная нотация (мантисса/экспонента) (UpperCase)
        case 'f':  // Десятичное число с плавающей точкой
        case 'g':  // кратчайший из представлений десятичного числа
        case 'G':  // кратчайший из представлений десятичного числа (UpperCase)
          str = print_float(str, &specs, &args);
          break;

        case 'o':  // Восьмеричное число
        case 'x':  // Шестнадцатеричное целое число
        case 'X':  // Шестнадцатеричное целое число (UpperCase)
        case 'p':  // Адрес указателя
          str = notation_handler(str, va_arg(args, long), specs);
          break;
      }
    }
  }
  *str = '\0';
  va_end(args);
  return str - save_str_pointer;
}