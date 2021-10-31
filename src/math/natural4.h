#pragma once
#ifndef UVEC4_H
#define UVEC4_H

#include "mconfig.h"

#include "natural.h"

namespace math {

	struct natural4 {
		natural x, y, z, t;
	};

	natural4 operator+(natural4 lhs, natural4 rhs);
	natural4 operator-(natural4 lhs, natural4 rhs);
	natural operator*(natural4 lhs, natural4 rhs);

	natural4 operator+(natural lhs, natural4 rhs);
	natural4 operator-(natural lhs, natural4 rhs);
	natural4 operator*(natural lhs, natural4 rhs);
	natural4 operator/(natural lhs, natural4 rhs);

	natural4 operator+(natural4 lhs, natural rhs);
	natural4 operator-(natural4 lhs, natural rhs);
	natural4 operator*(natural4 lhs, natural rhs);
	natural4 operator/(natural4 lhs, natural rhs);

}

#endif /* !UVEC4_H */
