struct DLX
{
    int m, size;
    int U[maxnode], D[maxnode], R[maxnode], L[maxnode], Row[maxnode], Col[maxnode];
    int H[MaxN], S[MaxM];
    int ands, ans[MaxN];
    bool v[maxnode];

    void init(int _m) {  // columns
        m = _m;
        for (int i = 0; i <= m; i++) {
            S[i] = 0;
            U[i] = D[i] = i;
            L[i] = i - 1;
            R[i] = i + 1;
        }
        R[m] = 0; L[0] = m;
        size = m;
        memset(H, -1, sizeof(H));
    }

    void link(int r, int c) {
        ++S[Col[++size] = c];
        Row[size] = r;
        D[size] = D[c];
        U[D[c]] = size;
        U[size] = c;
        D[c] = size;
        if (H[r] < 0) H[r] = L[size] = R[size] = size;
        else {
            R[size] = R[H[r]];
            L[R[H[r]]] = size;
            L[size] = H[r];
            R[H[r]] = size;
        }
    }

    void remove(int c) {
        for (int i = D[c]; i != c; i = D[i])
            L[R[i]] = L[i], R[L[i]] = R[i];
    }

    void resume(int c) {
        for (int i = U[c]; i != c; i = U[i])
            L[R[i]] = R[L[i]] = i;
    }

    int f() {
        int ret = 0;
        for (int c = R[0]; c != 0; c = R[c])v[c] = true;
        for (int c = R[0]; c != 0; c = R[c])
            if (v[c]) {
                ret++;
                v[c] = false;
                for (int i = D[c]; i != c; i = D[i])
                    for (int j = R[i]; j != i; j = R[j])
                        v[Col[j]] = false;
            }
        return ret;
    }

    void dance(int d) {
        if (d + f() >= res) return;
        if (R[0] == 0) {
            res = min(res, d);
            return;
        }
        int c = R[0];
        for (int i = R[0]; i != 0; i = R[i])
            if (S[i] < S[c])
                c = i;
        for (int i = D[c]; i != c; i = D[i]) {
            remove(i);
            for (int j = R[i]; j != i; j = R[j]) remove(j);
            dance(d + 1);
            for (int j = L[i]; j != i; j = L[j]) resume(j);
            resume(i);
        }
    }
};
