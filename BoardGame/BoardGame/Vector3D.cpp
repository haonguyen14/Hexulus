#include "Includes\Vector3D.h"
#include <math.h>


Vector3D::Vector3D()
{
}

Vector3D::Vector3D(GLfloat x, GLfloat y, GLfloat z)
{
	this->mX = x;
	this->mY = y;
	this->mZ = z;
}

Vector3D::~Vector3D()
{
}


GLfloat Vector3D::getMagnitude()
{
	return (GLfloat)sqrtf((this->mX * this->mX) + (this->mY * this->mY) + (this->mZ * this->mZ));
}

Vector3D Vector3D::add(Vector3D v)
{
	Vector3D ret(this->mX + v.mX, this->mY + v.mY, this->mZ + v.mZ);
	return ret;
}

Vector3D Vector3D::sub(Vector3D v)
{
	Vector3D ret(this->mX - v.mX, this->mY - v.mY, this->mZ - v.mZ);
	return ret;
}

Vector3D Vector3D::scalarMul(GLfloat a)
{
	Vector3D ret(this->mX * a, this->mY * a, this->mZ * a);
	return ret;
}

Vector3D Vector3D::normalize()
{
	GLfloat magnitude = this->getMagnitude();
	Vector3D ret(this->mX / magnitude, this->mY / magnitude, this->mZ / magnitude);
	return ret;
}

Vector3D Vector3D::crossProduct(Vector3D v)
{
	Vector3D ret((this->mY * v.mZ) - (this->mZ * v.mY),
		(this->mZ * v.mX) - (this->mX * v.mZ),
		(this->mX * v.mY) - (this->mY * v.mX));

	return ret;
}

GLfloat Vector3D::dotProduct(Vector3D v)
{
	return ((this->mX * v.mX) + (this->mY * v.mY) + (this->mZ * v.mZ));
}

