#pragma once
#define _USE_MATH_DEFINES
#include <vector>
#include <math.h>
#include <ostream>
#include <fstream>
#include <string>

using namespace std;
// Вычисления для матрицы Якоби и правой части
#define T double

// Интерфейс для реализации генерации F и J
class IGenerator
{
public:
	// Необходимо сразу учесть минус
	virtual void get_F(vector<T>& F, vector<T>& x) = 0;
	virtual void get_J(vector<vector<T>>& J, vector<T>& x) = 0;
	virtual int get_n() = 0;
	virtual int get_m() = 0;
};

// Пересечение прямых в точке -3 -3
class gen_test1: public IGenerator
{
public:
	virtual int get_n()
	{
		return 2;
	}
	virtual int get_m()
	{
		return 2;
	}

	// Получить элемент вектора
	// Необходимо сразу учесть минус
	virtual void get_F(vector<T>& F, vector<T>& x)
	{
		F[0] = -(x[0] + x[1] + 6);
		F[1] = -(x[1] - x[0]);
	}

	virtual void get_J(vector<vector<T>>& J, vector<T>& x)
	{
		J[0][0] = 1;
		J[0][1] = 1;
		J[1][0] = -1;
		J[1][1] = 1;
	}
};

// Пересечение окружностей в точке -3, 0
class gen_test2: public IGenerator
{
public:
	virtual int get_n()
	{
		return 2;
	}
	virtual int get_m()
	{
		return 2;
	}
	// Получить элемент вектора
	// Необходимо сразу учесть минус
	void get_F(vector<T>& F, vector<T>& x)
	{
		F[0] = -(x[0] * x[0] + x[1] * x[1] - 9);
		F[1] = -((x[0] + 6) * (x[0] + 6) + x[1] * x[1] - 9);
	}

	void get_J(vector<vector<T>>& J, vector<T>& x)
	{
		J[0][0] = 2 * x[0];
		J[0][1] = 2 * x[1];
		J[1][0] = 2 * x[0] + 12;
		J[1][1] = 2 * x[1];
	}
};

// Пересечение кривых в точке 1, 1
class gen_test3 : public IGenerator
{
public:
	virtual int get_n()
	{
		return 2;
	}
	virtual int get_m()
	{
		return 2;
	}
	// Получить элемент вектора
	// Необходимо сразу учесть минус
	void get_F(vector<T>& F, vector<T>& x)
	{
		// x^2 - 2*y^2 - xy + 2x - y + 1
		F[0] = -(x[0] * x[0] - 2 * x[1] * x[1] - x[0] * x[1] + 2 * x[0] - x[1] + 1);
		// 2x^2 - y^2 + xy + 3y - 5
		F[1] = -(2 * x[0] * x[0] - x[1] * x[1] + x[0] * x[1] + 3 * x[1] - 5);
	}

	void get_J(vector<vector<T>>& J, vector<T>& x)
	{
		J[0][0] = 2 * x[0] - x[1] + 2;	// 2x - y + 2
		J[0][1] = -2 - x[0] - 1;		// -2 - x - 1
		J[1][0] = 4 * x[0] + x[1];		// 4x + y
		J[1][1] = -2 * x[1] + x[0] + 3; // -2y + x + 3
	}
};

// Пересечение непересекающихся окружностей
class gen_research1 : public IGenerator
{
public:
	virtual int get_n()
	{
		return 2;
	}
	virtual int get_m()
	{
		return 2;
	}
	// Получить элемент вектора
	// Необходимо сразу учесть минус
	void get_F(vector<T>& F, vector<T>& x)
	{
		// x^2 + y^2 = 9
		F[0] = -(x[0] * x[0] + x[1] * x[1] - 9);	
		// (x+8)^2 + y^2 = 9
		F[1] = -((x[0] + 8) * (x[0] + 8) + x[1] * x[1] - 9);
	}

	void get_J(vector<vector<T>>& J, vector<T>& x)
	{
		J[0][0] = 2 * x[0];
		J[0][1] = 2 * x[1];
		J[1][0] = 2 * x[0] + 16;
		J[1][1] = 2 * x[1];
	}
};

// Пересечение окружностей в точке -3, 0
class gen_research2 : public IGenerator
{
public:
	virtual int get_n()
	{
		return 2;
	}
	virtual int get_m()
	{
		return 2;
	}
	// Получить элемент вектора
	// Необходимо сразу учесть минус
	void get_F(vector<T>& F, vector<T>& x)
	{
		// x^2 + y^2 = 9
		F[0] = -(x[0] * x[0] + x[1] * x[1] - 9);
		// (x+8)^2 + y^2 = 9
		F[1] = -((x[0] + 6) * (x[0] + 6) + x[1] * x[1] - 9);
	}

	void get_J(vector<vector<T>>& J, vector<T>& x)
	{
		J[0][0] = 2 * x[0];
		J[0][1] = 2 * x[1];
		J[1][0] = 2 * x[0] + 12;
		J[1][1] = 2 * x[1];
	}
};

// Пересечение окружностей в двух точках
class gen_research3 : public IGenerator
{
public:
	virtual int get_n()
	{
		return 2;
	}
	virtual int get_m()
	{
		return 2;
	}
	// Получить элемент вектора
	// Необходимо сразу учесть минус
	void get_F(vector<T>& F, vector<T>& x)
	{
		// x^2 + y^2 = 9
		F[0] = -(x[0] * x[0] + x[1] * x[1] - 9);
		// (x+8)^2 + y^2 = 9
		F[1] = -((x[0] + 5) * (x[0] + 5) + x[1] * x[1] - 9);
	}

	void get_J(vector<vector<T>>& J, vector<T>& x)
	{
		J[0][0] = 2 * x[0];
		J[0][1] = 2 * x[1];
		J[1][0] = 2 * x[0] + 10;
		J[1][1] = 2 * x[1];
	}
};

// Пересечение непересекающихся окружностей + рандомная прямая
class gen_research1_line : public IGenerator
{
public:
	virtual int get_n()
	{
		return 2;
	}
	virtual int get_m()
	{
		return 3;
	}
	// Получить элемент вектора
	// Необходимо сразу учесть минус
	void get_F(vector<T>& F, vector<T>& x)
	{
		// x^2 + y^2 = 9
		F[0] = -(x[0] * x[0] + x[1] * x[1] - 9);
		// (x+8)^2 + y^2 = 9
		F[1] = -((x[0] + 8) * (x[0] + 8) + x[1] * x[1] - 9);
		F[2] = -(x[0] + 4);
	}

	void get_J(vector<vector<T>>& J, vector<T>& x)
	{
		J[0][0] = 2 * x[0];
		J[0][1] = 2 * x[1];
		J[1][0] = 2 * x[0] + 16;
		J[1][1] = 2 * x[1];
		J[2][0] = 1;
		J[2][1] = 0;
	}
};

// Пересечение окружностей в точке -3, 0 + прямая, пересекающаяся в этой точке
class gen_research2_line : public IGenerator
{
public:
	virtual int get_n()
	{
		return 2;
	}
	virtual int get_m()
	{
		return 3;
	}
	// Получить элемент вектора
	// Необходимо сразу учесть минус
	void get_F(vector<T>& F, vector<T>& x)
	{
		// x^2 + y^2 = 9
		F[0] = -(x[0] * x[0] + x[1] * x[1] - 9);
		// (x+8)^2 + y^2 = 9
		F[1] = -((x[0] + 6) * (x[0] + 6) + x[1] * x[1] - 9);
		F[2] = -(x[0] + 3);
	}

	void get_J(vector<vector<T>>& J, vector<T>& x)
	{
		J[0][0] = 2 * x[0];
		J[0][1] = 2 * x[1];
		J[1][0] = 2 * x[0] + 12;
		J[1][1] = 2 * x[1];
		J[2][0] = 1;
		J[2][1] = 0;
	}
};

// Пересечение окружностей в двух точках + прямая, пересекающая в этих точках
class gen_research3_line : public IGenerator
{
public:
	virtual int get_n()
	{
		return 2;
	}
	virtual int get_m()
	{
		return 3;
	}
	// Получить элемент вектора
	// Необходимо сразу учесть минус
	void get_F(vector<T>& F, vector<T>& x)
	{
		// x^2 + y^2 = 9
		F[0] = -(x[0] * x[0] + x[1] * x[1] - 9);
		// (x+8)^2 + y^2 = 9
		F[1] = -((x[0] + 5) * (x[0] + 5) + x[1] * x[1] - 9);
		F[2] = -(x[0] + 2.5);
	}

	void get_J(vector<vector<T>>& J, vector<T>& x)
	{
		J[0][0] = 2 * x[0];
		J[0][1] = 2 * x[1];
		J[1][0] = 2 * x[0] + 10;
		J[1][1] = 2 * x[1];
		J[2][0] = 1;
		J[2][1] = 0;
	}
};

// Синусоида и пересечение в -2pi
class gen_research_sinline1 : public IGenerator
{
public:
	virtual int get_n()
	{
		return 2;
	}
	virtual int get_m()
	{
		return 2;
	}
	// Получить элемент вектора
	// Необходимо сразу учесть минус
	void get_F(vector<T>& F, vector<T>& x)
	{
		// y = sin(x)
		F[0] = -(sin(x[0]) - x[1]);
		F[1] = -(x[0] - x[1] + 2 * M_PI);
	}

	void get_J(vector<vector<T>>& J, vector<T>& x)
	{
		J[0][0] = cos(x[0]);
		J[0][1] = -1;
		J[1][0] = 1;
		J[1][1] = -1;
	}
};

// Синусоида и пересечение много раз
class gen_research_sinline2 : public IGenerator
{
public:
	virtual int get_n()
	{
		return 2;
	}
	virtual int get_m()
	{
		return 2;
	}
	// Получить элемент вектора
	// Необходимо сразу учесть минус
	void get_F(vector<T>& F, vector<T>& x)
	{
		// y = sin(x)
		F[0] = -(sin(x[0]) - x[1]);
		F[1] = -(0.1*x[0] - x[1]);
	}

	void get_J(vector<vector<T>>& J, vector<T>& x)
	{
		J[0][0] = cos(x[0]);
		J[0][1] = -1;
		J[1][0] = 0.1;
		J[1][1] = -1;
	}
};