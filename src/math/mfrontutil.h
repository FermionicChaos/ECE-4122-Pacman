#pragma once
#ifndef MFRONTUTIL_H
#define MFRONTUTIL_H

#include <cmath>

#include "mconfig.h"
#include "mcommonutil.h"

//#include "boolean.h" Probably Dumb Type
#include "natural.h"
#include "integer.h"
//#include "rational.h" Dumb Type
#include "real.h"
#include "complex.h"
#include "quaternion.h"

#include "constants.h"

#include "natural2.h"
#include "natural3.h"
#include "natural4.h"

#include "integer2.h"
#include "integer3.h"
#include "integer4.h"

#include "real2.h"
#include "real3.h"
#include "real4.h"

#include "real2x2.h"
#include "real2x3.h"
#include "real2x4.h"

#include "real3x2.h"
#include "real3x3.h"
#include "real3x4.h"

#include "real4x2.h"
#include "real4x3.h"
#include "real4x4.h"

#include "rmultiply.h"

//#include "R1.h"
//#include "R2.h"
//#include "R3.h"
//#include "R4.h"

//#include "real2_field.h"
//#include "real3_field.h"
//#include "real4_field.h"

/*
* This library was created to be useful for graphics programming.
*/

namespace math {

	// This function generates a perspective matrix. Transforms to clip coordinates.
	real4x4 perspective(real FOV, real AspectRatio, real Near, real Far);
	real4x4 rotation(real Angle, real3 V);

}

#endif // !MFRONTUTIL_H
