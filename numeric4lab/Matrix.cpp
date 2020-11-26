#include "Matrix.h"


using namespace std;
T eps1 = 1e-15; // Ограничение для beta
int max_iter = 100;

// Определяем, какие компоненты delta_x нужно убрать
// и какие столбцы нужно исключить из матрицы А
// n - количество переменных, m - количество уравнений
void zero_components(vector<vector<T>>& A, int n, int m, vector<int>& res)
{
    if (n == m)
    {
        return;
    }
	vector<T>* max_abs = new vector<T>(n);
	// Ищем по всем векторам max(abs(elem)) минимальный столбец
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

	// n-m раз ищем минимальный элемент в векторе max_abs
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
		// Исключаем элемент из списка
		max_abs->erase(max_abs->begin() + index);
		res[i] = index;
	}
}

// Для решения СЛАУ Ax=-F
// Матрица n x n, в последнем столбце вектор функции
// 1 - успешно выполнено, 0, -1 - решения нет
int gauss(vector<vector<T>>& A, vector<T>& F, vector<T>& x)
{
    double EPS = 1e-14;
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

// Считает Евклидову норму вектора
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

// Матрица имеет размерность n x n+1
// x - начальное приближение. Туда же записывается ответ.
// eps2 - условие выхода из итерационного процесса. Частное нормы текущей итерации и предыдущей < eps2
// 1 - не нашлось beta, решение расходится
// -1 - количество итераций превысило разрешимое количество
// 0 - успех.
// IGenerator - интерфейс, реализующий генерацию вектора F и Якобиана. Переопределяется пользователем.
int newton_solve(vector<T>& x, T eps2, Metrics metric, IGenerator& gen, ostream &out)
{
    int iters = 0;
    int m = gen.get_m(), n = gen.get_n();
    int d = n - m;
    vector<int> comp(d);

    vector<T> Fk(m), F0(m), xk = x;
    vector<vector<T>> J(m);
    for (int i = 0; i < m; i++)
        J[i].resize(n);

    out.imbue(locale(""));

    while (iters < max_iter)
    {
        for (int i = 0; i < m; i++)
            J[i].resize(3);
        // Вычислим матрицу Якоби с текущим значением x
        gen.get_J(J, x);

        // Превратим матрицу в квадратную, убрав столбцы, дающие меньший вклад
        zero_components(J, n, m, comp);
        for (int i = 0; i < m; i++)
            for (int j = 0; j < d; j++)
                J[i].erase(J[i].begin() + comp[j]);

        // Вычислим правую часть (подставить xk в систему A и получить значения с каждой строки)
        // Генерируется с отрицательной правой частью
        gen.get_F(F0, x);

        // Найдем delta_x решением Jx = -F
        vector<T> buff_x(m);
        gauss(J, F0, buff_x);

        vector<T> delta_x(n, -1);
        // Занулим компоненты вектора, которые исключили для решения СЛАУ.
        for (auto& num : comp)
            delta_x[num] = 0;
        int с = 0;
        for (int i = 0; i < n; i++)
            if (delta_x[i] == -1)
                delta_x[i] = buff_x[с++];

        // Найдем beta
        T beta = 1;
        for (int i = 0; i < n; i++)
            xk[i] += beta * delta_x[i];

        gen.get_F(Fk, xk);
        // Пока норма правой части меньше текущей нормы
        T F0_norm = vector_norm(F0, metric);
        while (vector_norm(Fk, metric) > F0_norm)
        {
            xk = x;
            beta /= 2;
            for (int i = 0; i < n; i++)
                xk[i] += beta * delta_x[i];

            gen.get_F(Fk, xk);
            // условие выхода из итерации, к решению не сходится.
            if (beta < eps1)
                return 1;
        }
        
        // Новое приближение запишем в результирующий вектор
        x = xk;

        // Выведем на экран номер текущей итерации и beta   
        out << iters << ";" << beta << ";";
        T norm = vector_norm(Fk, metric);
        out << norm << ";";
        for (int i = 0; i < n; i++)
            out << x[i] << ";";
        for (int i = 0; i < m; i++)
            out << Fk[i] << ";";
        out << endl;

        // Решение найдено
        T norm0 = vector_norm(F0, metric);
        if (norm < 1e-30)
            return 0;
        if (norm / norm0 < eps2)
            return 0;

        iters++;
    }
    return -1;
}

