#pragma once
// Вычисления для матрицы Якоби и правой части
#define T double
namespace test1
{
	int n = 2;
	int m = 2;

	// Получить элемент вектора
	T get_F(int i, vector<T>& x)
	{
		if (i == 0)
			// x^2 - 2*y^2 - xy + 2x - y + 1
			return x[0] * x[0] - 2 * x[1] * x[1] - x[0] * x[1] + 2 * x[0] - x[1] + 1;
		// 2x^2 - y^2 + xy + 3y - 5
		return 2 * x[0] * x[0] - x[1] * x[1] + x[0] * x[1] + 3 * x[1] - 5;
	}

	void get_J(vector<vector<T>>& J, vector<T>& x)
	{
		J[0][0] = 2 * x[0] - x[1] + 2; // 2x - y + 2
		J[0][1] = -2 - x[0] - 1; // -2 - x - 1
		J[1][0] = 4 * x[0] + x[1]; // 4x + y
		J[1][1] = -2 * x[1] + x[0] + 3; // -2y + x + 3
	}
}

namespace test2
{
	int n = 2;
	int m = 3;

	// Получить элемент вектора
	T get_F(int i, vector<T>& x)
	{
		return 0;
	}

	void get_J(vector<vector<T>>& J, vector<T>& x)
	{
		return;
	}
}

namespace test3
{
	int n = 2;
	int m = 3;

	// Получить элемент вектора
	T get_F(int i, vector<T>& x)
	{
		return 0;
	}

	void get_J(vector<vector<T>>& J, vector<T>& x)
	{
		return;
	}
}