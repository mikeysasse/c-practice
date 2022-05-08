#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef enum {
    ADD
} TodoCommand;

TodoCommand readLine(char* line) {
    char* readString;
    size_t len = 0;
    ssize_t lineSize = 0;
    lineSize = getline(&readString, &len, stdin);

    if (readString[lineSize - 1] == '\n')
        readString[lineSize - 1] = '\0';

    strcpy(line, readString);

    // Wasn't sure if the string was being null terminated
    if (line[lineSize - 1] != '\0') {
        printf("String is not null terminated, exiting.");
        exit(1);
    }

    return ADD;
}