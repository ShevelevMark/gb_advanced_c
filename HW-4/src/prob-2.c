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
    char next_symbol;
    int scanf_res;
    char_stack_t op_stack = char_stack_make(16);
    if (!char_stack_is_valid(&op_stack)) {
        printf("Stack allocation error. Application terminated\n");
        return -1;
    }

    while (1 == (scanf_res = scanf("%c",&next_symbol)) && '\n' != next_symbol) {
        if (' ' == next_symbol) { continue; }
        if (isdigit(next_symbol)) { printf("%c", next_symbol); continue; }
        if ('&' == next_symbol) { 
            if(!char_stack_push(&op_stack, next_symbol)) {
                printf("Stack push error. Application terminated\n");
                return -1;
            }
            printf(" ");
            continue;
        }
        if ('^' == next_symbol) {
            while (!char_stack_is_empty(&op_stack) && '&' == char_stack_top(&op_stack))
                printf("%c", char_stack_pop(&op_stack));
            if (!char_stack_push(&op_stack, '^')) {
                 printf("Stack push error. Application terminated\n");
                return -1;
            }
            printf(" ");
            continue;
        }
        if ('|' == next_symbol) {
            while (!char_stack_is_empty(&op_stack) && ('&' == char_stack_top(&op_stack) || '^' == char_stack_top(&op_stack)))
                printf("%c", char_stack_pop(&op_stack));
            if (!char_stack_push(&op_stack, '|')) {
                 printf("Stack push error. Application terminated\n");
                return -1;
            }
            printf(" ");
            continue;
        }
        printf("Unexpected symbol. Application terminated\n");
        return -1;
    }
    while (!char_stack_is_empty(&op_stack))
        printf("%c", char_stack_pop(&op_stack));

    char_stack_delete(&op_stack);

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