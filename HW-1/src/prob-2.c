/**
 * На вход программе подается беззнаковое 32-битное целое число N. Требуется
 * изменить значения всех битов старшего байта числа на противоположные и
 * вывести полученное таким образом число.
 * **/

#include <stdio.h>

int main() {
    unsigned N;
    if (1 != scanf("%u", &N)) {
        fprintf(stderr, "Can't read a number from stdin\n");
        return 1;
    }

    /**
     * XOR с 0 даст тот же бит, что и был
     * XOR c 1 приведёт к инверсии: 1^1->0 1^0->1
     */
    unsigned const mask = 0xFF000000;
    unsigned R = N ^ mask;

    printf("%u\n", R);

    return 0;
}