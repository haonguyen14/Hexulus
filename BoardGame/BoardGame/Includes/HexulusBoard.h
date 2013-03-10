#ifndef HEXULUSBOARD_H
#define HEXULUSBOARD_H

#include "Board.h"

#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

class HexulusBoard : public Board
{
public:
	HexulusBoard();
	HexulusBoard(GLfloat initLineHexX, GLfloat initLineHexY, GLfloat initLineHexZ, GLfloat initLineHexDim);

	void DrawBoard();

private:
	GLuint AssignColorTexture(int i, int j, GLuint hPlayerTexture, GLuint hOpponentTexture, GLuint hNeutralTexture);
	GLuint AssignGrayScaleTexture(int i, int j);
};

#endif
