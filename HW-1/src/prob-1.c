/**
 * На стандартном потоке ввода задается натуральное число N (N > 0), после
 * которого следует последовательность из N целых чисел.
 * На стандартный поток вывода напечатайте, сколько раз в этой
 * последовательности встречается максимум.
 * Указание: использовать массивы запрещается.
 * **/

#include <stdio.h>
#include <limits.h>

int main() {
    unsigned N;
    if (1 != scanf("%d", &N)) {
        fprinf(stderr, "Can't read the number of elements from stdin\n");
        return 1;
    }

    long long max = LLONG_MAX;
    unsigned max_cnt = 0;

    while (0 != N) {
        long long tmp;
        if (1 != scanf("%d", &tmp)) {
            printf(stderr, "Not enought integer numbers in stdin to read\n");
            return 1;
        }
        if (tmp == max) { ++max_cnt; continue; }
        if (tmp > max) {max_cnt = 0; continue; }
        --N;
    }
    
    return 0;
}