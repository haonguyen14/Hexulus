#ifndef MATRIX3X3_H
#define MATRIX3X3_H

#include "Matrix3x1.h"

class Matrix3x3
{
public:
	float mMatrix[9];
public:
	Matrix3x3(bool identity = false);
	~Matrix3x3(void);

	void SetColumn(float *values, int colNum);
	void SetColumn(Matrix3x1 col, int colNum);
	Matrix3x1 GetColumn(int colNum);

	Matrix3x1 MulMatrix3X1(Matrix3x1 matrix);
	Matrix3x3 MulMatrix(Matrix3x3 matrix);
};

#endif

