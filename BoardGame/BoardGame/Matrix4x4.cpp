#include "Matrix4x4.h"


Matrix4x4::Matrix4x4(bool identity )
{
	float value = 0.0f;
	if(identity)
		value = 1.0f;

	float col_0[4] = {value, 0.0f, 0.0f, 0.0f};
	float col_1[4] = {0.0f, value, 0.0f, 0.0f};
	float col_2[4] = {0.0f, 0.0f, value, 0.0f};
	float col_3[4] = {0.0f, 0.0f, 0.0f, value};

	this->SetColumn(col_0, 0);
	this->SetColumn(col_1, 1);
	this->SetColumn(col_2, 2);
	this->SetColumn(col_3, 3);
}

Matrix4x4::~Matrix4x4(void)
{
}

void Matrix4x4::SetColumn(float *values, int colNum)
{
	for(int i = colNum * 4, j = 0; j < 4; i++, j++)
		this->mMatrix[i] = values[j];
}

void Matrix4x4::SetColumn(Matrix4x1 col, int colNum)
{
	for(int i = colNum * 4, j = 0; j < 4; i++, j++)
		this->mMatrix[i] = col.mMatrix[j];
}

Matrix4x1 Matrix4x4::GetColumn(int colNum)
{
	float values[4];

	for(int i = colNum * 4, j = 0; j < 4; i++, j++)
		values[j] = this->mMatrix[i];

	return Matrix4x1(values[0], values[1], values[2], values[3]);
}

Matrix4x1 Matrix4x4::MulMatrix4X1(Matrix4x1 matrix)
{
	Matrix4x1 ret;
	for(int i = 0; i < 4; i++)
		for(int c = 0; c < 4; c++)
			ret.mMatrix[i] = ret.mMatrix[i] + (matrix.mMatrix[c] * this->mMatrix[(c * 4) + i]);

	return ret;
}

Matrix4x1 Matrix4x4::MulMatrix3X1(Matrix3x1 matrix)
{
	Matrix4x1 _matrix = Matrix4x1(matrix.mMatrix[0], matrix.mMatrix[1], matrix.mMatrix[2], 1.0f);
	return this->MulMatrix4X1(_matrix);
}

Matrix4x4 Matrix4x4::MulMatrix(Matrix4x4 matrix)
{
	Matrix4x4 ret;
	Matrix4x1 col;

	for(int i = 0; i < 4; i++)
	{
		col = this->MulMatrix4X1(matrix.GetColumn(i));
		ret.SetColumn(col, i);
	}

	return ret;
}
