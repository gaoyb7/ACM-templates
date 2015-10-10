//poj 1741
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define V first
#define W second
using namespace std;

const int maxn = 10000 + 10;
typedef pair<int, int> Pii;
vector<Pii> e[maxn];
vector<int> dep;
int f[maxn], s[maxn], d[maxn];
bool vis[maxn];
int n, k, root, sz, ans;

void getroot(int u, int fa) {
	s[u] = 1;
	f[u] = 0;
	for (size_t i = 0; i < e[u].size(); ++i) {
		int v = e[u][i].V;
		if (v == fa || vis[v]) continue;
		getroot(v, u);
		s[u] += s[v];
		f[u] = max(f[u], s[v]);
	}
	f[u] = max(f[u], sz - s[u]);
	if (f[u] < f[root]) root = u;
}

void getdep(int u, int fa) {
	dep.push_back(d[u]);
	for (size_t i = 0; i < e[u].size(); ++i) {
		int v = e[u][i].V;
		if (v == fa || vis[v]) continue;
		d[v] = d[u] + e[u][i].W;
		getdep(v, u);
	}
}

int calc(int u, int add) {
	int ret = 0;
	dep.clear();
	d[u] = add;
	getdep(u, 0);
	sort(dep.begin(), dep.end());
	for (int l = 0, r = dep.size() - 1; l < r;)
		if (dep[l] + dep[r] <= k) ret += r - l++;
		else --r;
	return ret;
}

void work(int u) {
	ans += calc(u, 0);
	vis[u] = true;
	for (size_t i = 0; i < e[u].size(); ++i) {
		int v = e[u][i].V;
		if (vis[v]) continue;
		ans -= calc(v, e[u][i].W);
		f[0] = sz = s[v];
		getroot(v, root = 0);
		work(root);
	}
}

int main() {
	while (scanf("%d%d", &n, &k) == 2 && n) {
		for (int i = 1; i <= n; ++i) e[i].clear();
		memset(vis, 0, sizeof(vis));

		for (int i = 1; i < n; ++i) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			e[u].push_back(Pii(v, w));
			e[v].push_back(Pii(u, w));
		}
		f[0] = sz = n;
		getroot(1, root = 0);
		ans = 0;
		work(root);
		printf("%d\n", ans);
	}
}


#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define For(i, s, t) for (int i = (s); i <= (t); ++i)
using namespace std;

const int maxn = 100000 + 10;
typedef pair<int, int> Pii;
vector<int> e[maxn], q[maxn];
int w[maxn], sz[maxn], f[maxn], d[maxn], ans[maxn];
bool vis[maxn];
Pii ql[maxn];
int n, m, root, size, clk;

struct BIT {
	int f[maxn], cnt[maxn], sum[maxn];
	int mx;
	void init() {
		cnt[0] = clk;
		f[mx = 0] = 0;
	}
	void add(int u) {
		if (cnt[u] != clk) cnt[u] = clk, f[u] = 0;
		++f[u];
	}
	int query(int u) {
		return sum[min(u, mx)];
	}
	void getsum() {
		sum[mx = 0] = f[0];
		For(i, 1, n)
			if (cnt[i] == clk)
				sum[i] = sum[i - 1] + f[i], mx = i;
			else
				break;
	}
} len[3];

void getroot(int u, int fa) {
	sz[u] = 1; f[u] = 0;
	for (int v: e[u])
		if (v != fa && !vis[v])
			getroot(v, u), sz[u] += sz[v], f[u] = max(f[u], sz[v]);
	f[u] = max(f[u], size - sz[u]);
	if (f[u] < f[root]) root = u;
}

void init() {
	scanf("%d%d", &n, &m);
	For(i, 1, n) {
		scanf("%d", w + i);
		e[i].clear();
		q[i].clear();
	}
	For(i, 1, n - 1) {
		int u, v; scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	For(i, 1, m) {
		int u, d;
		scanf("%d%d", &u, &d);
		ql[i] = make_pair(u, d);
		q[u].push_back(i);
		ans[i] = 0;
	}
}

void calc(int u, int fa, int cnt, bool mor, bool les, bool eq) {
	for (int id: q[u]) {
		if (cnt <= ql[id].second) {
			if (mor)
				ans[id] += len[0].query(ql[id].second - cnt);
			if (les)
				ans[id] += len[1].query(ql[id].second - cnt);
			if (eq)
				ans[id] -= len[2].query(ql[id].second - cnt);
		}
	}
	for (int v: e[u]) {
		if (v == fa || vis[v]) continue;
		calc(v, u, cnt + 1, 
				mor && w[v] >= w[u], les && w[v] <= w[u], eq && w[v] == w[u]);
	}
}

void dfs(int u, int fa, int cnt, bool les, bool mor, bool eq) {
	if (les) len[0].add(cnt);
	if (mor) len[1].add(cnt);
	if (eq) len[2].add(cnt);
	for (int v: e[u]) {
		if (v == fa || vis[v]) continue;
		dfs(v, u, cnt + 1, 
				les && w[v] <= w[u], mor && w[v] >= w[u], eq && w[v] == w[u]);
	}
}

void work(int u) {
	vis[u] = true;
	++clk;
	rep(i, 3)
		len[i].init(), len[i].add(0), len[i].getsum();
	for (int v: e[u]) {
		if (vis[v]) continue;
		calc(v, u, 1, w[v] >= w[u], w[v] <= w[u], w[v] == w[u]);
		dfs(v, u, 1, w[v] <= w[u], w[v] >= w[u], w[v] == w[u]);
		rep(j, 3) len[j].getsum();
	}

	for (int id: q[u]) {
		ans[id] += len[0].query(ql[id].second);
		ans[id] += len[1].query(ql[id].second);
		ans[id] -= len[2].query(ql[id].second);
	}

	++clk;
	rep(i, 3)
		len[i].init(), len[i].getsum();
	reverse(e[u].begin(), e[u].end());
	for (int v: e[u]) {
		if (vis[v]) continue;
		calc(v, u, 1, w[v] >= w[u], w[v] <= w[u], w[v] == w[u]);
		dfs(v, u, 1, w[v] <= w[u], w[v] >= w[u], w[v] == w[u]);
		rep(j, 3) len[j].getsum();
	}

	for (int v: e[u]) {
		if (vis[v]) continue;
		f[0] = size = sz[v];
		getroot(v, root = 0);
		work(root);
	}
}

void solve() {
	For(i, 1, n) vis[i] = false;
	f[0] = size = n;
	getroot(1, root = 0);
	work(root);
	For(i, 1, m)
		printf("%d\n", ans[i]);
}

int main() {
	int tt;
	scanf("%d", &tt);
	while (tt--) {
		init();
		solve();
	}
}
