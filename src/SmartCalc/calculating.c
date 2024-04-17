#include "smartcalc.h"

Stack pop_back_arg(Stack stack) {
  if (stack.next == NULL) {
    return stack;
  }
  Stack *stack1 = stack.next;
  return *stack1;
}

double calculating_graph(Stack input, double x) {
  Stack *number = (Stack *)malloc(sizeof(Stack));
  int flag1 = 0;
  while (input.priority != -10 && flag1 == 0) {
    if (input.type == 0) {
      number = push_back(input.value, input.priority, input.type, number);
    } else if (input.type == 1) {
      number = push_back(x, input.priority, input.type, number);
    } else if (input.type >= 2 && input.type <= 7) {
      double b = number->value;
      number = pop_back(number);
      double a = number->value;
      number = pop_back(number);

      number = push_back(sign(a, b, input), 0, 0, number);
    } else {
      double res = number->value;
      number = pop_back(number);

      res = trigonometria(res, input);
      number = push_back(res, 0, 0, number);
    }
    input = pop_back_arg(input);
  }
  if (flag1 == 1) {
    return S21_NAN;
  } else {
    return number->value;
  }
}

double sign(double a, double b, Stack input) {
  double res = 0;
  if (input.type == 2) res = a + b;
  if (input.type == 3) res = a - b;
  if (input.type == 4) res = a * b;
  if (input.type == 5) {
    res = a / b;
  }
  if (input.type == 6) res = pow(a, b);
  if (input.type == 7) {
    if (a >= 0) {
      int ost = (int)a % abs((int)b);
      res = ost;
    } else {
      int ost = abs((int)a) / abs((int)b);
      ost = abs((int)a) - abs((int)b) * ost;
      ost = abs((int)b) - ost;
      res = ost;
    }
  }
  return res;
}

double trigonometria(double res, Stack input) {
  if (input.type == 8) res = cos(res);
  if (input.type == 9) res = sin(res);
  if (input.type == 10) {
    res = tan(res);
  }
  if (input.type == 11) {
    res = acos(res);
  }
  if (input.type == 12) {
    res = asin(res);
  }
  if (input.type == 13) res = atan(res);
  if (input.type == 14) {
    res = sqrt(res);
  }
  if (input.type == 15) {
    res = log(res);
  }
  if (input.type == 16) {
    res = log(res) / log(10);
  }
  return res;
}
