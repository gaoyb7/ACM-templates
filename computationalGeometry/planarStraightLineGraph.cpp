struct edge { int s, t; double ang; };
vector<edge> e;

bool cmpang(const int &i, const int &j) {
	return e[i].ang < e[j].ang;
}

struct PSLG {
	vector<int> g[maxn];
	vector<poly> faces;
	point p[maxn];
	double area[maxn];
	bool vis[maxe * 2];
	int left[maxe * 2], pre[maxe * 2];
	int n, face_cnt;

	void init(int n) {
		this->n = n;
		for (int i = 0; i < n; ++i) g[i].clear();
		e.clear();
		faces.clear();
	}

	void add_edge(int s, int t) {
		e.push_back((edge){s, t, arg(p[t] - p[s])});
		e.push_back((edge){t, s, arg(p[s] - p[t])});
		int m = e.size();
		g[s].push_back(m - 2);
		g[t].push_back(m - 1);
	}

	void build() {
		for (int u = 0; u < n; ++u) {
			sort(g[u].begin(), g[u].end(), cmpang);
			for (size_t i = 0; i < g[u].size(); ++i)
				pre[g[u][(i + 1) % g[u].size()]] = g[u][i];
		}

		memset(vis, 0, sizeof(vis));
		face_cnt = 0;
		for (int u = 0; u < n; ++u)
			for (size_t i = 0; i < g[u].size(); ++i) {
				int id = g[u][i];
				if (!vis[id]) {
					++face_cnt;
					poly ply;
					while (1) {
						vis[id] = true; left[id] = face_cnt;
						ply.push_back(p[e[id].s]);
						id = pre[id ^ 1];
						if (id == g[u][i]) break;
						assert(vis[id] == 0);
					}
					faces.push_back(ply);
				}
			}
		for (size_t i = 0; i < faces.size(); ++i)
			area[i] = get_area(faces[i]);
	}
};
