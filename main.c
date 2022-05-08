#include <stdio.h>
#include <stdlib.h>
#include "TodoItem.c"
#include "TodoIO.c"
#include "TodoItemList.c"

int main(int argc, char* argv[]) {
    printf("Enter a line to add to the todo:\n");
    TodoItemList list = new_TodoItemList();

    while (1) {
        char* line = (char*) malloc(64);
        TodoCommand command = readLine(line);
        
        if (command == ADD) {
            TodoItem item = new_TodoItem(line);
            TodoItemList_add(list, item);
            printf("Added \'%s\'. \n", TodoItem_getText(item));
            TodoItemList_print(list);
            printf("=====\n");
        }

        // TODO free line after doing the copy change
    }

    return 0;
}

