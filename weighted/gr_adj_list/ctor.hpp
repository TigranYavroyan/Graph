#ifndef CTOR_HPP
#define CTOR_HPP

template <bool directed>
Graph_al<directed>::Graph_al (int n, vec_2d& edges) : al(n + 1) {
	for (int i = 0; i < edges.size(); ++i) {
		add_edge(edges[i][0], edges[i][1], edges[i][2]);
	}
}

#endif // CTOR_HPP