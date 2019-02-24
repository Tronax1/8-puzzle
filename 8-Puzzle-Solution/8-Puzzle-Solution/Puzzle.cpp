#include "Puzzle.h"
#include <iostream>
#include <cstdlib>

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
				value_row = i - k;
				value_column = j - l;
				return abs(value_row + value_column);
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
	int test_h = heuristic(board);
	return test_h;
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