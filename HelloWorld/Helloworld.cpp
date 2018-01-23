#define WIN32_LEAN_AND_MEAN	
#pragma comment(linker, "/subsystem:windows")
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT paintStruct;

	HDC hDC;

	char string[] = "hello world!";

	int size = strlen(string) - 1;
	wchar_t *string1 = new wchar_t[size];

	switch (message)
	{
		case WM_CREATE :
			return 0;
			break;
		case WM_CLOSE :
			PostQuitMessage(0);
			return 0;
			break;
		case WM_PAINT :
			hDC = BeginPaint(hwnd, &paintStruct);
			/*	Set txt color to blue*/
			SetTextColor(hDC, COLORREF(0x00BF00));
			/*	Display text in middle of window*/

			for (int i = 0; i <= size; i++)
			{
				string1[i] = string[i];
			}
			TextOut(hDC, 150, 150, string1, sizeof(string) - 1);

			EndPaint(hwnd, &paintStruct);
			return 0;
			break;
		default :
			break;
	}
	delete[] string1;
	string1 = NULL;
	return (DefWindowProc(hwnd, message, wParam, lParam));
}

int APIENTRY WinMain(	HINSTANCE hInstance,
						HINSTANCE hPrevInstance,
						LPSTR lpCmdLine,
						int ncmdShow)
{
	WNDCLASSEX windowClass;
	HWND hwnd;
	MSG msg;
	bool done;

	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WndProc;
	windowClass.cbWndExtra = 0;
	windowClass.cbClsExtra = 0;
	windowClass.hInstance = hInstance;
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	char class_Name[] = "MyClass";

	int size = strlen(class_Name) ;
	wchar_t *className = new wchar_t[size];
	for (int i = 0; i <= size; i++)
	{
		className[i] = class_Name[i];
	}
	windowClass.lpszClassName = className;
	windowClass.lpszMenuName = NULL;
	windowClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

	if (!RegisterClassEx(&windowClass))
	{
		return 0;
	}

	hwnd = CreateWindowEx(NULL,
		TEXT("MyClass"), TEXT("A Real win app"),
		WS_OVERLAPPEDWINDOW |
		WS_VISIBLE |
		WS_SYSMENU,
		100, 100,
		400, 400,
		NULL, NULL,
		hInstance,
		NULL);

	if (!hwnd)
		return 0;
	done = false;

	while (!done)
	{
		PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE);

		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}