#pragma once
#ifndef ECE_CAMERA_H
#define ECE_CAMERA_H

#include "../math/mathematics.h"

class ECE_Camera {
public:

	// Corresponds to WASD
	bool KeyActive[8];

	math::real3 Pos;
	math::real3 Vel;

	math::real Theta, Phi;
	math::real3 Forward;
	math::real3 Right;
	math::real3 Up;

	math::real FOV;
	math::integer Width;
	math::integer Height;

	ECE_Camera();
	ECE_Camera(math::real3 aPos, math::real aTheta, math::real aPhi);
	~ECE_Camera() {}

	int update(double dt);

	math::real4x4 get_transform(math::real3 p) const;

};

#endif // !ECE_CAMERA_H
