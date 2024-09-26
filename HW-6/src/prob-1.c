/**
 * Используя код задачи 1, написать программу поиска первого и последнего слова в строке.
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
 */
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
 */
void word_list_delete(word_list_t *head) {
    while (NULL != head) {
        word_list_t *tmp = head->next;
        free(head); // нам нужно только одно освобождение памяти, так как было лишь одно выделение
        head = tmp;
    }
}

/**
 * Основная функция задания:
 * рекурсивно находит последний элемент в списке. 
 * 
 * @param head word_list_t* - указатель на голову списка, либо NULL 
 * @return word_list_t* - возвращает последний элемент списка, т.е. такой элемент A, что NULL == A->next, либо NULL, если NULL == head 
 */
word_list_t* word_list_find_last(word_list_t *head) {
    if (NULL == head) return NULL;          // Нет ручек, нет конфетки (ц)
    if (NULL == head->next) return head;    // Если это последний элемент - возвращаем его
    return word_list_find_last(head->next); // Иначе ищем последний элемент в хвосте
}

int main() {
    word_list_t *wl = NULL;
    /**
     * Читаем слова в список пока существуют символы в потоке и не 
     * достигнут конец строки ('\n').
     * Важно! Использование функции push_front приводит к тому, что 
     * список формируется в обратном порядке!
     * При чтении слова посимвольно используется буфер длины 1001:
     * 1000 символов + завершающий ноль. Если размер слова превысит 1000 
     * символов, программа сообщит об ошибке и завершится.
     * **/
    char word[1001];       // буфер для слова
    char next_char;        // буфер для одного считанного символа
    bool in_word = false;  // флаг позволяет нам отслеживать промежутки между словами, если флаг true, но мы встретили пробел, то буфер немедленно сбрасывается в элемент списка 
    unsigned pos = 0;
    while (1 == scanf("%c", &next_char) && '\n' != next_char) {
        if (!isspace(next_char)) {
            if (1000 == pos) {
                printf("Too long word!\n");
                goto FREE;
            }
            in_word = true;
            word[pos++] = next_char;
        } else {
            if (in_word) {
                word[pos] = 0;
                pos = 0;
                in_word = false;
                word_list_t *tmp = word_list_push_front(wl, word);
                if (NULL == tmp) { // проверка на успешное выделение памяти
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