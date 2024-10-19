const int MAXN = 100005;

struct TNode {
    int sz, p, L, R;
    TNode() { sz = p = L = R = 0; }

} node[MAXN];

int root, nArr;

inline void update(const int &x) {
    node[x].sz = 1 + node[node[x].L].sz + node[node[x].R].sz;
}

int buildSplay(int l, int r, int pa = 0) {
    if(l > r) return 0;
    int mid = (l + r) >> 1;
    node[mid].p = pa;
    node[mid].L = buildSplay(l, mid - 1, mid);
    node[mid].R = buildSplay(mid + 1, r, mid);
    update(mid); return mid;
}

inline void setChild(int pa, int child, bool isRight) {
    node[child].p = pa;
    if(isRight) { node[pa].R = child; } else { node[pa].L = child; }
}

inline void upTree(int x) {
    int y = node[x].p, z = node[y].p;
    if(x == node[y].R) {
        int b = node[x].L; setChild(y, b, 1); setChild(x, y, 0);
    } else {
        int b = node[x].R; setChild(y, b, 0); setChild(x, y, 1);
    }
    setChild(z, x, (node[z].R == y)); update(y); update(x);
}

void splay(int x) {
    while(1) {
        if(node[x].p == 0) break;
        int y = node[x].p, z = node[y].p;
        if(z > 0)
            if((y == node[z].R) == (x == node[y].R)) { upTree(y); } else { upTree(x); }
        upTree(x);
    }
}

int locate(int root, int c) {
    int x(root);
    while(1) {
        int s = node[node[x].L].sz;
        if(s + 1 == c) return x;
        if(s + 1 > c) { x = node[x].L; } else { c -= s + 1; x = node[x].R; }
    }
}

void split(int T, int &A, int &B, int c) {
    if(c == 0) { A = 0, B = T; return; }
    int x = locate(T, c); splay(x);
    A = x, B = node[A].R; node[A].R = node[B].p = 0; update(A);
}

int join(int A, int B) {
    if(A == 0) return B;
    while(node[A].R != 0) A = node[A].R;
    splay(A); setChild(A, B, 1); update(A);
    return A;
}