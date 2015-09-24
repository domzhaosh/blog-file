/************************************************************************		
\link	www.twinklingstar.cn
\author Twinkling Star
\date	2013/11/23
****************************************************************************/
#include "SrCameraEdit.h"
#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glaux.h>		// Header File For The Glaux Library



SrCameraEdit::SrCameraEdit(double	doFovy,
	double	doZNear,
	double	doZFar,
	int		inViewX,
	int		inViewY,
	int		unWidth,
	int		unHeight,
	const SrPoint3D& origin,
	const SrVector3& center):SrCameraBase(doFovy,doZNear,doZFar,inViewX,inViewY,unWidth,unHeight,origin)
{
	m_rotCenter = center;
}

SrVector3 SrCameraEdit::center()
{
	return m_rotCenter;
}
void SrCameraEdit::setCenter(SrVector3 center)
{
	m_rotCenter = center;
}

void SrCameraEdit::setCamera()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLoadMatrixf(m_lastMatrix);
	glTranslatef(-m_moveDist.x,-m_moveDist.y,-m_moveDist.z);
	glTranslatef(m_rotCenter.x,m_rotCenter.y,m_rotCenter.z);
	glRotatef(m_rotAngle.y,0,1.0f,0);
	glRotatef(m_rotAngle.x,1.0f,0,0);
	glRotatef(m_rotAngle.z,0,0,1.0f);
	glTranslatef(-m_rotCenter.x,-m_rotCenter.y,-m_rotCenter.z);
	update();
	m_rotAngle = SrVector3(0,0,0);
	m_moveDist = SrVector3(0,0,0);
}

