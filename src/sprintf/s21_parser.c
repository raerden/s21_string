#include "../s21_string.h"

void specifiers_clean(Specifiers* specs) {
  specs->spec_char = 0;
  specs->minus = false;
  specs->plus = false;
  specs->space = false;
  specs->hash = false;
  specs->zero = false;
  specs->width = 0;
  specs->accuracy = 0;
  specs->length = 0;
  specs->dot = false;
}

void flags_conflict(Specifiers* specs) {
  if (specs->space && specs->plus) specs->space = false;
  if (specs->zero && specs->minus) specs->zero = false;
}

bool is_digit(char ch) { return (ch >= '0' && ch <= '9') ? true : false; }

// вычитает из строки число, сконвертирует его в int "123.9034" -> 123
s21_size_t scan_int(char** format) {
  int res = 0;
  while (is_digit(**format)) {
    res = res * 10 + (**format - '0');
    (*format)++;
  }
  return res;
}

void get_flags(Specifiers* specs, char** format) {
  bool proceed = true;
  while (proceed && **format) {
    if (**format == ' ')
      specs->space = true;
    else if (**format == '-')
      specs->minus = true;
    else if (**format == '+')
      specs->plus = true;
    else if (**format == '#')
      specs->hash = true;
    else if (**format == '0')
      specs->zero = true;
    else
      proceed = false;
    if (proceed) (*format)++;
  }
}

// считываем число отвечающее за ширину поля.
void get_width(Specifiers* specs, char** format, va_list* args) {
  if (**format == '*') {
    int width = va_arg(*args, int);
    if (width < 0) {
      // отрицательная ширина, через аргументы, дает выравнивание влево.
      // и отменяет 0 во флагах
      width *= -1;
      specs->minus = true;
    }
    specs->width = width;
    (*format)++;
  } else
    specs->width = scan_int(format);
}

// считываем точку и длину, если задано поле [точность]
void get_accuracy(Specifiers* specs, char** format, va_list* args) {
  if (**format == '.') {
    specs->dot = 1;
    (*format)++;
    if (**format == '*') {
      int accuracy = va_arg(*args, int);
      if (accuracy > 0) specs->accuracy = accuracy;
      (*format)++;
    } else {
      specs->accuracy = scan_int(format);
    }
  }
}

// считываем параметр [длина] (h,l,L)
void get_length(Specifiers* specs, char** format) {
  char* spec_flag = s21_strchr("hlL", **format);
  if (spec_flag != S21_NULL) {
    (*format)++;
    specs->length = *spec_flag;
  }
}

void get_spec_ch(Specifiers* specs, char** format) {
  char allspecs[] = "cdeEfgGosuxXp";
  char* spec_char = s21_strchr(allspecs, **format);
  if (spec_char != S21_NULL) {
    (*format)++;
    specs->spec_char = *spec_char;
  }
}

// %[флаги][ширина][.точность][длина]спецификатор.
// флаги: -, +, space, #, 0
// ширина: число, *          количество символов для печати поля
// точность: .число, .*      количество знаков после запятой
// длина: h, l, L            long int
void specifiers_parser(Specifiers* specs, char** format, va_list* args) {
  (*format)++;  // сдвигаем за знак %
  specifiers_clean(specs);

  // считываем первое поле [флаги]
  get_flags(specs, format);

  // считываем число отвечающее за ширину поля.
  get_width(specs, format, args);  // 4 - 2345.77

  // считываем точку и длину, если задано поле [точность]
  get_accuracy(specs, format, args);

  // считываем параметр [длина] (h,l,L)
  // для поля длина задана один флаг char length;
  get_length(specs, format);

  // на этом этапе останется только последний символ - спецификатор
  get_spec_ch(specs, format);

  flags_conflict(specs);
}