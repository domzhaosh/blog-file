/************************************************************************		
\link	www.twinklingstar.cn
\author Twinkling Star
\date	2014/06/18
****************************************************************************/
/************************************************************************		
\description	�ڶ�ά�ռ��ϣ�����3�������ߵĵ㣬�������ǵ�����Բ��
				����ά�ռ��ϣ�����4��������ĵ㣬�������ǵ��������壻
****************************************************************************/

#include "../include/SrGeometricTools.h"
#include "../include/SrDataType.h"
#include <stdio.h>
#include <math.h>

/**
\brief 3D sphere class.

This is a 3D sphere class with public data members.
It includes center and radius.
*/
class SrSphere3D
{
public:
	/**
	\brief Default constructor. Set center to (0,0) and radius to 0.
	*/
	SrSphere3D()
	{
		mCenter.set(0,0,0);
		mRadius = -1.0;
	}
	/**
	\brief The circle is initialized by center and radius.
	*/
	SrSphere3D(const SrPoint3D& ct ,SrReal rd)
	{
		mCenter = ct;
		mRadius = rd;
	}
public:
	SrPoint3D	mCenter;
	SrReal		mRadius;
};

/**
\brief 2D circle class.

This is a 2D circle class with public data members.
It includes center and radius.
*/
class SrCircle2D
{
public:
	/**
	\brief Default constructor. Set center to (0,0) and radius to 0.
	*/
	SrCircle2D()
	{
		mCenter.set(0,0);
		mRadius = 0;
	}
	/**
	\brief The circle is initialized by center and radius.
	*/
	SrCircle2D(const SrPoint2D& ct,SrReal rd)
	{
		mCenter = ct;
		mRadius = rd;
	}
public:
	SrPoint2D	mCenter;
	SrReal		mRadius;
};

/*
\brief	�ڶ�ά�ռ��£�����㵽ֱ�ߵľ��롣
\param[in]	p0,p1	ȷ��һ��ֱ�ߣ������ɵ�p0ָ���p1��
*/
SrReal PointToLineDistance(const SrPoint2D& p,const SrPoint2D& p0, const SrPoint2D& p1)
{
	SrVector2D  mBase= p1;
	SrVector2D	mDirection = p1 - p0;
	mDirection.normalize();
	SrVector2D tmp = p - mBase;
	SrReal tmpDot = mDirection.dot(tmp);
	return sqrt(tmp.dot(tmp)-tmpDot*tmpDot);
}

SrReal PointToPlaneDistance(const SrPoint3D& p,const SrPoint3D& p0, const SrPoint3D& p1,const SrPoint3D& p2)
{
	SrVector3D norm = (p1-p0).cross(p2-p0);
	if( EQUAL(norm.x,0)&&EQUAL(norm.y,0)&&EQUAL(norm.z,0) )
		return -1.0;
	SrVector3D mNormal = norm;
	SrReal mD = -mNormal.dot(p0);
	return fabs((p.dot(mNormal)+mD)/mNormal.magnitude());
}

/*
\brief	������������ε�����Բ��
\return true	�������ε��������㲻���ߣ���������Բ��
		false	�������ε��������㹲�ߣ�����������Բ��
*/
bool InitInscribedCircle(const SrPoint2D& p0,const SrPoint2D& p1,const SrPoint2D& p2,SrCircle2D& circle)
{
	SrReal A = fabs((p1-p0).cross(p2-p0));
	//Check the three points are not on one line.
	if( EQUAL(A,0) )
		return false;
	SrReal l0 = (p0-p1).magnitude(), l1 = (p1-p2).magnitude() , l2 = (p2-p0).magnitude();
	SrReal l = l0 + l1 + l2;
	circle.mRadius = A / l;
	circle.mCenter = (l1*p0 + l2*p1 + l0*p2) / l;
	return true;
}

/*
\brief ���Ը���Բ�Ƿ��������ε�����Բ��
\return true	��Բ�ĵ������������ߵľ��붼���ڰ뾶��
		false	��֮��
*/
bool IsInscribedCircle(const SrPoint2D& p0,const SrPoint2D& p1,const SrPoint2D& p2, const SrCircle2D& circle)
{
	if( EQUAL(PointToLineDistance(circle.mCenter,p0,p1),circle.mRadius) &&
		EQUAL(PointToLineDistance(circle.mCenter,p1,p2),circle.mRadius) && 
		EQUAL(PointToLineDistance(circle.mCenter,p2,p0),circle.mRadius))
		return true;
	return false;
}


/*
\brief ����������ݣ����������ε�����Բ�㷨����ȷ�ԡ�
�������ֵ��Χ�ܴ����ھ�ȷ���⣬�ᵼ�´���ķ�����
*/
void Test_InscribedCircle()
{
	int num = 100000 , i;
	SrPoint2D* p0 = new SrPoint2D[num];
	SrPoint2D* p1 = new SrPoint2D[num];
	SrPoint2D* p2 = new SrPoint2D[num];
	int range = 100;
	for( i=0 ; i<num ;  i++ )
	{
		p0[i].x = rand() % range;
		p0[i].y = rand() % range;
		p1[i].x = rand() % range;
		p1[i].y = rand() % range;
		p2[i].x = rand() % range;
		p2[i].y = rand() % range;
	}
	SrCircle2D circle;
	for( i=0 ; i<num ; i++ )
	{
		if( InitInscribedCircle(p0[i],p1[i],p2[i],circle) )
		{
			ASSERT(IsInscribedCircle(p0[i],p1[i],p2[i],circle));
		}
	}
}

/*
\brief	��������������������
\return true	����������ĸ����㲻���棬����������
		false	����������ĸ����㹲�棬������������
*/
bool InitInscribedSphere(const SrPoint3D& p0,const SrPoint3D& p1,const SrPoint3D& p2,const SrPoint3D& p3,SrSphere3D& sphere)
{
	SrVector3D v1 = p1 - p0 , v2 = p2 - p0 , v3 = p3 - p0;
	SrReal V = fabs(v1.dot(v2.cross(v3)));
	if( EQUAL(V,0) )
		return false;
	SrReal a0 , a1 , a2 , a3;
	//Compute the normal of the triangle composed of p1,p2,p3
	SrVector3D n0 = (p2 - p1).cross(p3 - p1);
	n0.normalize();
	//Compute the area of the triangle composed of p1,p2,p3
	a0 = n0.dot(p1.cross(p2) + p2.cross(p3) + p3.cross(p1));

	SrVector3 n1 = (p2 - p0).cross(p3 - p0);
	n1.normalize();
	a1 = n1.dot(p0.cross(p2) + p2.cross(p3) + p3.cross(p0));

	SrVector3 n2 = (p1 - p0).cross(p3 - p0);
	n2.normalize();
	a2 = n2.dot(p0.cross(p1) + p1.cross(p3) + p3.cross(p0));

	SrVector3 n3 = (p1 - p0).cross(p2 - p0);
	n3.normalize();
	a3 = n3.dot(p0.cross(p1) + p1.cross(p2) + p2.cross(p0));

	SrReal A = a0 + a1 + a2 + a3;
	sphere.mRadius = V/A;
	sphere.mCenter = (p0*a0 + p1*a1 + p2*a2 + p3*a3)/A;
	return true;
}

/*
\brief ���Ը������Ƿ����������������
\return true	�����ĵ��������ĸ���ľ��붼���ڰ뾶��
		false	��֮��
*/
bool IsInscribedSphere(const SrPoint3D& p0,const SrPoint3D& p1,const SrPoint3D& p2, const SrPoint3D& p3, const SrSphere3D& sphere)
{
	//������������п����Ǹ��������������ɵ�
	if( EQUAL(PointToPlaneDistance(sphere.mCenter,p0,p1,p2),sphere.mRadius) &&
		EQUAL(PointToPlaneDistance(sphere.mCenter,p0,p2,p3),sphere.mRadius) && 
		EQUAL(PointToPlaneDistance(sphere.mCenter,p0,p1,p3),sphere.mRadius) &&
		EQUAL(PointToPlaneDistance(sphere.mCenter,p1,p2,p3),sphere.mRadius))
		return true;
	return false;
}

/*
\brief ����������ݣ�������������������㷨����ȷ�ԡ�
�������ֵ��Χ�ܴ����ھ�ȷ���⣬�ᵼ�´���ķ�����
*/
void Test_InscribedSphere()
{
	int num = 100000 , i;
	SrPoint3D* p0 = new SrPoint3D[num];
	SrPoint3D* p1 = new SrPoint3D[num];
	SrPoint3D* p2 = new SrPoint3D[num];
	SrPoint3D* p3 = new SrPoint3D[num];
	int range = 10000;
	for( i=0 ; i<num ;  i++ )
	{
		p0[i].x = rand() % range;
		p0[i].y = rand() % range;
		p0[i].z = rand() % range;

		p1[i].x = rand() % range;
		p1[i].y = rand() % range;
		p1[i].z = rand() % range;

		p2[i].x = rand() % range;
		p2[i].y = rand() % range;
		p2[i].z = rand() % range;

		p3[i].x = rand() % range;
		p3[i].y = rand() % range;
		p3[i].z = rand() % range;
	}
	SrSphere3D sphere;
	for( i=0 ; i<num ; i++ )
	{
		if( InitInscribedSphere(p0[i],p1[i],p2[i],p3[i],sphere) )
		{
			ASSERT(IsInscribedSphere(p0[i],p1[i],p2[i],p3[i],sphere));
		}
	}
}

int main( )
{
	Test_InscribedCircle();
	Test_InscribedSphere();
	return 0;
}