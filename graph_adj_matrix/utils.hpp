#ifndef UTILS_HPP
#define UTILS_HPP

template <bool directed>
void Graph_adj_matrix<directed>::print () const {
    int size = am.size();

    int maxRowIndexDigits = 2/*std::to_string(m_row - 1).length()*/;
    int maxColIndexDigits = std::to_string(size - 1).length();

    std::cout << "      ";
    for (int j = 0; j < size; ++j) {
        std::cout << std::setw(maxColIndexDigits + 1) << j;
    }
    std::cout << '\n' << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << std::setw(maxRowIndexDigits + 2) << i << " |";
        for (int j = 0; j < size; ++j) {
            std::cout << std::setw(maxColIndexDigits + 1) << am[i][j];
        }
        std::cout.put('\n');
    }
    std::cout << std::endl;
}
#endif // UTILS_HPP