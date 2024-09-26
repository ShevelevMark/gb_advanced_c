/**
 * Напишите программу, которая находит разницу между максимальным и минимальным элементом в дереве.
 *
 * Если мы найдём максимальный и минимальный элементы, то найдём и разницу.
 * В задании представлено бинарное дерево поиска, но явно это в условии не оговорено. 
 * В решении есть  разные функции, для дерева поиска и 
 * для произвольного бинарного дерева.
 * **/

#include <stdio.h>
#include <stdlib.h>

typedef struct tree {
    struct tree *left, *right;
    int val;
} tree_t;

/**
 * В дереве поиска минимальный элемент - это элемент, у которого нет левого потомка.
 * Важно! Функция работает только на непустом дереве!
 * **/
int tree_search_min(tree_t *root) {
    if (NULL != root->left) return tree_search_min(root->left);
    return root->val;
}

/**
 * В дереве поиска максимальный элемент - это элемент, у которого нет правого потомка.
 * Важно! Функция работает только на непустом дереве!
 * **/
int tree_search_max(tree_t *root) {
    if (NULL != root->right) return tree_search_max(root->right);
    return root->val;
}

static inline int _min(int a, int b) {
    return b < a ? b : a;
}

/**
 * В обычном дереве нам придётся просмотреть обе ветки и найти минимум из трёх:
 *     корень, левое поддерево и правое поддерево.
 * **/
int tree_min(tree_t *root) {
    int min = root->val;
    if (NULL != root->left) min = _min(min, tree_min(root->left));
    if (NULL != root->right) min = _min(min, tree_min(root->right));
    return min;
}

static inline int _max(int a, int b) {
    return b > a ? b : a;
}

/**
 * В обычном дереве нам придётся просмотреть обе ветки и найти максимум из трёх:
 *     корень, левое поддерево и правое поддерево.
 * **/
int tree_max(tree_t *root) {
    int max = root->val;
    if (NULL != root->left) max = _max(max, tree_max(root->left));
    if (NULL != root->right) max = _max(max, tree_max(root->right));
    return max;
}

/**
 * Функция из задачи 2.
 * **/
tree_t* tree_new_node(int val);
tree_t* tree_from_array(int *arr, unsigned pos, unsigned size, int *errcode);
void tree_delete(tree_t *root);

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

    printf("As a search tree: max - min = %d\n", tree_search_max(root) - tree_search_min(root));
    printf("As an any binary tree: max - min = %d\n", tree_max(root) - tree_min(root));

    tree_delete(root);

    return 0;
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


