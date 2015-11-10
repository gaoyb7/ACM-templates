const int N = 1 << 17;
const int M = 3;
const int MO = 1000000007;

const int MOD[] = {998244353, 995622913, 786433}; 
const int ROOT[] = {3, 5, 10};
const LL M1 = 397550359381069386LL;
const LL M2 = 596324591238590904LL;
const LL MM = 993874950619660289LL;

LL mul(LL x,LL y,LL z){
	return (x * y - (LL)(x / (long double) z * y + 1e-3) * z + z) % z;
}

LL china(int x1, int x2){
	return (mul(M1, x1, MM) + mul(M2, x2, MM)) % MM;
}

int merge(int a, int b, int c){
	int iv = pow_mod(1LL * MOD[0] * MOD[1] % MOD[2], MOD[2] - 2, MOD[2]);
	int ret;
	LL m1 = china(a, b);
	int m2 = c;
	int z = 1LL * ((m2 - m1) % MOD[2]) * iv % MOD[2];
	z = (z % MOD[2] + MOD[2]) % MOD[2];
	ret = (1LL * z * MOD[0] % MO * MOD[1] + m1) % MO;
	return (ret % MO + MO) % MO;
}

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
