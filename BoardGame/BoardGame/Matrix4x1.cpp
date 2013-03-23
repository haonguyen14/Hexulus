#include "Matrix4x1.h"


Matrix4x1::Matrix4x1(void)
{
	this->mMatrix[0] = 0.0f;
	this->mMatrix[1] = 0.0f;
	this->mMatrix[2] = 0.0f;
	this->mMatrix[3] = 0.0f;
}

Matrix4x1::Matrix4x1(float a, float b, float c, float d)
{
	this->mMatrix[0] = a;
	this->mMatrix[1] = b;
	this->mMatrix[2] = c;
	this->mMatrix[3] = d;
}


Matrix4x1::~Matrix4x1(void)
{
}


void Matrix4x1::SetColumn(float *values)
{
	for(int i = 0; i < 4; i++)
		this->mMatrix[i] = values[i];
}
