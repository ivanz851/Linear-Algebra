#include "Vector.h"

Vector::Vector() : size(0) {

}

Vector::Vector(size_t size_) : size(size_) {
    vector.assign(size, 0);
}

Vector::Vector(size_t size_, std::initializer_list<int> vector_) : size(size_) {
    vector.resize(size);
    copy(vector_.begin(), vector_.end(), vector.begin());
}