#include "Matrix.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	vector<T> x({ 0.9, 0.9 });
	ofstream out("out.csv");
	int res = newton_solve(x, 0.001, Metrics::euclidean, 1, out);
	cout << "Done with " << res;
}