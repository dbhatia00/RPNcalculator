//
// Created by devbh on 4/2/2021.
//

#ifndef PS4_RPN_H
#define PS4_RPN_H
#include <string.h>
#include <stdbool.h>
#include <string.h>
#include "stack.h"
#include "node.h"
#include "errors.h"
double evaluate (char* expression, int* status, FILE* writefile);
char * convert(char * expression, int ** status);
#endif //PS4_RPN_H
