template<typename T1, typename T2> struct hashmap {
	const static int mod = 99991;
	const static int size = 50005;
	int pre[mod], mcnt;
	struct node {
		T1 key;
		T2 val;
		int next;
	} e[size];
	void clear() {
		memset(pre, -1, sizeof(pre));
		mcnt = 0;
	}
	void insert(T1 K, T2 V) {
		int x = K % mod;
		e[mcnt] = (node){K, V, pre[x]};
		pre[x] = mcnt++;
	}
	int find(T1 K) {
		int x = K % mod;
		for (int i = pre[x]; ~i; i = e[i].next)
			if (e[i].key == K)
				return i;
		return -1;
	}
	T2& operator [] (T1 x) {
		int i = find(x);
		if (!~i) {
			insert(x, 0);
			return e[mcnt - 1].val;
		}
		return e[i].val;
	}
};
