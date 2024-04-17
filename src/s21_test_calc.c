#include <check.h>

#include "SmartCalc/smartcalc.h"

START_TEST(test_calc1) {
  char *str = "2 + 2";

  Stack *stack1 = (Stack *)malloc(sizeof(Stack));
  stack1 = Parsing(str);

  Stack *pol = (Stack *)malloc(sizeof(Stack));
  pol = RPN(stack1);

  double result = 0;
  result = calculating_graph(*pol, 0);

  ck_assert_double_eq(result, 4);
}
END_TEST

START_TEST(test_calc2) {
  char *str = "sin(5) * tan(1) + 23";

  Stack *stack1 = (Stack *)malloc(sizeof(Stack));
  stack1 = Parsing(str);

  Stack *pol = (Stack *)malloc(sizeof(Stack));
  pol = RPN(stack1);

  double result = 0;
  result = calculating_graph(*pol, 0);

  ck_assert_double_eq_tol(result, 21.5066, 4);
}
END_TEST

START_TEST(test_calc3) {
  char *str = "cos(5) / 2^5";

  Stack *stack1 = (Stack *)malloc(sizeof(Stack));
  stack1 = Parsing(str);

  Stack *pol = (Stack *)malloc(sizeof(Stack));
  pol = RPN(stack1);

  double result = 0;
  result = calculating_graph(*pol, 0);

  ck_assert_double_eq_tol(result, 0.0089, 4);
}
END_TEST

START_TEST(test_calc4) {
  char *str = "asin(1) + acos(0) + atan(1)";

  Stack *stack1 = (Stack *)malloc(sizeof(Stack));
  stack1 = Parsing(str);

  Stack *pol = (Stack *)malloc(sizeof(Stack));
  pol = RPN(stack1);

  double result = 0;
  result = calculating_graph(*pol, 0);

  ck_assert_double_eq_tol(result, 3.9270, 4);
}
END_TEST

START_TEST(test_calc5) {
  char *str = "log(1000) - ln(56)";

  Stack *stack1 = (Stack *)malloc(sizeof(Stack));
  stack1 = Parsing(str);

  Stack *pol = (Stack *)malloc(sizeof(Stack));
  pol = RPN(stack1);

  double result = 0;
  result = calculating_graph(*pol, 0);

  ck_assert_double_eq_tol(result, -1.0253, 4);
}
END_TEST

START_TEST(test_calc6) {
  char *str = "(17)%2";

  Stack *stack1 = (Stack *)malloc(sizeof(Stack));
  stack1 = Parsing(str);

  Stack *pol = (Stack *)malloc(sizeof(Stack));
  pol = RPN(stack1);

  double result = 0;
  result = calculating_graph(*pol, 0);

  ck_assert_double_eq(result, 1);
}
END_TEST

START_TEST(test_calc7) {
  char *str = "(-17)%2";

  Stack *stack1 = (Stack *)malloc(sizeof(Stack));
  stack1 = Parsing(str);

  Stack *pol = (Stack *)malloc(sizeof(Stack));
  pol = RPN(stack1);

  double result = 0;
  result = calculating_graph(*pol, 0);

  ck_assert_double_eq(result, 1);
}
END_TEST

START_TEST(test_calc8) {
  char *str = "X + 5";

  Stack *stack1 = (Stack *)malloc(sizeof(Stack));
  stack1 = Parsing(str);

  Stack *pol = (Stack *)malloc(sizeof(Stack));
  pol = RPN(stack1);

  double result = 0;
  result = calculating_graph(*pol, 0);

  ck_assert_double_eq(result, 5);
}
END_TEST

START_TEST(test_calc9) {
  char *str = "sqrt(16)";

  Stack *stack1 = (Stack *)malloc(sizeof(Stack));
  stack1 = Parsing(str);

  Stack *pol = (Stack *)malloc(sizeof(Stack));
  pol = RPN(stack1);

  double result = 0;
  result = calculating_graph(*pol, 0);

  ck_assert_double_eq(result, 4);
}
END_TEST

START_TEST(test_calc10) {
  char *str = "sqrt(-5)";

  Stack *stack1 = (Stack *)malloc(sizeof(Stack));
  stack1 = Parsing(str);

  Stack *pol = (Stack *)malloc(sizeof(Stack));
  pol = RPN(stack1);

  double result = 0;
  result = calculating_graph(*pol, 0);

  ck_assert_msg(isnan(result), "gg");
}
END_TEST

START_TEST(test_calc11) {
  char *str = "asin(-5)";

  Stack *stack1 = (Stack *)malloc(sizeof(Stack));
  stack1 = Parsing(str);

  Stack *pol = (Stack *)malloc(sizeof(Stack));
  pol = RPN(stack1);

  double result = 0;
  result = calculating_graph(*pol, 0);

    ck_assert_msg(isnan(result), "gg");
}
END_TEST

START_TEST(test_calc12) {
  char *str = "acos(5)";

  Stack *stack1 = (Stack *)malloc(sizeof(Stack));
  stack1 = Parsing(str);

  Stack *pol = (Stack *)malloc(sizeof(Stack));
  pol = RPN(stack1);

  double result = 0;
  result = calculating_graph(*pol, 0);

    ck_assert_msg(isnan(result), "gg");
}
END_TEST

START_TEST(test_calc13) {
  char *str = "acos(5))";
  int check = check_braces(str);
  ck_assert_int_eq(check, 1);
}
END_TEST

Suite *my_tests_suite() {
  Suite *suite;
  TCase *tc_core;

  suite = suite_create("SmartCalc Tests");

  tc_core = tcase_create("TESTS");

  tcase_add_test(tc_core, test_calc1);
  tcase_add_test(tc_core, test_calc2);
  tcase_add_test(tc_core, test_calc3);
  tcase_add_test(tc_core, test_calc4);
  tcase_add_test(tc_core, test_calc5);
  tcase_add_test(tc_core, test_calc6);
  tcase_add_test(tc_core, test_calc7);
  tcase_add_test(tc_core, test_calc8);
  tcase_add_test(tc_core, test_calc9);
  tcase_add_test(tc_core, test_calc10);
  tcase_add_test(tc_core, test_calc11);
  tcase_add_test(tc_core, test_calc12);
  tcase_add_test(tc_core, test_calc13);

  suite_add_tcase(suite, tc_core);

  return suite;
}

int main() {
  int number_failed = 0;
  Suite *suite;
  SRunner *srunner;

  suite = my_tests_suite();
  srunner = srunner_create(suite);

  srunner_run_all(srunner, CK_NORMAL);
  number_failed = srunner_ntests_failed(srunner);
  srunner_free(srunner);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
