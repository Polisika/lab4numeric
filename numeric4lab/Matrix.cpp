#include "Matrix.h"
#include "Calculations.h"
#include <iostream>
#include <string>

using namespace std;
double EPS = 1e-14;
T eps1 = 1e-30;
int max_iter = 10000;

// ����������, ����� ���������� delta_x ����� ������
// � ����� ������� ����� ��������� �� ������� �
// n - ���������� ����������, m - ���������� ���������
void zero_components(vector<vector<T>>& A, int n, int m, vector<int>& res)
{
    if (n == m)
    {
        return;
    }
	vector<T>* max_abs = new vector<T>(n);
	// ���� �� ���� �������� max(abs(elem)) ����������� �������
	for (int j = 0; j < n; j++)
	{
		T max = 0;
		size_t size = m;
		for (size_t i = 0; i < size; i++)
		{
			T elem = abs(A[i][j]);
			if (elem > max)
				max = elem;
		}
		max_abs->at(j) = max;
	}

	// n-m ��� ���� ����������� ������� � ������� max_abs
	int d = n - m;
	for (int i = 0; i < d; i++)
	{
		T min = INFINITY;
		int index = 0;
		size_t size = max_abs->size();
		for (size_t j = 0; j < size; j++)
		{
			T elem = max_abs->at(j);
			if (elem < min)
			{
				min = elem;
				index = j;
			}
		}
		// ��������� ������� �� ������
		max_abs->erase(max_abs->begin() + index);
		res[i] = index;
	}
}

// ��� ������� ���� Ax=-F
// ������� n x n+1, � ��������� ������� ������ �������
// 1 - ������� ���������, 0, -1 - ������� ���
int gauss(vector<vector<T>>& A, vector<T>& x)
{
    int n = (int)A.size();
    int m = (int)A[0].size() - 1;
    x.resize(n);

    std::vector<int> where(m, -1);

    for (int col = 0, row = 0; col < m && row < n; ++col)
    {
        int sel = row;

        for (int i = row; i < n; ++i)
            if (abs(A[i][col]) > abs(A[sel][col]))
                sel = i;

        if (abs(A[sel][col]) < EPS)
            continue;

        for (int i = col; i <= m; ++i)
            swap(A[sel][i], A[row][i]);

        where[col] = row;

        for (int i = 0; i < n; ++i)
            if (i != row)
            {
                double c = A[i][col] / A[row][col];

                for (int j = col; j <= m; ++j)
                    A[i][j] -= A[row][j] * c;
            }

        ++row;
    }

    x.assign(m, 0);

    for (int i = 0; i < m; ++i)
        if (where[i] != -1)
            x[i] = A[where[i]][m] / A[where[i]][i];

    for (int i = 0; i < n; ++i)
    {
        double sum = 0;

        for (int j = 0; j < m; ++j)
            sum += x[j] * A[i][j];

        if (abs(sum - A[i][m]) > EPS)
            return 0;
    }

    for (int i = 0; i < m; ++i)
        if (where[i] == -1)
            return -1;

    return 1;
}

// ��� ������� ���� Ax=-F
// ������� n x n, � ��������� ������� ������ �������
// 1 - ������� ���������, 0, -1 - ������� ���
int gauss(vector<vector<T>>& A, vector<T>& F, vector<T>& x)
{
    int n = (int)A.size();
    x.resize(n);

    std::vector<int> where(n, -1);

    for (int col = 0, row = 0; col < n && row < n; ++col)
    {
        int sel = row;

        for (int i = row; i < n; ++i)
            if (abs(A[i][col]) > abs(A[sel][col]))
                sel = i;

        if (abs(A[sel][col]) < EPS)
            continue;

        for (int i = col; i < n; ++i)
            swap(A[sel][i], A[row][i]);
        swap(F[sel], F[row]);

        where[col] = row;

        for (int i = 0; i < n; ++i)
            if (i != row)
            {
                double c = A[i][col] / A[row][col];

                for (int j = col; j < n; ++j)
                    A[i][j] -= A[row][j] * c;
                F[i] -= F[row] * c;
            }

        ++row;
    }

    x.assign(n, 0);

    for (int i = 0; i < n; ++i)
        if (where[i] != -1)
            x[i] = F[where[i]] / A[where[i]][i];

    for (int i = 0; i < n; ++i)
    {
        double sum = 0;

        for (int j = 0; j < n; ++j)
            sum += x[j] * A[i][j];

        if (abs(sum - F[i]) > EPS)
            return 0;
    }

    for (int i = 0; i < n; ++i)
        if (where[i] == -1)
            return -1;

    return 1;
}

// ������� ��������� ����� �������
T vector_norm(vector<T>& F, Metrics num)
{
    T res = 0;
    int size = F.size();
    int max = -INFINITY;

    switch (num)
    {
    case Metrics::euclidean:
        for (int i = 0; i < size; i++)
            res += F[i] * F[i];
        res = sqrt(res);
        break;
    case Metrics::l:
        for (int i = 0; i < size; i++)
            res += abs(F[i]);
        break;
    //case Metrics::max:
    //    for (int i = 0; i < size; i++)
    //    {
    //        T elem = abs(F[i]);
    //        if (max < elem)
    //            max = elem;
    //    }
    //    res = max;
    //    break;
    default:
        throw new exception();
    }

    return res;
}

// F ������������ ����� � �������
void gen_F(vector<T>& F, vector<T>& x, int num_test)
{
    switch (num_test)
    {
    case 1:
        test1::get_F(F, x);
        break;
    case 2:
        test2::get_F(F, x);
        break;
    case 3:
        test3::get_F(F, x);
        break;
    }
}

void gen_J(vector<vector<T>>& J, vector<T>& x, int num_test)
{
    switch (num_test)
    {
    case 1:
        test1::get_J(J, x);
        break;
    case 2:
        test2::get_J(J, x);
        break;
    case 3:
        test3::get_J(J, x);
        break;
    }
}

int get_m(int num_test)
{
    switch (num_test)
    {
    case 1:
        return test1::m;

    case 2:
        return test2::m;

    case 3:
        return test3::m;
    default:
        throw new exception();
    }
}

int get_n(int num_test)
{
    switch (num_test)
    {
    case 1:
        return test1::n;

    case 2:
        return test2::n;

    case 3:
        return test3::n;
    default:
        throw new exception();
    }
}

// ������� ����� ����������� n x n+1
// 1 - �� ������� beta, ������� ����������
// -1 - ���������� �������� ��������� ���������� ����������
// 0 - �����.
int newton_solve(vector<T>& x, T eps2, Metrics metric, int num_test, ostream &out)
{
    int iters = 0;
    int m = get_m(num_test), n = get_n(num_test);
    int d = n - m;
    vector<int> comp(d);

    vector<T> Fk(m), F0(m), xk = x;
    vector<vector<T>> J(m);
    for (int i = 0; i < m; i++)
        J[i].resize(n);

    out.imbue(locale(""));
    out << "Iteration;beta;norm;";
    for (int i = 0; i < n; i++)
        out << "x" << to_string(i) << ";";
    out << endl;

    while (iters < max_iter)
    {
        // �������� ������� ����� � ������� ��������� x
        gen_J(J, x, num_test);

        // ��������� ������� � ����������, ����� �������, ������ ������� �����
        zero_components(J, n, m, comp);
        for (int i = 0; i < m; i++)
            for (int j = 0; j < d; j++)
                J[i].erase(J[i].begin() + comp[j]);

        // �������� ������ ����� (���������� xk � ������� A � �������� �������� � ������ ������)
        // ������������ � ������������� ������ ������
        gen_F(F0, x, num_test);

        // ������ delta_x �������� Jx = -F
        vector<T> delta_x(n);
        gauss(J, F0, delta_x);

        // ������ beta
        T beta = 1;
        for (int i = 0; i < n; i++)
            xk[i] += beta * delta_x[i];

        gen_F(Fk, xk, num_test);
        // ���� ����� ������ ����� ������ ������� �����
        T F0_norm = vector_norm(F0, metric);
        while (vector_norm(Fk, metric) > F0_norm)
        {
            xk = x;
            beta /= 2;
            for (int i = 0; i < n; i++)
                xk[i] += beta * delta_x[i];

            gen_F(Fk, xk, num_test);
            // ������� ������ �� ��������, � ������� �� ��������.
            if (beta < eps1)
                return 1;
        }
        
        // ����� ����������� ������� � �������������� ������
        x = xk;

        // ������� �� ����� ����� ������� �������� � beta   
        out << iters << ";" << beta << ";";
        T norm = vector_norm(Fk, metric);
        out << norm << ";";
        // ������ ��������� �������� xk+1 = xk + beta*delta_x
        for (int i = 0; i < n; i++)
            out << x[i] << ";";
        out << endl;

        // ������� �������
        if (norm / vector_norm(F0, metric) < eps2)
            return 0;

        iters++;
    }
    return -1;
}

