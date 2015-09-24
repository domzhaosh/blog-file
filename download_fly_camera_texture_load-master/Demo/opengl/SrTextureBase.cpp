/************************************************************************		
\link	www.twinklingstar.cn
\author Twinkling Star
\date	2013/11/23
****************************************************************************/
#include "SrTextureBase.h"


SrTextureBase::SrTextureBase()
{
	m_textureInfo.id		= 0;
	m_textureInfo.bpp		= 3;
	m_textureInfo.format	= GL_RGB;
	m_textureInfo.width		= 256;
	m_textureInfo.height	= 256;
	m_textureInfo.magFilter = GL_LINEAR;
	m_textureInfo.minFilter = GL_LINEAR;
}

SrTextureBase::SrTextureBase(	  GLuint	uiId,
								  GLint		inMagFilter,
								  GLint		inMinFilter,
								  GLint 	inBpp,
								  GLint 	enFormat,
								  GLint 	inWidth,
								  GLint 	inHeight)
{
	m_textureInfo.id		=	uiId;
	m_textureInfo.magFilter	=	inMagFilter;
	m_textureInfo.minFilter	=	inMinFilter;
	m_textureInfo.bpp		=	inBpp;
	m_textureInfo.format	=	enFormat;
	m_textureInfo.width		=	inWidth;
	m_textureInfo.height	=	inHeight;

}
SrTextureBase::~SrTextureBase()
{
	if( m_textureInfo.id )
		glDeleteTextures(1,&m_textureInfo.id);
	m_textureInfo.id = 0;
}


bool	SrTextureBase::active()
{
	if( !m_textureInfo.id )
		return false;
	glBindTexture(GL_TEXTURE_2D, m_textureInfo.id);

	return true;
}

void	SrTextureBase::buildTexture(unsigned char ucRed, unsigned char ucGreen, unsigned char ucBlue)
{
	unsigned char data[12];	// a 2x2 texture at 24 bits

	// Store the data
	for(int i = 0; i < 12; i += 3)
	{
		data[i] = ucRed;
		data[i+1] = ucGreen;
		data[i+2] = ucBlue;
	}

	// Generate the OpenGL texture id
	glGenTextures(1, &m_textureInfo.id);

	// Bind this texture to its id
	glBindTexture(GL_TEXTURE_2D, m_textureInfo.id);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Use mipmapping filter
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,m_textureInfo.minFilter);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,m_textureInfo.magFilter);

	m_textureInfo.bpp = 3;
	m_textureInfo.format = GL_RGB;
	// Generate the texture
	glTexImage2D(GL_TEXTURE_2D, 0, m_textureInfo.bpp, 2, 2, 0, m_textureInfo.format, GL_UNSIGNED_BYTE, data);
}

bool	SrTextureBase::loadTexture(char* chPtrFilename)
{
	// make the texture name all lower case
	char* texturename = strlwr(strdup(chPtrFilename));

	// check the file extension to see what type of texture
	if(strstr(texturename, ".bmp"))
	{
		free(texturename);
		return loadBMPTexture(chPtrFilename);
	}
	else if(strstr(texturename, ".tga"))	
	{
		free(texturename);
		return loadTGATexture(chPtrFilename);
	}
	free(texturename);
	return false;
}

bool		SrTextureBase::loadBMPTexture(char *chPtrFilename)
{
	unsigned char* data;


	SrImageBmp imageBmp(IMAGE_READ_ONLY);

	int pixelCount,rgbType;

	if( !imageBmp.readFile(chPtrFilename,data,pixelCount,rgbType) )
	{
		return false;
	}
	if( rgbType == IMAGE_RGB)
	{
		m_textureInfo.bpp = 3;
		m_textureInfo.format = GL_RGB;
	}
	else if( rgbType == IMAGE_RGBA )
	{
		m_textureInfo.bpp = 4;
		m_textureInfo.format = GL_RGBA;		
	}
	glGenTextures(1, &m_textureInfo.id);
	glBindTexture(GL_TEXTURE_2D, m_textureInfo.id);
	gluBuild2DMipmaps(GL_TEXTURE_2D, m_textureInfo.bpp, imageBmp.getWidth(), imageBmp.getHeight(), m_textureInfo.format, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,m_textureInfo.magFilter);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,m_textureInfo.minFilter);

	return true;
}


void	SrTextureBase::changeMagFilter(GLint inMagFilter)
{
	glBindTexture(GL_TEXTURE_2D, m_textureInfo.id);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,inMagFilter);
}

void	SrTextureBase::changeMinFilter(GLint inMinFilter)
{
	glBindTexture(GL_TEXTURE_2D, m_textureInfo.id);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,inMinFilter);
}

bool		SrTextureBase::loadTGATexture(char * chPtrFilename)
{

	unsigned char *data=NULL;
	SrImageTga tgaImage(IMAGE_READ_ONLY);
	int pixelCount,rgbType;
	if( !tgaImage.readFile(chPtrFilename,data,pixelCount,rgbType) )
		return false;
	
	if( rgbType == IMAGE_RGB )
	{
		m_textureInfo.bpp = 3;
		m_textureInfo.format = GL_RGB;
	}
	else if( rgbType == IMAGE_RGBA)
	{
		m_textureInfo.bpp = 4;
		m_textureInfo.format = GL_RGBA;

	}

	glGenTextures(1, &m_textureInfo.id);
	glBindTexture(GL_TEXTURE_2D, m_textureInfo.id);
	gluBuild2DMipmaps(GL_TEXTURE_2D, m_textureInfo.bpp, tgaImage.getWidth(), tgaImage.getHeight(), m_textureInfo.format, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,m_textureInfo.magFilter);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,m_textureInfo.minFilter);

	return true;
}
