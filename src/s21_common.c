#include "s21_string.h"

void reverse_str(char* left) {
  char* right = left;
  for (; *(right + 1); right++);
  while (left < right) {
    char tmp = *left;
    *left = *right;
    *right = tmp;
    left++;
    right--;
  }
}

// записывает переданное целое неотрицательное число num в строку str начиная с
// индекса ind
void int_to_str(char* str, int ind, unsigned long long num) {
  const s21_size_t max_size = 22;  // заменить на размер максимального целого
  char buffer[max_size];  // массив для записи числа в обратном порядке
  s21_size_t int_len = 0;  // вычисляемая длина целой части
  if (num == 0) {
    buffer[0] = '0';
    int_len = 1;
  } else {
    while (num > 0) {
      buffer[int_len] = (num % 10) + '0';
      num /= 10;
      int_len++;
    }
  }
  buffer[int_len] = 0;
  for (s21_size_t i = 0; i < int_len; i++)
    str[i + ind] = buffer[int_len - 1 - i];
}

void flag_spec_conflicts(Specifiers* specs) {
  switch (specs->spec_char) {
    case 'c':
    case 's':
#if defined(__linux__)
      specs->zero = false;  // for linux.
#endif
      specs->plus = false;
      specs->space = false;
      if (specs->spec_char == 'c') specs->dot = false;
      specs->hash = false;
      if (specs->spec_char == 'c') specs->accuracy = 0;
      break;

    case 'd':
      if (specs->dot)  // for linux
        specs->zero = 0;
      break;

    case 'u':
      specs->plus = 0;
      specs->space = 0;
      break;
  }
}

// применяет форматирование по флагам и ширине к переданной строке
// str_after_spec
char* wrapper(Specifiers* data, char* str_after_spec, bool is_negative) {
  const s21_size_t act_len = s21_strlen(str_after_spec);
  const s21_size_t len_with_sign =
      act_len + (is_negative || data->space || data->plus);

  bool to_add_for_width =
      (data->width >
       len_with_sign);  // нужно добить пробелами или нулями до ширины
  const s21_size_t new_len = (to_add_for_width) ? data->width : len_with_sign;
  char* str_with_format = (char*)calloc(new_len + 2, sizeof(char));
  s21_size_t signs_to_add =
      (to_add_for_width) ? (data->width - len_with_sign) : 0;

  if (data->minus)  // форматирование по левому краю
  {
    add_sign(data, str_with_format, 0, is_negative);
    s21_strncat(str_with_format, str_after_spec, act_len);
    fill_to_width(str_with_format, len_with_sign, ' ', signs_to_add);
  } else  // число остаётся справа
  {
    if (data->zero)  // дополняем нулями слева при необходимости
    {
      // printf("data-zero execution\n");
      add_sign(data, str_with_format, 0, is_negative);
      fill_to_width(str_with_format, (is_negative || data->space || data->plus),
                    '0', signs_to_add);
    } else  // дополняем пробелами слева при необходимости
    {
      fill_to_width(str_with_format, 0, ' ', signs_to_add);
      add_sign(data, str_with_format, signs_to_add, is_negative);
    }
    s21_strncat(str_with_format, str_after_spec, act_len);
  }
  free(str_after_spec);
  return str_with_format;
}

// добавляет числу знак -/+/пробел (+/пробел - в зависимости от флага)
void add_sign(Specifiers* data, char* str, const int ind, bool is_negative) {
  if (is_negative)
    str[ind] = '-';
  else if (data->plus)
    str[ind] = '+';
  else if (data->space)
    str[ind] = ' ';
}

// добавляет нужное количество символов filler с указанного индекса ind
void fill_to_width(char* str, int ind, const char filler,
                   const s21_size_t signs_to_add) {
  for (s21_size_t i = ind; i < ind + signs_to_add; i++) str[i] = filler;
}

s21_size_t wrapper_handler(char* str, Specifiers* data, char* str_after_spec,
                           bool is_negative) {
  const s21_size_t maxlen = s21_strlen(str_after_spec);
  char work_str[maxlen + 1];
  work_str[maxlen] = 0;
  s21_strncpy(work_str, str_after_spec, maxlen);

  flag_spec_conflicts(data);

  if (data->spec_char == 's' && data->dot && maxlen > data->accuracy) {
    work_str[data->accuracy] = '\0';
  }

  s21_size_t len = s21_strlen(work_str);

  char* str_heap = (char*)calloc(len + 1, sizeof(char));
  if (str_heap) {
    s21_strncat(str_heap, work_str, len);

    // str_heap будет освобожден внутри wrapper
    str_heap = wrapper(data, str_heap, is_negative);
    len = s21_strlen(str_heap);

    // заменить заглушку -1 на 0
    for (s21_size_t i = 0; i < len; i++)
      if (str_heap[i] == -1) {
        str_heap[i] = 0;
        break;
      }

    s21_strncat(str, str_heap, len);
    free(str_heap);
  }

  return len;
}
