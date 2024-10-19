struct TrieNode {
    int nxt[NUM_CHAR], link, term;
};

vector<TrieNode> Trie;

void insertString(const string &str) {
    int pt(0);
    for (char ch : str) {
        int c(ch - '0');
        if(!Trie[pt].nxt[c]) {
            Trie[pt].nxt[c] = Trie.size(); Trie.emplace_back();
        }
        pt = Trie[pt].nxt[c];
    }
    Trie[pt].term = pt;
}

void buildAutomaton(void) {
    Trie.emplace_back();
    for (int t = 0; t < numQuery; ++t) {
        string &str(qr[t].str);
        int type(qr[t].type);
        if(type == 0) insertString(str);
    }
    queue<int> qu; qu.push(0);
    while(qu.size()) {
        int v(qu.front()), u(Trie[v].link); qu.pop();
        if(!Trie[v].term) Trie[v].term = Trie[u].term;
        for (int c = 0; c < NUM_CHAR; ++c) {
            if(Trie[v].nxt[c]) {
                Trie[Trie[v].nxt[c]].link = (v) ? Trie[u].nxt[c] : 0;
                qu.push(Trie[v].nxt[c]);
            } else { Trie[v].nxt[c] = Trie[u].nxt[c]; }
        }
    }
}

void query(const string &str) {
    int pt(0);
    for (char ch : str) {
        int c(ch - '0');
        while(pt > 0 && !Trie[pt].nxt[c]) pt = Trie[pt].link;
        pt = Trie[pt].nxt[c];
    }
}