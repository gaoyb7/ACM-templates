//farthest pair
double maxdis(point *p, int n) {
    int m;
    andrew(p, n, h, m);
    if (m == 2) return dis(h[0], h[1]);
    h[m] = h[0];
    double ans = 0;
    for (int p = 0, q = 1; p < m; ++p) {
        while (cross(h[p], h[p + 1], h[q]) < cross(h[p], h[p + 1], h[q + 1]))
            q = (q + 1) % m;
        ans = max(ans, max(dis(h[p], h[q]), dis(h[p + 1], h[q])));
    }
    return ans;
}

//mininal distance between convec hull
double mindis(point *p1, int n, point *p2 , int m) {
    int i = 0, j = 0;
    for (int k = 1; k < n; ++k) if (cmp(p1[k], p1[i])) i = k;
    for (int k = 1; k < m; ++k) if (cmp(p2[j], p2[k])) j = k;
    p1[n] = p1[0]; p2[m] = p2[0];
    double ans = dis(p1[i], p2[j]);
    for (int t = 0; t < n + m; ++t) {
        if (dcmp(cross(p1[i + 1] - p1[i] , p2[j + 1] - p2[j])) < 0) {
            ans = min(ans, distoseg(p2[j], line(p1[i], p1[i + 1])));
            i = (i + 1) % n;
        } else {
            ans = min(ans, distoseg(p1[i], line(p2[j], p2[j + 1])));
            j = (j + 1) % m;
        }
    }
    return ans;
}

//minimal rectangle
void minrec(point *p, int n, double &A, double &P) {
    andrew(p, n, h, m);
    int l = 1, r = 1, u = 1;
    A = P = inf; h[m] = h[0];
    for (int i = 0; i < m; ++i) {
        vec edge = unit(h[i + 1] - h[i]);
        while (dot(edge, h[r % m] - h[i]) < dot(edge, h[(r + 1) % m] - h[i])) ++r;
        while (u < r || cross(edge, h[u % m] - h[i]) < cross(edge, h[(u + 1) % m] - h[i])) ++u;
        while (l < u || dot(edge, h[l % m] - h[i]) > dot(edge, h[(l + 1) % m] - h[i])) ++l;
        double W = dot(edge, h[r % m] - h[i]) - dot(edge, h[l % m] - h[i]);
        double H = distoline(h[u % m], line(h[i + 1], h[i]));
        A = min(A, W * H);
        P = min(P, 2 * (W + H));
    }
}
