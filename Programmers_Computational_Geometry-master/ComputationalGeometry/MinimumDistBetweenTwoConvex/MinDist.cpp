///************************************************************************		
//\link	www.twinklingstar.cn
//\author Twinkling Star
//\date	2014/10/27
//****************************************************************************/
#include "SrGeometricTools.h"
#include "SrDataType.h"
#include <time.h>
#include <stdio.h>

#define Real		SrReal
#define Point2D		SrPoint2D
#define Vector2D	SrVector2D

/*
\brief	����������ڲ��Ե�͹����Σ����ɵ�͹���������ʱ��˳��ġ�
*/
void GenerateConvex(int numPoint, Real radius, const Point2D& center,Point2D* pts )
{
	ASSERT(numPoint>=3);

	Real*	angle = new Real[numPoint];
	int range = 1000;
	int	base  = 100;
	Real sum = 0 , partSum = 0, curAngle;
	int i;
	for( i=0 ; i<numPoint ; i++ )
	{
		angle[i] = ((rand() % range) + base) / (Real)(range);
		sum += angle[i];
	}
	for( i=0 ; i<numPoint ; i++ )
	{
		partSum += angle[i];
		curAngle = 2*SrPiF32*partSum / sum;
		pts[i].x = -sin(curAngle)*radius + center.x;
		pts[i].y = cos(curAngle)*radius + center.y;
	}
	delete []angle;
}

/*
\brief	��͹������϶���indx����һ������
*/
int Next(int indx, int n)
{
	if( indx==n-1 )
		return 0;
	else
		return indx + 1;
}
/*
\brief	�Ƚ������������Ĵ�С�����ؽ�Сֵ
*/
Real Min(Real a , Real b)
{
	return (a>b)?b:a;
}


/*
\brief	�����q���߶�p1-p2�ľ���
*/
Real PointDistSegment(const Point2D& p1, const Point2D& p2,const Point2D& q)
{
	Vector2D d = p2 - p1;
	Vector2D pp1 = q - p1;
	Real t = d.dot(pp1);
	//t<=0
	if( t<=0 )
	{
		//t<=0.Minimum distance is from p to point1.
		return sqrt(pp1.dot(pp1));
	}
	Real dDotd = d.dot(d);
	//The division can be deferred until absolutely needed.
	if( t >= dDotd )
	{
		//t>=1,Minimum distance is from p to point2.
		Vector2D pp2 = q - p2;
		return sqrt(pp2.dot(pp2));
	}
	//Intersection point is on the segment.
	return sqrt(pp1.dot(pp1) - t*t / dDotd);
}

/*
\brief	�����-�߶���Եľ��룬�����Ϊq,�����Ϊp1-p2
*/
Real ComputeAntiDist(const Point2D& p1, const Point2D& p2, const Point2D& q)
{
	Vector2D direction = p2 - p1;
	Vector2D vec1 = q - p1;
	Vector2D vec2 = q - p2;
	Real t1 = direction.dot(vec1);
	Real t2 = direction.dot(vec2);
	Real d;
	Vector2D normal;
	if( (t1 <= 0 && t2 >= 0) || (t1 >= 0 && t2 <= 0) )
	{
		normal = Vector2D(-direction.y , direction.x);
		d = -normal.dot(p1);

		return fabs(normal.dot(q) + d) / normal.magnitude();
	}
	else
	{
		return ((q - p2).magnitude());
	}
}

/*
\brief	��ת�⾶�������㲻�ཻ������͹�����֮��ľ���
*/
Real MinimumDist_RotatingCalipers(const Point2D* pts1,int n1, const Point2D* pts2, int n2)
{
	int i;
	//������pts1�ϣ�Y�᷽����ֵ��С�ĵ�
	int mnInx = 0;
	for( i = 1 ; i < n1 ; ++ i )
	{
		if( pts1[i].y < pts1[mnInx].y )
			mnInx = i;
	}
	//������pts2�ϣ�Y�᷽����ֵ���ĵ�
	int mxInx = 0;
	for( i = 0 ; i < n2 ; ++i )
	{
		if( pts2[i].y > pts2[mxInx].y )
			mxInx = i;
	}
	int crInx1 = mnInx , crInx2 = mxInx;
	Real minDist = SR_MAX_F32 , dist;
	int cnt1 = 0, cnt2 = 0;
	do
	{
		int nxInx1 = Next(crInx1 , n1);
		int nxInx2 = Next(crInx2 , n2);
		Vector2D d1 = pts1[nxInx1] - pts1[crInx1];
		Vector2D d2 = pts2[nxInx2] - pts2[crInx2];
		Real angle = d1.cross(d2);

		
		if( angle < 0 )
		{//��ת͹�����pts1����
			dist = ComputeAntiDist(pts1[crInx1],pts1[nxInx1],pts2[crInx2]);
			minDist = Min(dist , minDist);
			
			crInx1 = Next(crInx1 , n1);
			cnt1 += 1;
		}
		else
		{//��ת͹�����pts2����
			dist = ComputeAntiDist(pts2[crInx2],pts2[nxInx2],pts1[crInx1]);
			minDist = Min(dist , minDist);

			crInx2 = Next(crInx2 , n2);
			cnt2 += 1;
		}
	}while( cnt1 <= n1 || cnt2 <= n2 );

	return minDist;
}

/*
\brief	�������������������ཻ��͹�����֮��ľ���
*/
Real MinimumDist_Naive(const Point2D* pts1,int n1, const Point2D* pts2, int n2)
{
	Real dist , minDist = SR_MAX_F32;
	int i , j;
	for( i = 0 ; i < n1 ; ++i )
	{
		for( j = 0 ; j < n2 ; ++j )
		{
			//��pts1[i]��pts2[j]֮��ľ���
			dist = (pts1[i] - pts2[j]).magnitude();
			minDist = Min(dist,minDist);

			//��pts2[j]���߶�pts1[i]-pts1[Next(i,n1)]֮��ľ���
			dist = PointDistSegment(pts1[i] , pts1[Next(i,n1)] , pts2[j]);
			minDist = Min(dist,minDist);

			//��pts1[i]���߶�pts2[j]-pts2[Next(j,n2)]֮��ľ���
			dist = PointDistSegment(pts2[j] , pts2[Next(j,n2)] , pts1[i]);
			minDist = Min(dist,minDist);
		}
	}
	return minDist;
}

void Test()
{
	int n1 = 200;
	Point2D* pts1 = new Point2D[n1];
	GenerateConvex(n1,1000,Point2D(0,0),pts1);

	int n2 = 300;
	Point2D* pts2 = new Point2D[n2];
	GenerateConvex(n2,1000,Point2D(5000,5000),pts2);

	Real dist1 = MinimumDist_RotatingCalipers(pts1,n1,pts2,n2);
	Real dist2 = MinimumDist_Naive(pts1,n1,pts2,n2);

	//�Ա���ת�⾶���ͱ����������㷨������Ľ���������㷨����ȷ��
	ASSERT(EQUAL(dist1,dist2));
	printf("Minimum Distance-Rotating Calipers:\t%f\n",dist1);
	printf("Minimum Distance-Naive	          :\t%f\n",dist2);

	delete []pts1;
	delete []pts2;
}

int main()
{
	int cntCas = 100;
	int total = cntCas;
	while( cntCas-- )
	{
		printf("Case %d:\n",total-cntCas);
		Test();
	}
	return 0;
}