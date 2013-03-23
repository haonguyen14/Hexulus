#ifndef MATRIX3X1_H
#define MATRIX3X1_H

class Matrix3x1
{
public:
	float mMatrix[3];
public:
	Matrix3x1(void);
	Matrix3x1(float a, float b, float c);
	~Matrix3x1(void);

	void SetColumn(float *values);
};


#endif

