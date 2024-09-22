/**
 * Написать алгоритм перевода из инфиксной записи в обратную польскую. 
 * Для его реализации нужны данные по приоритетам операций. 
 * Реализовать алгоритм, используя побитовые операции (&, |, ^).
 * 
 * Эту задачу решает алгоритм Дейкстры "Сортировочная станция".
 * Для успешной работы требуется организовать очередь вывода и 
 * стек операций. Вместо очереди вывода будем писать сразу в поток вывода.
 * Стек реализован на основе динамически расширяющегося массива. 
 * **/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct char_stack {
    unsigned top, size;
    char *stack;
} char_stack_t;

char_stack_t char_stack_make(unsigned initial_size);
void char_stack_delete(char_stack_t *stack);
bool char_stack_is_valid(char_stack_t *stack);
bool char_stack_is_empty(char_stack_t *stack);
char char_stack_top(char_stack_t *stack);
char char_stack_pop(char_stack_t *stack);
bool char_stack_push(char_stack_t *stack, char ch);

#include <ctype.h>

int main() {
    char_stack_t stack = char_stack_make(16);
    printf("%d ", char_stack_is_valid(&stack));
    printf("%d\n", char_stack_is_empty(&stack));
    printf("%d ", char_stack_push(&stack, 'a'));
    printf("%d ", char_stack_push(&stack, 'b'));
    printf("%d\n", char_stack_push(&stack, 'c'));

    printf("%c ", char_stack_top(&stack));
    while (!char_stack_is_empty(&stack)) {
        printf("%c ", char_stack_pop(&stack));
    }
    printf("\n");

    printf("%d ", char_stack_is_empty(&stack));
    printf("%d\n", char_stack_is_valid(&stack));


    char_stack_delete(&stack);
    printf("%d\n", char_stack_is_valid(&stack));
    return 0;
}

char_stack_t char_stack_make(unsigned initial_size) {
    char *stack = (char*)malloc(initial_size * sizeof(char));
    if (NULL == stack) 
        return (char_stack_t){0u, 0u, NULL};
    return (char_stack_t){0u, initial_size, stack};
}

void char_stack_delete(char_stack_t *stack) {
    free(stack->stack);
    stack->stack = NULL;
    stack->top = stack->size = 0;
}

bool char_stack_is_empty(char_stack_t *stack) {
    return 0 == stack->top;
}

bool char_stack_is_valid(char_stack_t *stack) {
    return NULL != stack->stack;
}

bool char_stack_expand(char_stack_t *stack) {
    char *new_stack = (char*)malloc(stack->size * 2 * sizeof(char));
    if (NULL == new_stack)
        return false;
    
    for (unsigned idx = 0; idx != stack->top; ++idx)
        new_stack[idx] = stack->stack[idx];

    free(stack->stack);
    stack->stack = new_stack;
    return true;
}

char char_stack_top(char_stack_t *stack) {
    return stack->stack[stack->top - 1];
}

char char_stack_pop(char_stack_t *stack) {
    return stack->stack[--(stack->top)];
}

bool char_stack_push(char_stack_t *stack, char ch) {
    if (stack->top == stack->size) {
        if (!char_stack_expand(stack))
            return false;
    }
    stack->stack[(stack->top)++] = ch;
    return true;
}