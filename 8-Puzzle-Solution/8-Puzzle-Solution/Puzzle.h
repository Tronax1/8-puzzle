#pragma once
#ifndef PUZZLE
#define PUZZLE
#include <vector>

class puzzle {

private:
	int **board;
	int solution[3][3] = {
		{1,2,3},
		{8,0,4},
		{7,6,5}
	};
public:
	puzzle();
	int distance(int **state, int i, int j); //Helper function for heuristic
	int heuristic(int **state);
	int A_star();
	bool is_solution(int **state);
	void legal_moves(std::vector<int> &vect, std::vector<std::vector<int>> &matrix, int **state, int i, int j);
	void add_state(std::vector<int> &vect, int **state, int heuristics);
	void add_tile(int i, int j, int value);
	void to_string();
	~puzzle();
};

#endif

