#include "Research.h"

using namespace std;

const int num_test = 3;

void do_research(vector<IGenerator*>& gens, vector<vector<T>>& start_x, string path)
{
	for (int i = 0; i < gens.size(); i++)
	{
		ofstream out(path + "out" + to_string(i) + ".csv");
		IGenerator* g = gens[i];
		out << "Iteration;beta;norm;";
		for (int i = 0; i < g->get_n(); i++)
			out << "x" << to_string(i) << ";";
		for (int i = 0; i < g->get_m(); i++)
			out << "F" << to_string(i) << "(xk);";
		out << endl;

		int res = newton_solve(start_x[i], 1e-3, Metrics::euclidean, *g, out);
		out << "res " << res;
		out.close();
	}
}

// Инициализировать генератор определенными объектами для теста или исследований.
// num_research = 
// 0 - 3 теста программы.
// 1 - окружности.
// 2 - окружности и линия.
// 3 - синус и прямая.
// 4 - три попарно пересекающихся прямых.
void initGen(vector<IGenerator*>& gen, int num_research)
{
	switch (num_research)
	{
	case 0:
		gen = { new gen_test1(), new gen_test2(), new gen_test3() };
		break;
	case 1:
		gen = { new gen_research1(), new gen_research2(), new gen_research3() };
		break;
	case 2:
		gen = { new gen_research1_line(), new gen_research2_line(), new gen_research3_line() };
		break;
	case 3:
		gen = { new gen_research_sinline2() };
		break;
	case 4:
		gen = { new gen_three_lines() };
		break;
	default:
		throw new exception();
	}
}

// Инициализировать начальные приближения для исследований.
// num_research = 
// 0 - 3 теста программы.
// 1 - окружности.
// 2 - окружности и линия.
// 3 - синус и прямая.
// 4 - три попарно пересекающихся прямых.
void initX(vector<vector<T>>& start_x, int num_research)
{
	switch (num_research)
	{
	case 0:
		start_x.resize(num_test);
		for (int i = 0; i < num_test; i++)
			start_x[i] = { 1, 1, 1 };
		break;
	case 1:
		start_x.resize(3);
		start_x[0] = { 1, 1 };
		start_x[1] = { 1, 1 };
		start_x[2] = { 1, 1 };
		break;
	case 2:
		start_x.resize(3);
		start_x[0] = { 1, 1 };
		start_x[1] = { 1, 1 };
		start_x[2] = { 1, 1 };
		break;
	case 3:
		start_x.resize(1);
		start_x[0] = { 1, 1 };
		break;
	case 4:
		
		break;
	default:
		throw new exception();
	}
}