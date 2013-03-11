#ifndef LINE3D_H
#define LINE3D_H

#include "Vector3D.h"

#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

class Line3D
{
public:
	Vector3D mPoint;
	Vector3D mDirection;

public:
	Line3D();
	Line3D(Vector3D point, Vector3D direction);
	~Line3D();

	Vector3D getPoint(GLfloat t);
};

#endif

