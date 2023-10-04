#ifndef PILHAENCADEADA_HPP
#define PILHAENCADEADA_HPP

#include <vector>

#include "cell.hpp"

class pilhaEncadeada {
private:
    cell *top;
    int size;
public:
    pilhaEncadeada();

    bool isEmpty();
    void push(int x, int y);
    int* pop();
    int getSize();

};

#endif // PILHAENCADEADA_HPP