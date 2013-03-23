#ifndef MATRIX4X1_H
#define MATRIX4X1_H

class Matrix4x1
{
public:
	float mMatrix[4];
public:
	Matrix4x1(void);
	Matrix4x1(float a, float b, float c ,float d);
	~Matrix4x1(void);

	void SetColumn(float *values);
};


#endif

