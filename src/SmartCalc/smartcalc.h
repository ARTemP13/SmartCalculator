#ifndef SRC_SMARTCALC_H
#define SRC_SMARTCALC_H
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define S21_NAN 1.0 / 0.0

typedef enum P {
  NUMBER = 0,
  X = 1,
  PLUS = 2,
  MINUS = 3,
  MULTIPLY = 4,
  DIVIDE = 5,
  DEGREE = 6,
  MOD = 7,
  COSINUS = 8,
  SINUS = 9,
  TANGENS = 10,
  ACOSINUS = 11,
  ASINUS = 12,
  ATANGENS = 13,
  SQRT = 14,
  LN = 15,
  LOG = 16,
  BRACKET_OPEN = 17,
  BRACKET_CLOSE = 18
} Type_t;

typedef struct Stack {
  double value;
  int priority;
  Type_t type;
  struct Stack *next;
} Stack;

Stack *push_back(double value, int priority, int type, Stack *stack);
Stack *pop_back(Stack *stack);
Stack pop_back_arg(Stack stack);
Stack *Parsing(char *str);
Stack *reverse_stack(Stack *stack);
Stack *RPN(Stack *input);
double calculating_graph(Stack input, double x);
int check_braces(char *str);
double sign(double a, double b, Stack input);
double trigonometria(double res, Stack input);

#endif
