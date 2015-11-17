struct palindromic_tree {
	int next[maxn][26];
	int fail[maxn], cnt[maxn], num[maxn], len[maxn], s[maxn];
	int last, n, p;

	void init() {
		p = 0;
		newnode(0);
		newnode(-1);
		last = n = 0;
		s[n] = -1;
		fail[0] = 1;
	}

	int newnode(int l) {
		for (int i = 0; i < 26; ++i) next[p][i] = 0;
		cnt[p] = 0;
		num[p] = 0;
		len[p] = l;
		return p++;
	}

	int get_fail(int u) {
		while (s[n - len[u] - 1] != s[n]) u = fail[u];
		return u;
	}

	bool add(int c) {
		s[++n] = c;
		int cur = get_fail(last);
		bool flag = false;
		if (!next[cur][c]) {
			flag = true;
			int now = newnode(len[cur] + 2);
			fail[now] = next[get_fail(fail[cur])][c];
			next[cur][c] = now;
			num[now] = num[fail[now]] + 1;
		}
		last = next[cur][c];
		cnt[last]++;
		return flag;
	}

	void count() {
		for (int i = p - 1; i >= 0; --i) cnt[fail[i]] += cnt[i];
	}
};
