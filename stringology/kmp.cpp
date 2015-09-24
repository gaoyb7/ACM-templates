void get_fail(char *p, int *f) {
    int n = strlen(p);
    f[0] = f[1] = 0;
    for (int i = 1; i < n; ++i) {
        int j = f[i];
        while (j && p[i] != p[j]) j = f[j];
        f[i + 1] = p[i] == p[j] ? j + 1 : 0;
    }
}

int find(char *T, char *p, int *f) {
    int n = strlen(T), m = strlen(p);
    getFaile(p, f);
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        while (cnt && p[cnt] != T[i]) cnt = f[cnt];
        if (p[cnt] == T[i]) ++cnt;
        if (cnt == m) return i;
    }
    return -1;
}
