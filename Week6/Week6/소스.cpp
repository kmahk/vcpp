#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    static int x1 = 50, y1 = 50;
    static int x2 = 100, y2 = 100;
    static bool collisionDetected = false;

    switch (message) {
    case WM_KEYDOWN:
        switch (wParam) {
        case VK_UP:
            y1 -= 10;
            break;
        case VK_DOWN:
            y1 += 10;
            break;
        case VK_LEFT:
            x1 -= 10;
            break;
        case VK_RIGHT:
            x1 += 10;
            break;
        }

        collisionDetected = (x1 < x2 + 50 && x1 + 50 > x2 && y1 < y2 + 50 && y1 + 50 > y2);
        InvalidateRect(hWnd, NULL, TRUE);
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT paintStruct;
        HDC hDC = BeginPaint(hWnd, &paintStruct);

        HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 255, 255));
        FillRect(hDC, &paintStruct.rcPaint, whiteBrush);
        DeleteObject(whiteBrush);

        Rectangle(hDC, x1, y1, x1 + 50, y1 + 50);
        Rectangle(hDC, x2, y2, x2 + 50, y2 + 50);

        if (collisionDetected) {
            TextOut(hDC, 10, 10, L"Ãæµ¹!", 3);
        }

        EndPaint(hWnd, &paintStruct);
    }
    break;

    case WM_CLOSE:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"RectangleCollision";

    RegisterClass(&wc);

    HWND hWnd = CreateWindow(wc.lpszClassName, L"202237010ÀÓ¼öºó",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 400, NULL, NULL, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
