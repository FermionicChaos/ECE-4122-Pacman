#pragma once
#ifndef MCOMMONUTIL_H
#define MCOMMONUTIL_H

#include <stdarg.h>

#include "mconfig.h"

/*
* This is supposed to be a backend library for the other classes.
* levi_cevita is used to find determinants of NxN matrices.
* can be extended to any size matrix to compute determinant.
*/
namespace math {

	int sift_down(int* A, int Length, int i);
	int build_heap(int* A, int Length);
	int heap_sort(int* A, int Length);

	int kronecker_delta(int I, int J);
	int levi_civita(int Rank, ...);
	//int levi_civita(int Rank, int *Index);

}

#endif // !MCOMMONUTIL_H
