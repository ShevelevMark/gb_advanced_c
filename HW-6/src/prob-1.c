/**
 * Используя код задачи 1, написать программу поиска первого и последнего слова в строке.
 * **/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

typedef struct word_list {
    char *word;
    struct word_list *next;
} word_list_t;

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

void word_list_delete(word_list_t *head) {
    while (NULL != head) {
        word_list_t *tmp = head->next;
        free(head);
        head = tmp;
    }
}

word_list_t* word_list_find_last(word_list_t *head) {
    if (NULL == head) return NULL;
    if (NULL == head->next) return head;
    return word_list_find_last(head->next);
}

int main() {
    word_list_t *wl = NULL;
    /**
     * Читаем слова в список.
     */
    char word[1001];
    char next_char;
    bool in_word = false;
    unsigned pos = 0;
    while (1 == scanf("%c", &next_char) && '\n' != next_char) {
        if (!isspace(next_char)) {
            in_word = true;
            word[pos++] = next_char;
        } else {
            if (in_word) {
                word[pos] = 0;
                pos = 0;
                in_word = false;
                word_list_t *tmp = word_list_push_front(wl, word);
                if (NULL == tmp) {
                    printf("Can't push next element into list\n");
                    goto FREE;
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
            printf("Can't push next element into list\n");
            goto FREE;
        }
        wl = tmp;
    }

    if (NULL != wl) {
        printf("The first word: %s\n", word_list_find_last(wl)->word);
        printf("The last word: %s\n", wl->word);
        
    } else {
        printf("The word list is empty :(\n");
    }

FREE:
    word_list_delete(wl);
    return 0;
}