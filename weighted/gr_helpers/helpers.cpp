#include "helpers.h"

void graph_utils::print_path (const std::vector<int>& path) {
    if (path.empty()) {
        std::cout << "The path is empty";
    }
    else {
        for (int i = 0; i < path.size(); ++i) {
            std::cout << path[i];
            if ((i + 1) != path.size()) std::cout << " -> ";
        }
    }
}

int graph_utils::edges_max (const std::vector<std::vector<int>>& edges) {
    std::optional<int> max;
    for (int i = 0; i < edges.size(); ++i) {
        for (int j = 0; j < 2; ++j) {
            if (!max.has_value() || max.value() < edges[i][j])
                max = edges[i][j];
        }
    }
    return max.value();
}

void graph_utils::endl (int count) {
	while (count--)
		std::cout << '\n';
}