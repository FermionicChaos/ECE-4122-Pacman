#pragma once
#ifndef ECE_PACMAN_H
#define ECE_PACMAN_H

#ifdef _WIN32
#include <Windows.h>
#endif // __WIN32

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "../math/mathematics.h"

#include "ECE_Camera.h"
#include "ECE_Map.h"

class ECE_Pacman {
public:

	enum direction {
		STALL		= -1,
		UP			= 0,
		LEFT		= 1,
		DOWN		= 2,
		RIGHT		= 3
	};

	bool PowerUpTaken;
	ECE_Map *Map;
	int Points;

	bool ButtonDir[4];

	int Dir;
	math::real3 Pos;

	ECE_Pacman();
	~ECE_Pacman() {}

	int update(double dt);
	int draw(const ECE_Camera Camera);


private:
	// Gets intersection node
	math::real3 get_inode(double dt) const;
	// Checks if pacman is at intersection.
	bool at_intersection(double dt) const ;
	// gets velocity to particular direction.
	math::real3 get_vel(int aDir) const;
};

#endif // !ECE_PACMAN_H
