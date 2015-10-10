int key[maxn], ch[maxn][2], dist[maxn], n;

int merge(int a, int b) {
	if (!a) return b;
	if (!b) return a;
	if (key[b] > key[a]) swap(a, b);
	ch[a][1] = merge(ch[a][1], b);
	if (dist[ch[a][0]] < dist[ch[a][1]]) swap(ch[a][0], ch[a][1]);
	dist[a] = dist[ch[a][1]] + 1;
	return a;
}

//dist[0] = -1;
