#include "Matrix.h"

using namespace std;

void do_research(vector<IGenerator*>& gens, vector<vector<T>>& start_x, string path)
{
	for (int i = 0; i < gens.size(); i++)
	{
		ofstream out(path + "out" + to_string(i) + ".csv");
		IGenerator* g = gens[i];
		out << "Iteration;beta;norm;";
		for (int i = 0; i < g->get_n(); i++)
			out << "x" << to_string(i) << ";";
		out << endl;

		newton_solve(start_x[i], 1e-3, Metrics::euclidean, *g, out);
	}
}