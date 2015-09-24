/************************************************************************		
\link	www.twinklingstar.cn
\author Twinkling Star
\date	2013/11/23
****************************************************************************/
#include "SrCameraBase.h"
#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glaux.h>		// Header File For The Glaux Library



SrCameraBase::SrCameraBase(double			doFovy,
							double			doZNear,
							double			doZFar,
							int			inViewX,
							int			inViewY,
							int			unWidth,
							int			unHeight,
							const SrPoint3D& origin)
{
	m_cameraDesc.fovy	=	doFovy;
	m_cameraDesc.zNear	=	doZNear;
	m_cameraDesc.zFar	=	doZFar;
	m_cameraDesc.viewX	=	inViewX;
	m_cameraDesc.viewY	=	inViewY;
	m_cameraDesc.width =	unWidth;
	m_cameraDesc.height=	unHeight;


	m_moveDist	= origin;
	m_rotAngle  = SrVector3(0,0,0);

	for(int i=0 ; i<16 ; i++ )
		m_lastMatrix[i] = 0.0f;
	m_lastMatrix[0] = 1.0f;
	m_lastMatrix[5] = 1.0f;
	m_lastMatrix[10]= 1.0f;
	m_lastMatrix[15]= 1.0f;
}

SrCameraBase::~SrCameraBase()
{

}

int SrCameraBase::viewX()
{
	return m_cameraDesc.viewX;
}
int SrCameraBase::viewY()
{
	return m_cameraDesc.viewY;
}
void SrCameraBase::setView(int viewX,int viewY)
{
	m_cameraDesc.viewX = viewX;
	m_cameraDesc.viewY = viewY;
}
int SrCameraBase::width()
{
	return m_cameraDesc.width;
}
int SrCameraBase::height()
{
	return m_cameraDesc.height;
}
void SrCameraBase::setViewSize(int width,int height)
{
	m_cameraDesc.height = height;
	m_cameraDesc.width = width;
}
double SrCameraBase::fovy()
{
	return m_cameraDesc.fovy;
}
void SrCameraBase::setFovy(double fov)
{
	m_cameraDesc.fovy = fov;
}
double SrCameraBase::zNear()
{
	return m_cameraDesc.zNear;
}
void SrCameraBase::setZNear(double zN)
{
	m_cameraDesc.zNear = zN;
}
double SrCameraBase::zFar()
{
	return m_cameraDesc.zFar;
}
void SrCameraBase::setZFar(double zF)
{
	m_cameraDesc.zFar = zF;
}

void SrCameraBase::setViewPort( )
{
	glViewport(m_cameraDesc.viewX,m_cameraDesc.viewY,m_cameraDesc.width,m_cameraDesc.height);
}

void SrCameraBase::setProjection()
{
	glViewport(m_cameraDesc.viewX,m_cameraDesc.viewY,m_cameraDesc.width,m_cameraDesc.height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(m_cameraDesc.fovy, (float)m_cameraDesc.width/(float)m_cameraDesc.height, m_cameraDesc.zNear, m_cameraDesc.zFar);
}

void SrCameraBase::setCamera()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(m_rotAngle.x,1.0f,0,0);
	glRotatef(m_rotAngle.y,0,1.0f,0);
	glRotatef(m_rotAngle.z,0,0,1.0f);
	update();
	glTranslatef(-m_moveDist.x,-m_moveDist.y,-m_moveDist.z);


}

void SrCameraBase::rotateAxisX(float theta)
{
	SrVector3 u(m_lastMatrix[0],m_lastMatrix[4],m_lastMatrix[8]);
	m_rotAngle += theta*u;

}

void SrCameraBase::rotateAxisY(float theta)
{
	SrVector3 v(m_lastMatrix[1],m_lastMatrix[5],m_lastMatrix[9]);
	m_rotAngle += theta*v;
}

void SrCameraBase::rotateAxisZ(float theta)
{
	SrVector3 n(m_lastMatrix[2],m_lastMatrix[6],m_lastMatrix[10]);
	m_rotAngle += theta*n;
}

void SrCameraBase::moveAxisX( float theta )
{
	SrVector3 u(m_lastMatrix[0],m_lastMatrix[4],m_lastMatrix[8]);
	m_moveDist += theta*u;
}

void SrCameraBase::moveAxisY( float theta )
{
	SrVector3 v(m_lastMatrix[1],m_lastMatrix[5],m_lastMatrix[9]);
	m_moveDist += theta*v;
}

void SrCameraBase::moveAxisZ( float theta )
{
	SrVector3 n(m_lastMatrix[2],m_lastMatrix[6],m_lastMatrix[10]);
	m_moveDist += theta*n;

}


void SrCameraBase::moveAxis(float nX,float nY,float nZ)
{
	SrVector3 u(m_lastMatrix[0],m_lastMatrix[4],m_lastMatrix[8]);
	SrVector3 v(m_lastMatrix[1],m_lastMatrix[5],m_lastMatrix[9]);
	SrVector3 n(m_lastMatrix[2],m_lastMatrix[6],m_lastMatrix[10]);

	m_moveDist += nX*u;
	m_moveDist += nY*v;
	m_moveDist += nZ*n;
}

SrPoint3D SrCameraBase::getEye()
{

	update();
	SrVector3 eye;
	float matrix[9];
	matrix[0] = m_lastMatrix[0] ; matrix[1] = m_lastMatrix[4] ; matrix[2] = m_lastMatrix[8];
	matrix[3] = m_lastMatrix[1] ; matrix[4] = m_lastMatrix[5] ; matrix[5] = m_lastMatrix[9];
	matrix[6] = m_lastMatrix[2] ; matrix[7] = m_lastMatrix[6] ; matrix[8] = m_lastMatrix[10];
	float d = determinant(matrix);
	matrix[0] = m_lastMatrix[12] ; matrix[1] = m_lastMatrix[13] ; matrix[2] = m_lastMatrix[14];
	eye.x = determinant(matrix)/d;
	matrix[0] = m_lastMatrix[0] ; matrix[1] = m_lastMatrix[4] ; matrix[2] = m_lastMatrix[8];
	matrix[3] = m_lastMatrix[12] ; matrix[4] = m_lastMatrix[13] ; matrix[5] = m_lastMatrix[14];
	eye.y = determinant(matrix)/d;
	matrix[3] = m_lastMatrix[1] ; matrix[4] = m_lastMatrix[5] ; matrix[5] = m_lastMatrix[9];
	matrix[6] = m_lastMatrix[12] ; matrix[7] = m_lastMatrix[13] ; matrix[8] = m_lastMatrix[14];
	eye.z = determinant(matrix)/d;

	return eye;
}


void SrCameraBase::update()
{
	glGetFloatv(GL_MODELVIEW_MATRIX, m_lastMatrix);
}

float SrCameraBase::determinant( float* ptrMatrix )
{
	double determ = ptrMatrix[0]*(ptrMatrix[4]*ptrMatrix[8] - ptrMatrix[5]*ptrMatrix[7] );
	determ -= ptrMatrix[1]*(ptrMatrix[3]*ptrMatrix[8] - ptrMatrix[5]*ptrMatrix[6]);
	determ += ptrMatrix[2]*(ptrMatrix[3]*ptrMatrix[7] - ptrMatrix[4]*ptrMatrix[6]);
	return (float)determ;
}

