#include "../s21_string.h"
s21_size_t int_to_wrapper(char *str, Specifiers *data, char *str_for_num,
                          bool is_negative);

char *print_int(char *str, Specifiers *data, va_list *args) {
  long signed_val = 0;
  unsigned long unsigned_val = 0;
  bool is_unsigned = false;

  // Определяем тип числа
  if (data->spec_char == 'u') {
    is_unsigned = true;
    if (data->length == 'l') {
      unsigned_val = va_arg(*args, unsigned long);
    } else if (data->length == 'h') {
      unsigned_val = (unsigned short)va_arg(*args, int);
    } else
      unsigned_val = va_arg(*args, unsigned int);
  } else {
    if (data->length == 'l') {
      signed_val = va_arg(*args, long);
    } else if (data->length == 'h') {
      signed_val = (short)va_arg(*args, int);
    } else
      signed_val = va_arg(*args, int);
  }

  // Определяем знак числа
  bool is_negative = false;
  if (!unsigned_val && signed_val < 0) {
    is_negative = true;
    signed_val = -signed_val;
  }

  // Получаем строку из числа
  char str_for_num[22] = {0};
  int_to_str(str_for_num, 0,
             is_unsigned ? unsigned_val : (unsigned long)signed_val);

  s21_size_t len = int_to_wrapper(str, data, str_for_num, is_negative);

  return str + len;
}

//  добавит 0 перед числом если указана точность больше ширины числа.
//  отформатирует строку по флагам для вывода на печать
//  вернет количество полученных символов
s21_size_t int_to_wrapper(char *str, Specifiers *data, char *str_for_num,
                          bool is_negative) {
  // устанавливаем длину итоговой строки
  s21_size_t len = 0;

  // измеряем длину полученного в строке числа
  s21_size_t max_len = s21_strlen(str_for_num);

  // если точность больше длины числа. Значит нужно будет слева добавить нули
  // устанавливаем длину итоговой строки с учетом этих нулей. 00 + 123
  if (data->accuracy > max_len) max_len = data->accuracy;

  // выделяем в памяти буфер для формирования строки 00123
  char *buffer = (char *)calloc(max_len + 1, sizeof(char));
  if (buffer) {
    if (data->accuracy) {
      int signs_to_add = data->accuracy - s21_strlen(str_for_num);
      // добавляем 0 слева, если потребуется
      fill_to_width(buffer, 0, '0', signs_to_add);
    }

    // конкатенируем полученный буффер (с нулями или без) с самим числом
    s21_strncat(buffer, str_for_num, max_len);

    // получившийся buffer передаем в дальнейшее форматирование по флагам и
    // ширине
    len = wrapper_handler(str, data, buffer, is_negative);

    // прощай
    free(buffer);
  }

  // возвращаем длину итоговой строки после форматирования
  return len;
}