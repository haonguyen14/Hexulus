#ifndef HEXLINE_H
#define HEXLINE_H

#include <GLTools.h>
#include <GLShaderManager.h>

#include "Hexagon.h"

#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

class HexLine
{
public:
	GLfloat mAngle;		//in degree
	GLint	mLen;		//the number of hexagons extending
	Hexagon **mHexes;

public:
	HexLine();
	HexLine(GLfloat firstHexX, GLfloat firstHexY, GLfloat firstHexZ, GLfloat dim, GLfloat angle, GLint len);

	~HexLine();
};


#endif