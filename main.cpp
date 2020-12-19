//
//  main.cpp
//  Tsisa_6
//
//  Created by Мария Забродина on 19/12/2020.
//  Copyright © 2020 Мария Забродина. All rights reserved.

#include <iostream>
#include <random>

std::vector<std::vector<double>> res(2, std::vector<double>(16));

double Function(double c, double d, int N){
    double MNK = 0;
    for (auto i = 0; i < N; i++){
        auto x = res[0][i];
        auto t = res[1][i];
        double y = c * x + d;
        MNK += (y - t) * (y - t);
    }
    return MNK;
}

double passive(int a, int b, double c, int N){
    double e = 0.1;
    double pres = (b - a) / 2;
    int n = 1;
    double d1 = a;
    while(pres >= e){
        double x, x_min = a;
        double func_curr;
        double func_min = Function(c, a, N);
        for (auto i = 1; i <= n; i++){
            x = (b - a) * i / (n + 1) + a;
            func_curr = Function(c, x, N);
            if (func_curr < func_min){
                func_min = func_curr;
                x_min = x;
            }
        }
        n++;
        pres = (b - a) / (n + 1);
        d1 = x_min;
    }
    return d1;
}

unsigned int Fib(const size_t& n) {
    if (n < 1)
        return 0;
    unsigned int f1 = 0, f2 = 1, fn = 0;
    for (size_t i = 1; i < n; ++i) {
        fn = f1 + f2;
        f1 = f2;
        f2 = fn;
    }
    return fn;
}

double fib(int N, double a, double b) {
    double m = 0;
    int f = 5;
    int i = 0;
    do {
        int n = f + i;
        std::vector<double> values;
        double  c1 = a + (b - a) * Fib(N) / Fib(N + 2);
        double  c2 = a + b - c1;
        double  d1 = passive(-2, 4, c1, N);
        double  d2 = passive(-2, 4, c2, N);
        double  y1 = Function(c1, d1, N);
        double  y2 = Function(c2, d2, N);
        while (n--) {
            if (y1 > y2) {
                a = c1;
                c1 = c2;
                c2 = b - (c1 - a);
                y1 = y2;
                y2 = Function(c2, d2, N);
                values.push_back(((b - a) / 2) + a);
            }
            else {
                b = c2;
                c2 = c1;
                c1 = a + (b - c2);
                y2 = y1;
                y1 = Function(c1, d1, N);
                values.push_back(((b - a) / 2) + a);
            }
        }
        m = values[values.size() - 1];
        i++;
    } while (b - a > 0.1);
    return m;
}

int main() {
    srand((unsigned)time(NULL));
    double c = 3;
    double d = 1;
    double a = -1;
    double b = 3;
    int N = 16;
    int A = 3;
    double dist = (b - a) / N;
    int i = 0;
    for (double x = a; x < b; x += dist){
        double f = rand()%1000;
        res[0][i] = x;
        res[1][i] = c * x + d + A * (-0.5 + f/1000);
        i++;
    }
    double C = fib(N, 0, 6);
    double D = passive(-2, 4, C, N);
    std::cout << C << " " << D << std::endl;
    for (auto i = 0; i < N; i++){
        std::cout << "(" << res[0][i] << ";" << res[1][i] << ") ";
    }
    return 0;
}
