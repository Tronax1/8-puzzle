#include "Puzzle.h"
#include <iostream>

puzzle::puzzle() {
	board = new int*[3];
	for (int i = 0; i < 3; i++) {
		board[i] = new int[3];
		for (int j = 0; j < 3; j++) {
			board[i][j] = 0;
		}
	}
}
void puzzle::add_tile(int i, int j, int value) {
	board[i][j] = value;
}
void puzzle::to_string() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			std::cout << board[i][j];
		}
		std::cout << std::endl;
	}
}
puzzle::~puzzle() {
	for (int i = 0; i < 3; i++) 
		delete[] board[i];
	delete[] board;
}