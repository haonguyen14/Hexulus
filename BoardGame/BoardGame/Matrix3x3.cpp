#include "Matrix3x3.h"


Matrix3x3::Matrix3x3(bool identity)
{
	float value = 0.0f;
	if(identity)
		value = 1.0f;

	float col_0[3] = {value, 0.0f, 0.0f};
	float col_1[3] = {0.0f, value, 0.0f};
	float col_2[3] = {0.0f, 0.0f, value};

	this->SetColumn(col_0, 0);
	this->SetColumn(col_1, 1);
	this->SetColumn(col_2, 2);
}

Matrix3x3::~Matrix3x3(void)
{
}

void Matrix3x3::SetColumn(float *values, int colNum)
{
	for(int i = colNum * 3, j = 0; j < 3; i++, j++)
		this->mMatrix[i] = values[j];
}

void Matrix3x3::SetColumn(Matrix3x1 col, int colNum)
{
	for(int i = colNum * 3, j = 0; j < 3; i++, j++)
		this->mMatrix[i] = col.mMatrix[j];
}

Matrix3x1 Matrix3x3::GetColumn(int colNum)
{
	float values[3];

	for(int i = colNum * 3, j = 0; j < 3; i++, j++)
		values[j] = this->mMatrix[i];

	return Matrix3x1(values[0], values[1], values[2]);
}

Matrix3x1 Matrix3x3::MulMatrix3X1(Matrix3x1 matrix)
{
	Matrix3x1 ret;
	for(int i = 0; i < 3; i++)
		for(int c = 0; c < 3; c++)
			ret.mMatrix[i] = ret.mMatrix[i] + (matrix.mMatrix[c] * this->mMatrix[(c * 3) + i]);

	return ret;
}

Matrix3x3 Matrix3x3::MulMatrix(Matrix3x3 matrix)
{
	Matrix3x3 ret;
	Matrix3x1 col;

	for(int i = 0; i < 3; i++)
	{
		col = this->MulMatrix3X1(matrix.GetColumn(i));
		ret.SetColumn(col, i);
	}

	return ret;
}
