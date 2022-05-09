#ifndef TodoItem_H
#define TodoItem_H

#include <stdlib.h>
#include <string.h>
#include "debug.c"

typedef struct TodoItem {
    char* text;
}* TodoItem;

TodoItem new_TodoItem(char* text) {
    TodoItem item = (TodoItem) malloc(sizeof(struct TodoItem));
    item->text = strdup(text);
    return item;
}

void TodoItem_free(TodoItem this) {
    free(this->text);
    free(this);
}

char* TodoItem_getText(TodoItem this) {
    return this->text;
}

#endif