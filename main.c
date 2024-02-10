#include <stdio.h>
#include <stdlib.h>

struct stack {
    void** stack;
    int length;
    int actual_length;
};
typedef struct stack stack;

void extend_stack(stack* s, int diff) {
    void** new = malloc(sizeof(void*)*(s->actual_length+diff));
    for (int i = 0; i < s->length; ++i) {
        new[i] = s->stack[i];
    }
    free(s->stack);
    s->stack = new;
    s->actual_length += diff;
}

int has_item(stack* s) {
    return s->length > 0;
}

void push(stack* s, void* item) {
    if(s->length +1 > s->actual_length) {
        extend_stack(s, 1);
    }
    s->length++;
    s->stack[s->length-1] = item;
}

void* pop(stack* s) {
    if(has_item(s)) {
        s->length--;
        void* output = s->stack[s->length];
        s->stack[s->length] = NULL;
        return output;
    }
    else {
        printf("cannot pop empty stack");
        return NULL;
    }
}

void* peek(stack* s) {
    void* item = pop(s);
    push(s, item);
    return item;
}

stack* create_stack() {
    stack* s = malloc(sizeof(stack));
    s->stack = malloc(sizeof(void*));
    s->actual_length = 0;
    s->length = 0;
    return s;
}

void free_stack(stack* s) {
    free(s->stack);
    free(s);
}

int main()
{
    stack* s = create_stack();
    int* i = malloc(sizeof(int));
    *i = 10;
    int* j = malloc(sizeof(int));
    *j = 20;
    push(s, i);
    push(s, j);

    printf("%d\n", *(int*)(pop(s)));
    printf("%d\n", *(int*)(pop(s)));

    push(s, j);
    push(s, i);

    printf("%d\n", *(int*)(pop(s)));
    printf("%d\n", *(int*)(pop(s)));

    free_stack(s);

    return 0;
}
