#ifndef CARDPIECE_H
#define CARDPIECE_H

#include "Hexagon.h"
#include "Vector3D.h"
#include "LocalFrame.h"
#include "math3d.h"

#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

class CardPiece : public Hexagon
{
private:
	Hexagon *mBase;
	LocalFrame	mFrame;

	Vector3D mVelocity;
public:
	CardPiece(void);
	CardPiece(GLfloat y, char *texture, Hexagon *base);
	~CardPiece(void);

	void MoveTo(GLint angle, Hexagon *hexagon);
	LocalFrame GetFrame(float timeElapsed);
	bool IsOnBase();

private:
	void Move30To(Hexagon *hexagon);
	void Move90To(Hexagon *hexagon);
	void Move150To(Hexagon *hexagon);
	void Move210To(Hexagon *hexagon);
	void Move270To(Hexagon *hexagon);
	void Move330To(Hexagon *hexagon);
};

#endif

