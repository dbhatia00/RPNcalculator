//
// Created by devbh on 4/2/2021.
//

#ifndef PS4_NODE_H
#define PS4_NODE_H
#include <stdlib.h>

typedef struct node {
    union {
        double value;
        char operator;
    } contents;
    int type;
    int precedence;
    struct node *next;
} node;
enum {OPERATOR, NUMBER} typeChar;
enum {add_sub, mult_div, exponent} precedenceSwitch;
struct node* createNode(double value, int type, char operator, int precedence);
#endif //PS4_NODE_H
