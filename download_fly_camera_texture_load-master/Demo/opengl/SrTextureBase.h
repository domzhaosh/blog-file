/************************************************************************		
\link	www.twinklingstar.cn
\author Twinkling Star
\date	2013/11/23
****************************************************************************/
#ifndef SR_OPENGL_TEXTURE_H_
#define SR_OPENGL_TEXTURE_H_

/** \addtogroup opengl
  @{
*/

#include "SrGobalHead.h"

/*
\brief The information of the texture is stored here.
*/
typedef struct
{ 
	GLuint	id;
	GLint	magFilter;		// Style of texture magnification function	
	GLint	minFilter;		// Style of texture minifying function				
	GLint 	bpp;			// Image Color Depth In Bits Per Pixel.
	GLint 	format;			// Image Type (GL_RGB, GL_RGBA)
	GLint 	width;			// Image Width
	GLint 	height;			// Image Height
}StTextureInfo;

/*
\brief A simple class of loading texture from the images in the application of opengl


*/
class SrTextureBase
{
public:
	SrTextureBase();
	SrTextureBase(	GLuint	uiId,
					GLint	inMagFilter,
					GLint	inMinFilter,
					GLint 	inBpp,
					GLint 	enFormat,
					GLint 	inWidth,
					GLint 	inHeight);
	~SrTextureBase();
	/*
	\brief	Activate this texture.
	*/
	bool	active();
	/*
	\brief	Load texture from the image file.Currently only two image types,'bmp' and 'tga',are supported,
	*/
	bool	loadTexture(char* chPtrFilename);
	/*
	\brief	Build a texture of uniform color
	*/
	void	buildTexture(unsigned char ucRed, unsigned char ucGreen, unsigned char ucBlue);	
	/*
	\brief	Change the texture magnification function and then activate this texture.
	*/
	void	changeMagFilter(GLint inMagFilter);
	/*
	\brief	Change the texture minifying function and then activate this texture.
	*/
	void	changeMinFilter(GLint inMinFilter);

private:
	bool		loadBMPTexture(char *chPtrFilename);
	bool		loadTGATexture(char *chPtrFilename);
	
public:
	StTextureInfo m_textureInfo;
};


/** @} */
#endif