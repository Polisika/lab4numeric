#include "Matrix.h"
#include <iostream>
using namespace std;

int main()
{
	vector<T> x({ 0.9, 0.9 });
	int res = newton_solve(x, 0.001, Metrics::max, 1);
	cout << "Done with " << res;
}