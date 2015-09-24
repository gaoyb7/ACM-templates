//cross area of circle and a polygon
double area(circle c, point a, point b) {
    a -= c.c; b -= c.c;
    if (zero(a) || zero(b)) return 0;
    double s1 = 0.5 * arg(b / a) * sqr(c.r);
    double s2 = 0.5 * cross(a, b);
    return fabs(s1) < fabs(s2) ? s1 : s2;
}

double crossarea(circle c, point *p, int n) {
    double s = 0;
    for (int i = 0; i < n; ++i) {
        point A = p[i] , B = p[(i + 1) % n], p1, p2;
        line AB = line(A, B);
        if (inter(c, AB, p1, p2) && (onseg(p1, AB) || onseg(p2, AB)))
            s += area(c, A, p1) + area(c, p1, p2) + area (c, p2, B) ;
        else
            s += area(c, A, B);
    }
    return fabs(s);
}
