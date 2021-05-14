//
// Created by devbh on 4/2/2021.
//

#include "rpn.h"

bool parseTok(char* token){
    if (token[0] == '0' ||token[0] == '1' ||token[0] == '2' ||token[0] == '3' ||token[0] == '4' ||token[0] == '5' ||token[0] == '6' ||token[0] == '7' ||token[0] == '8' ||token[0] == '9'){
        return true;
    }
    return false;
}

double add(double first,double second){
    return first+second;
}
double divide(double num ,double den ){
    return num/den;
}
double multiply(double first,double second){
    return first*second;
}
double sub(double first ,double second){
    return first-second;
}

double rPower(double base, double pow){
    if(pow < 1){
        return 1;
    }
    return base*rPower(base, pow-1);
}

char * convert(char * expression, int ** status){
    int bufferLength = 255;
    char* buffer = malloc(bufferLength);
    memset(buffer, 0, bufferLength);
    char * token = strtok(expression, " \r\n");
    int index = 0;
    int len;
    int statFlag = 0;
    while (token != NULL && statFlag == 0){
        if(parseTok(token)) {
            //NUMBER
            len = strlen(token);
            for (int i = 0; i < strlen(token); i++) {
                buffer[index] = token[i];
                index++;
            }
            buffer[index] = ' ';
            index++;
        } else if(token[0] == '('){
            //Left parenthesis
            push(createNode(0, OPERATOR, token[0], -1));
        } else if (token[0] == ')'){
            //Right parenthesis
            while (stackSize() !=0 && peek()->contents.operator != '('){
                buffer[index] = pop()->contents.operator;
                index++;
                buffer[index] = ' ';
                index++;
            }

            if(stackSize()== 0){ //reached the bottom sans left parenthesis
                statFlag = 1;
                *status = statFlag;
            } else{
                pop();
            }

        } else{
            //Operator
            //First figure out what it is
            int prec = -1;
            if(token[0] == 42 || token[0] == 47){
                prec = mult_div;
            } else if (token[0] == 43 || token[0] == 45){
                prec = add_sub;
            } else if(token[0] == 94){
                prec = exponent;
            }
            node * tempOperator = createNode(0, OPERATOR, token[0], prec);

            if(stackSize() !=0) {
                while ((stackSize() != 0) && (peek()->contents.operator != '(')  &&
                       (peek()->precedence >= tempOperator->precedence)) {
                    buffer[index] = pop()->contents.operator;
                    index++;
                    buffer[index] = ' ';
                    index++;
                }
            }
            push(tempOperator);
        }

        token = strtok(NULL, " \r\n");
    }
    while (stackSize()!= 0 && peek()->contents.operator!= ')' && peek()->contents.operator!= '(') {
        buffer[index] = pop()->contents.operator;
        index++;
        buffer[index] = ' ';
        index++;
    }

    return buffer;
}

double evaluate (char* expression, int* status, FILE * writefile){
    //Print infix
    fprintf(writefile, "Infix Expression: %s", expression);

    //infix to postfix conversion
    expression = convert(expression, &status);

    //Print prefix
    fprintf(writefile, "Postfix Expression: %s\n", expression);

    //original rpn from ps4
    char * token = strtok(expression, " \r\n");

    node * inputIterator = (struct node*)malloc(sizeof(node));
    inputIterator = NULL;
    if(token == NULL){
        status = NULLPTR;
    }
    while (token != NULL){
        if(status != SUCCESS){
            break;
        }
        //Parse Token
        if(parseTok(token)){
            inputIterator =createNode(atof(token), NUMBER, 0, 0);
            push(inputIterator);
        } else{
            inputIterator =createNode(atof(token), OPERATOR, 0, 0);
        }


        //If we got an operation, perform it and push the result to the stack.
        if(inputIterator -> type == OPERATOR){
            if (stackSize() < 2){
                status = MISMATCH;
                break;
            }
            char singleToken = token[0];
            node * valOne = pop();
            node * valTwo = pop();
            if (valOne == NULL || valTwo == NULL){
                status = NULLPTR;
                break;
            }
            switch (singleToken) {
                case 42:
                    //mult
                    push(createNode(multiply(valOne->contents.value, valTwo->contents.value), NUMBER, 0, 0));
                    break;
                case 94:
                    //exp
                    push(createNode(rPower((valTwo->contents.value), valOne->contents.value), NUMBER, 0, 0));
                    break;
                case 43:
                    //add
                    push(createNode(add(valOne->contents.value, (valTwo->contents.value)), NUMBER, 0, 0));
                    break;
                case 45:
                    //sub
                    push(createNode(sub((valTwo->contents.value),valOne->contents.value), NUMBER, 0, 0));
                    break;
                case 47:
                    //div
                    push(createNode(divide((valTwo->contents.value), valOne->contents.value), NUMBER, 0, 0));
                    break;
                default:
                    status = BADOPERATOR;
                    break;
            }
            free(valOne);
            free(valTwo);
        }
        token = strtok(NULL, " \r\n");
    }

    if(stackSize()>=2){
        status = MISMATCH;
    }
    fprintf(writefile,"%s", getErrorMessage(status));
    node * returnVal = pop();
    free(expression);
    free(inputIterator);

    if (returnVal == NULL){
        return 0;
    } else {
        return returnVal->contents.value;
    }
}

