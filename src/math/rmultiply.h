#pragma once
#ifndef RMULTIPLY_H
#define RMULTIPLY_H
/*
* This file defines the various forms of matrix multiplication.
*/
#include "real.h"
#include "real2.h"
#include "real3.h"
#include "real4.h"

/* Matrix Types */
#include "real2x2.h"
#include "real2x3.h"
#include "real2x4.h"

#include "real3x2.h"
#include "real3x3.h"
#include "real3x4.h"

#include "real4x2.h"
#include "real4x3.h"
#include "real4x4.h"

namespace math {

	//real2x2 operator*(real2x2 Lhs, real2x2 Rhs);
	real2x3 operator*(real2x2 Lhs, real2x3 Rhs);
	real2x4 operator*(real2x2 Lhs, real2x4 Rhs);

	real2x2 operator*(real2x3 Lhs, real3x2 Rhs);
	real2x3 operator*(real2x3 Lhs, real3x3 Rhs);
	real2x4 operator*(real2x3 Lhs, real3x4 Rhs);

	real2x2 operator*(real2x4 Lhs, real4x2 Rhs);
	real2x3 operator*(real2x4 Lhs, real4x3 Rhs);
	real2x4 operator*(real2x4 Lhs, real4x4 Rhs);



	real3x2 operator*(real3x2 Lhs, real2x2 Rhs);
	real3x3 operator*(real3x2 Lhs, real2x3 Rhs);
	real3x4 operator*(real3x2 Lhs, real2x4 Rhs);

	real3x2 operator*(real3x3 Lhs, real3x2 Rhs);
	//real3x3 operator*(real3x3 Lhs, real3x3 Rhs);
	real3x4 operator*(real3x3 Lhs, real3x4 Rhs);

	real3x2 operator*(real3x4 Lhs, real4x2 Rhs);
	real3x3 operator*(real3x4 Lhs, real4x3 Rhs);
	real3x4 operator*(real3x4 Lhs, real4x4 Rhs);



	real4x2 operator*(real4x2 Lhs, real2x2 Rhs);
	real4x3 operator*(real4x2 Lhs, real2x3 Rhs);
	real4x4 operator*(real4x2 Lhs, real2x4 Rhs);

	real4x2 operator*(real4x3 Lhs, real3x2 Rhs);
	real4x3 operator*(real4x3 Lhs, real3x3 Rhs);
	real4x4 operator*(real4x3 Lhs, real3x4 Rhs);

	real4x2 operator*(real4x4 Lhs, real4x2 Rhs);
	real4x3 operator*(real4x4 Lhs, real4x3 Rhs);
	//real4x4 operator*(real4x4 Lhs, real4x4 Rhs);

}

#endif // !RMULTIPLY_H
