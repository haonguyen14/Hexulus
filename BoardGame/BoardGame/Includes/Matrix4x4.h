#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include "Matrix4x1.h"
#include "Matrix3x1.h"

class Matrix4x4
{
public:
	float mMatrix[16];
public:
	Matrix4x4(bool identity = false);
	~Matrix4x4(void);

	void SetColumn(float *values, int colNum);
	void SetColumn(Matrix4x1 col, int colNum);
	Matrix4x1 GetColumn(int colNum);

	Matrix4x1 MulMatrix4X1(Matrix4x1 matrix);
	Matrix4x1 MulMatrix3X1(Matrix3x1 matrix);
	Matrix4x4 MulMatrix(Matrix4x4 matrix);
};

#endif

