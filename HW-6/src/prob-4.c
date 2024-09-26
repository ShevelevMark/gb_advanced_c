/** 
 * Напишите программу, которая удаляет из списка все элементы с нечетным порядковым номером.
 * **/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

/**
 * Списочная пара:
 * @property word char*             - указатель на память, где содержится завершаемая нулём строка
 * @property next struct word_list* - указатель на следующий элемент списка, либо NULL
 * **/
typedef struct word_list {
    char *word;
    struct word_list *next;
} word_list_t;

/**
 * Функция добавляет элемент перед головой списка.
 * Функция выделяет память на одну списочную пару и
 * на строку в одном блоке. 
 * 
 * @param head word_list_t* - указатель на голову списка, либо NULL
 * @param word word_list_t* - указатель на завершаемую нулём строку; память обязательно должна быть верной и содержать по крайней мере один элемент - завершающий ноль

 * @return word_list_t* - если выделение памяти прошло успешно, то возвращается указатель на новую голову списка, иначе возвращается NULL
 * **/
word_list_t* word_list_push_front(word_list_t *head, char const *word) {
    unsigned w_len = strlen(word);
    word_list_t *new_head = malloc(sizeof(word_list_t) + w_len + 1);
    if (NULL != new_head) {
        new_head->next = head;
        strcpy((char*)(new_head + 1), word);
        new_head->word = (char*)(new_head + 1);
    }
    return new_head;
}

/**
 * Функция возвращает память списка системе.
 * 
 * @param head word_list_t* - голова списка, либо NULL 
 * **/
void word_list_delete(word_list_t *head) {
    while (NULL != head) {
        word_list_t *tmp = head->next;
        free(head); // нам нужно только одно освобождение памяти, так как было лишь одно выделение
        head = tmp;
    }
}

/**
 * Функция выделена из кода первой задачи.
 * Функция читает из стандартного потока ввода слова пока поток не пуст 
 * и не встретился символ перевода строки ('\n').
 * Функция ожидает, что каждое отдельное слово не превышает 1000 символов, 
 * иначе функция завершится с ошибкой.
 * Функция составляет список в обратном порядке!
 * 
 * @param errcode int* - указатель на переменную для записи кода ошибки:
 *     0 - успешно;
 *     1 - слишком длинное слово;
 *     2 - ошибка выделения памяти;
 *     4 - не было прочитано ни одного слова. 
 * @return word_list_t* - если код ошибки 0, функция вернёт указатель на голову списка, во всех остальных случаях функция вернёт NULL; функция сама освободит память, если она была выделена, но произошла ошибка.
 * **/
word_list_t* read_words(int *errcode) {
    word_list_t *wl = NULL;
    *errcode = 0;
    char word[1001];       
    char next_char;        
    bool in_word = false;  
    unsigned pos = 0;
    while (1 == scanf("%c", &next_char) && '\n' != next_char) {
        if (!isspace(next_char)) {
            if (1000 == pos) {
                *errcode = 1;
                goto ERROR;
            }
            in_word = true;
            word[pos++] = next_char;
        } else {
            if (in_word) {
                word[pos] = 0;
                pos = 0;
                in_word = false;
                word_list_t *tmp = word_list_push_front(wl, word);
                if (NULL == tmp) { 
                    *errcode = 2; 
                    goto ERROR;
                }
                wl = tmp;
            }
        }
    }

    if (in_word) {
        word[pos] = 0;
        pos = 0;
        in_word = false;
        word_list_t *tmp = word_list_push_front(wl, word);
        if (NULL == tmp) {
            *errcode = 2;
            goto ERROR;
        }
        wl = tmp;
    }

    if (NULL == wl) {
        *errcode = 4;
        goto ERROR;
    }
    
    return wl;
       //  ^
       //  |
ERROR: // до этой метки нельзя дойти если всё хорошо
    word_list_delete(wl);
    return NULL;
}

/**
 * Функция рекурсивного разворота списка.
 * 
 * @param given word_list_t*    - голова оригинального списка
 * @param reversed word_list_t* - голова развёрнутого списка
 * @return word_list_t* - голова развёрнутого списка, либо NULL, если оригинальный список пуст
 * **/
word_list_t* word_list_reverse(word_list_t *given, word_list_t *reversed) {
    if (NULL == given) return reversed;
    word_list_t *tmp = given->next;
    given->next = reversed;
    return word_list_reverse(tmp, given);
}

/**
 * Основная функция задания: удаляет нечётные элементы.
 * Первый элемент считается чётным.
 * Функция рекурсивно делит список на стек смыкния и стек удаления.
 * При сворачивании стека чётные элементы зацепляются в новый список,
 * а нечётные удаляются.
 * Чётные элементы после смыканию сохраняют оригинальный порядок. 
 * 
 * @param wl word_list_t* - указатель на первый элемент списка, либо NULL
 * @return word_list_t* - возвращает голову нового списка, либо NULL, если изначальный список пуст
 * **/
word_list_t* word_list_remove_odd(word_list_t *wl) {
    if (NULL == wl || NULL == wl->next) return wl;
    word_list_t *tmp = wl->next;
    wl->next = word_list_remove_odd(wl->next->next);
    free(tmp);
    return wl;
}