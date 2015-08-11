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
    LL r0 = r[0], m0 = m[0];
    for (int i = 1; i < n; ++i) {
        LL r1 = r[i], m1 = m[i], g, x0, y0;
        extend_gcd(m0, m1, g, x0, y0);
        if ((r1 - r0) % g) return -1;
        LL r2 = (r1 - r0) / g * x0 % m1, m2 = m0;
        m0 = m0 / g * m1;
        r0 = (r0 + r2 * m2 % m0) % m0;
    }
    return r0;
}
