#include "real.h"

#include "mconfig.h"

//#include <math.h>
#include <cmath>

//using namespace math;

namespace math {

	real ln(real Arg) {
		return std::log(Arg);
	}

	real log(real Base, real RetVal) {
		return std::log(RetVal) / std::log(Base);
	}

	real deg2rad(real Arg) {
#ifdef REAL_TYPE_FLOAT
		return Arg * (3.1415926536f / 180.0f);
#endif // REAL_TYPE_FLOAT
#ifdef REAL_TYPE_DOUBLE
		return Arg * (3.14159265358979323846 / 180.0);
#endif // REAL_TYPE_DOUBLE
	}

	real rad2deg(real Arg) {
#ifdef REAL_TYPE_FLOAT
		return Arg * (180.0f / 3.1415926536f);
#endif // REAL_TYPE_FLOAT
#ifdef REAL_TYPE_DOUBLE
		return Arg * (180.0 / 3.14159265358979323846);
#endif // REAL_TYPE_DOUBLE
	}

	//real atan(real ArgY, real ArgX) {
	//	return atan2(ArgY, ArgX);
	//}

}
