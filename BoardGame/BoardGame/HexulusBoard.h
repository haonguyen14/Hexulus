#include "Board.h"

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
