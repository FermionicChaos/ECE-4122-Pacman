#pragma once
#ifndef MCONFIG_H
#define MCONFIG_H

/* Enable to use common computer science notation. */
//#define CS_PLEB_NOTATION

/* Defines the base type of real numbers. */
#define REAL_TYPE_FLOAT

/* Default is column major memory layout */
//#define ROW_MAJOR_MEMORY_LAYOUT

//tex:
// Consider an array $m[9]$ interpereted as a matrix $A$.
//tex:
// $$ 
// A =
// \begin{bmatrix} 
//	a_{11} & a_{12} & a_{13} \\
//  a_{21} & a_{22} & a_{23} \\
//  a_{31} & a_{32} & a_{33} \\
// \end{bmatrix}
// $$
// Row Major Memory Format:
// $$ 
// \begin{bmatrix} 
//	m[0] & m[1] & m[2] \\
//  m[3] & m[4] & m[5] \\
//  m[6] & m[7] & m[8] \\
// \end{bmatrix}
// $$
// Column Major Memory Format:
// $$ 
// \begin{bmatrix} 
//	m[0] & m[3] & m[6] \\
//  m[1] & m[4] & m[7] \\
//  m[2] & m[5] & m[8] \\
// \end{bmatrix}
// $$


/* Enables IO */
#define MATH_ENABLE_IO

/* Uses stack memory for Levi Civita tensor. Use heap if rank is too large. */
//#define LEVI_CEVITA_STACK_MEMORY

#ifdef LEVI_CEVITA_STACK_MEMORY
 #define LEVI_CEVITA_STACK_MEMORY_SIZE 10
#endif // LEVI_CEVITA_STACK_MEMORY

#endif // !MCONFIG_H
