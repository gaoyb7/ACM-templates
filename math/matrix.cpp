struct matrix {
	int n, m;
	vector<int> v;
	matrix(int r, int c): n(r), m(c), v(r * c) {};
	int get(int i, int j) const { return v[i * m + j]; }
	void set(int i, int j, int val) { v[i * m + j] = val; }
};

matrix operator * (const matrix &a, const matrix &b) {
	matrix ret(a.n, b.m);
	for (int i = 0; i < ret.n; ++i)
		for (int j = 0; j < ret.m; ++j) {
			int s = 0;
			for (int k = 0; k < a.m; ++k)
				s += a.get(i, k) * b.get(k, j);
			ret.set(i, j, s);
		}
	return ret;
}

matrix pow(const matrix &a, int k) {
	if (k == 1) return a;
	matrix ret = pow(a, k >> 1);
	return k & 1 ? ret * ret * a : ret * ret;
}
