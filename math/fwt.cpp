LL inv2 = pow_mod(2, mod - 2, mod);
 
void fwt_xor(LL a[], int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    fwt_xor(a, l, mid);
    fwt_xor(a, mid + 1, r);
    int len = mid - l + 1;
    for (int i = l; i <= mid; ++i){
        LL x1 = a[i], x2 = a[i + len];
        a[i] = (x1 + x2) % mod;
        a[i + len] = (x1 - x2 + mod) % mod;
    }
}
 
void ifwt_xor(LL a[], int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    int len = mid - l + 1;
    for (int i = l; i <= mid; ++i){
        LL x1 = a[i], x2 = a[i + len];
        a[i] = (x1 + x2) * inv2 % mod;
        a[i + len] = ((x1 - x2 + mod) % mod * inv2) % mod;
    }
    ifwt_xor(a, l, mid);
    ifwt_xor(a, mid + 1, r);
}
 
void fwt_and(LL a[], int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    fwt_and(a, l, mid);
    fwt_and(a, mid + 1, r);
    int len = mid - l + 1;
    for (int i = l; i <= mid; ++i){
        LL x1 = a[i], x2 = a[i + len];
        a[i] = (x1 + x2) % mod;
        a[i + len] = x2 % mod;
    }
}
 
void ifwt_and(LL a[], int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    int len = mid - l + 1;
    for (int i = l; i <= mid; ++i){
        LL x1 = a[i], x2 = a[i + len];
        a[i] = (x1 - x2 + mod) % mod;
        a[i + len] = x2 % mod;
    }
    ifwt_and(a, l, mid);
    ifwt_and(a, mid + 1, r);
}
 
void fwt_or(LL a[], int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    fwt_or(a, l, mid);
    fwt_or(a, mid + 1, r);
    int len = mid - l + 1;
    for (int i = l; i <= mid; ++i){
        LL x1 = a[i], x2 = a[i + len];
        a[i] = x1 % mod;
        a[i + len] = (x2 + x1) % mod;
    }
}
 
void ifwt_or(LL a[], int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    int len = mid - l + 1;
    for (int i = l; i <= mid; ++i){
        LL x1 = a[i], x2 = a[i + len];
        a[i] = x1 % mod;
        a[i + len] = (x2 - x1 + mod) % mod;
    }
    ifwt_or(a, l, mid);
    ifwt_or(a, mid + 1, r);
}
