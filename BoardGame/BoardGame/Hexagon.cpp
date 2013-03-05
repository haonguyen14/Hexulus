#include "Hexagon.h"
#include "Ultilities.h"
#include <math.h>


//initialize the other vertices in order
Hexagon::Hexagon(GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat dim)
{
	mDim = dim;
	mVertices[0][0] = centerX;
	mVertices[0][1] = centerY;
	mVertices[0][2] = centerZ;

	//initialize vertices
	//		2---1
	//     /	 \
	//    3   0   6
	//	   \     /
	//      4---5
	//////////////////////

	GLfloat leftX = mVertices[0][0] - (mDim / 2.0f);
	GLfloat rightX = mVertices[0][0] + (mDim / 2.0f);

	GLfloat topZ = mVertices[0][2] - ((sqrt(3.0f) / 2.0f) * mDim);
	GLfloat bottomZ = mVertices[0][2] + ((sqrt(3.0f) / 2.0f) * mDim);

	mVertices[1][0] = rightX;
	mVertices[1][1] = mVertices[0][1];
	mVertices[1][2] = topZ;

	mVertices[2][0] = leftX;
	mVertices[2][1] = mVertices[0][1];
	mVertices[2][2] = topZ;

	mVertices[3][0] = mVertices[0][0] - mDim;
	mVertices[3][1] = mVertices[0][1];
	mVertices[3][2] = mVertices[0][2];

	mVertices[4][0] = leftX;
	mVertices[4][1] = mVertices[0][1];
	mVertices[4][2] = bottomZ;

	mVertices[5][0] = rightX;
	mVertices[5][1] = mVertices[0][1];
	mVertices[5][2] = bottomZ;

	mVertices[6][0] = mVertices[0][0] + mDim;
	mVertices[6][1] = mVertices[0][1];
	mVertices[6][2] = mVertices[0][2];

	//connect the last side
	mVertices[7][0] = rightX;
	mVertices[7][1] = mVertices[0][1];
	mVertices[7][2] = topZ;
}

Hexagon::~Hexagon()
{
	glDeleteTextures(1, &mHTexture);
}

void Hexagon::PrepareBatch(M3DVector2f *texCoor, GLboolean hasTexture)
{
	GLint numTexture = 0;
	if(hasTexture)
		numTexture = 1;

	mHexBatch.Begin(GL_TRIANGLE_FAN, 8, numTexture);
	if(hasTexture)
		mHexBatch.CopyTexCoordData2f(texCoor, 0);
	mHexBatch.CopyVertexData3f(mVertices);
	mHexBatch.End();
}

void Hexagon::PrepareTexture(char *textureFile)
{
	if(textureFile)
	{
		if(!LoadTextures(textureFile, &mHTexture))
			glDeleteTextures(1, &mHTexture);
	}
}

void Hexagon::DrawHex(GLboolean withTexture)
{
	if(withTexture)
		glBindTexture(GL_TEXTURE_2D, mHTexture);
	mHexBatch.Draw();
}

void Hexagon::DrawHex(GLuint hTexture)
{
	glBindTexture(GL_TEXTURE_2D, hTexture);
	mHexBatch.Draw();
}

Hexagon::Hexagon()
{
}

