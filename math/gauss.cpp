const int maxn = 500 + 10;

void gauss(double a[][maxn], int n) {
    for (int i = 0; i < n; ++i) {
        int r = i;
        for (int k = i + 1; k < n; ++k)
            if (fabs(a[k][i]) > fabs(a[r][i]))
                r = k;
        if (r != i)
            for (int j = 0; j <= n; ++j)
                swap(a[r][j], a[i][j]);
        for (int k = i + 1; k < n; ++k)
            for (int j = n; j >= i; --j)
                a[k][j] -= a[k][i] / a[i][i] * a[i][j];
    }
    for (int i = n - 1; i >= 0; --i) {
        for (int j = i + 1; j < n; ++j)
            a[i][n] -= a[i][j] * a[j][n];
        a[i][n] /= a[i][i];
    }
}
