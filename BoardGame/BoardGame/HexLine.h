#include <GLTools.h>
#include <GLShaderManager.h>

#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

#include "Hexagon.h"

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