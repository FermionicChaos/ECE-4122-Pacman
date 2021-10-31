#pragma once
#ifndef ECE_GHOST_H
#define ECE_GHOST_H

#ifdef _WIN32
#include <Windows.h>
#endif // __WIN32

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "../math/mathematics.h"

#include "ECE_Camera.h"
#include "ECE_Map.h"

class ECE_Ghost {
public:

	static const math::real3 FColor;

	enum direction {
		STALL		= -1,
		UP			= 0,
		LEFT		= 1,
		DOWN		= 2,
		RIGHT		= 3
	};

	enum Ghost_State {
		/*STANDSTILL	= -1,*/
		// In this state, the ghost will use dijkstras algorithm to determine path to find pacman.
		CHASE		= 0, //HUNT,
		// 
		SCATTER		= 1,
		// Return to Ghost house to return to normal state.
		EATEN		= 2,
		// Will turn blue and move the opposite direction of pacman.
		FRIGHTENED	= 3,
	};

	enum Color_Type {
		RED		= 0,
		GREEN	= 1,
		ORANGE	= 2,
		PINK	= 3,
	};

	ECE_Map* Map;
	math::real ModeTimer;
	int ID;

	int State;
	int Dir;

	math::real3 Color;
	math::real3 Pos;
	math::real3 TargetPos;

	ECE_Ghost(int ID);
	~ECE_Ghost() {}

	int update(double dt);
	int draw(const ECE_Camera Camera);

	int reset();

private:

	// Gets intersection node
	math::real3 get_inode(double dt) const;
	// Checks if pacman is at intersection.
	bool at_intersection(double dt) const;
	// gets velocity to particular direction.
	math::real3 get_vel(int aDir) const;

};

#endif // !ECE_GHOST_H
