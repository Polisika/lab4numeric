#include "Research.h"
#include <fstream>
using namespace std;

int main()
{
	vector<IGenerator*> gens;
	initGen(gens, 0);
	vector<vector<T>> start_x;
	initX(start_x, 0);
	do_research(gens, start_x, "test/");
}