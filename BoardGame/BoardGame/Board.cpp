#include "Includes/Board.h"
#include "Includes/Ultilities.h"
#include "math.h"

#include <iostream>


Board::Board()
{
}

Board::Board(GLfloat initLineHexX, GLfloat initLineHexY, GLfloat initLineHexZ, GLfloat initLineHexDim, int initLen, int longestLen)
{
	mInitLineLen = initLen;
	mLongestLineLen = longestLen;
	mColNum = (((mLongestLineLen - mInitLineLen) * 2) + 1);

	//initialize the board mesh
	mColNum = (((mLongestLineLen - mInitLineLen) * 2) + 1);
	mHexLines = (HexLine **)malloc(sizeof(HexLine *) * mColNum);

	mHTexture = NULL;
	mNumTextures = 0;

	//initialize HexLine columns
	Hexagon *firstHex = new Hexagon(initLineHexX, initLineHexY, initLineHexZ, initLineHexDim);
	//coordinates of the next hexagon. Just to make life easier
	GLfloat nextHex[4];

	bool cntState = true;			//true means increasing the lenCnt. Also cntState determines how to calculate the next hexagon
	int lenCnt = mInitLineLen;

	for(int i = 0; i < mColNum; i++)
	{
		if(lenCnt == mLongestLineLen)
			cntState = false;

		//lenCnt++
		if(cntState)
		{
			mHexLines[i] = new HexLine(firstHex->mVertices[0][0], firstHex->mVertices[0][1], firstHex->mVertices[0][2], firstHex->mDim, 120.0f, lenCnt);
			
			nextHex[0] = firstHex->mVertices[0][0] + (firstHex->mDim * 1.5f);
			nextHex[1] = firstHex->mVertices[0][1];
			nextHex[2] = firstHex->mVertices[0][2] + ((sqrt(3.0f) / 2.0f) * firstHex->mDim);
			nextHex[3] = firstHex->mDim;
			delete firstHex;

			firstHex = new Hexagon(nextHex[0], nextHex[1], nextHex[2], nextHex[3]);
			lenCnt++;
		}
		else
		{
			mHexLines[i] = new HexLine(firstHex->mVertices[0][0], firstHex->mVertices[0][1], firstHex->mVertices[0][2], firstHex->mDim, 120.0f, lenCnt);
			
			nextHex[0] = firstHex->mVertices[0][0] + (firstHex->mDim * 1.5f);
			nextHex[1] = firstHex->mVertices[0][1];
			nextHex[2] = firstHex->mVertices[0][2] - ((sqrt(3.0f) / 2.0f) * firstHex->mDim);
			nextHex[3] = firstHex->mDim;
			delete firstHex;

			firstHex = new Hexagon(nextHex[0], nextHex[1], nextHex[2], nextHex[3]);
			lenCnt--;
		}
	}
}

//Return array of batches used for rendering
//Don't overflow the numTextures argument
void Board::PrepareBatch(M3DVector2f *texCoor)
{
	GLboolean hasTexture = true;
	if(mNumTextures <= 0)
		hasTexture = false;

	//populate batches
	//Texture Coordinates subject to changes in the future for optimizing purposes
	//GLfloat texCoor[8][2] = {{0.5f, 1.0 - 0.5f}, {0.731f, 1.0 - 0.00333f}, {0.272f, 1.0 - 0.00333f}, {0.0427f, 1.0 - 0.502f}, {0.272f, 1.0 - 0.997f}, {0.731f, 1.0 - 0.997f}, {0.959f, 1.0 - 0.502f}, {0.731f, 1.0 - 0.00333f}};

	//populate batches
	for(int i = 0; i < mColNum; i++)		//hexBatch counter
	{
		for(int j = 0; j < this->mHexLines[i]->mLen; j++)	//hexLine counter
		{
			this->mHexLines[i]->mHexes[j]->PrepareBatch(texCoor, hasTexture);
		}
	}
}

void Board::PrepareTexture(char **textureFiles, GLint numTextures)
{
	if((textureFiles == NULL) || (numTextures == 0))	//no texture
	{
		mNumTextures = 0;
	}
	else                                                                   //with texture
	{
		mNumTextures = numTextures;
		mHTexture = (GLuint *)malloc(sizeof(GLuint *) * numTextures);
		if(!LoadTextures(textureFiles, mHTexture, numTextures))
		{
			glDeleteTextures(mNumTextures, mHTexture);
			mHTexture = NULL;
			mNumTextures = 0;
		}
	}
}

void Board::DrawBoard()
{
	for(int i = 0; i < mColNum; i++)
	{
		for(int j = 0; j < mHexLines[i]->mLen; j++)
		{
			if(mNumTextures <= 0)
				mHexLines[i]->mHexes[j]->DrawHex((GLboolean)true);
			else
				mHexLines[i]->mHexes[j]->DrawHex(mHTexture[0]);
		}
	}
}



void Board::GetDimensions(GLint *width, GLint *height)
{
	//get board's width
	*width =  this->mHexLines[mColNum - 1]->mHexes[0]->mVertices[6][0] - this->mHexLines[0]->mHexes[0]->mVertices[3][0];

	//get board's height
	*height = (GLfloat)mLongestLineLen * sqrt(3.0f) * this->mHexLines[0]->mHexes[0]->mDim;
}


Board::~Board()
{
	for(int i = 0; i < mColNum; i++)
		delete mHexLines[i];
	free(mHexLines);

	glDeleteTextures(mNumTextures, mHTexture);
	free(mHTexture);
}