/************************************************************************		
\link	www.twinklingstar.cn
\author Twinkling Star
\date	2013/11/23
****************************************************************************/
#ifndef SR_OPENGL_CAMERA_BASE_H_
#define SR_OPENGL_CAMERA_BASE_H_
/** \addtogroup opengl
  @{
*/
#include "SrDataType.h"
#include "SrVector3.h"

/*
\brief Setting some configuration of the tranformations and the camera,including view port transformation,
		projection transformation(only perspective transformation).

This class provides with a simple to fly a camera through a scene, like the person in CS moving in the scene.
*/


class SrCameraBase
{
protected:
	typedef struct
	{
		double	fovy;
		double	zNear;
		double	zFar;
		int		viewX;
		int		viewY;
		int		width;
		int		height;
	}StCameraDesc;

public:
	SrCameraBase(double		doFovy,
			 double			doZNear,
			 double			doZFar,
			 int			inViewX,
			 int			inViewY,
			 int			unWidth,
			 int			unHeight,
			 const SrPoint3D& origin=SrVector3(0,0,-3));
	~SrCameraBase();
	int viewX();
	int viewY();
	int width();
	int height();
	double fovy();
	double zNear();
	double zFar();

	void setView(int viewX,int viewY);
	void setFovy(double fov);
	void setZNear(double zN);
	void setViewSize(int width,int height);
	void setZFar(double zF);

	/*
	\brief	Set the view port.
	*/
	virtual void setViewPort( );
	/*
	\brief	Set the perspective projection.
	*/
	virtual void setProjection();
	/*
	\brief	Set the configuration of the camera.
	*/
	virtual void setCamera();
	/*
	\brief	In the camera coordination system, there are three axises. The following methods provides
			with interfaces to rotate around an axis or move in the direction of an axis.
	*/

	virtual void rotateAxisX(float theta);
	virtual void rotateAxisY(float theta);
	virtual void rotateAxisZ(float theta);

	virtual void moveAxisX( float theta );
	virtual void moveAxisY( float theta );
	virtual void moveAxisZ( float theta );

	virtual void moveAxis(float nX,float nY,float nZ);

	/*
	\brief	Get the original of the camera.
	*/
	SrPoint3D getEye();
protected:
	void update();
	static float determinant( float* ptrMatrix );


protected:
	float				m_lastMatrix[16];
	SrVector3			m_moveDist;
	SrVector3			m_rotAngle;
	StCameraDesc		m_cameraDesc;
};

/** @} */
#endif