#ifndef PLANE3D_H
#define PLANE3D_H

#include "Vector3D.h"


class Plane3D
{
public:
	Vector3D mNormal;
	Vector3D mPoint;

	//Equation of plane: N dot X = D
	GLfloat mD;
public:
	Plane3D();
	Plane3D(Vector3D normal, Vector3D point);
	Plane3D(Vector3D a, Vector3D b, Vector3D c);

	~Plane3D();
};

#endif

