#include "lab1_func.h"

using namespace lab1;

int main() {
    Matrix matr1 = {0, 0, nullptr};
    Matrix matr2 = {0, 0, nullptr};
    if (!input(&matr1))
        return 1;
    output(&matr1, "Source matrix");
    rebuild_matrix(&matr1, &matr2);
    output(&matr2, "Final matrix");
    erase(&matr1);
    erase(&matr1);
    erase(&matr2);
    return 0;
}
