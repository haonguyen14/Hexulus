#include "LocalFrame.h"


LocalFrame::LocalFrame(GLfloat originX, GLfloat originY, GLfloat originZ)
{
	//set up origin
	this->mOrigin.mX = originX;
	this->mOrigin.mY = originY;
	this->mOrigin.mZ = originZ;

	//set up default forward axis
	this->mForward = Vector3D(0.0f, 0.0f, -1.0f);

	//set up default up axis
	this->mUp = Vector3D(0.0f, 1.0f, 0.0f);

	//set up default horizontal axis
	this->mHorizon = Vector3D(1.0f, 0.0f, 0.0f);
}


LocalFrame::~LocalFrame(void)
{
}

Matrix4x4 LocalFrame::GetMatrix()
{
	Matrix4x4 ret;

	ret.SetColumn(Matrix4x1(this->mHorizon.mX, this->mHorizon.mY, this->mHorizon.mZ, 0.0f), 0);
	ret.SetColumn(Matrix4x1(this->mUp.mX, this->mUp.mY, this->mUp.mZ, 0.0f), 1);

	Vector3D temp = this->mHorizon.crossProduct(this->mUp);
	ret.SetColumn(Matrix4x1(temp.mX, temp.mY, temp.mZ, 0.0f), 2);
	ret.SetColumn(Matrix4x1(this->mOrigin.mX, this->mOrigin.mY, this->mOrigin.mZ, 1.0f), 3);

	return ret;
}

Matrix4x4 LocalFrame::GetRotationMatrix(GLfloat angle, Vector3D axis)
{
	Matrix4x4 rotMatrix;
	GLfloat mag, s, c;
	GLfloat x, y, z;
	GLfloat xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;

	s = float(sin(angle));
	c = float(cos(angle));

	x = axis.mX;
	y = axis.mY;
	z = axis.mZ;

	mag = float(sqrt( x*x + y*y + z*z ));

	// Identity matrix
	if (mag == 0.0f)
		return Matrix4x4(true);

	// Rotation matrix is normalized
	x /= mag;
	y /= mag;
	z /= mag;

    #define M(row,col)	rotMatrix.mMatrix[col*4+row]

	xx = x * x;
	yy = y * y;
	zz = z * z;
	xy = x * y;
	yz = y * z;
	zx = z * x;
	xs = x * s;
	ys = y * s;
	zs = z * s;
	one_c = 1.0f - c;

	M(0,0) = (one_c * xx) + c;
	M(0,1) = (one_c * xy) - zs;
	M(0,2) = (one_c * zx) + ys;
	M(0,3) = 0.0f;

	M(1,0) = (one_c * xy) + zs;
	M(1,1) = (one_c * yy) + c;
	M(1,2) = (one_c * yz) - xs;
	M(1,3) = 0.0f;

	M(2,0) = (one_c * zx) - ys;
	M(2,1) = (one_c * yz) + xs;
	M(2,2) = (one_c * zz) + c;
	M(2,3) = 0.0f;

	M(3,0) = 0.0f;
	M(3,1) = 0.0f;
	M(3,2) = 0.0f;
	M(3,3) = 1.0f;

    #undef M

	return rotMatrix;
}

Matrix4x4 LocalFrame::GetTranslationMatrix(GLfloat x, GLfloat y,GLfloat z)
{
	Matrix4x4 ret = Matrix4x4(true);
	float values[4] = {x, y, z, 1.0f};
	ret.SetColumn(values, 3);

	return ret;
}

void LocalFrame::MoveForward(GLfloat delta)
{
	this->mOrigin = this->mOrigin.add(this->mForward.scalarMul(delta));
}

void LocalFrame::MoveRight(GLfloat delta)
{
	this->mOrigin = this->mOrigin.add(this->mHorizon.scalarMul(delta));
}

void LocalFrame::MoveUp(GLfloat delta)
{
	this->mOrigin = this->mOrigin.add(this->mUp.scalarMul(delta));
}

void LocalFrame::Rotate(GLfloat angle, Vector3D axis)
{
	Matrix4x4 rotMatrix = GetRotationMatrix(angle, axis);
	Matrix4x1 newMatrix;

	//recalculate forward axis
	newMatrix = rotMatrix.MulMatrix3X1(Matrix3x1(this->mForward.mX, this->mForward.mY, this->mForward.mZ));
	this->mForward = Vector3D(newMatrix.mMatrix[0], newMatrix.mMatrix[1], newMatrix.mMatrix[2]);

	//recalculate up axis
	newMatrix = rotMatrix.MulMatrix3X1(Matrix3x1(this->mUp.mX, this->mUp.mY, this->mUp.mZ));
	this->mUp = Vector3D(newMatrix.mMatrix[0], newMatrix.mMatrix[1], newMatrix.mMatrix[2]);

	//recalculate horizontal axis
	newMatrix = rotMatrix.MulMatrix3X1(Matrix3x1(this->mHorizon.mX, this->mHorizon.mY, this->mHorizon.mZ));
	this->mHorizon = Vector3D(newMatrix.mMatrix[0], newMatrix.mMatrix[1], newMatrix.mMatrix[2]);
}

