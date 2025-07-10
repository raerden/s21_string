#include <stdio.h>

#include "s21_string.h"

void clean_buf(char* str1, char* str2) {
  s21_memset(str1, 0, 100);
  s21_memset(str2, 0, 100);
}

int main() {
  int len1, len2;
  char str1[100];
  char str2[100];

  char ch = 'a';
  char str[] = "abc";
  long int li = 1234567890;
  double fl = 0.000000000765;

  printf("\nпроверка спецификатора c\n");
  clean_buf(str1, str2);

  len1 = sprintf(str1, "|%c|", ch);
  len2 = s21_sprintf(str2, "|%c|", ch);

  printf("sys[%d]: %s\n", len1, str1);
  printf("s21[%d]: %s\n", len2, str2);

  printf("\nпроверка спецификатора s\n");
  clean_buf(str1, str2);

  len1 = sprintf(str1, "|%s|", str);
  len2 = s21_sprintf(str2, "|%s|", str);

  printf("sys[%d]: %s\n", len1, str1);
  printf("s21[%d]: %s\n", len2, str2);

  printf("\nпроверка спецификатора d\n");
  clean_buf(str1, str2);

  len1 = sprintf(str1, "|%d|", (int)li);
  len2 = s21_sprintf(str2, "|%d|", (int)li);

  printf("sys[%d]: %s\n", len1, str1);
  printf("s21[%d]: %s\n", len2, str2);

  printf("\nпроверка спецификатора u\n");
  clean_buf(str1, str2);

  len1 = sprintf(str1, "|%u|", (unsigned int)li);
  len2 = s21_sprintf(str2, "|%u|", (unsigned int)li);

  printf("sys[%d]: %s\n", len1, str1);
  printf("s21[%d]: %s\n", len2, str2);

  printf("\nпроверка спецификатора f\n");
  clean_buf(str1, str2);

  len1 = sprintf(str1, "|%f|", fl);
  len2 = s21_sprintf(str2, "|%f|", fl);

  printf("sys[%d]: %s\n", len1, str1);
  printf("s21[%d]: %s\n", len2, str2);

  printf("\nпроверка спецификатора e\n");
  clean_buf(str1, str2);

  len1 = sprintf(str1, "|%e|", fl);
  len2 = s21_sprintf(str2, "|%e|", fl);

  printf("sys[%d]: %s\n", len1, str1);
  printf("s21[%d]: %s\n", len2, str2);

  printf("\nпроверка спецификатора E\n");
  clean_buf(str1, str2);

  len1 = sprintf(str1, "|%E|", fl);
  len2 = s21_sprintf(str2, "|%E|", fl);

  printf("sys[%d]: %s\n", len1, str1);
  printf("s21[%d]: %s\n", len2, str2);

  printf("\nпроверка спецификатора g\n");
  clean_buf(str1, str2);

  len1 = sprintf(str1, "|%g|", fl);
  len2 = s21_sprintf(str2, "|%g|", fl);

  printf("sys[%d]: %s\n", len1, str1);
  printf("s21[%d]: %s\n", len2, str2);

  printf("\nпроверка спецификатора G\n");
  clean_buf(str1, str2);

  len1 = sprintf(str1, "|%G|", fl);
  len2 = s21_sprintf(str2, "|%G|", fl);

  printf("sys[%d]: %s\n", len1, str1);
  printf("s21[%d]: %s\n", len2, str2);

  printf("\nпроверка спецификатора o\n");
  clean_buf(str1, str2);

  len1 = sprintf(str1, "|%o|", (unsigned int)li);
  len2 = s21_sprintf(str2, "|%o|", (unsigned int)li);

  printf("sys[%d]: %s\n", len1, str1);
  printf("s21[%d]: %s\n", len2, str2);

  printf("\nпроверка спецификатора x\n");
  clean_buf(str1, str2);

  len1 = sprintf(str1, "|%x|", (unsigned int)li);
  len2 = s21_sprintf(str2, "|%x|", (unsigned int)li);

  printf("sys[%d]: %s\n", len1, str1);
  printf("s21[%d]: %s\n", len2, str2);

  printf("\nпроверка спецификатора X\n");
  clean_buf(str1, str2);

  len1 = sprintf(str1, "|%X|", (unsigned int)li);
  len2 = s21_sprintf(str2, "|%X|", (unsigned int)li);

  printf("sys[%d]: %s\n", len1, str1);
  printf("s21[%d]: %s\n", len2, str2);

  printf("\nпроверка спецификатора p\n");
  clean_buf(str1, str2);

  len1 = sprintf(str1, "|%p|", &li);
  len2 = s21_sprintf(str2, "|%p|", &li);

  printf("sys[%d]: %s\n", len1, str1);
  printf("s21[%d]: %s\n", len2, str2);
}