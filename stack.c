//
// Created by devbh on 4/2/2021.
//

#include "stack.h"
node * HEAD = NULL;

void push(node * input){
    if (HEAD == NULL){
        HEAD = input;
    } else{
        node * formerHead = HEAD;
        HEAD = input;
        HEAD ->next = formerHead;
    }
}

node* pop(){
    node * tempNode = HEAD;

    if (HEAD == NULL){
        HEAD = NULL;
    } else{
        HEAD = HEAD->next;
    }
    return tempNode;
}

node* peek(){
    return HEAD;
}

void clearStack(){
    node * delNode = pop();
    while (delNode != NULL){
        free(delNode);
        delNode = pop();
    }
}

void printStack(){
    struct node * traversalNode = HEAD;
    while (traversalNode != NULL){
        printf("%f\n", traversalNode->contents.value);
        traversalNode = traversalNode ->next;
    }
}

int stackSize(){
    struct node * traversalNode = HEAD;
    int count = 0;
    while (traversalNode != NULL){
        count++;
        traversalNode = traversalNode ->next;
    }
    return count;
}