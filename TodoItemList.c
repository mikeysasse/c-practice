#include <stdio.h>
#include "TodoItem.c"
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
    for (int i = 0; i < this->maxCount; i++) {
        free(this->items[i]);
    }

    free(this);
}

void todo_item_list_expand(TodoItemList this) {
    int newMaxCount = 2 * this->maxCount;
    this->items = realloc(this->items, newMaxCount * sizeof(TodoItem));
    this->maxCount = newMaxCount;
}

void TodoItemList_print(TodoItemList this) {
    printf("count=%d, maxCount=%d\n", this->count, this->maxCount);
    for (int i = 0; i < this->count; i++) {
        printf("%d %s\n", i, this->items[i]->text);
    }
}