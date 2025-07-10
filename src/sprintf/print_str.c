#include "../s21_string.h"

char *print_str(char *str, Specifiers *data, va_list *args) {
  s21_size_t len = 0;
  if (data->spec_char == 's') {
    char *new_str = va_arg(*args, char *);
    if (!new_str) {
      new_str = "(null)";
    }
    len = wrapper_handler(str, data, new_str, 0);
  } else if (data->spec_char == 'c') {
    // Перевел чар в указатель на масив чаров
    int ch = va_arg(*args, int);
    char ch_buff[2] = {0};
    // если ch = 0 меняем на заглушку -1. т.к все строковые функции не считают
    // его за символ
    ch_buff[0] = (ch == 0) ? -1 : ch;
    len = wrapper_handler(str, data, ch_buff, 0);
  }
  return str + len;
}
