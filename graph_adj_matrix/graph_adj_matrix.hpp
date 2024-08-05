#ifndef GRAPH_ADJ_MATRIX_HPP
#define GRAPH_ADJ_MATRIX_HPP

#include <vector>
#include <iostream>
#include <iomanip>
#include <queue>
#include <algorithm>

class Graph_adj_matrix {
protected:
    using matrix = std::vector<std::vector<int>>;
    using vec_vis = std::vector<bool>;
public:
    Graph_adj_matrix (int n, const matrix& edges);
    Graph_adj_matrix (int n, int (*edges)[2], int size);

    ~Graph_adj_matrix () = default;
public:
    void add_edge (int u, int v);
    void add_vertex ();

    template <typename func>
    void dfs (func f, int u = 0);

    template <typename func>
    void bfs (func f, int u = 0);

    std::vector<int> shortest_path (int u, int v) const;

    void print () const;
private:
    matrix am; // adj_matrix

    template <typename func>
    void _dfs (int u, vec_vis& visits, func f) ;
};

#include "graph_adj_matrix.cpp"

#endif // GRAPH_ADJ_MATRIX_HPP