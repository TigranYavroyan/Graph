#ifndef FIND_SCCS_TARJAN_HPP
#define FIND_SCCS_TARJAN_HPP

template <bool directed>
typename Graph_adj_list<directed>::list Graph_adj_list<directed>::find_sccs_tarjan () const {
    int size = al.size();

    std::vector<int> ids (size, -1);
    std::vector<int> low_link (size, -1);
    std::stack<val_type> st;
    vec_vis in_stack(size, false);
    list res;
    std::vector<val_type> sub_res;

    for (int i = 0; i < size; ++i) {
        if (ids[i] == -1)
            _find_scc_tarjan (i, ids, low_link, in_stack, res, sub_res, st);
    }

    return res;

}

template <bool directed>
void Graph_adj_list<directed>::_find_scc_tarjan (val_type u, vec_i& ids, vec_i& low_link, vec_vis& in_stack, list& res, std::vector<val_type>& sub_res, std::stack<val_type>& st) const {

    static int id = 0;
    st.push(u);
    in_stack[u] = true;

    ids[u] = low_link[u] = id++;
    for (int v : al[u]) {
        if (ids[v] == -1) _find_scc_tarjan(v, ids, low_link, in_stack, res, sub_res, st);
        if (in_stack[v] == true)
            low_link[u] = std::min(low_link[u], low_link[v]);
    }

    if (low_link[u] == ids[u]) {

        for (val_type top = st.top() ; ; top = st.top()) {
            sub_res.push_back(top);
            st.pop();
            in_stack[top] = false;
            if (u == top) {
                break;
            }
        }

        res.push_back(std::move(sub_res));
    }
}

#endif // FIND_SCCS_TARJAN_HPP