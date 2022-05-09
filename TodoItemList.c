#ifndef TodoItemList_H
#define TodoItemList_H

#include <stdio.h>
#include "TodoItem.c"
#include "debug.c"
#define DEFAULT_LENGTH 1

typedef struct TodoItemList {
    int count;
    int maxCount;
    TodoItem *items;
}* TodoItemList;

void todo_item_list_expand(TodoItemList);

TodoItemList new_TodoItemList() {
    TodoItemList list = (TodoItemList) malloc(sizeof(struct TodoItemList));
    list->items = (TodoItem*) calloc(DEFAULT_LENGTH, sizeof(TodoItem));
    list->maxCount = DEFAULT_LENGTH;
    list->count = 0;
    return list;
}

void TodoItemList_add(TodoItemList this, TodoItem item) {
    if (this->count + 1 > this->maxCount) {
        todo_item_list_expand(this);
    }

    this->items[this->count] = item;
    this->count++;
}

void TodoItemList_free(TodoItemList this) {
    for (int i = 0; i < this->count; i++) {
        TodoItem_free(this->items[i]);
    }

    free(this->items);
    free(this);
}

void TodoItemList_clear(TodoItemList this) {
    for (int i = 0; i < this->count; i++) {
        TodoItem_free(this->items[i]);
    }

    this->count = 0;
    this->maxCount = DEFAULT_LENGTH;
    this->items = realloc(this->items, DEFAULT_LENGTH * sizeof(TodoItem));
}

void TodoItemList_print(TodoItemList this) {
    printf("count=%d, maxCount=%d\n", this->count, this->maxCount);
    for (int i = 0; i < this->count; i++) {
        printf("%d %s\n", i, this->items[i]->text);
    }
    printf("=====\n");
}

void todo_item_list_expand(TodoItemList this) {
    int newMaxCount = 2 * this->maxCount;
    this->items = realloc(this->items, newMaxCount * sizeof(TodoItem));
    this->maxCount = newMaxCount;
}

#endif