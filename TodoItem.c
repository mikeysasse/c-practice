#include <stdlib.h>
#ifndef PARSER_H  // header guard
#define PARSER_H

typedef struct TodoItem {
    char* text;
}* TodoItem;

TodoItem new_TodoItem(char* text) {
    TodoItem item = (TodoItem) malloc(sizeof(struct TodoItem));
    item->text = text; // TODO copy the string instead of assigning it here
    return item;
}

char* TodoItem_getText(TodoItem this) {
    return this->text;
}

#endif // PARSER_H