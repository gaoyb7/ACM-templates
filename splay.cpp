#include <bits/stdc++.h>
using namespace std;

struct Node {
    Node *ch[2];
    int s, v, flip;
    int cmp(int k) const {
        int d = k - ch[0] -> s;
        if(d == 1) return -1;
        return d <= 0 ? 0 : 1;
    }
    void maintain() {
        s = 1 + ch[0] -> s + ch[1] -> s;
    }
    void pushdown() {
        if(flip) {
            flip = 0;
            swap(ch[0], ch[1]);
            ch[0] -> flip ^= 1;
            ch[1] -> flip ^= 1;
        }
    }
};

Node *null, *root;     //null = new Node(); null -> s = 0;

void rotate(Node* &o, int d) {
    Node* k = o -> ch[d ^ 1]; 
    o -> ch[d ^ 1] = k -> ch[d]; k -> ch[d] = o;
    o -> maintain(); k -> maintain(); 
    o = k;
}

void splayKth(Node* &o, int k) {       //the Kth minimal
    o -> pushdown();
    int d = o -> cmp(k);
    if(d == 1) k -= o -> ch[0] -> s + 1;
    if(d != -1) {
        Node* p = o -> ch[d];
        p -> pushdown();
        int d2 = p -> cmp(k);
        int k2 = (d2 == 0 ? k : k - p -> ch[0] -> s - 1);
        if(d2 != -1) {
            splayKth(p -> ch[d2], k2);
            if(d == d2) rotate(o, d ^ 1); 
            else rotate(o -> ch[d], d);
        }
        rotate(o, d ^ 1);
    }
}

void prepare() {
    null = new Node;
    null->ch[0] = null->ch[1] = null;
    null->s = 0;
    root = null;
}

void clear(Node* &o) {
    if (o == null) return;
    clear(o -> ch[0]);
    clear(o -> ch[1]);
    delete(o);
}

Node* newnode(int val) {
    Node *o = new Node;
    o -> ch[0] = o -> ch[1] = null;
    o -> s = 1;
    o -> v = val;
    o -> flip = 0;
    return o;
}

void insert(int x) {
    int rank = _insert(root, x);
    splayKth(root, rank);
}

Node* merge(Node* left, Node* right) {
    splayKth(left, left -> s);
    left -> ch[1] = right;
    left -> maintain();
    return left;
}

void split(Node* o, int k, Node* &left, Node* &right) {     // k != 0
    splayKth(o, k);
    left = o;
    right = o -> ch[1];
    o -> ch[1] = null;
    left -> maintain();
}
