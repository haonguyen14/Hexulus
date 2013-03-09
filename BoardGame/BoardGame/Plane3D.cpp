#include "Includes\Plane3D.h"

Plane3D::Plane3D()
{
}

Plane3D::Plane3D(Vector3D normal, Vector3D point)
{
	mPoint = point;
	mNormal = normal.normalize();
	mD = mNormal.dotProduct(mPoint);
}

Plane3D::Plane3D(Vector3D a, Vector3D b, Vector3D c)
{
	mPoint = a;

	Vector3D ab = b.sub(a);	//vector ab
	Vector3D ac = c.sub(a);	//vector ac
	mNormal = ab.crossProduct(ac);

	mD = mNormal.dotProduct(mPoint);
}

Plane3D::~Plane3D()
{
}
