#pragma once
#include "Calculations.h"
#include <vector>
#include <math.h>
#include <ostream>
#define T double
using namespace std;

// Euclidean - ≈вклидова норма sqrt(sum(xi^2))
// (не используетс€) max - max(|xi|)
// l - sum(|xi|)
enum class Metrics
{
    euclidean,
    //max,
    l,
};

void zero_components(vector<vector<T>>& A, int n, int m, vector<int>& res);
int gauss(vector<vector<T>>& A, vector<T>& F, vector<T>& x);

// ћатрица имеет размерность n x n+1
// 1 - не нашлось beta, решение расходитс€
// -1 - количество итераций превысило разрешимое количество
// 0 - успех.
// ћетрики: Euclidean, l, max. ѕодробнее в определении Metrics.
int newton_solve(vector<T>& x, T eps2, Metrics metric, IGenerator& gen, ostream& out);