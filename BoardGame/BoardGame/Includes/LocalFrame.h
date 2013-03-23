#ifndef LOCALFRAME_H
#define LOCALFRAME_H

#include "Vector3D.h"
#include "Matrix4x4.h"
#include <math.h>

class LocalFrame
{
public:
	Vector3D mOrigin;
	Vector3D mForward;
	Vector3D mUp;
	Vector3D mHorizon;

public:
	LocalFrame(GLfloat originX = 0.0f, GLfloat originY = 0.0f, GLfloat originZ = 0.0f);
	~LocalFrame(void);

	Matrix4x4 GetMatrix();

	void MoveUp(GLfloat delta);
	void MoveRight(GLfloat delta);
	void MoveForward(GLfloat delta);
	void Rotate(GLfloat angle, Vector3D axis);

protected:
	Matrix4x4 GetRotationMatrix(GLfloat angle, Vector3D axis);
	Matrix4x4 GetTranslationMatrix(GLfloat x, GLfloat y, GLfloat z);
};

#endif