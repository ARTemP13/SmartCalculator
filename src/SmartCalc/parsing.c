#include "smartcalc.h"



Stack *Parsing(char *str) {
  Stack *stack = (Stack *)malloc(sizeof(Stack));
  stack = push_back(0, -10, 0, stack);
  char number[256] = "";
  int i = 0;
  if (str[0] == '-' || str[0] == '+') {
    stack = push_back(0, 0, 0, stack);
    stack = push_back(0, 2, 3, stack);
    i++;
  }
  for (; i < (int)strlen(str); i++) {
    if (str[i] == '+') stack = push_back(0, 1, 2, stack);
    if (str[i] == '-') stack = push_back(0, 1, 3, stack);
    if (str[i] == '*') stack = push_back(0, 2, 4, stack);
    if (str[i] == '/') stack = push_back(0, 2, 5, stack);
    if (str[i] == '%') stack = push_back(0, 2, 7, stack);
    if (str[i] == '^') stack = push_back(0, 3, 6, stack);
    if (str[i] == '(' && (str[i + 1] == '+' || str[i + 1] == '-')) {
      stack = push_back(0, 5, 17, stack);
      stack = push_back(0, 0, 0, stack);
      stack = push_back(0, 2, 3, stack);
      i++;
      continue;
    }
    if (str[i] == '(') stack = push_back(0, 5, 17, stack);
    if (str[i] == ')') stack = push_back(0, 5, 18, stack);
    if (str[i] == 'X') stack = push_back(0, 0, 1, stack);
    if (str[i] == 'c') {
      stack = push_back(0, 4, 8, stack);
      i += 2;
      continue;
    }
    if (str[i] == 's' && str[i + 1] == 'i') {
      stack = push_back(0, 4, 9, stack);
      i += 2;
      continue;
    }
    if (str[i] == 's' && str[i + 1] == 'q') {
      stack = push_back(0, 4, 14, stack);
      i += 3;
      continue;
    }
    if (str[i] == 't') {
      stack = push_back(0, 4, 10, stack);
      i += 2;
      continue;
    }
    if (str[i] == 'a' && str[i + 1] == 'c') {
      stack = push_back(0, 4, 11, stack);
      i += 3;
      continue;
    }
    if (str[i] == 'a' && str[i + 1] == 's') {
      stack = push_back(0, 4, 12, stack);
      i += 3;
      continue;
    }
    if (str[i] == 'a' && str[i + 1] == 't') {
      stack = push_back(0, 4, 13, stack);
      i += 3;
      continue;
    }
    if (str[i] == 'l' && str[i + 1] == 'n') {
      stack = push_back(0, 4, 15, stack);
      i += 1;
      continue;
    }
    if (str[i] == 'l' && str[i + 1] == 'o') {
      stack = push_back(0, 4, 16, stack);
      i += 2;
      continue;
    }
    if (str[i] >= '0' && str[i] <= '9') {
      int j = 0;
      while (i < (int)strlen(str)) {
        number[j] = str[i];
        i++;
        j++;
        if ((str[i] >= '0' && str[i] <= '9') || (str[i] == '.')) {
        } else {
          i--;
          break;
        }
      }
      stack = push_back(atof(number), 0, 0, stack);
      memset(number, ' ', 256);
    }
  }
  return reverse_stack(stack);
}

Stack *reverse_stack(Stack *stack) {
  Stack *stack1 = (Stack *)malloc(sizeof(Stack));
  stack1 = push_back(0, -10, 0, stack1);
  while (stack->priority != -10) {
    stack1 = push_back(stack->value, stack->priority, stack->type, stack1);
    stack = pop_back(stack);
  }
  return stack1;
}

Stack *push_back(double value, int priority, int type, Stack *stack) {
  Stack *stack1 = (Stack *)malloc(sizeof(Stack));
  stack1->value = value;
  stack1->priority = priority;
  stack1->type = type;
  stack1->next = stack;
  return stack1;
}

Stack *pop_back(Stack *stack) {
  if (stack->next == NULL) {
    return stack;
  }
  Stack *stack1 = stack->next;
  free(stack);
  return stack1;
}

int check_braces(char *str) {
  int error = 0;
  int count_left = 0;
  int count_right = 0;
  for (int i = 0; i < (int)strlen(str); i++) {
    if (str[i] == '(') {
      count_left++;
    }
    if (str[i] == ')') {
      count_right++;
    }
  }
  if (count_left != count_right) {
    error = 1;
  }
  return error;
}
