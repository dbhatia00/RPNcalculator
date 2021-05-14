//
// Created by devbh on 4/2/2021.
//

#include "node.h"

node* createNode(double value, int type, char operator, int precedence){
    node *newNode = NULL;
    newNode = (struct node*)malloc(sizeof(node));
    if (newNode){
        if (type == OPERATOR){
            newNode->contents.operator = operator;
            newNode->precedence = precedence;
        }
        if(type == NUMBER){
            newNode->contents.value = value;
        }

        newNode->type = type;
        newNode->next = NULL;
    } else{
        exit(-1);
    }
    return newNode;
}