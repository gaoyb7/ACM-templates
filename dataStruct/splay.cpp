#define KEY ch[ch[root][1]][0]
int ch[maxn][2], pre[maxn], sz[maxn], key[maxn], root, cnt;
int s[maxn], tot = 0;

void pushup(int r) {
    sz[r] = sz[ch[r][0]] + sz[ch[r][1]] + 1;
}

void pushdown(int r) {
}

void rotate(int x, int kind) {
    int y = pre[x];
    //pushdown(y);    
    //pushdown(x);
    ch[y][!kind] = ch[x][kind];
    pre[ch[x][kind]] = y;
    if (pre[y])
        ch[pre[y]][ch[pre[y]][1] == y] = x;
    pre[x] = pre[y];
    ch[x][kind] = y;
    pre[y] = x;
    //pushup(y); 
}

void splay(int r, int goal) {
    //pushdown(r); 
    while (pre[r] != goal) {
        if (pre[pre[r]] == goal)
            rotate(r, ch[pre[r]][0] == r);
        else {
            int y = pre[r];
            int kind = (ch[pre[y]][0] == y);
            if (ch[y][kind] == r) {
                rotate(r, !kind);
                rotate(r, kind);
            } else {
                rotate(y, kind);
                rotate(r, kind);
            }
        }
    }
    //pushup(r); 
    if (goal == 0) root = r;
}

void select(int k, int goal) {              //splay(Kth(root, k), goal)
    int tmp = 0, r = root;
    while (true) {
        //pushdown(r);
        tmp = sz[ch[r][0]];
        if (k == tmp + 1) break;
        if (k <= tmp) r = ch[r][0];
        else k -= tmp + 1, r = ch[r][1];
    }
    splay(r, goal);
}

void newnode(int &r, int x, int fa) {
    r = tot ? s[tot--] : ++cnt;             //Memory reclamation
    ch[r][0] = ch[r][1] = 0;
    pre[r] = fa; key[r] = x; sz[r] = 1;
}

void erase(int r) {                         //Memory reclamation 
    if (!r) return;
    s[++tot] = r;
    erase(ch[r][0]); erase(ch[r][1]);
}

void build(int &r, int L, int R, int fa) {
}

void init() {
    root = cnt = tot = 0;
    newnode(root, -1, 0); 
    newnode(ch[root][1], -1, root);
    sz[root] = 2;
    build(KEY, 1, n , ch[root][1]);
    pushup(ch[root][1]); pushup(root);
}
