/**
 * Преподаватели Geek Brains создали набор, содержащий N (1 ≤ N ≤ 1 000 000)
 * натуральных чисел, не превосходящих 1 000 000. Известно, что ровно одно
 * число в этом наборе встречается один раз, а остальные — ровно по два раза.
 * Помогите им найти это число. Входные данные: в первой входной строке
 * вводится число N, затем по одному числу в строке вводятся N натуральных
 * чисел, не превосходящих 2 000 000 000. Выходные данные: ваша программа
 * должна определить число, встречающееся один раз, и вывести его на экран.
 * Указание: использовать массивы запрещается
 * **/

/**
 * Классическая задача, решается с помощью скользящего XOR.
 * Если рассмотреть отдельную позицию в двоичном числе, 
 * то парные числа имеют одинаковый бит, 
 * значит этот бит после применения XOR с парными числами будет тем 
 * же, каким был без них. Рассуждая таким образом для всех парных чисел
 * мы придём к тому, что остаётся только бит непарного числа.
 * Если инициировать скользяций XOR нулём, то в результате бит 
 * будет точно такой, как у непарного числа, т.к. XOR с нулём даёт 
 * то же значение бита: 0^0->0 0^1->1.
 */

#include <stdio.h>

int main() {
    unsigned sliding_xor = 0;
    unsigned numbers_cnt;
    unsigned next_number;

    if (1 != scanf("%u", &numbers_cnt)) {
        fprintf(stderr, "Can't read the number from stdin\n");
        return 1;
    }

    while (0 != numbers_cnt) {
        if (1 != scanf("%u", &next_number)) {
            fprintf(stderr, "Not enought numbers in stdin\n");
            return 1;
        }
        --numbers_cnt;
        sliding_xor ^= next_number;
    }

    printf("%u\n",sliding_xor);
    return 0;
}