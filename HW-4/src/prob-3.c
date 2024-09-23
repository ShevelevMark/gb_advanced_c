#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static inline unsigned _min(unsigned a, unsigned b) {
    return b < a ? b : a;
}

static inline unsigned _max(unsigned a, unsigned b) {
    return b > a ? b : a;
}

/**
 * Реализует "быстрый" за O(len(s)) алгоритм нахождения 
 * Z-функции.
 * Важно! массив zf должен содержать достаточно свободной 
 * памяти.
 * **/
void Z(char const *s, unsigned *zf) {
    unsigned s_len = strlen(s);

    for (unsigned i = 1, l = 0, r = 0; i < s_len; ++i) {
        if (i <= r)
            zf[i] = _min(r + 1 - i, zf[i - l]);

        while (i + zf[i] < s_len && s[zf[i]] == s[i + zf[i]])
            ++zf[i];

        if (i + zf[i] - 1 > r)
            l = i, r = i + zf[i] - 1;        
    }
}

int main() {
    char s[1001], h[1001];
    if (1 != scanf("%1000s", s)) {
        printf("Can't read the first word\n");
        return -1;
    }
    if (1 != scanf("%1000s", h)) {
        printf("Can't read the second word\n");
        return -1;
    }

    unsigned s_len = strlen(s), h_len = strlen(h);
    char *m = (char*)malloc(s_len + h_len + 2);
    unsigned m_len = s_len + 1 + h_len;
    unsigned *zf = (unsigned*)calloc(m_len, sizeof(unsigned));

    strcpy(m, s); m[s_len] = '#'; strcpy(m + s_len + 1, h); 
    {
        Z(m, zf);
        unsigned max_prefsuff_len = 0;
        for (unsigned p = s_len + 1; p != m_len; ++p)
            if (zf[p] == m_len - p) {
                max_prefsuff_len = zf[p];
                break;
            }
        printf("s_pref:h_suff = %u ", max_prefsuff_len);
    }

    strcpy(m, h); m[h_len] = '#'; strcpy(m + h_len + 1, s);
    {
        Z(m, zf);
        unsigned max_prefsuff_len = 0;
        for (unsigned p = h_len + 1; p != m_len; ++p)
            max_prefsuff_len = _max(max_prefsuff_len, zf[p]);
        printf("h_pref:s_suff = %u ", max_prefsuff_len);
    }

    free(zf); 
    free(m);

    return 0;
}