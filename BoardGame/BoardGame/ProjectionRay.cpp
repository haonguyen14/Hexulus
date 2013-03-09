#include "Includes\ProjectionRay.h"
#include <math.h>


ProjectionRay::ProjectionRay()
{
}

ProjectionRay::ProjectionRay(Vector3D point, Vector3D direction):Line3D(point, direction) { }

ProjectionRay::ProjectionRay(GLfloat _mouseX, GLfloat _mouseY, Vector3D cameraPos, Vector3D cameraLookAt, Vector3D cameraUp, GLfloat fovy, GLfloat aspect, GLfloat nearPlane, GLfloat farPlane)
{
	//Get viewport information
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	//Convert Windows Coordinate to Viewport Coordinate (Near Plane Coordinate)
	GLfloat mouseX = _mouseX - ((GLfloat)viewport[2] / 2.0f);
	GLfloat mouseY = ((GLfloat)viewport[3] - _mouseY) - ((GLfloat)viewport[3] / 2.0f);

	mouseX  = mouseX / ((GLfloat)viewport[2] / 2);
	mouseY	= mouseY / ((GLfloat)viewport[3] / 2);

	//Let v and h are the axis on the Viewport (Near Plane Coordinate)
	Vector3D cameraDir = cameraLookAt.sub(cameraPos).normalize();
	
	GLfloat vLength = (GLfloat)tanf((float)fovy) * nearPlane;
	GLfloat hLength = vLength * (aspect);

	Vector3D h = cameraDir.crossProduct(cameraUp).normalize().scalarMul(hLength); 
	Vector3D v = cameraUp.normalize().scalarMul(vLength);

	//update mPoint and mDirection
	mPoint = cameraPos.add(cameraDir.scalarMul(nearPlane).add(h.scalarMul(mouseX).add(v.scalarMul(mouseY))));
	mDirection = mPoint.sub(cameraPos);
}


ProjectionRay::~ProjectionRay()
{
}


Vector3D *ProjectionRay::planeIntersect(Plane3D plane)
{
	//the ray and the plane intesect as long as this equation is true
	//			mNormal dot ( mPoint + (t * mDirection) ) = mD
	//			t = (mD - ( mNormal dot mPoint)) / (mNormal dot mDirection)

	GLfloat bottom = plane.mNormal.dotProduct(this->mDirection);
	GLfloat top = plane.mD - (plane.mNormal.dotProduct(this->mPoint));
	
	if(bottom == 0)
		return NULL;	//parallel to the plane

	GLfloat t = top / bottom;
	if(t < 0)
		return NULL;	//intersect the plane from behind the viewport

	Vector3D intersection = this->mPoint.add(this->mDirection.scalarMul(t));
	return new Vector3D(intersection.mX, intersection.mY, intersection.mZ);
}
