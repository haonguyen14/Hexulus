#include "Includes\Line3D.h"


Line3D::Line3D()
{
}


Line3D::~Line3D()
{
}


Line3D::Line3D(Vector3D point, Vector3D direction)
{
	mPoint = point;
	mDirection = direction.normalize();
}

Vector3D Line3D::getPoint(GLfloat t)
{
	Vector3D ret = mPoint.add(mDirection.scalarMul(t));
	return ret;
}
