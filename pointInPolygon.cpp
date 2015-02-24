int inpoly(point a, point *p, int n) {
    int wn = 0;
    for (int i = 0; i < n; ++i) {
        point p1 = p[i], p2 = p[(i + 1) % n];
        if (onseg(a, line(p1, p2))) return 0;
        int d = dcmp(cross(a, p1, p2));
        int d1 = dcmp(p1.Y - a.Y), d2 = dcmp(p2.Y - a.Y);
        if (d > 0 && d1 <= 0 && d2 > 0) ++wn;
        if (d < 0 && d2 <= 0 && d1 > 0) --wn;
    }
    return wn ? 1 : -1;
}
