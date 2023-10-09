#include <windows.h>
#include <tchar.h>


// ���� ����
HINSTANCE hInstance;
HWND hWnd;
BOOL isDrawing = FALSE;
POINT startPoint;
POINT endPoint;

// ������ ���ν��� �Լ�
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_LBUTTONDOWN:
        isDrawing = TRUE;
        startPoint.x = LOWORD(lParam);
        startPoint.y = HIWORD(lParam);
        break;
    case WM_LBUTTONUP:
        isDrawing = FALSE;
        endPoint.x = LOWORD(lParam);
        endPoint.y = HIWORD(lParam);
        // ��ȫ�� �簢�� �׸���
        if (hWnd != NULL)
        {
            HDC hdc = GetDC(hWnd);
            HBRUSH pinkBrush = CreateSolidBrush(RGB(255, 0, 255)); // ��ȫ��
            SelectObject(hdc, pinkBrush);
            Rectangle(hdc, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
            DeleteObject(pinkBrush);
            ReleaseDC(hWnd, hdc);
        }
        break;
    case WM_MOUSEMOVE:
        if (isDrawing)
        {
            // �簢�� �׸��⸦ �巡�� �߿� ������Ʈ
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);
            // �ٽ� �׸��� ��û
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
    case WM_PAINT:
        if (hWnd != NULL)
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            HBRUSH pinkBrush = CreateSolidBrush(RGB(255, 0, 255)); // ��ȫ��
            SelectObject(hdc, pinkBrush);
            Rectangle(hdc, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
            DeleteObject(pinkBrush);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
    hInstance = hInst;

    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WndProc, 0, 0,
                      GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("MyWindowClass"), NULL };

    RegisterClassEx(&wc);

    hWnd = CreateWindowEx(0, _T("MyWindowClass"), _T("202237010 �Ӽ���"),
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, hInst, NULL);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}
