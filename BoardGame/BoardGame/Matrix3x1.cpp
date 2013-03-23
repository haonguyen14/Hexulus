#include "Includes\Matrix3x1.h"


Matrix3x1::Matrix3x1(void)
{
	this->mMatrix[0] = 0.0f;
	this->mMatrix[1] = 0.0f;
	this->mMatrix[2] = 0.0f;
}

Matrix3x1::Matrix3x1(float a, float b, float c)
{
	this->mMatrix[0] = a;
	this->mMatrix[1] = b;
	this->mMatrix[2] = c;
}


Matrix3x1::~Matrix3x1(void)
{
}


void Matrix3x1::SetColumn(float *values)
{
	for(int i = 0; i < 3; i++)
		this->mMatrix[i] = values[i];
}


