#include "Matrix.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	vector<T> x({ 0.9, 0.9 });
	gen_test2 test;
	vector<IGenerator*> v({&test});
	int res = newton_solve(x, 1e-3, Metrics::euclidean, *v[0], std::cout);
	cout << "Done with " << res;
}