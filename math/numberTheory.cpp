#define LL long long

bool vis[maxn];
int prime[maxp];
void sieve(int n) {
    int m = (int)sqrt(n + 0.5);
    memset(vis, 0, sizeof(vis));
    for (int i = 2; i <= m; ++i)
        if (!vis[i])
            for (int j = i * i; j <= n; j += i)
                vis[i] = true;
}

int gen_primes(int n) {
    sieve(n);
    int c = 0;
    for (int i = 2; i <= n; ++i)
        if (!vis[i])
            prime[c++] = i;
    return c;
}

void extend_gcd(LL a, LL b, LL &d, LL &x, LL &y) {
    if (!b) {
        d = a; x = 1; y = 0;
    } else {
        extend_gcd(b, a % b, d, y, x);
        y -= x * (a / b);
    }
}

// a ^ n % mod
int pow_mod(int a, int n, int mod) {
    int ret = 1;
    while (n) {
        if (n & 1) ret = 1LL * ret * a % mod;
        a = 1LL * a * a % mod;
        n >>= 1;
    }
    return ret;
}

// a * inv(a) % p == 1
int inv(int a, int p) {
    return pow_mod(a, p - 2, p);
}

int inv2(int x) {
    if (x <= 1) return 1;
    return 1LL * (mod - mod / x) * inv2(mod % x) % mod;
}

int _inv[maxn];
void gen_inv() {
    _inv[1] = 1;
    for (int i = 2; i < maxn; ++i)
        _inv[i] = (-mod / i * (LL)_inv[mod % i] % mod + mod) % mod;
}

int euler_phi(int n) {
    int m = (int)sqrt(n + 0.5);
    int ret = n;
    for (int i = 2; i <= m; ++i)
        if (n % i == 0) {
            ret = ret / i * (i - 1);
            while (n % i == 0) n /= i;
        }
    if (n > 1) ret = ret / n * (n - 1);
    return ret;
}

int phi[maxn];
void phi_table() {
    memset(phi, 0, sizeof(phi));
    phi[1] = 1;
    for (int i = 2; i < maxn; ++i)
        if (!phi[i])
            for (int j = i; j < maxn; j += i) {
                if (!phi[j]) phi[j] = j;
                phi[j] = phi[j] / i * (i - 1);
            }
}

// a ^ x % mod == b
LL log_mod(LL a, LL b, LL mod) {
    int n = (int)sqrt(mod + 0.5);
    LL iv = inv(pow_mod(a, n, mod), mod), p = 1;
    map<LL, int> mp;
    mp[p] = 0;
    for (int i = 1; i < n; ++i) {
        p = p * a % mod;
        if (!mp.count(p)) mp[p] = i;
    }
    for (int i = 0; i < n; ++i) {
        if (mp.count(b)) return 1LL * n * i + mp[b];
        b = b * iv % mod;
    }
    return -1;
}

// x == r[i] (mod m[i])
LL china(LL r[], LL m[], int n) {
    LL y, d, M = 1, ret = 0;
    for (int i = 0; i < n; ++i) M *= m[i];
    for (int i = 0; i < n; ++i) {
        LL w = M / m[i];
        extend_gcd(m[i], w, d, d, y);
        // y = pow_mod(w, m[i] - 2, m[i]);
        ret = (ret + y * w * r[i]) % M;
    }
    return (ret + M) % M;
}


// lucas: comb(n, m) % mod
LL comb(LL n, LL m, LL mod) {
    if (n < m) return 0;
    return (frac[n] * inv[m] % mod) * inv[n - m] % mod;
}

LL lucas(LL n, LL m, LL mod) {
    if (m == 0) return 1;
    return lucas(n / mod, m / mod, mod) * comb(n % mod, m % mod, mod) % mod;
}
