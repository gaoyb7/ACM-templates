void fft(cp *a, int n, int f) {
    static cp tmp[maxn];
    double arg = pi;
    for (int k = n >> 1; k; k >>= 1, arg *= 0.5) {
        cp wm = polar(1.0, f * arg), w(1, 0);
        for (int i = 0; i < n; i += k, w *= wm) {
            int p = i << 1;
            if (p >= n) p -= n;
            for (int j = 0; j < k; ++j)
                tmp[i + j] = a[p + j] + w * a[p + k + j];
        }
        for (int i = 0; i < n; ++i) a[i] = tmp[i];
    }
    if (f == -1)
        for (int i = 0; i < n; ++i)
            a[i] /= n;
}

// fft(a, n, 1); --- dft
// fft(a, n, -1); for (i) a[i] /= n; --- idft
// n == 2 ^ k;
