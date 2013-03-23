#ifndef CAMERAFRAME_H
#define CAMERAFRAME_H

#include "LocalFrame.h"

class CameraFrame : public LocalFrame
{
public:
	CameraFrame(GLfloat originX = 0.0f, GLfloat originY = 0.0f, GLfloat originZ = 0.0f);
	~CameraFrame(void);

	Matrix4x4 GetMatrix();
};

#endif