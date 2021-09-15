//
// Created by sam on 04.09.2021.
//
#include <iostream>
#include "lab1_func.h"

namespace lab1 {
    void erase(Matrix* rm) {
        int i;
        for (i = 0; i < rm->m; i++)
            delete[] rm->matr[i].a;
        delete[] rm->matr;
    }

    Matrix* input(Matrix *rm) {
        const char *pr = "";
        int m, n;
        do {
            std::cout << pr << std::endl;
            std::cout << "Enter number of lines: ";
            pr = "You are wrong, repeat please";
            if (get_num(m) < 0)
                return nullptr;
            std::cout << "Enter number of columns: ";
            if (get_num(n) < 0)
                return nullptr;
        } while (m < 1);

        rm->m = m;
        rm->n = n;
        try {
            rm->matr = new Line [m];
        }
        catch (std::bad_alloc &ba) {
            std::cout << "------ Too many items in matrix: " << ba.what() << std::endl;
            erase(rm);
            return nullptr;
        }

        for (int i = 0; i < m; i++) {
            try {
                rm->matr[i].a = new int [1];
                rm->matr[i].pos = new int [1];
            }
            catch (std::bad_alloc &ba) {
                std::cout << "------ Too many items in matrix: " << ba.what() << std::endl;
                erase(rm);
                return nullptr;
            }
            std::cout << "Enter items for matrix line #" << (i + 1) << ":" << std::endl;
            int k = 0;
            for (int j = 0; j < rm->n; j++) {
                int a;
                if (get_num(a) < 0) {
                    erase(rm);
                    return nullptr;
                }
                if (a != 0){
                    rm->matr[i].a = myrealloc(rm->matr[i].a, k);
                    rm->matr[i].pos = myrealloc(rm->matr[i].pos, k);
                    rm->matr[i].a[k] = a;
                    rm->matr[i].pos[k] = j;
                    k++;
                }
            }
            rm->matr[i].sz = k;
        }
        return rm;
    }

    int amount_of_digits(int a) {
        int res = 0;
        if (a == 0)
            return 1;
        while (a != 0) {
            res++;
            a = a / 10;
        }
        return res;
    }

    int average_in_line(Line *line, int n) {
        int sum = 0, amnt = 0;
        for (int i = 0; i < line->sz; i++) {
            sum = sum + amount_of_digits(line->a[i]);
            amnt++;
        }
        amnt = n - line->sz + amnt;
        sum = n - line->sz + sum;
        return sum / amnt;
    }

    Matrix* rebuild_matrix(Matrix *m1, Matrix *m2) {
        int mid;
        m2->m = m1->m;
        m2->n = m1->n;

        try {
            m2->matr = new Line [m1->m];
        }
        catch (std::bad_alloc &ba) {
            std::cout << "------ Too many items in matrix: " << ba.what() << std::endl;
            erase(m2);
            return nullptr;
        }

        for (int i = 0; i < m1->m; i++) {
            mid = average_in_line(&(m1->matr[i]), m1->n);
            try {
                m2->matr[i].a = new int [m2->matr[i].sz];
            }
            catch (std::bad_alloc &ba) {
                std::cout << "------ Too many items in matrix: " << ba.what() << std::endl;
                erase(m2);
                return nullptr;
            }

            int k = 0;
            for (int j = 0; j < m1->matr[i].sz; j++) {
                if (amount_of_digits(m1->matr[i].a[j]) > mid) {
                    m2->matr[i].a[k] = m1->matr[i].a[j];
                    k++;
                }
            }
            m2->matr[i].sz = k;
        }

        return m2;
    }

    void output(Matrix* rm, const char *str){
        std::cout << str << std::endl;
        if (str[0] == 'S') {
            for (int i = 0; i < rm->m; i++) {
                int k;
                int j = 0;
                for (; j < rm->matr[i].sz; j++) {
                    if (j == 0 && rm->matr[i].pos[j] != 0)
                        k = rm->matr[i].pos[j];
                    else
                        k = rm->matr[i].pos[j] - rm->matr[i].pos[j - 1] - 1;

                    while (k > 0) {
                        std::cout << '0' << ' ';
                        k--;
                    }
                    std::cout << rm->matr[i].a[j] << ' ';
                }
                j--;
                k = rm->n - rm->matr[i].pos[j] - 1;

                while (k > 0) {
                    std::cout << '0' << ' ';
                    k--;
                }
                std::cout << std::endl;
            }
        }

        else {
            for (int i = 0; i < rm->m; i++) {
                for (int j = 0; j < rm->matr[i].sz; j++)
                    std::cout << rm->matr[i].a[j] << " ";
                std::cout << std::endl;
            }
        }
    }
}