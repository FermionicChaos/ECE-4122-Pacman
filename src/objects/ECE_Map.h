#pragma once
#ifndef ECE_MAP_H
#define ECE_MAP_H

#include "ECE_Camera.h"

class ECE_Map {
public:

	//enum Element {
	//	EMPTY_SPACE		= 0,
	//	COIN			= 1,
	//	POWER_UP		= 2,
	//	PLAYER_START	= 3,
	//	GHOST_WALL		= 4,
	//	GENERIC_WALL	= 5
	//};

	enum Element {
		EMPTY_SPACE		= 0,
		GENERIC_WALL	= 1,
		GHOST_WALL		= 2,
		COIN			= 3,
		POWER_UP		= 4,
		TELEPORT		= 5
		//PLAYER_START	= 3,
	};

	const int Row = 22;
	const int Col = 19;

	int Tile[22][19];
	//bool PowerUpTaken; // Lasts for 5 seconds
	//math::real PowerUpTimer;

	ECE_Map();
	~ECE_Map();

	//// Origin is at center.
	//int operator()(int X, int Y) const;
	//int &operator()(int X, int Y);

	int update(double dt);
	int draw(ECE_Camera Cam);

	int get_element(int X, int Y);
	int set_element(int X, int Y, int Arg);

	int reset();

	bool check();

private:

	void draw_maze(const ECE_Camera& c);
	void draw_grid_piece(const ECE_Camera& Camera, math::real3 p1, math::real3 p2);

};

#endif // !ECE_MAP_H
