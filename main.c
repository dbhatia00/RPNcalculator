#include <stdio.h>
#include "stack.h"
#include "rpn.h"

int main() {
    FILE* readFilePointer;
    FILE* writeFilePointer;

    int bufferLength = 255;
    char buffer[bufferLength];

    readFilePointer = fopen("/home/cs210/cs210/ps4/ps5-infile.txt", "r");
    writeFilePointer = fopen("/home/cs210/cs210/ps4/ps5-outfile.txt", "w");

    if (readFilePointer && writeFilePointer) {
        while (fgets(buffer, bufferLength, readFilePointer)) {
            double eval = evaluate(buffer, 0, writeFilePointer);
            fprintf(writeFilePointer,"%f\n\n\n", eval);
            clearStack();
        }
        fclose(readFilePointer);
        fclose(writeFilePointer);
    } else{
        printf("Unable to open target file(s)");
    }
    return 0;
}
