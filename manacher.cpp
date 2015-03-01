char s[MAXN], t[MAXN + MAXN + 3];
int rad[MAXN + MAXN + 3];

void manacher(char *s) {
    int n = strlen(s), len = 0;
    t[len++] = '^'; t[len++] = '#';
    for (int i = 0; i < n; ++i) {
        t[len++] = s[i];
        t[len++] = '#';
    }
    t[len] = 0;
    int i = 1, j = 1, k;
    while (i < len) {
        while (t[i - j] == t[i + j]) ++j;
        rad[i] = j;
        for (k = 1; k < j && rad[i - k] != rad[i] - k; ++k) {
            rad[i + k] = min(rad[i - k], rad[i] - k);
        }
        i += k; j = max(j - k, 1);
    }
}

/*
s: abaaba
t: ^ # a # b # a # a # b # a # \0
rad: 0 1 2 1 4 1 2 7 2 1 4 1 2 1
 */
