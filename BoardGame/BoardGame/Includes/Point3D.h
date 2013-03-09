#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

class Point3D
{
public:
	GLfloat mX;
	GLfloat mY;
	GLfloat mZ;
public:
	Point3D();
	Point3D(GLfloat x, GLfloat y, GLfloat z);
	~Point3D();
};

