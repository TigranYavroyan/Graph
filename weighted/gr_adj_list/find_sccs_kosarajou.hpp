#ifndef FIND_SCCS_KOSARAJOU
#define FIND_SCCS_KOSARAJOU

template <bool directed>
typename Graph_al<directed>::vec_2d Graph_al<directed>::find_sccs_kosarajou () const {
    int size = al.size();
    Graph_al transposed = clone_transpose();
    vec_vis visits(size, false);
    std::stack<int> st;
    std::vector<int> component;
    vec_2d res;

    for (int i = 0; i < size; ++i) {
        if (!visits[i])
            _fill_in_order(i, visits, st);
    }

    fill(visits.begin(), visits.end(), false);

    int u;
    while (!st.empty()) {
        u = st.top(); st.pop();

        if (!visits[u]) {
            transposed._find_scc(u, visits, component);
            res.push_back(std::move(component));
        }
    }

    return res;
}

template <bool directed>
void Graph_al<directed>::_fill_in_order (int u, vec_vis& visits, std::stack<int>& st) const {
    visits[u] = true;

    for (const auto& pair : al[u]) {
        if (!visits[pair.first]) 
            _fill_in_order(pair.first, visits, st);
    }

    st.push(u);
}

template <bool directed>
void Graph_al<directed>::_find_scc (int u, vec_vis& visits, std::vector<int>& component) const {
    visits[u] = true;
    component.push_back(u);

    for (const auto& pair : al[u]) {
        if (!visits[pair.first])
            _find_scc(pair.first, visits, component);
    }
}

#endif // FIND_SCCS_KOSARAJOU