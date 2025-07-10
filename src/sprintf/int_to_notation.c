#include "../s21_string.h"

static inline int get_notation(char spec_char) {
  int notation = 0;
  switch (spec_char) {
    case 'o':
      notation = 8;
      break;
    case 'x':
    case 'X':
    case 'p':
      notation = 16;
      break;
  }
  return notation;
}

static inline char *hash_handler(char *str, char spec_char) {
  switch (spec_char) {
    case 'x':
    case 'p':
      *str = 'x';
      str++;
      break;
    case 'X':
      *str = 'X';
      str++;
      break;
  }

  *str = '0';
  str++;
  return str;
}

static inline char *int_to_notation(char *str, long num, Specifiers *data) {
  if (num == 0) {
    *str = '0';
    *(str + 1) = '\0';
    return str;
  }

  const char upper_map[] = "0123456789ABCDEF";
  const char lower_map[] = "0123456789abcdef";
  const char *map = lower_map;
  if ('X' == data->spec_char) map = upper_map;

  char *start_str = str;

  int notation = get_notation(data->spec_char);
  for (s21_size_t mod = 0; num;) {
    mod = num % notation;
    *str = map[mod];
    str++;
    num /= notation;
  }

  if (data->hash || 'p' == data->spec_char)
    str = hash_handler(str, data->spec_char);

  *str = '\0';
  reverse_str(start_str);
  return start_str;
}

char *notation_handler(char *str, long num, Specifiers data) {
  str = int_to_notation(str, num, &data);

  s21_size_t str_len = s21_strlen(str);
  char *str_formatted = (char *)calloc(str_len + 1, sizeof(char));
  s21_strncpy(str_formatted, str, str_len);

  str_formatted = wrapper(&data, str_formatted, false);

  str_len = s21_strlen(str_formatted);
  s21_strncpy(str, str_formatted, str_len);
  str += str_len;
  free(str_formatted);

  return str;
}
