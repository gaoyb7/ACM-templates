void fft(cp *a, int n, int f) {
    static cp b[maxn];
    double arg = pi;
    for (int k = n >> 1; k; k >>= 1, arg *= 0.5) {
        cp wm = polar(1.0, f * arg), w(1, 0);
        for (int i = 0; i < n; i += k, w *= wm) {
            int p = i << 1;
            if (p >= n) p -= n;
            for (int j = 0; j < k; ++j)
                b[i + j] = a[p + j] + w * a[p + k + j];
        }
        for (int i = 0; i < n; ++i) a[i] = b[i];
    }
}
