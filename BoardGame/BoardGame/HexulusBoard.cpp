#include "Includes/HexulusBoard.h"

HexulusBoard::HexulusBoard():Board(){}

HexulusBoard::HexulusBoard(GLfloat initLineHexX, GLfloat initLineHexY, GLfloat initLineHexZ, GLfloat initLineHexDim)
	:Board(initLineHexX, initLineHexY, initLineHexZ, initLineHexDim, 6, 11)
{
}

void HexulusBoard::DrawBoard()
{
	if(mNumTextures > 0)
	{
		for(int i = 0; i < mColNum; i++)
		{
			for(int j = 0; j < mHexLines[i]->mLen; j++)
			{
				mHexLines[i]->mHexes[j]->DrawHex(AssignColorTexture(i, j, mHTexture[0], mHTexture[1], mHTexture[2]));
			}
		}
	}
}

GLuint HexulusBoard::AssignColorTexture(int i, int j, GLuint hPlayerTexture, GLuint hOpponentTexture, GLuint hNeutralTexture)
{
	//this block of code is used to loop the i back if it is greater than 5 
	int temp = i;
	if(temp > 5)
	{
		temp = 10 - temp;
	}

	//this player region
	if((j >= 0) && (j <= 2))
	{
		return hPlayerTexture;
	}
	//neutral region
	else if((j >= 3) && (j <= (2 + temp)))
	{
		return hNeutralTexture;
	}
	//opponent region
	else
	{
		return hOpponentTexture;
	}
}

GLuint HexulusBoard::AssignGrayScaleTexture(int i, int j)
{
	return 0;
}