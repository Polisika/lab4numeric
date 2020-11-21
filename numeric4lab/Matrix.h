#pragma once
#include <vector>
#include <math.h>
#define T double
using namespace std;
void zero_components(vector<vector<T>>& A, int n, int m, vector<int>& res);
int gauss(vector<vector<T>>& A, vector<T>& F, vector<T>& x);

// Матрица имеет размерность n x n+1
// 1 - не нашлось beta, решение расходится
// -1 - количество итераций превысило разрешимое количество
// 0 - успех.
int newton_solve(vector<T>& x, T eps2, int num_test);

// Умножение матрицы на вектор
// res - нулевой вектор размера B
void matt_mul(vector<vector<T>>& A, vector<T>& B, vector<T>& res);