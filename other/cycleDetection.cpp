// sgu455
#include <bits/stdc++.h>
#define LL long long
using namespace std;

const int limit = 2000000;

LL A, B, C;

LL f(LL x) {
    return (A * x + x % B) % C;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> A >> B >> C;
    LL x = f(1), y = f(x);
    int v = 1;
    while (v <= limit && x != y)
        x = f(x), y = f(f(y)), ++v;
    if (v > limit) {
        puts("-1");
        return 0;
    }
    int st = 0;
    x = 1;
    while (x != y)
        x = f(x), y = f(y), ++st;
    int sz = 1;
    y = f(x);
    while (x != y)
        y = f(y), ++sz;
    if (st + sz <= limit) printf("%d\n", st + sz);
    else puts("-1");
}

