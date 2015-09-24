/************************************************************************		
\link	www.twinklingstar.cn
\author Twinkling Star
\date	2013/11/23
****************************************************************************/
#ifndef SR_OPENGL_CAMERA_EDIT_H_
#define SR_OPENGL_CAMERA_EDIT_H_
/** \addtogroup opengl
  @{
*/
#include "SrCameraBase.h"

/*
\brief Inherit the class SrCameraBase. We can use it to move camera to edit an object like the software of 3d max.
*/

class SrCameraEdit:public SrCameraBase
{
public:
	SrCameraEdit(double	doFovy,
				double	doZNear,
				double	doZFar,
				int		inViewX,
				int		inViewY,
				int		unWidth,
				int		unHeight,
				const SrPoint3D& origin=SrVector3(0,0,-3),
				const SrVector3& center=SrVector3(0,0,0));

	SrVector3 center();
	void setCenter(SrVector3 center);

	virtual void setCamera();
private:

	SrVector3 m_rotCenter;
};


/** @} */

#endif