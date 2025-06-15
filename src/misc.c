#include "s21_string.h"

int is_char_in_set(const char ch, const char *set) {
  int res = 0;
  for (const char *p = set; *p != '\0'; p++)
    if (ch == *p) {
      res = 1;
      break;
    }
  return res;
}