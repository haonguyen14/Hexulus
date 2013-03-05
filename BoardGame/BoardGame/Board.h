#include <GLTools.h>

#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

#include "HexLine.h"

class Board
{
public:
	HexLine	**mHexLines;
	int		mInitLineLen;
	int		mLongestLineLen;

	int		mColNum;

protected:
	GLuint	*mHTexture;
	GLint	mNumTextures;

public:
	Board(GLfloat initLineHexX, GLfloat initLineHexY, GLfloat initLineHexZ, GLfloat initLineHexDim, int initLen, int longestLen);
	Board();

	~Board();

	void PrepareBatch(M3DVector2f *texCoor);
	void PrepareTexture(char **textureFiles, GLint numTextures);
	void DrawBoard();
	void GetDimensions(GLint *width, GLint *height);
};
