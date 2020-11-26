#pragma once
#include "Matrix.h"

void do_research(vector<IGenerator*>& gens, vector<vector<T>>& start_x, string path);

void initGen(vector<IGenerator*>& gen, int num_research);

void initX(vector<vector<T>>& start_x, int num_research);