#pragma "once"
#include <vector>

class Vector {
public:
    size_t size;
    std::vector<int> vector;

    // Default constructor which initializes empty vector
    Vector();
    // Constructor which initializes vector of size size_ filled with zeros
    explicit Vector(size_t size_);
    // Constructor which initializes vector of size size_ filled with vector_ values
    Vector(size_t size_, std::initializer_list<int> vector_);
};