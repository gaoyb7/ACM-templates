struct edge { int v, f, nxt; } e[maxe];
int g[maxn], dis[maxn], gap[maxn], pre[maxn], cur[maxn];
queue<int> que;
int esz, vsz, S, T;

void init(int n) {
	esz = 1; vsz = n;
	memset(g, 0, sizeof(g));
}

void add_edge(int u, int v, int f) {
	e[++esz] = (edge){v, f, g[u]}; g[u] = esz;
	e[++esz] = (edge){u, 0, g[v]}; g[v] = esz;
}

void bfs() {
	memset(dis, 0x3f, sizeof(dis));
	memset(gap, 0, sizeof(gap));
	dis[T] = 0; que.push(T);

	while (!que.empty()) {
		int u = que.front(); que.pop(); ++gap[dis[u]];
		for (int i = g[u]; i; i = e[i].nxt) {
			int v = e[i].v;
			if (e[i ^ 1].f && dis[v] == inf) {
				dis[v] = dis[u] + 1;
				que.push(v);
			}
		}
	}
}

int aug(int &u) {
	if (u == T) {
		int d = inf;
		for (int i = S; i != T; i = e[cur[i]].v) 
			if (e[cur[i]].f < d) d = e[cur[i]].f, u = i;
		for (int i = S; i != T; i = e[cur[i]].v)
			e[cur[i]].f -= d, e[cur[i] ^ 1].f += d;
		return d;
	}
	for (int i = g[u]; i; i = e[i].nxt) {
		int v = e[i].v;
		if (e[i].f && dis[u] == dis[v] + 1) {
			cur[u] = i; pre[v] = u; u = v;
			return 0;
		}
	}
	if (--gap[dis[u]]) {
		int d = vsz;
		for (int i = g[u]; i; i = e[i].nxt) {
			int v = e[i].v;
			if (e[i].f && dis[v] < d) d = dis[v], cur[u] = i;
		}
		++gap[dis[u] = d + 1];
		if (u != S) u = pre[u];
	} else {
		dis[S] = vsz;
	}
	return 0;
}

int max_flow() {
	int ret = 0;
	bfs();
	memcpy(cur, g, sizeof(cur));
	int u = S;
	while (dis[S] < vsz) ret += aug(u);
	return ret;
}
