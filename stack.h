//
// Created by devbh on 4/2/2021.
//

#ifndef PS4_STACK_H
#define PS4_STACK_H
#include "node.h"
#include <stdio.h>

void push(node*);
node* pop();
node* peek();
void clearStack();
void printStack();
int stackSize();
#endif //PS4_STACK_H
