#include <windows.h>

// ������ ���ν��� �Լ�
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    // �����̴� ������ �ʱ� ��ġ (��ȫ��)
    static int x1 = 50, y1 = 50;
    // ������ ������ �ʱ� ��ġ (�Ķ���)
    static int x2 = 100, y2 = 100;

    switch (message) {
    case WM_KEYDOWN:  // Ű���� �Է� �̺�Ʈ
        switch (wParam) {
        case VK_UP:
            y1 -= 10;  // ����� Ű�� ������ �� ���� �̵�
            break;
        case VK_DOWN:
            y1 += 10;  // �Ϲ��� Ű�� ������ �� �Ʒ��� �̵�
            break;
        case VK_LEFT:
            x1 -= 10;  // �¹��� Ű�� ������ �� �������� �̵�
            break;
        case VK_RIGHT:
            x1 += 10;  // ����� Ű�� ������ �� ���������� �̵�
            break;
        }

        InvalidateRect(hWnd, NULL, TRUE);  // ȭ���� �ٽ� �׸����� ����
        break;

    case WM_PAINT:  // ȭ�� �׸��� �̺�Ʈ
    {
        PAINTSTRUCT paintStruct;
        HDC hDC = BeginPaint(hWnd, &paintStruct);

        // ������ ���� �귯���� ����
        HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 255));
        HBRUSH pinkBrush = CreateSolidBrush(RGB(255, 0, 255));
        HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 255, 255));

        // ��ü ������ ����� ������� ĥ�ϱ�
        RECT windowRect;
        GetClientRect(hWnd, &windowRect);
        FillRect(hDC, &windowRect, whiteBrush);

        // ������ ���� (�Ķ���) �׸���
        SelectObject(hDC, blueBrush);
        Rectangle(hDC, x2, y2, x2 + 50, y2 + 50);

        // �����̴� ���� (��ȫ��) �׸���
        SelectObject(hDC, pinkBrush);
        Rectangle(hDC, x1, y1, x1 + 50, y1 + 50);

        // �浹 ���� �� '�浹!' ���ڿ� ���
        if (x1 < x2 + 50 && x1 + 50 > x2 && y1 < y2 + 50 && y1 + 50 > y2) {
            TextOut(hDC, 10, 10, L"�浹!", 3);
        }

        // �귯�� �޸� ����
        DeleteObject(blueBrush);
        DeleteObject(pinkBrush);
        DeleteObject(whiteBrush);

        EndPaint(hWnd, &paintStruct);
    }
    break;

    case WM_CLOSE:  // â ���� �̺�Ʈ
        PostQuitMessage(0);  // ���� �޽��� ����
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // ������ Ŭ���� ���� �� ���
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"RectangleCollision";
    RegisterClass(&wc);

    // ������ ����
    HWND hWnd = CreateWindow(wc.lpszClassName, L"202237010�Ӽ���",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 400, NULL, NULL, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);  // ������ ǥ��

    // �޽��� ���� ó��
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
