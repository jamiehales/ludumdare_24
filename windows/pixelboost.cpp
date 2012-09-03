#include "stdafx.h"

#include <Windowsx.h>

#include "GL/glew.h"
#include "GL/wglew.h"

#include "pixelboost/framework/game.h"
#include "pixelboost/input/keyboardManager.h"
#include "pixelboost/input/mouseManager.h"
#include "pixelboost/input/touchManager.h"
#include "pixelboost/graphics/device/device.h"
#include "game/game.h"

#include "pixelboost.h"

float desiredFPS = 60.f;
float speedupFactor = 3.f;

Game* g_Game;

#define MAX_LOADSTRING 100

bool CreateGLContext(HWND hWnd, HDC* hDC, HGLRC* hRC)
{   
    *hDC = GetDC(hWnd);

	PIXELFORMATDESCRIPTOR pixelFormat;
    ZeroMemory(&pixelFormat, sizeof(pixelFormat));
    pixelFormat.nSize = sizeof(pixelFormat);
    pixelFormat.nVersion = 1;
    pixelFormat.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pixelFormat.iPixelType = PFD_TYPE_RGBA;
    pixelFormat.cColorBits = 24;
    pixelFormat.cDepthBits = 16;
    pixelFormat.iLayerType = PFD_MAIN_PLANE;
    
	SetPixelFormat(*hDC, ChoosePixelFormat(*hDC, &pixelFormat), &pixelFormat);

    *hRC = wglCreateContext(*hDC);
	wglMakeCurrent(*hDC, *hRC);

	glewInit();

	return true;
}

void DestroyGLContext(HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hWnd, hDC);
}

TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int, HWND&);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	MSG msg;
	HACCEL hAccelTable;

	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_PIXELBOOST, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	HWND hWnd;
	HDC hDC;
	HGLRC hRC;

	if (!InitInstance (hInstance, nCmdShow, hWnd))
		return FALSE;

	int width = 1024;
	int height = 768;
	
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = width;
	rect.bottom = height;
	AdjustWindowRect( &rect, WS_OVERLAPPEDWINDOW, FALSE );
	SetWindowPos(hWnd, HWND_TOP, 0, 0, rect.right-rect.left, rect.bottom-rect.top, SWP_NOMOVE);
	
	CreateGLContext(hWnd, &hDC, &hRC);

	pb::GraphicsDevice::Instance()->SetDisplayDensity(32.f);
    pb::GraphicsDevice::Instance()->SetDisplayResolution(glm::vec2(width, height));

	g_Game = new Game(0);
	g_Game->Initialise();

	bool quit = false;
	DWORD  timePerFrame=0;
	LONGLONG nextFrameTime=0;
	LONGLONG timerFrequency;

	QueryPerformanceFrequency((LARGE_INTEGER *)&timerFrequency);
	timePerFrame = timerFrequency/desiredFPS;

	while (!quit)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			switch (msg.message)
			{
				case WM_QUIT:
				{
					quit = true;
					break;
				}
				case WM_SIZING:
				{
					RECT* pRect = (RECT*)msg.lParam;
					pb::GraphicsDevice::Instance()->SetDisplayResolution(glm::vec2(pRect->right-pRect->left, pRect->bottom-pRect->top));
					break;
				}
				case WM_LBUTTONDOWN:
				{
					pb::Game::Instance()->GetTouchManager()->OnTouchDown(0, glm::vec2(GET_X_LPARAM(msg.lParam),GET_Y_LPARAM(msg.lParam)));
   
					break;
				}
				case WM_LBUTTONUP:
				{
					pb::Game::Instance()->GetTouchManager()->OnTouchUp(0, glm::vec2(GET_X_LPARAM(msg.lParam),GET_Y_LPARAM(msg.lParam)));
   
					break;
				}
				default:
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
					break;
				}
			}
		}
		else 
		{
			LONGLONG currentTime;
			QueryPerformanceCounter((LARGE_INTEGER *)&currentTime);

			if (currentTime>nextFrameTime)
			{
				g_Game->Update(1.f/(desiredFPS/speedupFactor));
				g_Game->Render();
				SwapBuffers(hDC);

				nextFrameTime += timePerFrame;

				if (nextFrameTime < currentTime)
				    nextFrameTime = currentTime + timePerFrame;
			}
		}
	}

	DestroyGLContext( hWnd, hDC, hRC );
	DestroyWindow( hWnd );

	return (int)msg.wParam;
}

// TODO: Code below is from windows app template, clean up

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PIXELBOOST));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= 0;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow, HWND& hWnd)
{
   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
      return FALSE;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
