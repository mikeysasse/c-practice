#include <stdio.h>
#include <stdlib.h>
#include "TodoItem.c"
#include "TodoIO.c"
#include "TodoItemList.c"
#include "debug.c"

typedef struct TodoContext {
    TodoItemList list;
    TodoCommand command;
    char* line;
}* TodoContext;

void add(TodoContext context) {
    TodoItem item = new_TodoItem(context->line);
    TodoItemList_add(context->list, item);
    printf("Added \'%s\'. \n", TodoItem_getText(item));

    #ifdef DEBUG
        TodoItemList_print(context->list);
    #endif
}

void process(TodoContext context) {
    if (context->command == ADD) {
        add(context);
    } else if (context->command == CLEAR) {
        TodoItemList_clear(context->list);
    } else if (context->command == PRINT) {
        TodoItemList_print(context->list);
    }
}

int main(int argc, char* argv[]) {
    debug("Debug Mode.\n");
    printf("Enter a line to add to the todo:\n");
    TodoItemList list = import();

    for(;;) {
        char* line = readLine();
        TodoCommand command = getCommand(line);

        if (command == EXIT) {
            free(line);
            break;
        }

        TodoContext context = (TodoContext) malloc(sizeof(struct TodoContext));
        context->list = list;
        context->command = command;
        context->line = line;
        
        printf("Process %u\n", command);
        process(context);
        free(context);
        free(line);
        export(list);
    }

    TodoItemList_free(list);
    return 0;
}