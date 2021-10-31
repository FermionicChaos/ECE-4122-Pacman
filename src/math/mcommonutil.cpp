#include "mcommonutil.h"

#include <stdlib.h>
#include <stdarg.h>

#include "mconfig.h"

#include "constants.h"

namespace math {

	int sift_down(int* A, int Length, int i) {
		if ((i < 0) && (i >= Length)) return 0;
		static int SwapCount = 0;
		static int StackDepth = 0;
		StackDepth += 1;

		int L = 2 * i + 1; // Left Child
		int R = 2 * i + 2; // Right Child

		int SwapContainer;
		if ((L < Length) && (R < Length)) {
			if (A[L] > A[R]) {
				if (A[L] > A[i]) {
					SwapContainer = A[L];
					A[L] = A[i];
					A[i] = SwapContainer;
					SwapCount += 1;
					sift_down(A, Length, L);
				}
			}
			else {
				if (A[R] > A[i]) {
					SwapContainer = A[R];
					A[R] = A[i];
					A[i] = SwapContainer;
					SwapCount += 1;
					sift_down(A, Length, R);
				}
			}
		}
		else if (L < Length) {
			if (A[L] > A[i]) {
				SwapContainer = A[L];
				A[L] = A[i];
				A[i] = SwapContainer;
				SwapCount += 1;
			}
		}

		StackDepth -= 1;
		if (StackDepth == 0) {
			int SwapTotal = SwapCount;
			SwapCount = 0;
			return SwapTotal;
		}
		else {
			return 0;
		}
	}

	int build_heap(int* A, int Length) {
		int SwapCount = 0;
		for (int i = Length - 1; i >= 0; i--) {
			if (2 * i + 1 >= Length) continue;
			SwapCount += sift_down(A, Length, i);
		}
		return SwapCount;
	}

	int heap_sort(int* A, int Length) {
		int SwapCount = 0;
		SwapCount += build_heap(A, Length);
		int SwapContainer;
		int HeapSize = Length;
		while (HeapSize > 1) {
			SwapContainer = A[0];
			A[0] = A[HeapSize - 1];
			A[HeapSize - 1] = SwapContainer;
			HeapSize -= 1;
			SwapCount += 1;
			SwapCount += sift_down(A, HeapSize, 0);
		}
		return SwapCount;
	}


	int kronecker_delta(int I, int J) {
		if (I == J) {
			return 1;
		}
		else {
			return 0;
		}
	}

	//static int levi_civita_stack_memory() {
	//
	//}
	//
	//static int levi_civita_heap_memory() {
	//
	//}

	int levi_civita(int Rank, ...) {
#ifdef LEVI_CEVITA_STACK_MEMORY
		if (Rank > LEVI_CEVITA_STACK_MEMORY_SIZE) return 0;
#endif // LEVI_CEVITA_STACK_MEMORY


		int i = 0;
		int j = 0;

#ifdef LEVI_CEVITA_STACK_MEMORY
		int Index[LEVI_CEVITA_STACK_MEMORY_SIZE];
#else
		int* Index = NULL;
		Index = (int*)malloc(Rank * sizeof(int));
		if (Index == NULL) return 0;
#endif // LEVI_CEVITA_STACK_MEMORY

		va_list ArgList;
		va_start(ArgList, Rank);
		for (int i = 0; i < Rank; i++) {
			Index[i] = va_arg(ArgList, int);
		}
		va_end(ArgList);

		for (i = 0; i < Rank; i++) {
			if ((Index[i] < 0) && (Index[i] >= Rank)) {
#ifndef LEVI_CEVITA_STACK_MEMORY
				free(Index); Index = NULL;
#endif // !LEVI_CEVITA_STACK_MEMORY
				return 0;
			}
		}

		for (i = 0; i < Rank; i++) {
			for (j = i + 1; j < Rank; j++) {
				if (Index[i] == Index[j]) {
#ifndef LEVI_CEVITA_STACK_MEMORY
					free(Index); Index = NULL;
#endif // !LEVI_CEVITA_STACK_MEMORY
					return 0;
				}
			}
		}

		int IndexSwapCount = heap_sort(Index, Rank);

#ifndef LEVI_CEVITA_STACK_MEMORY
		free(Index); Index = NULL;
#endif // !LEVI_CEVITA_STACK_MEMORY

		if ((IndexSwapCount % 2) > 0) {
			return -1;
		}
		else {
			return +1;
		}
	}

	//int levi_civita(int Rank, int *Index) {
	//
	//}

}
