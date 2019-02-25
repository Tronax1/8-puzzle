#include <iostream>
#include <stdio.h>
#include <fstream>
#include "Puzzle.h"

using namespace std;

int main() {

	ifstream myFile;
	int tile = 0;
	puzzle board_game;

	myFile.open("Input.txt");
	if (!myFile) {
		cout << "Error opening file" << endl;
		exit(1);
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			myFile >> tile;
			board_game.add_tile(i, j, tile);
		}
	}
	myFile.close();
	board_game.to_string();
	cout << "The shortest path cost is:" << board_game.A_star() << endl;
	return 0;
}