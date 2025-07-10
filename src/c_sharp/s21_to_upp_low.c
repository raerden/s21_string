#include "../s21_string.h"

void* CaseChange(const char* str, bool to_upper) {
  char* str_changed = S21_NULL;
  if (str) {
    bool to_lower = !to_upper;
    s21_size_t len = s21_strlen(str);
    str_changed = (char*)calloc(len + 1, sizeof(char));

    int difference_a_to_A = 'a' - 'A';
    if (to_upper) difference_a_to_A *= -1;

    for (s21_size_t i = 0; i < len; i++) {
      char cur_char = str[i];
      if ((to_upper && cur_char >= 'a' && cur_char <= 'z') ||
          (to_lower && cur_char >= 'A' && cur_char <= 'Z'))
        str_changed[i] = cur_char + difference_a_to_A;
      else
        str_changed[i] = cur_char;
    }
    str_changed[len] = '\0';
  }

  return (void*)str_changed;
}

void* s21_to_upper(const char* str) { return CaseChange(str, true); }

void* s21_to_lower(const char* str) { return CaseChange(str, false); }