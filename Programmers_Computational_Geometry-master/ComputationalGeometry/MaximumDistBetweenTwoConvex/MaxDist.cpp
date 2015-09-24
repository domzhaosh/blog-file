///************************************************************************		
//\link	www.twinklingstar.cn
//\author Twinkling Star
//\date	2014/10/28
//****************************************************************************/
#include "SrGeometricTools.h"
#include "SrDataType.h"
#include <time.h>
#include <stdio.h>

#define Real		SrReal
#define Point2D		SrPoint2D
#define Vector2D	SrVector2D

/*
\brief	����������ڲ��Ե�͹����Σ����ɵ�͹���������ʱ��˳��ģ���һ��Բ����
\param[in]	numPoint	�涨���ɵ�͹����ζ������
\param[in]	radius		�涨Բ�̵İ뾶
\param[in]	center		�涨Բ�̵�����
\param[out]	pts			����ζ����ָ��
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
\brief	�Ƚ������������Ĵ�С�����ؽϴ�ֵ
*/
Real Max(Real a , Real b)
{
	return (a>b)?a:b;
}

/*
\brief	��ת�⾶������������͹����ε�������
*/
Real MaximumDist_RotatingCalipers(const Point2D* pts1,int n1, const Point2D* pts2, int n2)
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
	Real maxDist = 0 , dist;
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
			dist = (pts1[nxInx1] - pts2[crInx2]).magnitude();
			maxDist = Max(dist , maxDist);

			crInx1 = Next(crInx1 , n1);
			cnt1 += 1;
		}
		else
		{//��ת͹�����pts2����
			dist = (pts2[nxInx2] - pts1[crInx1]).magnitude();
			maxDist = Max(dist , maxDist);

			crInx2 = Next(crInx2 , n2);
			cnt2 += 1;
		}
	}while( cnt1 <= n1 || cnt2 <= n2 );

	return maxDist;
}

/*
\brief	����������������͹����ε�������
*/
Real MaximumDist_Naive(const Point2D* pts1,int n1, const Point2D* pts2, int n2)
{
	Real dist , maxDist = 0;
	int i , j;
	for( i = 0 ; i < n1 ; ++i )
	{
		for( j = 0 ; j < n2 ; ++j )
		{
			//��pts1[i]��pts2[j]֮��ľ���
			dist = (pts1[i] - pts2[j]).magnitude();
			maxDist = Max(dist,maxDist);
		}
	}
	return maxDist;
}

void Test()
{
	int n1 = 200;
	Point2D* pts1 = new Point2D[n1];
	GenerateConvex(n1,1000,Point2D(0,0),pts1);

	int n2 = 300;
	Point2D* pts2 = new Point2D[n2];
	GenerateConvex(n2,1000,Point2D(5000,5000),pts2);

	Real dist1 = MaximumDist_RotatingCalipers(pts1,n1,pts2,n2);
	Real dist2 = MaximumDist_Naive(pts1,n1,pts2,n2);

	//�Ա���ת�⾶���ͱ����������㷨������Ľ���������㷨����ȷ��
	ASSERT(EQUAL(dist1,dist2));
	printf("Maximum Distance-Rotating Calipers:\t%f\n",dist1);
	printf("Maximum Distance-Naive	          :\t%f\n",dist2);

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