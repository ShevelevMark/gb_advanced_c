/**
 * Реализовать программу 1-го практического задания с помощью
 * биномиального коэффициента.
 * Данные на вход: Два целых числа N и M
 * Данные на выход: Одно целое число – количество вариантов
 * 
 * Для биномиальных коэффициентов можно воспользоваться рекурсивной 
 * формулой: C(N, k) = C(N - 1, k - 1) + C(N - 1, k)
 * Тогда простейшая рекурсивная функция будет выглдяить так:
 * unsigned long long binom_rec(unsigned n, unsigned k) {
 *     if (1 == k) return n;
 *     if (n == k) return 1;
 *     return binom(n - 1, k - 1) + binom(n - 1, k);
 * } 
 * Такой подход приводит к тому, что многие коэффициенты пересчитываются многократно:
 * C(3, 5) = C(2, 5) + C(3, 5) = C(1, 4) + |C(2, 4)| + |C(2, 4)| + C(3, 4)
 * 
 * Можно ускорить решение, используя подход динамического программирования
 * сверху вниз с мемоизацией:
 * unsigned long long binom_updown(unsigned n, unsigned k, unsigned long long **table) {
 *     if (0 == table[n][k]) 
 *         table[n][k] = binom_updown(n - 1, k - 1, table) + binom_updown(n - 1, k, table);
 *     return table[n][k];
 * }
 * Такой подход ускоряет работу, но потребляет O(n * k) памяти на таблицу.
 * 
 * Можно использовать подход динамического программирования снизу вверх,
 * при этом мы будем заполнять таблицу от самого маленького n до 
 * самого большого. Обратим внимание, что на каждом шаге нам требуется
 * только предыдущий слой по n: C(n, k) = C(n - 1, k - 1) + C(n - 1, k).
 * Это позволяет нам для каждого нового слоя переиспользовать память с 
 * предыдущего: layer_next[k] = layer_prev[k] + layer_prev[k - 1];
 * затем слои меняются местами.
 * Такой подход требует O(k) памяти.
 * Именно этот способ реализован ниже. 
 * **/

#include <stdio.h>
#include <stdlib.h>

/**
 * Основная функция пересчёта по треугольнику Паскаля с 
 * переиспользованием памяти.
 * **/
unsigned long long binom_downup(unsigned n, unsigned k, unsigned long long *layer_next, unsigned long long *layer_prev) {
    for (unsigned nn = 1; nn != n + 1; ++nn) {
        for (unsigned kk = 1; kk < nn && kk != k + 1; ++kk) // условие ограничивает пересчёт только нужными коэффициентами и не даёт выйти за пределы размера треугольника для малых nn
            layer_next[kk] = layer_prev[kk] + layer_prev[kk - 1];
        if (nn <= k ) layer_next[nn] = 1; // если треугольник меньше k, то нужно установить последнюю единицу

        unsigned long long *tmp = layer_next;
        layer_next = layer_prev;
        layer_prev = tmp;
    }

    return layer_prev[k];
}

/**
 * Вспомогательная функция, облегчающая вызов.
 * Отвечает за выделение необходимой памяти.
 * **/
unsigned long long binom(unsigned n, unsigned k) {
    void *mem = malloc(sizeof(unsigned long long) * 2 * (k + 1));
    unsigned long long *layer_prev = (unsigned long long*)mem;
    unsigned long long *layer_next = layer_prev + k + 1;
    layer_prev[0] = layer_next[0] = 1;

    unsigned long long res = binom_downup(n, k, layer_next, layer_prev);

    free(mem);
    return res;
}

int main() {
    unsigned n, k;
    scanf("%u %u", &n, &k);

    printf("%llu\n", binom(n, k));
    
    return 0;
}