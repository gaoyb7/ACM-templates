//cross area of circle and a polygon
double sectorarea(circle c, point a, point b) {
    double ang = fabs(arg(a - c.c) - arg(b - c.c));
    ang = min(ang, 2.0 * pi - ang);
    return c.r * c.r * ang * 0.5;
}

double area2(circle c, point a, point b) {
    point p1, p2;
    if (dis(a, c.c) > dis(b, c.c)) swap(a, b);
    bool ina = dcmp(dis(a, c.c) - c.r) <= 0;
    bool inb = dcmp(dis(b, c.c) - c.r) <= 0;
    if (ina) {
        if (inb)
            return fabs(cross(c.c, a, b)) * 0.5;
        else {
            inter(c, line(a, b), p1, p2);
            return fabs(cross(c.c, a, p2)) * 0.5 + sectorarea(c, b, p2);
        }
    } else {
        int num = inter(c, line(a, b), p1, p2);
        if (num == 2) {
            if (!onseg(p1,line(a, b)))
                num = 0;
        }
        if (num < 2) return sectorarea(c, a, b);
        else return fabs(cross(c.c, p1, p2)) * 0.5 + sectorarea(c, a, p1) + sectorarea(c, b, p2);
    }
}

double crossarea(circle c, point *p, int n) {
    double s = 0;
    p[n] = p[0];
    for (int i = 0; i < n; ++i)
        s += area2(c, p[i], p[i + 1]) * dcmp(cross(c.c, p[i], p[i + 1]));
    return fabs(s);
}
