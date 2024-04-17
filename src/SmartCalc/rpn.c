#include "smartcalc.h"

Stack *RPN(Stack *input) {
  Stack *ready = (Stack *)malloc(sizeof(Stack));
  ready = push_back(0, -10, 0, ready);
  Stack *support = (Stack *)malloc(sizeof(Stack));
  support = push_back(0, -10, 0, support);
  while (input->priority != -10) {
    if (input->type == NUMBER || input->type == X) {
      ready = push_back(input->value, input->priority, input->type, ready);
    } else {
      if (support->priority == -10) {
        support =
            push_back(input->value, input->priority, input->type, support);
      } else {
        int flag = 0;
        if (input->priority == 5) {
          if (input->type == BRACKET_OPEN) {
            support =
                push_back(input->value, input->priority, input->type, support);
          } else {
            while (flag == 0 && support->priority != -10) {
              if (support->type == BRACKET_OPEN) {
                support = pop_back(support);
                flag = 1;
                continue;
              }
              ready = push_back(support->value, support->priority,
                                support->type, ready);
              support = pop_back(support);
            }
          }
        } else {
          if (input->priority <= support->priority &&
              support->type != BRACKET_OPEN) {
            while (flag == 0 && support->priority != -10) {
              ready = push_back(support->value, support->priority,
                                support->type, ready);
              support = pop_back(support);
              if (input->priority != -10 && input->priority > support->priority)
                flag = 1;
            }
            support =
                push_back(input->value, input->priority, input->type, support);
          } else {
            support =
                push_back(input->value, input->priority, input->type, support);
          }
        }
      }
    }
    input = pop_back(input);
  }
  while (support->priority != -10) {
    ready = push_back(support->value, support->priority, support->type, ready);
    support = pop_back(support);
  }
  free(support);
  free(input);
  return reverse_stack(ready);
}
