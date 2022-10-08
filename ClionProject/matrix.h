#pragma once

#include <iostream>
#include <vector>

class matrix {
public:
    void PrintMatrix() {
        std::cout << "matrix height " << height << "\n";
        std::cout << "matrix width " << width << "\n";
        std::cout << "matrix = \n";
        for (size_t i = 0; i < height; i++) {
            for (size_t j = 0; j < width; j++) {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }


private:
    size_t height, width; // height and width of the matrix
    std::vector<std::vector<int>> matrix; // matrix

protected:

};