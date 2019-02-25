#include "Puzzle.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>

puzzle::puzzle() {
	board = new int*[3];
	for (int i = 0; i < 3; i++) {
		board[i] = new int[3];
		for (int j = 0; j < 3; j++) {
			board[i][j] = 0;
		}
	}
}
int puzzle::distance(int **state, int i, int j) {
	int target_value = state[i][j];
	int value_row = 0;
	int value_column = 0;
	for (int k = 0; k < 3; k++) {
		for (int l = 0; l < 3; l++) {
			if (target_value == solution[k][l]) {
				value_row = pow(i - k,2);
				value_column = pow(j - l,2);
				return sqrt(value_row + value_column);
			}
		}
	}
}
int puzzle::heuristic(int **state) {
	int h_val = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (state[i][j] != solution[i][j]) {
				h_val += distance(state, i, j);
			}
		}
	}
	return h_val;
}
int puzzle::A_star() {
	int cost = 0;

	std::vector<int> state;
	std::vector<int> lowest_heuristics;
	std::vector<std::vector<int>> set;

	while (!is_solution(board)) {
		cost++;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (board[i][j] == 0) {
					legal_moves(state, set, board, i, j);
				}
			}
		}
		for (int i = 0; i < 9; i++) {
			lowest_heuristics.push_back(set[0][i]);
		}
		lowest_heuristics.pop_back();
		int elements = 0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (elements < 8) {
					board[i][j] = lowest_heuristics[elements];
					elements++;
				}
			}
		}
		lowest_heuristics.clear();
		set.clear();
	}
	return cost;
}
bool puzzle::is_solution(int **state) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (state[i][j] != solution[i][j])
				return false;
		}
	}
	return true;
}
void puzzle::legal_moves(std::vector<int> &vect, std::vector<std::vector<int>> &matrix, int **state, int i, int j) {
	int temp = 0;
	int h_cost = 0;
	int starting_state[3][3];
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			starting_state[i][j] = state[i][j];//Keep record of the starting state
		}
	}
	if (i + 1 < 3) {
		temp = state[i][j];
		state[i][j] = state[i + 1][j];
		state[i + 1][j] = temp;
		h_cost = heuristic(state);
		add_state(vect, state, h_cost);
		matrix.push_back(vect);
		vect.clear();
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				state[i][j] = starting_state[i][j];
			}
		}
	}
	if (i - 1 > -1) {
		temp = state[i][j];
		state[i][j] = state[i - 1][j];
		state[i - 1][j] = temp;
		h_cost = heuristic(state);
		add_state(vect, state, h_cost);
		if(!matrix.empty() && vect[9] <= matrix[0][9])
			matrix.insert(matrix.begin(),vect);
		else matrix.push_back(vect);
		vect.clear();
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				state[i][j] = starting_state[i][j];
			}
		}
	}
	if (j + 1 < 3) {
		temp = state[i][j];
		state[i][j] = state[i][j+1];
		state[i][j+1] = temp;
		h_cost = heuristic(state);
		add_state(vect, state, h_cost);
		if (!matrix.empty() && vect[9] <= matrix[0][9])
			matrix.insert(matrix.begin(), vect);
		else matrix.push_back(vect);
		vect.clear();
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				state[i][j] = starting_state[i][j];
			}
		}
	}
	if (j - 1 > -1) {
		temp = state[i][j];
		state[i][j] = state[i][j-1];
		state[i][j-1] = temp;
		h_cost = heuristic(state);
		add_state(vect, state, h_cost);
		if (!matrix.empty() && vect[9] <= matrix[0][9])
			matrix.insert(matrix.begin(), vect);
		else matrix.push_back(vect);
		vect.clear();
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				state[i][j] = starting_state[i][j];
			}
		}
	}
}
void puzzle::add_state(std::vector<int> &vect, int **state, int heuristics) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			vect.push_back(state[i][j]);
		}
	}
	vect.push_back(heuristics);
}
void puzzle::add_tile(int i, int j, int value) {
	board[i][j] = value;
}
void puzzle::to_string() {
	std::cout << "The starting state is: " << std::endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			std::cout << board[i][j]<<" ";
		}
		std::cout << std::endl;
	}
	std::cout << "The goal state is:" << std::endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			std::cout << solution[i][j]<<" ";
		}
		std::cout << std::endl;
	}
}
puzzle::~puzzle() {
	for (int i = 0; i < 3; i++) 
		delete[] board[i];
	delete[] board;
}