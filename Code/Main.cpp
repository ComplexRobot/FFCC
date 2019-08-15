#include "CommonIncludes.h"
#include "Menu.h"

const char* WINDOW_CLASS_NAME = "FFCC Main Window";
const char* WINDOW_TITLE = "FFCC File Editor";

std::mutex messageMutex;
HWND mainWindowHandle;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void CreateWindowClass(HINSTANCE hInstance);
void AtExit();

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
  std::atexit(AtExit);
  CreateWindowClass(hInstance);
  HWND windowHandle = CreateWindowEx(0, WINDOW_CLASS_NAME, WINDOW_TITLE, WS_OVERLAPPEDWINDOW, 
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, CreateWindowMenu(), hInstance, NULL);
  FatalErrorTest(windowHandle == NULL, "CreateWindowEx: Error code (0x%X)", GetLastError());
  mainWindowHandle = windowHandle;
  ShowWindow(windowHandle, nShowCmd);
  MSG message = { };
  while (GetMessage(&message, NULL, 0, 0))
  {
    TranslateMessage(&message);
    DispatchMessage(&message);
  }
  return 0;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
  case WM_CREATE:
    break;
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  case WM_PAINT:
  {
    /*PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW + 1));
    EndPaint(hWnd, &ps);*/
  }
    break;
  case WM_COMMAND:
    if ((wParam & 0xFFFF0000) == 0)
    {
      HandleMenuCommand(wParam);
    }
    break;
  }
  return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void CreateWindowClass(HINSTANCE hInstance)
{
  WNDCLASSEX windowClass = { };
  windowClass.cbSize = sizeof(windowClass);
  windowClass.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
  windowClass.lpfnWndProc = WindowProc;
  windowClass.hInstance = hInstance;
  windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
  windowClass.hbrBackground = CreateSolidBrush(RGB(32, 32, 32));
  windowClass.lpszClassName = WINDOW_CLASS_NAME;
  FatalErrorTest(RegisterClassEx(&windowClass) == 0, "RegisterClassEx: Error code (0x%X)", GetLastError());
}

void AtExit()
{
  messageMutex.lock();
  messageMutex.unlock();
}