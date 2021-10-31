#include "ECE_Map.h"

#include <string.h>

#ifdef _WIN32
#include <Windows.h>
#endif // __WIN32

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h> // Fucking garbage API, go back to 2001.

// Initial Grid
/*
* Cols = 19
* Rows = 22
* GridElement[][]
* 0 - Empty Space
* 1 - Coin
* 2 - Power Up
* 3 - Player Start // IGNORE
* 4 - Ghost Wall
* 5 - Generic Wall
* 6 - Teleporter
* 
* 0 - Empty Space
* 1 - Generic Wall
* 2 - Ghost Wall
* 3 - Coin
* 4 - Powerup
*/
//static const int GridElement[22][19] = {
//	{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
//	{5, 1, 1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 5},
//	{5, 2, 5, 5, 1, 5, 5, 5, 1, 5, 1, 5, 5, 5, 1, 5, 5, 2, 5},
//	{5, 1, 5, 5, 1, 5, 5, 5, 1, 5, 1, 5, 5, 5, 1, 5, 5, 1, 5},
//	{5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5},
//	{5, 1, 5, 5, 1, 5, 1, 5, 5, 5, 5, 5, 1, 5, 1, 5, 5, 1, 5},
//	{5, 1, 1, 1, 1, 5, 1, 1, 1, 5, 1, 1, 1, 5, 1, 1, 1, 1, 5},
//	{5, 5, 5, 5, 1, 5, 5, 5, 0, 5, 0, 5, 5, 5, 1, 5, 5, 5, 5},
//	{0, 0, 0, 5, 1, 5, 0, 0, 0, 0, 0, 0, 0, 5, 1, 5, 0, 0, 0},
//	{5, 5, 5, 5, 1, 5, 0, 5, 5, 4, 5, 5, 0, 5, 1, 5, 5, 5, 5},
//	{0, 0, 0, 0, 1, 0, 0, 5, 0, 0, 0, 5, 0, 0, 1, 0, 0, 0, 0}, /* tunnel */
//	{5, 5, 5, 5, 1, 5, 0, 5, 5, 5, 5, 5, 0, 5, 1, 5, 5, 5, 5},
//	{0, 0, 0, 5, 1, 5, 0, 0, 0, 0, 0, 0, 0, 5, 1, 5, 0, 0, 0},
//	{5, 5, 5, 5, 1, 5, 0, 5, 5, 5, 5, 5, 0, 5, 1, 5, 5, 5, 5},
//	{5, 1, 1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 5},
//	{5, 1, 5, 5, 1, 5, 5, 5, 1, 5, 1, 5, 5, 5, 1, 5, 5, 1, 5},
//	{5, 2, 1, 5, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 5, 1, 2, 5},
//	{5, 5, 1, 5, 1, 5, 1, 5, 5, 5, 5, 5, 1, 5, 1, 5, 1, 5, 5},
//	{5, 1, 1, 1, 1, 5, 1, 1, 1, 5, 1, 1, 1, 5, 1, 1, 1, 1, 5},
//	{5, 1, 5, 5, 5, 5, 5, 5, 1, 5, 1, 5, 5, 5, 5, 5, 5, 1, 5},
//	{5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5},
//	{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}
//};

// Initial Grid
/*
* Cols = 19
* Rows = 22
* GridElement[][]
*
* 0 - Empty Space
* 1 - Generic Wall
* 2 - Ghost Wall
* 3 - Coin
* 4 - Powerup
* 5 - Teleport
*/
static const int GridElement[22][19] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 1},
	{1, 4, 1, 1, 3, 1, 1, 1, 3, 1, 3, 1, 1, 1, 3, 1, 1, 4, 1},
	{1, 3, 1, 1, 3, 1, 1, 1, 3, 1, 3, 1, 1, 1, 3, 1, 1, 3, 1},
	{1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1},
	{1, 3, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 3, 1},
	{1, 3, 3, 3, 3, 1, 3, 3, 3, 1, 3, 3, 3, 1, 3, 3, 3, 3, 1},
	{1, 1, 1, 1, 3, 1, 1, 1, 0, 1, 0, 1, 1, 1, 3, 1, 1, 1, 1},
	{0, 0, 0, 1, 3, 1, 0, 0, 0, 0, 0, 0, 0, 1, 3, 1, 0, 0, 0},
	{1, 1, 1, 1, 3, 1, 0, 1, 1, 2, 1, 1, 0, 1, 3, 1, 1, 1, 1},
	{5, 0, 0, 0, 3, 0, 0, 1, 0, 0, 0, 1, 0, 0, 3, 0, 0, 0, 5}, /* tunnel */
	{1, 1, 1, 1, 3, 1, 0, 1, 1, 1, 1, 1, 0, 1, 3, 1, 1, 1, 1},
	{0, 0, 0, 1, 3, 1, 0, 0, 0, 0, 0, 0, 0, 1, 3, 1, 0, 0, 0},
	{1, 1, 1, 1, 3, 1, 0, 1, 1, 1, 1, 1, 0, 1, 3, 1, 1, 1, 1},
	{1, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 1},
	{1, 3, 1, 1, 3, 1, 1, 1, 3, 1, 3, 1, 1, 1, 3, 1, 1, 3, 1},
	{1, 4, 3, 1, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3, 1, 3, 4, 1},
	{1, 1, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 1},
	{1, 3, 3, 3, 3, 1, 3, 3, 3, 1, 3, 3, 3, 1, 3, 3, 3, 3, 1},
	{1, 3, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 3, 1},
	{1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

//static const int GridElement[22][19] = {
//	{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
//	{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
//	{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
//	{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
//	{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
//	{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
//	{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
//	{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
//	{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
//	{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
//	{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}, /* tunnel */
//	{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
//	{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
//	{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
//	{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
//	{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
//	{3, 3, 1, 1, 1, 1, 1, 1, 3, 3, 3, 1, 1, 1, 1, 1, 1, 3, 3},
//	{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
//	{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
//	{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
//	{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
//	{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}
//};

ECE_Map::ECE_Map() {
	memcpy(this->Tile, GridElement, 22 * 19 * sizeof(int));
	//this->PowerUpTaken = false; // This will set the ghosts in frightened mode.
}

ECE_Map::~ECE_Map() {

}

int ECE_Map::update(double dt) {
	//if (PowerUpTaken) {
	//	if (PowerUpTimer <= 5.0) {
	//		PowerUpTimer += dt;
	//	}
	//	else {
	//		// Resets once 
	//		PowerUpTimer = 0.0;
	//		PowerUpTaken = false;
	//	}
	//}
	return 0;
}

int ECE_Map::draw(ECE_Camera Cam) {

	this->draw_maze(Cam);

	for (int x = -9; x < 10; x++) {
		for (int y = -11; y < 11; y++) {
			// i = 10, j = 9 at origin.
			//math::real3 ePos = math::real3(10 - i, 9 - j, 0);
			//math::real4x4 temp = Cam.get_transform(math::real3(9 - y, 10 - x, 0));
			math::real4x4 temp = Cam.get_transform(math::real3(x, y, 0));

			//switch (this->Tile[i][j]) {
			switch (this->get_element(x, y)) {
				//switch (GridElement[i][j]) {
			default:
				break;
			case COIN:
				// Draw Coin
				glLoadMatrixf(temp.ptr);
				glColor3f(0.90196f, 0.90980f, 0.98039f);
				glutSolidSphere(0.1, 10, 10);
				break;
			case POWER_UP:
				// Draw Power Up
				glLoadMatrixf(temp.ptr);
				glScalef(1.0, 1.0, 0.3);
				glColor3f(1.00000f, 0.84314f, 0.00000f);
				//glColor3f(0.93333f, 0.90980f, 0.82353f);
				//glColor3f(0.81176f, 0.70980f, 0.21569f);
				glutSolidSphere(0.3, 10, 10);
				break;
			case GENERIC_WALL:
				// Add softening spheres to grid
				glLoadMatrixf(temp.ptr);
				glColor3f(0.0, 0.5, 0.8);
				glutSolidSphere(0.1, 10, 10);
				break;
			}
		}
	}

	return 0;
}

int ECE_Map::get_element(int X, int Y) {
	//int i = -Y + 16;
	int i = -Y + 10;
	int j = X + 9;
	if ((i >= 0) && (i < 22) && (j >= 0) && (j < 19)) {
		return this->Tile[i][j];
	}
	else {
		return 0;
	}
}

int ECE_Map::set_element(int X, int Y, int Arg) {
	//int i = -Y + 16;
	int i = -Y + 10;
	int j = X + 9;
	if ((i >= 0) && (i < 22) && (j >= 0) && (j < 19)) {
		this->Tile[i][j] = Arg;
		return 0;
	}
	else {
		return -1;
	}
}

int ECE_Map::reset() {
	memcpy(this->Tile, GridElement, 22 * 19 * sizeof(int));
	return 0;
}

bool ECE_Map::check() {
	bool temp = false;
	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 19; j++) {
			if ((this->Tile[i][j] == COIN) || (this->Tile[i][j] == POWER_UP)) {
				temp = true;
				break;
			}
		}
		if (temp) break;
	}
	return !temp;
}

void ECE_Map::draw_maze(const ECE_Camera& c) {
	// Ghost Start Section
	this->draw_grid_piece(c, math::real3(1, 1, 0), math::real3(2, 1, 0));
	this->draw_grid_piece(c, math::real3(2, 1, 0), math::real3(2, -1, 0));
	this->draw_grid_piece(c, math::real3(2, -1, 0), math::real3(-2, -1, 0));
	this->draw_grid_piece(c, math::real3(-2, -1, 0), math::real3(-2, 1, 0));
	this->draw_grid_piece(c, math::real3(-2, 1, 0), math::real3(-1, 1, 0));
	this->draw_grid_piece(c, math::real3(-2, -3, 0), math::real3(2, -3, 0));
	this->draw_grid_piece(c, math::real3(0, -5, 0), math::real3(0, -3, 0));
	this->draw_grid_piece(c, math::real3(-2, -7, 0), math::real3(2, -7, 0));
	this->draw_grid_piece(c, math::real3(0, -9, 0), math::real3(0, -7, 0));
	this->draw_grid_piece(c, math::real3(-2, 5, 0), math::real3(2, 5, 0));
	this->draw_grid_piece(c, math::real3(0, 3, 0), math::real3(0, 5, 0));
	this->draw_grid_piece(c, math::real3(0, 7, 0), math::real3(0, 10, 0));
	this->draw_grid_piece(c, math::real3(-9, 10, 0), math::real3(9, 10, 0));
	this->draw_grid_piece(c, math::real3(2, 8, 0), math::real3(4, 8, 0));
	this->draw_grid_piece(c, math::real3(2, 7, 0), math::real3(4, 7, 0));
	this->draw_grid_piece(c, math::real3(2, 7, 0), math::real3(2, 8, 0));
	this->draw_grid_piece(c, math::real3(4, 7, 0), math::real3(4, 8, 0));
	this->draw_grid_piece(c, math::real3(6, 8, 0), math::real3(7, 8, 0));
	this->draw_grid_piece(c, math::real3(6, 7, 0), math::real3(7, 7, 0));
	this->draw_grid_piece(c, math::real3(6, 7, 0), math::real3(6, 8, 0));
	this->draw_grid_piece(c, math::real3(7, 7, 0), math::real3(7, 8, 0));
	this->draw_grid_piece(c, math::real3(-2, 8, 0), math::real3(-4, 8, 0));
	this->draw_grid_piece(c, math::real3(-2, 7, 0), math::real3(-4, 7, 0));
	this->draw_grid_piece(c, math::real3(-2, 7, 0), math::real3(-2, 8, 0));
	this->draw_grid_piece(c, math::real3(-4, 7, 0), math::real3(-4, 8, 0));
	this->draw_grid_piece(c, math::real3(-6, 8, 0), math::real3(-7, 8, 0));
	this->draw_grid_piece(c, math::real3(-6, 7, 0), math::real3(-7, 7, 0));
	this->draw_grid_piece(c, math::real3(-6, 7, 0), math::real3(-6, 8, 0));
	this->draw_grid_piece(c, math::real3(-7, 7, 0), math::real3(-7, 8, 0));
	this->draw_grid_piece(c, math::real3(-9, 3, 0), math::real3(-9, 10, 0));
	this->draw_grid_piece(c, math::real3(9, 3, 0), math::real3(9, 10, 0));
	this->draw_grid_piece(c, math::real3(-9, -3, 0), math::real3(-9, -11, 0));
	this->draw_grid_piece(c, math::real3(9, -3, 0), math::real3(9, -11, 0));
	this->draw_grid_piece(c, math::real3(6, 5, 0), math::real3(7, 5, 0));
	this->draw_grid_piece(c, math::real3(-6, 5, 0), math::real3(-7, 5, 0));
	this->draw_grid_piece(c, math::real3(4, 1, 0), math::real3(4, 5, 0));
	this->draw_grid_piece(c, math::real3(-4, 1, 0), math::real3(-4, 5, 0));
	this->draw_grid_piece(c, math::real3(2, 3, 0), math::real3(4, 3, 0));
	this->draw_grid_piece(c, math::real3(-2, 3, 0), math::real3(-4, 3, 0));
	this->draw_grid_piece(c, math::real3(6, 3, 0), math::real3(9, 3, 0));
	this->draw_grid_piece(c, math::real3(-6, 3, 0), math::real3(-9, 3, 0));
	this->draw_grid_piece(c, math::real3(6, 1, 0), math::real3(9, 1, 0));
	this->draw_grid_piece(c, math::real3(-6, 1, 0), math::real3(-9, 1, 0));
	this->draw_grid_piece(c, math::real3(6, 1, 0), math::real3(6, 3, 0));
	this->draw_grid_piece(c, math::real3(-6, 1, 0), math::real3(-6, 3, 0));
	this->draw_grid_piece(c, math::real3(6, -3, 0), math::real3(9, -3, 0));
	this->draw_grid_piece(c, math::real3(-6, -3, 0), math::real3(-9, -3, 0));
	this->draw_grid_piece(c, math::real3(6, -1, 0), math::real3(9, -1, 0));
	this->draw_grid_piece(c, math::real3(-6, -1, 0), math::real3(-9, -1, 0));
	this->draw_grid_piece(c, math::real3(6, -1, 0), math::real3(6, -3, 0));
	this->draw_grid_piece(c, math::real3(-6, -1, 0), math::real3(-6, -3, 0));
	this->draw_grid_piece(c, math::real3(-9, -11, 0), math::real3(9, -11, 0));
	this->draw_grid_piece(c, math::real3(4, -1, 0), math::real3(4, -3, 0));
	this->draw_grid_piece(c, math::real3(-4, -1, 0), math::real3(-4, -3, 0));
	this->draw_grid_piece(c, math::real3(-2, -5, 0), math::real3(-4, -5, 0));
	this->draw_grid_piece(c, math::real3(2, -5, 0), math::real3(4, -5, 0));
	this->draw_grid_piece(c, math::real3(6, -5, 0), math::real3(7, -5, 0));
	this->draw_grid_piece(c, math::real3(-6, -5, 0), math::real3(-7, -5, 0));
	this->draw_grid_piece(c, math::real3(6, -5, 0), math::real3(6, -7, 0));
	this->draw_grid_piece(c, math::real3(-6, -5, 0), math::real3(-6, -7, 0));
	this->draw_grid_piece(c, math::real3(8, -7, 0), math::real3(9, -7, 0));
	this->draw_grid_piece(c, math::real3(-8, -7, 0), math::real3(-9, -7, 0));
	this->draw_grid_piece(c, math::real3(2, -9, 0), math::real3(7, -9, 0));
	this->draw_grid_piece(c, math::real3(-2, -9, 0), math::real3(-7, -9, 0));
	this->draw_grid_piece(c, math::real3(4, -9, 0), math::real3(4, -7, 0));
	this->draw_grid_piece(c, math::real3(-4, -9, 0), math::real3(-4, -7, 0));
}

void ECE_Map::draw_grid_piece(const ECE_Camera& Camera, math::real3 p1, math::real3 p2) {

	// This generates the perspective matrix.
	math::real4x4 Pers = math::perspective(Camera.FOV, (double)Camera.Width / (double)Camera.Height, 1.0, 100.0);

	// This rotates the vertex to the camera.
	math::real4x4 Rot = math::real4x4(
		Camera.Right.x, Camera.Right.y, Camera.Right.z, 0.0,
		Camera.Up.x, Camera.Up.y, Camera.Up.z, 0.0,
		Camera.Forward.x, Camera.Forward.y, Camera.Forward.z, 0.0,
		0.0, 0.0, 0.0, 1.0
	);

	// This translates the vertex to the camera coordinate space.
	math::real4x4 Trans = math::real4x4(
		1.0, 0.0, 0.0, (p1.x - Camera.Pos.x),
		0.0, 1.0, 0.0, (p1.y - Camera.Pos.y),
		0.0, 0.0, 1.0, (p1.z - Camera.Pos.z),
		0.0, 0.0, 0.0, 1.0
	);

	//math::real4x4 RR = math::rotation(math::deg2rad(180), math::real3(1, 0, 0));
	math::real4x4 RR = math::rotation(math::deg2rad(90), math::normalize(math::real3(0, 0, 1) ^ (p2 - p1)));
	math::real4x4 T = Pers * Rot * Trans * RR;
	//math::real4x4 T = Camera.get_transform(p1) * RR;

	glLoadMatrixf(T.ptr);
	glColor3f(0.0, 0.5, 0.8);
	GLUquadricObj* Obj = gluNewQuadric();
	gluCylinder(Obj, 0.1, 0.1, math::length(p2 - p1), 10, 10);
	gluQuadricDrawStyle(Obj, GLU_LINE);
	gluDeleteQuadric(Obj);
}