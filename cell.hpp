#ifndef CELL_HPP
#define CELL_HPP

struct cell {
    int row;
    int column;
    cell *next;
};

#endif // CELL_HPP