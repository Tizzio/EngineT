#pragma once


#include "engine_t.h"
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <time.h>

#define n_pieces 15

struct piece{
	int id;
	int A, B, C;
	int D, E, F;
	int G, H, I;
	int c_up[3];
	int c_right[3];
	int c_down[3];
	int c_left[3];
};

using namespace EngineT;

class Labyr
{
public:

	int **labyrinth;
	double eta;
	int N;
	int M;
	int start_i = 0, start_j = 0;
	int goal_i = 0, goal_j = 0;

	Labyr();
	~Labyr();
	bool set_difficulty(int a);
	bool set_dimensions(int n, int m);
	bool set_dimensions_max(int a);
	Mesh* generate_mesh(float cellSize = 1);
	bool build_labyrinth();
	bool set_start_goal();

private:

	clock_t start_eta, end_eta;

	int dimensions_max = 255000000;
	short *critical[2];
	int critical_i = 0;


	struct piece pieces[n_pieces];

	const int WALL = 1;
	const int START = 2;
	const int STOP = 3;
	int difficulty_level = 0;
	int depth_max;
	int goal_x;
	int goal_y;
	int step = 5;
	bool check_ok = false;

	void decolor(int N, int M, int** labyrinth);
	void next_step(int x, int y, int** labyrinth, int depth);
	bool connection_check(int x, int y, int N, int M, int** labyrinth);
	int pick_piece();
	int next_piece(int x, int y, int** labyrinth);
	void write_piece(int x, int y, int** labyrinth, piece current_piece);
	bool check_neighbor(int x, int y, int ** labyrinth);
};

