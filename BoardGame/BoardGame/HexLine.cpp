#include "Includes/HexLine.h"
#include <iostream>
#include <math.h>

//const GLfloat validAngles[] = {60.0f, 120.0f, 180.0f, 240.0f, 300.0f, 360.0f};		//in degree

typedef Hexagon* (*Extend)(Hexagon*);
Extend GetExtendFunc(GLfloat angle);

HexLine::HexLine(GLfloat firstHexX, GLfloat firstHexY, GLfloat firstHexZ, GLfloat dim, GLfloat angle, GLint len)
{
	mLen = len;
	mAngle = angle;
	
	//allocate dynamic memory for hexagons
	mHexes = (Hexagon **)malloc(sizeof(Hexagon *) * len);
	if(mHexes == NULL)
	{
		std::cout << ("HexLine: Failed to allocate memory");
		return;
	}

	//initialize the first hexagon
	Hexagon * firstHex = new Hexagon(firstHexX, firstHexY, firstHexZ, dim);
	mHexes[0] = firstHex;
	
	//initialize the rest of the hexagon
	Extend extendFunc = GetExtendFunc(mAngle);
	Hexagon *prevHex = mHexes[0];
	for(GLint i = 1; i < mLen; i++)
	{
		mHexes[i] = extendFunc(prevHex);
		prevHex = mHexes[i];
	}
}

HexLine::HexLine()
{
}

HexLine::~HexLine()
{
	//free all the hexagons
	for(int i = 0; i < mLen; i++)
	{
		delete mHexes[i];
	}

	//free the array of pointers
	free(mHexes);
}

Hexagon *extend60(Hexagon *hex)
{
	GLfloat centerVert[3];
	centerVert[0] = hex->mVertices[0][0] + (hex->mDim * (1.5f));
	centerVert[1] = hex->mVertices[0][1];
	centerVert[2] = hex->mVertices[0][2] - ((sqrt(3.0f) / 2.0f) * hex->mDim);

	Hexagon *newHex = new Hexagon(centerVert[0], centerVert[1], centerVert[2], hex->mDim);
	return newHex;
}

Hexagon *extend120(Hexagon *hex)
{
	GLfloat centerVert[3];
	centerVert[0] = hex->mVertices[0][0];
	centerVert[1] = hex->mVertices[0][1];
	centerVert[2] = hex->mVertices[0][2] - (sqrt(3.0f) * hex->mDim);

	Hexagon *newHex = new Hexagon(centerVert[0], centerVert[1], centerVert[2], hex->mDim);
	return newHex;
}

Hexagon *extend180(Hexagon *hex)
{
	GLfloat centerVert[3];
	centerVert[0] = hex->mVertices[0][0] - (hex->mDim * (1.5f));
	centerVert[1] = hex->mVertices[0][1];
	centerVert[2] = hex->mVertices[0][2] - ((sqrt(3.0f) / 2.0f) * hex->mDim);

	Hexagon *newHex = new Hexagon(centerVert[0], centerVert[1], centerVert[2], hex->mDim);
	return newHex;
}

Hexagon *extend240(Hexagon *hex)
{
	GLfloat centerVert[3];
	centerVert[0] = hex->mVertices[0][0] - (hex->mDim * (1.5f));
	centerVert[1] = hex->mVertices[0][1];
	centerVert[2] = hex->mVertices[0][2] + ((sqrt(3.0f) / 2.0f) * hex->mDim);

	Hexagon *newHex = new Hexagon(centerVert[0], centerVert[1], centerVert[2], hex->mDim);
	return newHex;
}

Hexagon *extend300(Hexagon *hex)
{
	GLfloat centerVert[3];
	centerVert[0] = hex->mVertices[0][0];
	centerVert[1] = hex->mVertices[0][1];
	centerVert[2] = hex->mVertices[0][2] + (sqrt(3.0f) * hex->mDim);

	Hexagon *newHex = new Hexagon(centerVert[0], centerVert[1], centerVert[2], hex->mDim);
	return newHex;
}

Hexagon *extend360(Hexagon *hex)
{
	GLfloat centerVert[3];
	centerVert[0] = hex->mVertices[0][0] + (hex->mDim * (1.5f));
	centerVert[1] = hex->mVertices[0][1];
	centerVert[2] = hex->mVertices[0][2] + ((sqrt(3.0f) / 2.0f) * hex->mDim);

	Hexagon *newHex = new Hexagon(centerVert[0], centerVert[1], centerVert[2], hex->mDim);
	return newHex;
}

Extend GetExtendFunc(GLfloat angle)
{
	switch((int)angle)
	{
	case 120:
		return &extend120;
		break;
	case 180:
		return &extend180;
		break;
	case 240:
		return &extend240;
		break;
	case 300:
		return &extend300;
		break;
	case 360:
		return &extend360;
		break;
	case 60:
	default:
		return &extend60;
		break;
	}
}