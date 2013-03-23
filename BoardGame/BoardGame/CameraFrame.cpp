#include "CameraFrame.h"


CameraFrame::CameraFrame(GLfloat originX, GLfloat originY, GLfloat originZ)
	:LocalFrame(originX, originY, originZ)
{
}

CameraFrame::~CameraFrame(void)
{
}


Matrix4x4 CameraFrame::GetMatrix()
{
	Matrix4x4 ret;
	Vector3D x, z;
			
	z.mX = -this->mForward.mX;
	z.mY = -this->mForward.mY;
	z.mZ = -this->mForward.mZ;


	x = this->mUp.crossProduct(z);


	#define M(row,col)  ret.mMatrix[col*4+row]
	M(0, 0) = x.mX;
	M(0, 1) = x.mY;
	M(0, 2) = x.mZ;
	M(0, 3) = 0.0;
	M(1, 0) = this->mUp.mX;
	M(1, 1) = this->mUp.mY;
	M(1, 2) = this->mUp.mZ;
	M(1, 3) = 0.0;
	M(2, 0) = z.mX;
	M(2, 1) = z.mY;
	M(2, 2) = z.mZ;
	M(2, 3) = 0.0;
	M(3, 0) = 0.0;
	M(3, 1) = 0.0;
	M(3, 2) = 0.0;
	M(3, 3) = 1.0;
	#undef M

                
   // Apply translation too
	Matrix4x4 trans, M;
	trans = GetTranslationMatrix(-this->mOrigin.mX, -this->mOrigin.mY, -this->mOrigin.mZ);  
	ret = ret.MulMatrix(trans);

	return ret;
}