/************************************************************************		
\link	www.twinklingstar.cn
\author Twinkling Star
\date	2013/11/23
****************************************************************************/

#include "SrGobalHead.h"

HDC			hDC=NULL;
HGLRC		hRC=NULL;
HWND		hWnd=NULL;
HINSTANCE	hInstance;

bool	keys[256];
bool	active=TRUE;
bool	fullscreen=TRUE;
bool	light;
bool	lp;

bool	g_blIsLButonDown	= false;
int		g_inLastMouseX		= 0;
int		g_inLastMouseY		= 0;

GLfloat LightAmbient[]=		{ 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[]=		{ 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[]=	{ 0.0f, 5.0f, 0.0f, 1.0f };

SrTextureBase	g_boxTexture;
SrTextureBase	g_planeTexture;
SrCameraEdit	g_camera(45.0f,				//透视投影的视场
						0.1f,				//近平面
						10000.0f,			//远平面
						0,0,				//视点位置
						100,100,			//窗口尺寸
						SrVector3(0,2.0f,5.0f));//初始位置

SrVector3		minLocation(-100,0,-100);
SrVector3		maxLocation(100,0,100);
typedef struct
{
	SrPoint3D boxCenter;
	float size;
}BoxInfo;

BoxInfo g_box[3];
int		g_selectIndex;


LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


GLvoid ReSizeGLScene(GLsizei width, GLsizei height)
{
	if (height==0)
	{
		height=1;
	}

	g_camera.setViewSize(width,height);
	g_camera.setViewPort();
	g_camera.setProjection();
}

int InitGL(GLvoid)
{
	if (!g_boxTexture.loadTexture("Data/box.bmp"))
	{
		return FALSE;
	}
	if( !g_planeTexture.loadTexture("Data/marbles.tga"))
	{
		return FALSE;
	}
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);
	glEnable(GL_LIGHT1);

	g_box[0].boxCenter = SrPoint3D(0,1.0f,0)	; g_box[0].size = 0.2f;
	g_box[1].boxCenter = SrPoint3D(1.0f,1.0f,0)	; g_box[1].size = 0.2f;
	g_box[2].boxCenter = SrPoint3D(-1.0f,1.0f,0); g_box[2].size = 0.2f;

	return TRUE;
}



void drawPlane()
{
	float step = 1.0f;
	int i , j;
	glBegin(GL_QUADS);
		for( i=0 ; i< (int)(maxLocation.x-minLocation.x)/step ; i++ )
			for( j=0 ; j<(int)(maxLocation.z - minLocation.z); j++ )
			{
				glTexCoord2f(0.0f, 0.0f);glVertex3f(minLocation.x + i*step,0,minLocation.z + j*step);
				glTexCoord2f(1.0f, 0.0f);glVertex3f(minLocation.x + (i+1)*step,0,minLocation.z + j*step);
				glTexCoord2f(1.0f, 1.0f);glVertex3f(minLocation.x + (i+1)*step,0,minLocation.z + (j+1)*step);
				glTexCoord2f(0.0f, 1.0f);glVertex3f(minLocation.x + i*step,0,minLocation.z + (j+1)*step);
			}
		
	glEnd();
}

void drawBoxTexture(SrPoint3D center,float size)
{
	glBegin(GL_QUADS);
	// Front Face
	glNormal3f( 0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(center.x-size, center.y-size,  center.z+size);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(center.x+size, center.y-size,  center.z+size);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(center.x+size, center.y+size,  center.z+size);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(center.x-size, center.y+size,  center.z+size);
	// Back Face
	glNormal3f( 0.0f, 0.0f,-1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(center.x-size, center.y-size,  center.z-size);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(center.x+size, center.y-size,  center.z-size);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(center.x+size, center.y+size,  center.z-size);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(center.x-size, center.y+size,  center.z-size);
	// Top Face
	glNormal3f( 0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(center.x-size, center.y+size,  center.z-size);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(center.x+size, center.y+size,  center.z-size);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(center.x+size, center.y+size,  center.z+size);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(center.x-size, center.y+size,  center.z+size);
	// Bottom Face
	glNormal3f( 0.0f,-1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(center.x-size, center.y-size,  center.z-size);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(center.x+size, center.y-size,  center.z-size);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(center.x+size, center.y-size,  center.z+size);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(center.x-size, center.y-size,  center.z+size);
	// Right face
	glNormal3f( 1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(center.x+size, center.y-size,  center.z-size);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(center.x+size, center.y-size,  center.z+size);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(center.x+size, center.y+size,  center.z+size);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(center.x+size, center.y+size,  center.z-size);
	// Left Face
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(center.x-size, center.y-size,  center.z-size);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(center.x-size, center.y-size,  center.z+size);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(center.x-size, center.y+size,  center.z+size);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(center.x-size, center.y+size,  center.z-size);
	glEnd();
}

void drawBoxNoTexture(SrPoint3D center,float size)
{
	glBegin(GL_LINE_STRIP);
	// Front Face
	glVertex3f(center.x-size, center.y-size,  center.z+size);
	glVertex3f(center.x+size, center.y-size,  center.z+size);
	glVertex3f(center.x+size, center.y+size,  center.z+size);
	glVertex3f(center.x-size, center.y+size,  center.z+size);
	// Back Face
	glVertex3f(center.x-size, center.y-size,  center.z-size);
	glVertex3f(center.x+size, center.y-size,  center.z-size);
	glVertex3f(center.x+size, center.y+size,  center.z-size);
	glVertex3f(center.x-size, center.y+size,  center.z-size);
	// Top Face
	glVertex3f(center.x-size, center.y+size,  center.z-size);
	glVertex3f(center.x+size, center.y+size,  center.z-size);
	glVertex3f(center.x+size, center.y+size,  center.z+size);
	glVertex3f(center.x-size, center.y+size,  center.z+size);
	// Bottom Face
	glVertex3f(center.x-size, center.y-size,  center.z-size);
	glVertex3f(center.x+size, center.y-size,  center.z-size);
	glVertex3f(center.x+size, center.y-size,  center.z+size);
	glVertex3f(center.x-size, center.y-size,  center.z+size);
	// Right face
	glVertex3f(center.x+size, center.y-size,  center.z-size);
	glVertex3f(center.x+size, center.y-size,  center.z+size);
	glVertex3f(center.x+size, center.y+size,  center.z+size);
	glVertex3f(center.x+size, center.y+size,  center.z-size);
	// Left Face
	glVertex3f(center.x-size, center.y-size,  center.z-size);
	glVertex3f(center.x-size, center.y-size,  center.z+size);
	glVertex3f(center.x-size, center.y+size,  center.z+size);
	glVertex3f(center.x-size, center.y+size,  center.z-size);
	glEnd();
}


int DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	g_camera.setCamera();

	g_planeTexture.active();
	drawPlane();

	g_boxTexture.active();
	int i;
	for( i=0 ; i<3 ; i++ )
		drawBoxTexture(g_box[i].boxCenter,g_box[i].size);

	glBindTexture(GL_TEXTURE_2D, 0);
	glColor3f(1.0f,1.0f,1.0f);
	drawBoxNoTexture(g_box[g_selectIndex].boxCenter,g_box[g_selectIndex].size+0.01f);

	return TRUE;
}

GLvoid KillGLWindow(GLvoid)
{
	if (fullscreen)	
	{
		ChangeDisplaySettings(NULL,0);
		ShowCursor(TRUE);
	}

	if (hRC)
	{
		if (!wglMakeCurrent(NULL,NULL))	
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;
	}

	if (hDC && !ReleaseDC(hWnd,hDC))
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;
	}

	if (hWnd && !DestroyWindow(hWnd))
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;
	}

	if (!UnregisterClass("OpenGL",hInstance))
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;	
	}
}


 
BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;
	WNDCLASS	wc;	
	DWORD		dwExStyle;
	DWORD		dwStyle;
	RECT		WindowRect;
	WindowRect.left=(long)0;
	WindowRect.right=(long)width;
	WindowRect.top=(long)0;	
	WindowRect.bottom=(long)height;	

	fullscreen=fullscreenflag;

	hInstance			= GetModuleHandle(NULL);
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc		= (WNDPROC) WndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;	
	wc.hInstance		= hInstance;
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);	
	wc.hbrBackground	= NULL;	
	wc.lpszMenuName		= NULL;	
	wc.lpszClassName	= "OpenGL";

	if (!RegisterClass(&wc))
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}
	
	if (fullscreen)	
	{
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth	= width;
		dmScreenSettings.dmPelsHeight	= height;
		dmScreenSettings.dmBitsPerPel	= bits;	
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;
			}
			else
			{
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;
			}
		}
	}

	if (fullscreen)	
	{
		dwExStyle=WS_EX_APPWINDOW;
		dwStyle=WS_POPUP;
		ShowCursor(FALSE);
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle=WS_OVERLAPPEDWINDOW;
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);	

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,
								"OpenGL",
								title,	
								dwStyle |	
								WS_CLIPSIBLINGS |
								WS_CLIPCHILDREN,
								0, 0,	
								WindowRect.right-WindowRect.left,
								WindowRect.bottom-WindowRect.top,
								NULL,
								NULL,	
								hInstance,	
								NULL)))
	{
		KillGLWindow();
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;	
	}

	static	PIXELFORMATDESCRIPTOR pfd=
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,	
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		bits,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,	
		0, 0, 0, 0,
		16,	
		0,	
		0,	
		PFD_MAIN_PLANE,	
		0,
		0, 0, 0	
	};
	
	if (!(hDC=GetDC(hWnd)))
	{
		KillGLWindow();	
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	
	{
		KillGLWindow();	
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))
	{
		KillGLWindow();
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (!(hRC=wglCreateContext(hDC)))
	{
		KillGLWindow();	
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	if(!wglMakeCurrent(hDC,hRC))
	{
		KillGLWindow();	
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	ShowWindow(hWnd,SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);	
	ReSizeGLScene(width, height);

	if (!InitGL())
	{
		KillGLWindow();	
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	return TRUE;
}

LRESULT CALLBACK WndProc(	HWND	hWnd,
							UINT	uMsg,
							WPARAM	wParam,
							LPARAM	lParam)
{
	switch (uMsg)
	{
		case WM_ACTIVATE:
		{
			if (!HIWORD(wParam))
			{
				active=TRUE;
			}
			else
			{
				active=FALSE;
			}

			return 0;
		}

		case WM_SYSCOMMAND:
		{
			switch (wParam)
			{
				case SC_SCREENSAVE:	
				case SC_MONITORPOWER:
				return 0;
			}
			break;
		}

		case WM_CLOSE:
		{
			PostQuitMessage(0);	
			return 0;
		}

		case WM_KEYDOWN:
		{
			keys[wParam] = TRUE;
			if( keys['C'])
			{
				g_selectIndex+=1;
				g_selectIndex%=3;
				g_camera.setCenter(g_box[g_selectIndex].boxCenter);
			
			}
			return 0;
		}

		case WM_KEYUP:
		{
			keys[wParam] = FALSE;
			return 0;
		}
		case WM_LBUTTONDOWN:
			{
				g_inLastMouseX	=	LOWORD(lParam); 
				g_inLastMouseY	=	HIWORD(lParam);
				
				g_blIsLButonDown = true;

				return 0;
			}
		case WM_LBUTTONUP:
			{
				g_blIsLButonDown = false;
				return 0;
			}
		case WM_MOUSELEAVE:
			{
				g_blIsLButonDown = false;
				return 0;
			}
		case WM_MOUSEMOVE:
			{
				int x	=	LOWORD(lParam); 
				int y	=	HIWORD(lParam);

				if( g_blIsLButonDown )
				{
					if( x!=g_inLastMouseX )
					{
						g_camera.rotateAxisY(10.0f*(g_inLastMouseX-x)*SrPiF32/(180.0f));
						g_inLastMouseX = x;
					}
					//if( y!=g_inLastMouseY )
					//{
					//	g_camera.rotateAxisX(10.0f*(g_inLastMouseY-y)*SrPiF32/(180.0f));
					//	g_inLastMouseY = y;
					//}
				}
				return 0;
			}
		case WM_MOUSEWHEEL:
			{
				short delta = HIWORD(wParam);
				g_camera.moveAxisZ(-delta/WHEEL_DELTA*0.1f);

				return 0;
			}
		case WM_SIZE:
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));
			return 0;
		}
	}

	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

int WINAPI WinMain(	HINSTANCE	hInstance,
					HINSTANCE	hPrevInstance,
					LPSTR		lpCmdLine,
					int			nCmdShow)
{
	MSG		msg;
	BOOL	done=FALSE;
	if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen=FALSE;
	}
	if (!CreateGLWindow("Texture",640,480,16,fullscreen))
	{
		return 0;
	}

	while(!done)
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			if (msg.message==WM_QUIT)
			{
				done=TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if ((active && !DrawGLScene()) || keys[VK_ESCAPE])
			{
				done=TRUE;
			}
			else
			{
				SwapBuffers(hDC);
				if (keys['L'] && !lp)
				{
					lp=TRUE;
					light=!light;
					if (!light)
					{
						glDisable(GL_LIGHTING);
					}
					else
					{
						glEnable(GL_LIGHTING);
					}
				}
				if (!keys['L'])
				{
					lp=FALSE;
				}

				if (keys[VK_UP])
				{
					g_camera.moveAxisY(-0.01f);
				}
				if (keys[VK_DOWN])
				{
					g_camera.moveAxisY(0.01f);
				}
				if (keys[VK_RIGHT])
				{
					g_camera.moveAxisX(0.01f);
				}
				if (keys[VK_LEFT])
				{
					g_camera.moveAxisX(-0.01f);
				}

				if (keys[VK_F1])
				{
					keys[VK_F1]=FALSE;	
					KillGLWindow();
					fullscreen=!fullscreen;	
					if (!CreateGLWindow("Texture",640,480,16,fullscreen))
					{
						return 0;
					}
				}
			}
		}
	}

	KillGLWindow();
	return (msg.wParam);
}
