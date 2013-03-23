#include "CardPiece.h"
#include <iostream>

#define PI (3.14159265358979323846)

#define SPEED (0.005)
#define DIFF (0.003)

CardPiece::CardPiece(void)
{
}

CardPiece::CardPiece(GLfloat y, char *texture, Hexagon *base)
	:Hexagon(0, 0, 0, base->mDim)
{
	//Initialize basic hexagon
	GLfloat texCoor[8][2] = {{0.5f, 1.0 - 0.5f}, {0.731f, 1.0 - 0.00333f}, {0.272f, 1.0 - 0.00333f}, {0.0427f, 1.0 - 0.502f}, {0.272f, 1.0 - 0.997f}, {0.731f, 1.0 - 0.997f}, {0.959f, 1.0 - 0.502f}, {0.731f, 1.0 - 0.00333f}};
	this->PrepareTexture(texture);
	this->PrepareBatch(texCoor, true);

	//Initiize on-board coordinates
	this->mBase = base;

	//Initialize velocity vector
	this->mVelocity = Vector3D(0.0f, 0.0f, 0.0f);

	//Initialize frame
	mFrame = LocalFrame(base->mVertices[0][0], y, base->mVertices[0][2]);
}

CardPiece::~CardPiece(void)
{
}

void CardPiece::Move30To(Hexagon *hexagon)
{
	//Calculate velocity
	GLfloat speed = SPEED;

	GLfloat vX = speed * cosf((30.0f * PI) / 180.0f);
	GLfloat vY = 0;
	GLfloat vZ = speed * sinf((30.0f * PI) / 180.0f);

	this->mVelocity = Vector3D(vX, vY, vZ);

	//reset the base
	this->mBase = hexagon;
}

void CardPiece::Move90To(Hexagon *hexagon)
{
	//Calculate velocity
	GLfloat speed = SPEED;

	GLfloat vX = 0;
	GLfloat vY = 0;
	GLfloat vZ = speed;	//in openGL coordinate system

	this->mVelocity = Vector3D(vX, vY, vZ);

	//reset the base
	this->mBase = hexagon;
}

void CardPiece::Move150To(Hexagon *hexagon)
{
	//Calculate velocity
	GLfloat speed = SPEED;

	GLfloat vX = speed * cosf((150.0f * PI) / 180.0f);	//sin(150) > 0
	GLfloat vY = 0;
	GLfloat vZ = speed * sinf((150.0f * PI) / 180.0f);	//cos(150) < 0

	this->mVelocity = Vector3D(vX, vY, vZ);

	//reset the base
	this->mBase = hexagon;
}

void CardPiece::Move210To(Hexagon *hexagon)
{
	//Calculate velocity
	GLfloat speed = SPEED;

	GLfloat vX = speed * cosf((210.0f * PI) / 180.0f);	//sin < 0
	GLfloat vY = 0;
	GLfloat vZ = speed * sinf((210.0f * PI) / 180.0f);	//cos < 0

	this->mVelocity = Vector3D(vX, vY, vZ);

	//reset the base
	this->mBase = hexagon;
}

void CardPiece::Move270To(Hexagon *hexagon)
{
	//Calculate velocity
	GLfloat speed = SPEED;

	GLfloat vX = 0;
	GLfloat vY = 0;
	GLfloat vZ = speed;	//in openGL coordinate system

	this->mVelocity = Vector3D(vX, vY, vZ);

	//reset the base
	this->mBase = hexagon;
}

void CardPiece::Move330To(Hexagon *hexagon)
{
	//Calculate velocity
	GLfloat speed = SPEED;

	GLfloat vX = speed * cosf((330.0f * PI) / 180.0f); //sin < 0
	GLfloat vY = 0;
	GLfloat vZ = speed * sinf((330.0f * PI) / 180.0f); //cos > 0

	this->mVelocity = Vector3D(vX, vY, vZ);

	//reset the base
	this->mBase = hexagon;
}

void CardPiece::MoveTo(GLint angle, Hexagon *hexagon)
{
	if(this->mVelocity.mX == 0 && this->mVelocity.mY == 0 && this->mVelocity.mZ == 0)	//to make sure that the piece is not in motion
	{
		switch(angle)
		{
		case 30:
			Move30To(hexagon);
			break;
		case 90:
			Move90To(hexagon);
			break;
		case 150:
			Move150To(hexagon);
			break;
		case 210:
			Move210To(hexagon);
			break;
		case 270:
			Move270To(hexagon);
			break;
		case 330:
			Move330To(hexagon);
			break;
		default:
			Move30To(hexagon);
		}
	}
}

LocalFrame CardPiece::GetFrame(float timeElapsed)
{
	LocalFrame ret;
	if(this->mVelocity.mX != 0 || this->mVelocity.mY != 0 || this->mVelocity.mZ !=0)
	{
		this->mFrame.MoveRight(this->mVelocity.mX * timeElapsed);
		this->mFrame.MoveForward(this->mVelocity.mZ * timeElapsed);
		this->mFrame.MoveUp(this->mVelocity.mY * timeElapsed);

		if(this->IsOnBase())
		{
			this->mVelocity = Vector3D(0.0f, 0.0f, 0.0f);	//zero-out the velocity vector
			this->mFrame = LocalFrame(this->mBase->mVertices[0][0], this->mVertices[0][1], this->mBase->mVertices[0][2]);
		}
	}

	ret = this->mFrame;

	return ret;
}

bool CardPiece::IsOnBase()
{
	//check if arrived
	if((this->mVelocity.mX != 0.0f && abs(this->mFrame.mOrigin.mX - this->mBase->mVertices[0][0]) < DIFF) || (abs(this->mFrame.mOrigin.mZ - this->mBase->mVertices[0][2]) < DIFF))
		return true;
	else
		return false;
}
