//
// Created by devbh on 4/2/2021.
//

char *getErrorMessage(int status) {
    char* errorMessages[] = {
            "Calculation successful\n",
            "Parenthesis/Operator Mismatch! Returning top of stack :\n",
            "Invalid Operator! Returning top of stack :\n",
            "Null Ptr Reference! Returning top of stack :\n"
    };
    return errorMessages[status];
}
