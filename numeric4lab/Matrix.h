#pragma once
#include "Calculations.h"
#include <vector>
#include <math.h>
#include <ostream>
#define T double
using namespace std;

// Euclidean - ��������� ����� sqrt(sum(xi^2))
// (�� ������������) max - max(|xi|)
// l - sum(|xi|)
enum class Metrics
{
    euclidean,
    //max,
    l,
};

void zero_components(vector<vector<T>>& A, int n, int m, vector<int>& res);
int gauss(vector<vector<T>>& A, vector<T>& F, vector<T>& x);

// ������� ����� ����������� n x n+1
// 1 - �� ������� beta, ������� ����������
// -1 - ���������� �������� ��������� ���������� ����������
// 0 - �����.
// �������: Euclidean, l, max. ��������� � ����������� Metrics.
int newton_solve(vector<T>& x, T eps2, Metrics metric, IGenerator& gen, ostream& out);