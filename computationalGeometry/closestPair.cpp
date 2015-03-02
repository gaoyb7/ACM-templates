double mindis(point p[], int l, int r)
{
    static point t[maxn];
    if (r - l <= 1) return inf;
    int mid = (l + r) >> 1, m = 0;
    double x = p[mid].X;
    double d = min(mindis(p, l, mid), mindis(p, mid, r));
    inplace_merge(p + l, p + mid, p + r, cmpy);
    for (int i = l; i < r; ++i)
        if (fabs(x - p[i].X) < d)
            t[m++] = p[i];
    for (int i = 0; i < m ; ++ i) {
        for (int j = i + 1; j < m; ++j) {
            if (t[j].Y - t[i].Y >= d) break;
            d = min(d, abs(t[i] - t[j]));
        }
    }
    return d;
}

/*
sort(p, p + n, cmpx)
mindis(p, 0, n)
*/
