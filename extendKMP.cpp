int f[maxn], ex[maxn];

void extend_kmp(const char* s, const char* t)
{
    int m = strlen(t), j = 0;
    while (j + 1 < m && t[j] == t[j+1]) ++j;
    f[0] = m; f[1] = j;
    for (int i = 2, k = 1; i < m; ++i) {
        if (f[i-k] < k + f[k] - i)
            f[i] = f[i-k];
        else {
            j = max(0, k + f[k] - i);
            while (i + j < m && t[i+j] == t[j]) ++j;
            f[i] = j; k = i;
        }
    }
    int n = strlen(s); j = 0;
    while (j < n && s[j] == t[j]) ++j;
    ex[0] = j;
    for (int i = 1, k = 0; i < n; ++i) {
        if (f[i-k] < k + ex[k] - i)
            ex[i] = f[i-k];
        else {
            j = max(0, k + ex[k] - i);
            while (i + j < n && s[i+j] == t[j]) ++j;
            ex[i] = j; k = i;
        }
    }
}
