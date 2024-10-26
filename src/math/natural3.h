#pragma once
#ifndef NATURAL3_H
#define NATURAL3_H

#include "mconfig.h"

#include "natural.h"

namespace math {

	struct natural3 {
		unsigned int x, y, z;
	};

	natural3 operator+(natural3 lhs, natural3 rhs);
	natural3 operator-(natural3 lhs, natural3 rhs);
	natural operator*(natural3 lhs, natural3 rhs);
	natural3 operator^(natural3 lhs, natural3 rhs);

	natural3 operator+(natural lhs, natural3 rhs);
	natural3 operator-(natural lhs, natural3 rhs);
	natural3 operator*(natural lhs, natural3 rhs);
	natural3 operator/(natural lhs, natural3 rhs);

	natural3 operator+(natural3 lhs, natural rhs);
	natural3 operator-(natural3 lhs, natural rhs);
	natural3 operator*(natural3 lhs, natural rhs);
	natural3 operator/(natural3 lhs, natural rhs);

}

#endif /* !NATURAL3_H */
