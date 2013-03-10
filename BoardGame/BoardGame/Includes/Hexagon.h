#ifndef HEXAGON_H
#define HEXAGON_H

#include <GLTools.h>
#include <Vector3D.h>

#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

class Hexagon
{
private:
	GLBatch	mHexBatch;
	GLuint	mHTexture;

public:
	//GLfloat mColor[4];
	GLfloat mVertices[8][3];		//{ce, lt, lm, lb, rt, rm, rb}
	GLfloat mDim;			//dimensions of hexagon's sides

	Vector3D mNormal;

	Hexagon();
	Hexagon(GLfloat centerx, GLfloat centery, GLfloat centerz, GLfloat dim);
	~Hexagon();

	void PrepareBatch(M3DVector2f *texCoor, GLboolean hasTexture);
	void PrepareTexture(char *textureFile);
	void DrawHex(GLboolean withTexture);
	void DrawHex(GLuint hTexture);
};

#endif
