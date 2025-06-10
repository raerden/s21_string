#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

START_TEST(s21_strlen_test) {
  char *test1 = "Hello world";
  char *test2 = "123456789\0";
  char *test3 = "    ";
  char *test4 = "";
  ck_assert_int_eq(strlen(test1), s21_strlen(test1));
  ck_assert_int_eq(strlen(test2), s21_strlen(test2));
  ck_assert_int_eq(strlen(test3), s21_strlen(test3));
  ck_assert_int_eq(strlen(test4), s21_strlen(test4));
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, s21_strlen_test);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
