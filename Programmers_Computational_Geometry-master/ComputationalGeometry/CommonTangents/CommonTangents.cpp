///************************************************************************		
//\link	www.twinklingstar.cn
//\author Twinkling Star
//\date	2014/11/08
//****************************************************************************/
#include "SrGeometricTools.h"
#include "SrDataType.h"
#include <time.h>
#include <stdio.h>

#define Real		SrReal
#define Point2D		SrPoint2D
#define Vector2D	SrVector2D

#define EPS			SR_EPS


int Next( int i , int n )
{
	return (i + 1) % n;
}

int Last( int i , int n)
{
	return ( i - 1 + n) % n;
}

/*
\brief	�������͹�����P��Q���Žӱߣ���͹���������ʱ�뷽���Ҳ����������Լ�������ǰ�ĵ㹲��
\param[in]	p,n		�涨͹�����P
\param[in]	q,m		�涨͹�����Q
\param[out] t0,t1	��ʾ�Žӱߣ��Žӱߵ���ֻ���������ֱ�Ϊt0[0]-t1[0],t0[1]-t1[1]��
					t0[0],t0[1]��ʾ�����P�ϵĵ㣬t1[0],t1[1]��ʾ�����Q�ϵĵ�
*/
void CommonTangents( const Point2D* p, int n , const Point2D* q, int m, int* t0, int* t1)
{
	//��������P�ϣ�X�������ĵ�
	int pm = 0, qm = 0, i;
	for( i = 1 ; i < n ; ++ i )
	{
		if( p[i].x > p[pm].x )
			pm = i;
	}
	//��������Q�ϣ�X�������ĵ�
	for( i = 1 ; i < m ; ++ i )
	{
		if( q[i].x > q[qm].x )
			qm = i;
	}
	int pc = 0, qc = 0;
	int pn, qn;
	int k = 0, t = 0;
	int pNext, pLast, qNext, qLast;
	Vector2D ep, eq, e, norm;
	Real p0, p1, q0, q1;

	//���ó�ʼֵ
	t0[0] = t0[1] = -1;
	t1[0] = t1[1] = -1;

	while( pc <= n || qc <= m )
	{
		pn = Next(pm,n);
		qn = Next(qm,m);
		ep = p[pn] - p[pm];
		eq = q[qn] - q[qm];
		if( ep.cross(eq) > 0 )
		{//���ն����P�ıߣ���ת֧����
			pm = pn;
			pc += 1;
		}
		else
		{//���ն����Q�ıߣ���ת֧����
			qm = qn;
			qc += 1;
		}
		pNext = Next(pm,n);
		pLast = Last(pm,n);
		qNext = Next(qm,m);
		qLast = Last(qm,m);

		//�ߵķ�������
		e = p[pm] - q[qm];
		norm = Vector2D(-e.y,e.x);

		p0 = norm.dot(p[pNext] - p[pm]);
		p1 = norm.dot(p[pLast] - p[pm]);
		q0 = norm.dot(q[qNext] - q[qm]);
		q1 = norm.dot(q[qLast] - q[qm]);
		
		if( (p0 >= 0 && p1 >= 0 && q0 >= 0 && q1 >= 0) || (p0 <= 0 && p1 <= 0 && q0 <= 0 && q1 <= 0) )
		{//���Ⱥų�������ʾ͹������ϴ��ڱߣ���p[pm]-q[qm]�߹���
			if(fabs(p0) < EPS && (p[pNext] - q[qm]).magnitudeSquared() > (p[pm] - q[qm]).magnitudeSquared())
				t = pNext;
			else if(fabs(p1) < EPS && (p[pLast] - q[qm]).magnitudeSquared() > (p[pm] - q[qm]).magnitudeSquared())
				t = pLast;
			else
				t = pm;
			if( k == 0 || t != t0[k - 1] )
			{
				t0[k] = t;
			}
	
			if(fabs(q0) < EPS && (q[qNext] - p[pm]).magnitudeSquared() > (q[qm] - p[pm]).magnitudeSquared())
				t = qNext;
			else if(fabs(q1) < EPS && (q[qLast] - p[pm]).magnitudeSquared() > (q[qm] - p[pm]).magnitudeSquared())
				t = qLast;
			else
				t = qm;
			if( k == 0 || t != t1[k - 1] )
			{
				t1[k] = t;
				k += 1;
			}
		}
	}
}

void Test()
{
	int n = 5;
	Point2D* p = new Point2D[n];
	p[0] = Point2D(0,1);
	p[1] = Point2D(1,0);
	p[2] = Point2D(3,0);
	p[3] = Point2D(3,1);
	p[4] = Point2D(2,2);

	int m = 6;
	Point2D* q = new Point2D[m];
	q[0] = Point2D(4,1);
	q[1] = Point2D(6,0);
	q[2] = Point2D(7,0);
	q[3] = Point2D(8,1);
	q[4] = Point2D(7,2);
	q[5] = Point2D(5,2);

	int t0[2], t1[2];
	CommonTangents(p,n,q,m,t0,t1);

	printf("Common Tangents:\n");
	printf("(%d,%d)\n",t0[0],t1[0]);
	printf("(%d,%d)\n",t0[1],t1[1]);
}

int main()
{
	Test();
	return 0;
}