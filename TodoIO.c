#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TodoItemList.c"
#include "TodoItem.c"

typedef enum {
    ADD, CLEAR, PRINT, EXIT
} TodoCommand;

char* readLine() {
    size_t len = 64;
    char* line = malloc(len);
    ssize_t lineSize = 0;
    lineSize = getline(&line, &len, stdin);

    if (line[lineSize - 1] == '\n')
        line[lineSize - 1] = '\0';

    // Wasn't sure if the string was being null terminated
    if (line[lineSize - 1] != '\0') {
        printf("String is not null terminated, exiting.");
        free(line);
        exit(1);
    }

    return line;
}

TodoCommand getCommand(char* line) {
    if (strcmp(line, "clear") == 0) {
        return CLEAR;
    } else if (strcmp(line, "print") == 0) {
        return PRINT;
    } else if (strcmp(line, "exit") == 0) {
        return EXIT;
    }

    return ADD;
}

void export(TodoItemList list) {
    FILE *file = fopen("./list.txt", "w");

    if (file == NULL) {
        printf("No file\n");
        exit(1);
    }

    for (int i = 0; i < list->count; i++) {
        fprintf(file, "%s\n", list->items[i]->text);
    }

    fclose(file);
}

TodoItemList import() {
    TodoItemList list = new_TodoItemList();

    FILE *fp = fopen("./list.txt", "r");

    for (;;) {
        int n = 64;
        char* buf = malloc(n);
        char* returnValue = fgets(buf, n, fp);

        if (returnValue == NULL) {
            debug("Reached end of the file.\n");
            free(buf);
            break;
        }

        int length = strlen(buf);
        if (buf[length - 1] == '\n') {
            buf[length - 1] = '\0';
            TodoItemList_add(list, new_TodoItem(buf));
            debug("Read from file: %s\n", buf);
        } else {
            printf("Read non newline terminated string from file, length=%lu: %s\n", strlen(buf), buf);
            free(buf);
            exit(1);
        }

        free(buf);
    }


    int status = fclose(fp);
    if (status != 0) {
        printf("Error when closing file %d\n", status);
        exit(1);
    }

    return list;
}