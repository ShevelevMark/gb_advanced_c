/**
 * Напишите программу, которая возвращает сумму всех элементов в дереве.
 * **/

#include <stdio.h>
#include <stdlib.h>

typedef struct tree {
    struct tree *left, *right;
    int val;
} tree_t;

/**
 * Рекурсивный подсчёт суммы элементов в дереве.
 * Пустое дерево имеет сумму элементов равную нулю.
 * Сумма элементов не должна превышать MAX_INT, иначе 
 * поведение функции не определено. 
 * **/
int tree_sum(tree_t *root) {
    if (NULL == root) return 0;
    return tree_sum(root->left) + tree_sum(root->right) + root->val;
}

/** 
 * Создаёт новый узел.
 * Если создание неудачно, возвращает NULL
 * **/
tree_t* tree_new_node(int val) {
    tree_t *root = (tree_t*)malloc(sizeof(tree_t));
    if (NULL != root) {
        root->val = val;
        root->left = root->right = NULL;
    }
    return root;
}

/**
 * Удаляет дерево из памяти.
 * **/
void tree_delete(tree_t *root) {
    if (NULL == root) return;
    tree_delete(root->left);
    tree_delete(root->right);
    free(root);
}

/**
 * Дополнительная функция для тестирования, позволяет создать дерево из массива.
 * 0 элемент - корень дерева. Для каждого элемента с индексом i:
 *     левый потомок 2 * i + 1
 *     правый потомок 2 * i + 2
 * Особое значение - 0. Если элемент массива равен 0, считаем, что потомка нет.  
 * 
 * @param arr int*      - адрес начала массива
 * @param pos unsigned  - текущая позиция в массиве (используется при рекурсивном вызове)
 * @param size unsigned - количество элементов в массиве 
 * @param errcode int   - код ошибки: 0 - всё успешно, 1 - ошибка памяти
 * @return tree_t* - адрес корня. Важно! Проверяйте код возврата! NULL может быть успешным результатом, означающим, что такого элемента нет в дереве!
 * **/
tree_t* tree_from_array(int *arr, unsigned pos, unsigned size, int *errcode) {
    if (pos >= size || 0 == arr[pos]) { errcode = 0; return NULL; }
    tree_t *root = tree_new_node(arr[pos]);
    if (NULL == root) {
        *errcode = 1;
        return NULL;
    }

    int left_errcode = 0, right_errcode = 0;
    root->left = tree_from_array(arr, 2 * pos + 1, size, &left_errcode);
    root->right = tree_from_array(arr, 2 * pos + 2, size, &right_errcode);
    if (0 != left_errcode || 0 != right_errcode) {
        *errcode = 1;
        tree_delete(root);
        return NULL;
    }
    return root;
}

int main() {
    /**
     * Тестовое дерево из примера задания. 
     * 0    1  2   3 4   5  6    7 8   9 10
     * 10 | 5 15 | 3 7 | 13 18 | 1 0 | 6 0 |
     * **/
    int arr[11] = {10, 5, 15, 3, 7, 13, 18, 1, 0, 6, 0};
    int errcode = 0;
    tree_t *root = tree_from_array(arr, 0, 11, &errcode);
    if (0 != errcode) {
        printf("Error in constructing tree\n");
        return 1;
    }

    printf("sum of all elements: %d\n", tree_sum(root));

    tree_delete(root);
    return 0;
}