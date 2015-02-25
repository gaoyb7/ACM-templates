bool onleft(point p, line hp) {
    return dcmp(cross(hp.s, hp.t, p)) >= 0;
}

bool cmpang(line a, line b) {
    return dcmp(a.ang - b.ang) ? a.ang < b.ang : cross(a.s, a.t, b.s) < 0;
}

void hpinter(line *q, int n, point *h, int &m) {
    int head = 0, tail = 0;
    m = 0;
    sort(q, q + n, cmpang);
    for (int i = 1; i < n; ++i) {
        if (!dcmp(q[i].ang - q[i - 1].ang)) continue;
        while (head < tail && !onleft(h[tail - 1], q[i])) --tail;
        while (head < tail && !onleft(h[head], q[i])) ++head;
        q[++tail] = q[i];
        if (head < tail) inter(q[tail - 1], q[tail], h[tail - 1]);
    }
    while (head < tail && !onleft(h[tail - 1], q[head])) --tail;
    if (head < tail) inter(q[tail], q[head], h[tail]);
    for (int i = head; i <= tail; ++i) h[m++] = h[i];
}

line makehp(double a, double b, double c) {     //ax + by + c > 0
    point p1 = fabs(a) > fabs(b) ? point(-c / a, 0) : point(0, -c / b);
    point p2 = p1 + vec(b, -a);
    return line(p1, p2);
}
