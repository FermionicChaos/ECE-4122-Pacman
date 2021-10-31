#include "constants.h"

#include "mconfig.h"

#include "natural.h"
#include "integer.h"
#include "real.h"

#ifdef REAL_TYPE_FLOAT
const math::real math::constant::pi = 3.1415926536f;
const math::real math::constant::e = 2.7182818284f;
#endif // REAL_TYPE_FLOAT

#ifdef REAL_TYPE_DOUBLE
const math::real math::constant::pi = 3.14159265358979323846;
const math::real math::constant::e = 2.71828182845904523536;
#endif // REAL_TYPE_DOUBLE
