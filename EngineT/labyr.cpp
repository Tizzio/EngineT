#include "labyr.h"
#include "mesh.h"
#include "mesh_generator.h"

Labyr::Labyr()
{
	N = 0;
	M = 0;

	fstream fin_p;
	fin_p.open("data/labyr/pieces");
	if(!fin_p){
		cout << endl << "Missing pieces file" << endl << endl;
		return;
	}
	for(int i = 0; i < n_pieces; i++){

		pieces[i].id = i;
		fin_p >> pieces[i].A;
		fin_p >> pieces[i].B;
		fin_p >> pieces[i].C;
		fin_p >> pieces[i].D;
		fin_p >> pieces[i].E;
		fin_p >> pieces[i].F;
		fin_p >> pieces[i].G;
		fin_p >> pieces[i].H;
		fin_p >> pieces[i].I;

	}
	fin_p.close();

}


Labyr::~Labyr()
{

	for(int i = 0; i < N; i++){
		delete labyrinth[i];
	};
	delete labyrinth;
}


bool Labyr::set_difficulty(int a)
{

	difficulty_level = a;
	if(difficulty_level > 9) difficulty_level = 9;
	if(difficulty_level < 0) difficulty_level = 0;
	return true;

}

bool Labyr::set_dimensions(int n, int m)
{

	if((n < 25 || m < 25) || (n*m > dimensions_max))
	{
		return false;
	}
	else
	{

		N = n;
		M = m;
		return true;
	}

}

bool Labyr::set_dimensions_max(int a)
{
	if((a > 625) && (a < 255000000)){
		dimensions_max = a;
		return true;
	}
	else
	{
		return false;
	}
}

Mesh* Labyr::generate_mesh(float cellSize)
{
	/*RawMesh* raw_mesh = new RawMesh();
	RawMesh* roof_mesh = MeshGenerator::GenerateFloorGrid(labyrinth, N, M, cellSize, cellSize);
	raw_mesh->AddMesh(roof_mesh);
*/

	RawMesh* raw_mesh = MeshGenerator::GenerateFloorGrid(labyrinth, N, M, cellSize, cellSize, N, M);
	raw_mesh->Translate(vec3(0, 3.0f, 0));

	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < M; j++)
		{
			//hor
			if(!labyrinth[i][j] && labyrinth[i][j - 1])
			{
				RawMesh* rm = MeshGenerator::GenerateWall(cellSize, 0, 3, true);
				rm->Translate(vec3(i*cellSize, 0, j*cellSize));
				raw_mesh->AddMesh(rm);
				delete rm;
			}

			if(!labyrinth[i][j] && labyrinth[i][j + 1])
			{
				RawMesh* rm = MeshGenerator::GenerateWall(cellSize, 0, 3);
				rm->Translate(vec3(i*cellSize, 0, j*cellSize + cellSize));
				raw_mesh->AddMesh(rm);
				delete rm;
			}

			//ver
			if(!labyrinth[i][j] && labyrinth[i - 1][j])
			{
				RawMesh* rm = MeshGenerator::GenerateWall(0, cellSize, 3);
				rm->Translate(vec3(i*cellSize, 0, j*cellSize));
				raw_mesh->AddMesh(rm);
				delete rm;
			}


			if(!labyrinth[i][j] && labyrinth[i + 1][j])
			{
				RawMesh* rm = MeshGenerator::GenerateWall(0, cellSize, 3, true);
				rm->Translate(vec3(i*cellSize + cellSize, 0, j*cellSize));
				raw_mesh->AddMesh(rm);
				delete rm;
			}

			//move these out of this cycle to gain performances
			if(j == 0)
			{
				RawMesh* rm = MeshGenerator::GenerateWall(cellSize, 0, 3);
				rm->Translate(vec3(i*cellSize, 0, j*cellSize));
				raw_mesh->AddMesh(rm);
				delete rm;
			}
			else if(j == M - 1)
			{
				RawMesh* rm = MeshGenerator::GenerateWall(cellSize, 0, 3, true);
				rm->Translate(vec3(i*cellSize, 0, j*cellSize + cellSize));
				raw_mesh->AddMesh(rm);
				delete rm;
			}

			if(i == 0)
			{
				RawMesh* rm = MeshGenerator::GenerateWall(0, cellSize, 3, true);
				rm->Translate(vec3(i*cellSize, 0, j*cellSize));
				raw_mesh->AddMesh(rm);
				delete rm;
			}
			else if(i == M - 1)
			{
				RawMesh* rm = MeshGenerator::GenerateWall(0, cellSize, 3);
				rm->Translate(vec3(i*cellSize + cellSize, 0, j*cellSize));
				raw_mesh->AddMesh(rm);
				delete rm;
			}

		}
	}


	return raw_mesh->Finalize();
}
bool Labyr::build_labyrinth()
{
	critical[0] = new short[10000000];
	critical[1] = new short[10000000];

	srand((unsigned int) time(NULL));

	N = (N - (N % 3)) + 2;
	M = (M - (M % 3)) + 2;

	labyrinth = new int *[N];
	for(int i = 0; i < N; i++){
		labyrinth[i] = new int[M];
		for(int j = 0; j < M; j++){
			labyrinth[i][j] = 1;
		};
	};

	int current_piece = pick_piece();

	for(int i = 1; i < (N - 1); i = i + 3){
		for(int j = 1; j < (M - 1); j = j + 3){
			current_piece = next_piece(i, j, labyrinth);
			write_piece(i, j, labyrinth, pieces[current_piece]);
		}
	}

	int * critical_deck = new int[critical_i];
	for(int i = 0; i < critical_i; i++){
		critical_deck[i] = i;
	}


	std::random_shuffle(&critical_deck[0], &critical_deck[critical_i - 1]);

	start_eta = clock();

	for(int j = 0; j < critical_i; j++){
		labyrinth[2][0] = 1;
		labyrinth[2][1] = 1;

		if(j % 100 == 0){
			end_eta = clock();
			eta = (((double) (end_eta - start_eta) / CLOCKS_PER_SEC) / j)*(critical_i - j);
		}
		int i = critical_deck[j];

		if(!connection_check(critical[0][i], critical[1][i], N, M, labyrinth)){

			if(critical[0][i] > 2){
				if(critical[1][i] < 3){
					labyrinth[critical[0][i] - 1][critical[1][i]] = 0;
					labyrinth[critical[0][i] - 2][critical[1][i]] = 0;
				}
				else {

					int coin = rand() % 2;
					if(coin == 0){
						labyrinth[critical[0][i] - 1][critical[1][i]] = 0;
						labyrinth[critical[0][i] - 2][critical[1][i]] = 0;

					}
					else {
						labyrinth[critical[0][i]][critical[1][i] - 1] = 0;
						labyrinth[critical[0][i]][critical[1][i] - 2] = 0;

					}

				}
			}
			else {
				labyrinth[critical[0][i]][critical[1][i] - 1] = 0;
				labyrinth[critical[0][i]][critical[1][i] - 2] = 0;
			}
		}

	}

	decolor(N, M, labyrinth);
	labyrinth[2][0] = 1;
	labyrinth[2][1] = 1;

	delete critical[0];
	delete critical[1];
	return true;
}

bool Labyr::set_start_goal()
{

	srand((unsigned int) time(NULL));

	while((int) std::sqrt(std::pow((abs(start_i - goal_i)), 2) + std::pow((abs(start_j - goal_j)), 2)) < (int) std::sqrt(std::pow(1 * (N / 2), 2) + std::pow(1 * (M / 2), 2)))
	{
		srand(time(NULL));
		start_i = 0;
		start_j = 0;
		goal_i = 0;
		goal_j = 0;
		int zone = rand() % 4;
		while(labyrinth[start_i][start_j] == 1){
			switch(zone){
			case(0) :
				start_i = (rand() % (N / 3 - 2)) + 1;
				start_j = (rand() % (M / 3 - 2)) + 1;
				break;
			case(1) :
				start_i = (rand() % (N / 3 - 2)) + 1;
				start_j = (rand() % (M / 3 - 2)) + ((2 * M) / 3) + 1;
				break;
			case(2) :
				start_i = (rand() % (N / 3 - 2)) + ((2 * N) / 3) + 1;
				start_j = (rand() % (M / 3 - 2)) + 1;
				break;
			case(3) :
				start_i = (rand() % (N / 3 - 2)) + ((2 * N) / 3) + 1;
				start_j = (rand() % (M / 3 - 2)) + ((2 * M) / 3) + 1;
				break;

			}
		}

		while(labyrinth[goal_i][goal_j] == 1 || !check_neighbor(goal_i, goal_j, labyrinth)){
			switch(zone){
			case(3) :
				goal_i = (rand() % (N / 3 - 2)) + 1;
				goal_j = (rand() % (M / 3 - 2)) + 1;
			case(1) :
				goal_i = (rand() % (N / 3 - 2)) + ((2 * N) / 3) + 1;
				goal_j = (rand() % (M / 3 - 2)) + 1;
			case(2) :
				goal_i = (rand() % (N / 3 - 2)) + 1;
				goal_j = (rand() % (M / 3 - 2)) + ((2 * M) / 3) + 1;
			case(0) :
				goal_i = (rand() % (N / 3 - 2)) + ((2 * N) / 3) + 1;
				goal_j = (rand() % (M / 3 - 2)) + ((2 * M) / 3) + 1;
			}

		}
	}

	labyrinth[start_i][start_j] = 2;
	labyrinth[goal_i][goal_j] = 3;

	return true;
}

void Labyr::decolor(int N, int M, int** labyrinth)
{
	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			if(labyrinth[i][j] >= 5) labyrinth[i][j] = 0;
		}
	}
	return;
}

void Labyr::next_step(int x, int y, int** labyrinth, int depth)
{
	depth++;
	labyrinth[x][y] = step;

	if(x == goal_x && y == goal_y) check_ok = true;
	if(check_ok) return;

	if(depth < depth_max){
		if(labyrinth[x - 1][y] != 1 && labyrinth[x - 1][y] != step) next_step(x - 1, y, labyrinth, depth);
		if(labyrinth[x][y + 1] != 1 && labyrinth[x][y + 1] != step) next_step(x, y + 1, labyrinth, depth);
		if(labyrinth[x + 1][y] != 1 && labyrinth[x + 1][y] != step) next_step(x + 1, y, labyrinth, depth);
		if(labyrinth[x][y - 1] != 1 && labyrinth[x][y - 1] != step) next_step(x, y - 1, labyrinth, depth);
	}
	return;


}

bool Labyr::connection_check(int x, int y, int N, int M, int** labyrinth)
{

	check_ok = false;
	if(step > 10000) {
		step = 5;
		decolor(N, M, labyrinth);
	}


	int goal_x1 = x - 3;
	int goal_y1 = y;

	int goal_x2 = x;
	int goal_y2 = y - 3;
	int depth_stop = (int) (50 + std::pow(2, difficulty_level));

	if(goal_x1 > 1){
		goal_x = goal_x1;
		goal_y = goal_y1;
		while(depth_max < depth_stop){
			next_step(x, y, labyrinth, 15);
			depth_max += 5;
			if(check_ok) break;
			step++;
		}
	}


	depth_max = 0;


	if(goal_y2 > 1 && !check_ok){
		goal_x = goal_x2;
		goal_y = goal_y2;
		while(depth_max < depth_stop){
			next_step(x, y, labyrinth, 15);
			depth_max += 5;
			if(check_ok) break;
			step++;
		}
	}


	return check_ok;


}

int Labyr::pick_piece()
{


	int x = (rand() % 1000);

	if(x >= 0 && x < 10){
		x = 6;
	}
	else if(x >= 10 && x < 90){
		x = (x % 4) + 2;
	}
	else if(x >= 90 && x < 400){
		x = (x % 8) + 7;
	}
	else if(x >= 400 && x < 1000){
		x = (x % 2);
	}


	return x;
}

int Labyr::next_piece(int x, int y, int** labyrinth)
{

	bool ok = false;
	int next_piece;

	int face_up = labyrinth[x - 1][y + 1];
	int face_left = labyrinth[x + 1][y - 1];


	while(!ok) {
		next_piece = pick_piece();
		if(
			pieces[next_piece].B == face_up &&
			pieces[next_piece].D == face_left
			)
			ok = true;
	}
	if(face_up == 1 && face_left == 1){

		critical[0][critical_i] = x + 1;
		critical[1][critical_i] = y + 1;
		critical_i++;
	}

	return next_piece;
}

void Labyr::write_piece(int x, int y, int** labyrinth, piece current_piece)
{

	labyrinth[x][y] = current_piece.A;
	labyrinth[x][y + 1] = current_piece.B;
	labyrinth[x][y + 2] = current_piece.C;
	labyrinth[x + 1][y] = current_piece.D;
	labyrinth[x + 1][y + 1] = current_piece.E;
	labyrinth[x + 1][y + 2] = current_piece.F;
	labyrinth[x + 2][y] = current_piece.G;
	labyrinth[x + 2][y + 1] = current_piece.H;
	labyrinth[x + 2][y + 2] = current_piece.I;


	return;
}

bool Labyr::check_neighbor(int x, int y, int ** labyrinth)
{

	int check = 0;

	if(labyrinth[x - 1][y] == 0) check++;
	if(labyrinth[x][y - 1] == 0) check++;
	if(labyrinth[x + 1][y] == 0) check++;
	if(labyrinth[x][y + 1] == 0) check++;

	if(check == 1) return true;
	else return false;
}