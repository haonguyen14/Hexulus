#ifndef VECTOR3D_H
#define VECTOR3D_H

#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif


class Vector3D
{
public:
	GLfloat mX;
	GLfloat mY;
	GLfloat mZ;
public:
	Vector3D();
	Vector3D(GLfloat x, GLfloat y, GLfloat z);
	~Vector3D();

	GLfloat getMagnitude();

	Vector3D add(Vector3D v);
	Vector3D sub(Vector3D v);
	Vector3D scalarMul(GLfloat a);
	Vector3D normalize();

	Vector3D crossProduct(Vector3D v);
	GLfloat  dotProduct(Vector3D v);
};

#endif

