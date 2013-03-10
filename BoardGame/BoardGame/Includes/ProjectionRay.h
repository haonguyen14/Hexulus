#include "GLFrame.h"

#include "Hexagon.h"
#include "Line3D.h"
#include "Plane3D.h"

#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

class ProjectionRay : public Line3D
{
public:
	ProjectionRay();
	ProjectionRay(Vector3D point, Vector3D direction);

	//constructors are for picking ray special use
	ProjectionRay(GLfloat mouseX, GLfloat mouseY, Vector3D cameraPos, Vector3D cameraLookAt, Vector3D cameraUp, GLfloat fovy, GLfloat aspect, GLfloat near, GLfloat far);
	ProjectionRay(GLfloat mouseX, GLfloat mouseY, GLFrame cameraFrame, GLfloat fovy, GLfloat aspect, GLfloat near, GLfloat far);
	//////////////////////////////////////////////////

	~ProjectionRay();

	Vector3D *planeIntersect(Plane3D plane);
	bool hexagonIntersect(Hexagon *hex);
};

