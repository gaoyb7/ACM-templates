void rader(LL a[], int n) {
	for (int i = 1, j = n >> 1; i < n - 1; ++i) {
		if (i < j) swap(a[i], a[j]);
		int k = n >> 1;
		while (j >= k) {
			j -= k;
			k >>= 1;
		}
		if (j < k) j += k;
	}
}

void ntt(LL a[], int n, int t) {
	rader(a, n);
	for (int h = 2; h <= n; h <<= 1) {
		LL wn = pow_mod(g, (mod - 1) / h, mod);
		if (t == -1) wn = pow_mod(wn, mod - 2);
		for (int j = 0; j < n; j += h) {
			LL w = 1;
			for (int k = j; k < j + (h >> 1); ++k) {
				LL u = a[k];
				LL t = w * a[k + (h >> 1)] % mod;
				a[k] = (u + t) % mod;
				a[k + (h >> 1)] = ((u - t) % mod + mod) % mod;
				w = w * wn % mod;
			}
		}
	}
	if (t == -1) {
		LL r = pow_mod(n, mod - 2, mod);
		for (int i = 0; i < n; ++i)
			a[i] = a[i] * r % mod;
	}
}

// n == 2 ^ k
// (mod - 1) % n == 0
// g is primitive root of mod
