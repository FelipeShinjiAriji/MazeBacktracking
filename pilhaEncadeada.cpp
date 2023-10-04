#include <vector>
#include "pilhaEncadeada.hpp"

pilhaEncadeada::pilhaEncadeada() {
    pilhaEncadeada::size = 0;
    pilhaEncadeada::top = nullptr;
}

bool pilhaEncadeada::isEmpty() {
    if(pilhaEncadeada::size == 0){
        return true;
    }
    else{
        return false;
    }
}

void pilhaEncadeada::push(int x, int y) {
    cell* newCell = new cell;
    newCell->x = x;
    newCell->y = y;
    newCell->next = pilhaEncadeada::top;

    pilhaEncadeada::top = newCell;
    pilhaEncadeada::size = pilhaEncadeada::size + 1;
}

int* pilhaEncadeada::pop() {
    if(pilhaEncadeada::size <= 0){
        int* errorArray = new int[2];
        errorArray[0] = -1;
        errorArray[1] = -1; 
        return errorArray;
    }
    else{
        int* poppedElement = new int[2];
        poppedElement[0] = pilhaEncadeada::top -> x;
        poppedElement[1] = pilhaEncadeada::top -> y;
        pilhaEncadeada::top = pilhaEncadeada::top -> next;
        pilhaEncadeada::size = pilhaEncadeada::size - 1;
        delete(pilhaEncadeada::top);
        return poppedElement;
    }
}

int pilhaEncadeada::getSize() {
    return pilhaEncadeada::size;
}
