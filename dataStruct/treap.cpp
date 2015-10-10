struct node {
	node *ch[2];
	int r, v, s;

	node (int v = 0): v(v) {
		ch[0] = ch[1] = NULL;
		r = rand(); s = 1;
	}
	bool operator < (const node &rhs) const {
		return r < rhs.r;
	}
	int cmp(int x) const {
		if (x == v) return -1;
		return x < v ? 0 : 1;
	}
	void maintain() {
		s = 1;
		if (ch[0] != NULL) s += ch[0] -> s;
		if (ch[1] != NULL) s += ch[1] -> s;
	}
};

void rotate(node* &o, int d) {
	node *k = o -> ch[d ^ 1];
	o -> ch[d ^ 1] = k -> ch[d];
	k -> ch[d] = o;
	o -> maintain(); k -> maintain();
	o = k;
}

void insert(node* &o, int x) {
	if (o == NULL) o = new node(x);
	else {
		int d = (x < o -> v ? 0 : 1);   //d = o -> cmp(x);
		insert(o -> ch[d], x);
		if (o -> ch[d] -> r > o -> r) rotate(o, d ^ 1);
	}
	o -> maintain();
}

void remove(node* &o, int x) {
	int d = o -> cmp(x);
	if (d == -1) {
		node *u = o;
		if (o -> ch[0] != NULL && o -> ch[1] != NULL) {
			int d2 = (o -> ch[0] -> r > o -> ch[1] -> r ? 1 : 0);
			rotate(o, d2); remove(o -> ch[d2], x);
		} else {
			if (o -> ch[0] == NULL) o = o -> ch[1];
			else o = o -> ch[0];
			delete u;
		}
	} else
		remove(o -> ch[d], x);
	if (o != NULL) o -> maintain();
}

int Kth(node* o, int k) {       //the Kth maximal
	if (o == NULL || k <= 0 || k > o -> s) return 0;
	int s = (o -> ch[1] == NULL ? 0 : o -> ch[1] -> s);
	if (k == s + 1) return o -> v;
	else if (k <= s) return Kth(o -> ch[1], k);
	else return Kth(o -> ch[0], k - s - 1);
}

void mergeto(node* &src, node* &dest) {
	if (src -> ch[0] != NULL) mergeto(src -> ch[0], dest);
	if (src -> ch[1] != NULL) mergeto(src -> ch[1], dest);
	insert(dest, src -> v);
	delete src; src = NULL;
}

void removetree(node* &x) {
	if (x -> ch[0] != NULL) removetree(x -> ch[0]);
	if (x -> ch[1] != NULL) removetree(x -> ch[1]);
	delete x; x = NULL;
}
