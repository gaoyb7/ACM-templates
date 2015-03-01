void andrew(point *p, int n, point *h, int &m) {
    int tmp = n;
    m = 0;
    sort(p, p + n, cmp); n = 1;
    for (int i = 1; i < tmp; ++i)
        if (!equal(p[i], p[i - 1]))
            p[n++] = p[i];

    for (int i = 0; i < n; ++i) {
        while (m > 1 && dcmp(cross(h[m - 2], h[m - 1], p[i])) <= 0) --m;
        h[m++] = p[i];
    }
    int k = m;
    for (int i = n - 2; i >= 0; --i) {
        while (m > k && dcmp(cross(h[m - 2], h[m - 1], p[i])) <= 0) --m;
        h[m++] = p[i];
    }
    if (n > 1) --m;
}
