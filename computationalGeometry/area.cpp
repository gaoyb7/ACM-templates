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
		if (inter(c, AB, p1, p2) && (onseg(p1, AB) || onseg(p2, AB)))	//proper_onseg
			s += area(c, A, p1) + area(c, p1, p2) + area (c, p2, B) ;
		else
			s += area(c, A, B);
	}
	return fabs(s);
}


// union area of circles 
bool incir(circle a, circle b) { 
	return dcmp(abs(a.c - b.c) + a.r - b.r) <= 0;
}

void unionarea(circle c[], int n, double tot[]) {
	static pair<double, int> a[MAXN * 2];
	memset(tot, 0, sizeof(tot));
	for (int i = 0; i < n; ++i) {
		int m = 0, k = 0;
		for (int j = 0; j < n; ++j) {
			if (i == j) continue;
			double a1, a2;
			if (incir(c[i], c[j])) { ++k; continue; }
			if (!inter(c[i], c[j], a1, a2)) continue;
			a[m++] = make_pair(a1, 1);
			a[m++] = make_pair(a2, -1);
			if (a1 > a2) ++k;
		}
		sort(a, a + m);
		double a1 = a[m - 1].first - 2 * pi, a2, rad;
		for (int j = 0; j < m; ++j) {
			a2 = a[j].first , rad = a2 - a1;
			tot[k] += 0.5 * sqr(c[i].r) * (rad - sin(rad));
			tot[k] += 0.5 * cross(c[i].p(a1), c[i].p(a2));
			k += a[j].second;
			a1 = a2;
		}
		if (!m) tot[k] += pi * sqr(c[i].r);
	}
}

/*
   tot[0] = the aera of union
   tot[n-1] = the aera of intersection
   tot[k-1] - tot[k] = the aera covered k times
*/


// Union Area of Polygons 
double pos(point p, line ln) {
	return dot(p - ln.s, dir(ln)) / norm(dir(ln));
}

void unionarea(vector<point> p[], int n, double tot[]) {
	memset(tot, 0, sizeof(tot));
	for (int i = 0; i < n; ++i) for (int ii = 0; ii < p[i].size(); ++ii) {
		point A = p[i][ii], B = p[i][(ii + 1) % p[i].size()];
		line AB = line(A, B);
		vector<pair<double, int> > c;
		for (int j = 0; j < n; ++j) if (i != j)
			for (int jj = 0; jj < p[j].size(); ++jj) {
				point C = p[j][jj], D = p[j][(jj + 1) % p[j].size()];
				line CD = line(C, D);
				int f1 = dcmp(cross(A, B, C));
				int f2 = dcmp(cross(A, B, D));
				if (!f1 && !f2) {
					if (i < j && dcmp(dot(dir(AB), dir(CD))) > 0) {
						c.push_back(make_pair(pos(C, AB), 1));
						c.push_back(make_pair(pos(D, AB), -1));
					}
					continue;
				}
				double s1 = cross(C, D, A);
				double s2 = cross(C, D, B);
				double t = s1 / (s1 - s2);
				if (f1 >= 0 && f2 < 0) c.push_back(make_pair(t, 1));
				if (f1 < 0 && f2 >= 0) c.push_back(make_pair(t, -1));
			}
		c.push_back(make_pair(0.0, 0));
		c.push_back(make_pair(1.0, 0));
		sort(c.begin(), c.end());
		double s = 0.5 * cross(A, B), z = min(max(c[0].s, 0.0), 1.0);
		for (int j = 1, k = c[0].second; j < c.size(); ++j) {
			double w = min(max(c[j].first , 0.0), 1.0);
			tot[k] += s * (w - z);
			k += c[j].second;
			z = w;
		}
	}
}

/*
   tot[0] = the aera of union
   tot[n-1] = the aera of intersection
   tot[k-1] - tot[k] = the aera covered by k times
*/
