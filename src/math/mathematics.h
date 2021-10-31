#pragma once
#ifndef MATHEMATICS_H
#define MATHEMATICS_H

/*\\ ---------------------------------------- mathematics.h ---------------------------------------- \\//

Vector Notation:
	Vectors are to be treated as column vectors, but there is flexibility in left multiplication
	where the vector will serve as a row vector

Matrix Notation:
	Memory Layout of these objects is by default column major, define ROW_MAJOR_MEMORY_LAYOUT in mconfig.h
	if row major memory layout is preferred.
	Row Count: M
	Column Count: N
	realMxN is a M x N matrix (aka real[ROWS]x[COLUMNS])

TODO List:
	- Add graphical functions for perspective matrices.

	- Add "math" namespace to prevent collisions with standard libraries.

	- Should matrix indices start at 1 or 0?

//\\ ---------------------------------------- mathematics.h ---------------------------------------- \\*/

#include <cmath>

/* This header configures usage. */
#include "mconfig.h"
#include "mcommonutil.h"

/* -------------------- All Types Included here -------------------- */

/* Number Types */
//#include "boolean.h" Probably Dumb Type
#include "natural.h"
#include "integer.h"
//#include "rational.h" Dumb Type
#include "real.h"
#include "complex.h"
#include "quaternion.h"

/* Built In Numerical Constants */
#include "constants.h"

/* Vector Types */
#include "natural2.h"
#include "natural3.h"
#include "natural4.h"

#include "integer2.h"
#include "integer3.h"
#include "integer4.h"

#include "real2.h"
#include "real3.h"
#include "real4.h"

/* Matrix Types */
/*
* When accessing matrix elements, the notation is 
* math::realmxn A;
* 
* Value = A(Row,Column);
*/
#include "real2x2.h"
#include "real2x3.h"
#include "real2x4.h"

#include "real3x2.h"
#include "real3x3.h"
#include "real3x4.h"

#include "real4x2.h"
#include "real4x3.h"
#include "real4x4.h"

/* Inter-Matrix Multiplication */
#include "rmultiply.h"

/* Matrix Multiplication Functions */
/* Scalar Field Types */
//#include "R1.h"
//#include "R2.h"
//#include "R3.h"
//#include "R4.h"

/* Vector Field Types */
//#include "real2_field.h"
//#include "real3_field.h"
//#include "real4_field.h"

/* -------------------- Extended Functions -------------------- */

/* Utility Functions */
#include "mfrontutil.h"

#endif // !MATHEMATICS_H
