#pragma once
#ifndef PUZZLE
#define PUZZLE

class puzzle {

private:
	int **board;
public:
	puzzle();
	void add_tile(int i, int j, int value);
	void to_string();
	~puzzle();
};

#endif

