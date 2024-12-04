void tarjan(int u) {
    low[u] = num[u] = ++num[0];
    for (int it = 0; it < int(adj[u].size()); ++it) {
        int v(adj[u][it]);
        if(!num[v]) {
            st.push(u); tarjan(v);
            low[u] = min(low[u], low[v]);
            if(low[v] == num[u]) {
                lastComp[u] = ++numBCC;
                adjp[u].push_back(numNode + numBCC);
                do {
                    v = st.top(); st.pop();
                    if(lastComp[v] != numBCC) {
                        lastComp[v] = numBCC;
                        adjp[numNode + numBCC].push_back(v);
                    }
                } while(v != u);
            }
        } else { low[u] = min(low[u], num[v]); }
    }
    st.push(u);
}