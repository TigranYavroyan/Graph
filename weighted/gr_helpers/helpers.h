#ifndef HELPERS_H
#define HELPERS_H

#include <vector>
#include <optional>
#include <iostream>

namespace graph_utils {
    void print_path (const std::vector<int>& path);
    int edges_max (const std::vector<std::vector<int>>& edges);
	void endl(int count = 1);
}

#endif // HELPERS_H