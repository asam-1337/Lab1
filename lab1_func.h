//
// Created by sam on 04.09.2021.
//

//#ifndef LAB1_LAB1_FUNC_H
//#define LAB1_LAB1_FUNC_H

//#endif //LAB1_LAB1_FUNC_H

#include <iostream>

namespace lab1 {
    struct Line {
        int sz;
        int *pos;
        int *a;
    };

    struct Matrix {
        int n;
        int m;
        Line *matr;
    };

    template <class T>
    int get_num(T &a) {
        std::cin >> a;
        if (!std::cin.good())
            return -1;
        return 1;
    }

    template <class T>
    T *myrealloc(T *a, int n){
        T *b = new T [n + 1];
        T *tmp = b;
        for (int i = 0; i < n; i++) {
            tmp[i] = a[i];
        }
        delete [] a;
        return b;
    }

    Matrix* input(Matrix *rm);
    void output(Matrix *rm, const char* str);
    Matrix* rebuild_matrix(Matrix *m1, Matrix *m2);
    void erase(Matrix* rm);
}
