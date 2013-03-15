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
	
	GLfloat vLength = (GLfloat)tanf((float)fovy / 2.0f) * nearPlane;
	GLfloat hLength = vLength * (aspect);

	Vector3D h = cameraDir.crossProduct(cameraUp).normalize().scalarMul(hLength); 
	Vector3D v = cameraUp.normalize().scalarMul(vLength);

	//update mPoint and mDirection
	mPoint = cameraPos.add(cameraDir.scalarMul(nearPlane).add(h.scalarMul(mouseX).add(v.scalarMul(mouseY))));
	mDirection = mPoint.sub(cameraPos);
}

ProjectionRay::ProjectionRay(GLfloat _mouseX, GLfloat _mouseY, GLFrame cameraFrame, GLfloat fovy, GLfloat aspect, GLfloat nearPlane, GLfloat farPlane)
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
	Vector3D cameraPos((GLfloat)cameraFrame.GetOriginX(), (GLfloat)cameraFrame.GetOriginY(), (GLfloat)cameraFrame.GetOriginZ());
	
	float temp[3];
	cameraFrame.GetUpVector(temp);
	Vector3D cameraUp((GLfloat)temp[0], (GLfloat)temp[1], (GLfloat)temp[2]);

	cameraFrame.GetForwardVector(temp);
	Vector3D cameraDir((GLfloat)temp[0], (GLfloat)temp[1], (GLfloat)temp[2]);
	cameraDir.normalize();

	GLfloat vLength = (GLfloat)tanf((float)fovy / 2.0f) * nearPlane;
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


bool ProjectionRay::hexagonIntersect(Hexagon *hex)
{
	//check if the ray intersect with the plan of the hexagon
	Vector3D hexCenter(hex->mVertices[0][0], hex->mVertices[0][1], hex->mVertices[0][2]);
	Plane3D plane(hex->mNormal, hexCenter);

	Vector3D *intersect = this->planeIntersect(plane);
	if(intersect == NULL)
		return NULL;	//not intersect with the plane

	//check if the intersecting point is inside the hexagon using counterclock wise curling
	Vector3D point1;
	Vector3D point2;

	Vector3D side1;
	Vector3D side2;

	Vector3D cross;

	for(int i = 1; i < 6; i++)
	{
		point1 = Vector3D(hex->mVertices[i][0], hex->mVertices[i][1], hex->mVertices[i][2]);
		point2 = Vector3D(hex->mVertices[i+1][0], hex->mVertices[i+1][1], hex->mVertices[i+1][2]);

		side1 = point2.sub(point1);
		side2 = intersect->sub(point1);

		cross = side1.crossProduct(side2);
		
		if(cross.dotProduct(hex->mNormal) < 0.0f)
			return false;
	}

	//check the last side of the hexagon
	point1 = Vector3D(hex->mVertices[6][0], hex->mVertices[6][1], hex->mVertices[6][2]);
	point2 = Vector3D(hex->mVertices[1][0], hex->mVertices[1][1], hex->mVertices[1][2]);

	side1 = point2.sub(point1);
	side2 = intersect->sub(point1);

	cross = side1.crossProduct(side2);
	if(cross.dotProduct(hex->mNormal) < 0.0f)
			return false;

	delete intersect;
	return true;
}
