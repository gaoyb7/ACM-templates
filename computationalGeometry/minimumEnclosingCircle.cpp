circle mincir(point *p, int n) {
    random_shuffle(p, p + n);
    point c = p[0]; 
    double r = 0;
    for (int i = 1; i < n; ++i) {
        if (dcmp(abs(p[i] - c) - r) <= 0) continue;
        c = p[i]; r = 0;
        for (int j = 0; j < i; ++j) {
            if (dcmp(abs(p[j] - c) - r) <= 0) continue;
            c = (p[i] + p[j]) * 0.5; r = abs(p[i] - p[j]) * 0.5;
            for (int k = 0; k < j; ++k) {
                if (dcmp(abs(p[k] - c) - r) <= 0) continue;
                c = circumcenter(p[i], p[j], p[k]); r = dis(p[k], c);
            }
        }
    }
    return circle(c, r);
}
