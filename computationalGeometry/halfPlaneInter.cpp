bool onleft(point p, line hp) {
	return dcmp(cross(hp.s, hp.t, p)) > 0;
	//return dcmp(cross(hp.s, hp.t, p)) >= 0;
}

bool cmpang(line a, line b) {
	return dcmp(a.ang - b.ang) ? a.ang < b.ang : cross(a.s, a.t, b.s) < 0;
}

void hpinter(line *L, int n, point *p, int &m) {
	int head = 0, tail = 0; m = 0;
	sort(L, L + n, cmpang);
	for (int i = 1; i < n; ++i) {
		if (!dcmp(L[i].ang - L[i - 1].ang)) continue;
		while (head < tail && !onleft(p[tail - 1], L[i])) --tail;
		while (head < tail && !onleft(p[head], L[i])) ++head;
		L[++tail] = L[i];
		if (head < tail) inter(L[tail - 1], L[tail], p[tail - 1]);
	}
	while (head < tail && !onleft(p[tail - 1], L[head])) --tail;
	if (head < tail) inter(L[tail], L[head], p[tail]);
	for (int i = head; i <= tail; ++i) p[m++] = p[i];
}

line makehp(double a, double b, double c) {     //ax + by + c > 0
	point p1 = fabs(a) > fabs(b) ? point(-c / a, 0) : point(0, -c / b);
	point p2 = p1 + vec(b, -a);
	return line(p1, p2);
}
