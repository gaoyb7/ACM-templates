int l[maxn], lp[maxn], fa[maxn], ch[maxn][26], cnt, len, last;

void init() {
    cnt = last = 1;
    len = 0;
    memset(ch[1], 0, sizeof(ch[1]));
}

void extend(int c) {
    int np = ++cnt, p = last; 
    last = np; l[np] = ++len; lp[np] = 0;
    memset(ch[np], 0, sizeof(ch[np]));
    for (; p && !ch[p][c]; p = fa[p]) ch[p][c] = np;
    if (!p) {
        fa[np] = 1;
    } else {
        int q = ch[p][c];
        if (l[q] == l[p] + 1) {
            fa[np] = q;
        } else {
            int nq = ++cnt;
            lp[nq] = lp[q] + l[q] - 1 - l[p];
            l[nq] = l[p] + 1;
            fa[nq] = fa[q];
            fa[q] = fa[np] = nq;
            memcpy(ch[nq], ch[q], sizeof(ch[q])); 
            for (; ch[p][c] == q; p = fa[p]) ch[p][c] = nq;
        }
    }
}

void topsort() {
    static int b[maxn], t[maxn];
    memset(b, 0, sizeof(b));
    for (int i = 1; i <= cnt; ++i) ++b[l[i]];
    for (int i = 1; i <= n; ++i) b[i] += b[i - 1];
    for (int i = 1; i <= cnt; ++i) t[b[l[i]]--] = i;
    for (int i = cnt; i; --i) {
        int u = t[i];
        /* code */
    }
}
