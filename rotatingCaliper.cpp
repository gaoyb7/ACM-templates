//Farthest Pair
double maxdis(point *p, int n) {
    int m;
    andrew(p, n, h, m);
    if (m == 2) return abs(h[0] - h[1]);
    h[m] = h[0];
    double d = 0;
    for (int i = 0, j = 1; i < m; ++i) {
        while (dcmp(cross(h[i + 1] - h[i], h[j + 1] - h[j])) > 0)
            j = (j + 1) % m;
        d = max(d, abs(h[i] - h[j]));
    }
    return d;
}

double maxdis(point *p, int n) {
    int m;
    andrew(p, n, h, m);
    if (m == 2) return abs(h[0], h[1]);
    h[m] = h[0];
    abs ans = 0;
    for (int p = 0, q = 1; p < m; ++p) {
        while (cross(h[p], h[p + 1], h[q]) < cross(h[p], h[p + 1], h[q + 1]))
            q = (q + 1) % m;
        ans = max(ans, max(abs(h[p], h[q]), abs(h[p + 1], h[q])));
    }
    return ans;
}


