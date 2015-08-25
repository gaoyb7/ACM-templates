const int maxnode = 11000;
int ch[maxnode][26], val[maxnode], f[maxnode], last[maxnode], sz;

void clear() {
    sz = 1;
    memset(ch[0], 0,sizeof(ch[0]));
}

void insert(const char *s, int v) {
    int u = 0;
    for (int i = 0; s[i]; ++i) {
        int c = s[i] - 'a';
        if (!ch[u][c]) {
            memset(ch[sz], 0, sizeof(ch[sz]));
            val[sz] = 0;
            ch[u][c] = sz++;
        }
        u = ch[u][c];
    }
    val[u] = v;
}

void getFail() {
    queue<int> que;
    f[0] = 0;
    for (int c = 0; c < 26; ++c) {
        int u = ch[0][c];
        if (u) {
            f[u] = 0;
            last[u] = 0;
            que.push(u);
        }
    }

    while (!que.empty()) {
        int r = que.front(); que.pop();
        for (int c = 0; c < 26; ++c) {
            int u = ch[r][c];
            if (!u) {
                ch[r][c] = ch[f[r]][c];
                continue;
            }
            que.push(u);
            f[u] = ch[f[r]][c];
            last[u] = val[f[u]] ? f[u] : last[f[u]];
        }
    }
}

void find(char *s) {
    int j = 0;
    for (int i = 0; s[i]; ++i) {
        int c = s[i] - 'a';
        j = ch[j][c];
        if (val[j]) visit(j);
        else if (last[j]) visit(last[j]);   // Be care
    }
}
