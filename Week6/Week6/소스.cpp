#include <windows.h>

// 윈도우 프로시저 함수
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    // 움직이는 상자의 초기 위치 (분홍색)
    static int x1 = 50, y1 = 50;
    // 고정된 상자의 초기 위치 (파란색)
    static int x2 = 100, y2 = 100;

    switch (message) {
    case WM_KEYDOWN:  // 키보드 입력 이벤트
        switch (wParam) {
        case VK_UP:
            y1 -= 10;  // 상방향 키를 눌렀을 때 위로 이동
            break;
        case VK_DOWN:
            y1 += 10;  // 하방향 키를 눌렀을 때 아래로 이동
            break;
        case VK_LEFT:
            x1 -= 10;  // 좌방향 키를 눌렀을 때 왼쪽으로 이동
            break;
        case VK_RIGHT:
            x1 += 10;  // 우방향 키를 눌렀을 때 오른쪽으로 이동
            break;
        }

        InvalidateRect(hWnd, NULL, TRUE);  // 화면을 다시 그리도록 지시
        break;

    case WM_PAINT:  // 화면 그리기 이벤트
    {
        PAINTSTRUCT paintStruct;
        HDC hDC = BeginPaint(hWnd, &paintStruct);

        // 각각의 색상 브러쉬를 생성
        HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 255));
        HBRUSH pinkBrush = CreateSolidBrush(RGB(255, 0, 255));
        HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 255, 255));

        // 전체 윈도우 배경을 흰색으로 칠하기
        RECT windowRect;
        GetClientRect(hWnd, &windowRect);
        FillRect(hDC, &windowRect, whiteBrush);

        // 고정된 상자 (파란색) 그리기
        SelectObject(hDC, blueBrush);
        Rectangle(hDC, x2, y2, x2 + 50, y2 + 50);

        // 움직이는 상자 (분홍색) 그리기
        SelectObject(hDC, pinkBrush);
        Rectangle(hDC, x1, y1, x1 + 50, y1 + 50);

        // 충돌 감지 후 '충돌!' 문자열 출력
        if (x1 < x2 + 50 && x1 + 50 > x2 && y1 < y2 + 50 && y1 + 50 > y2) {
            TextOut(hDC, 10, 10, L"충돌!", 3);
        }

        // 브러쉬 메모리 해제
        DeleteObject(blueBrush);
        DeleteObject(pinkBrush);
        DeleteObject(whiteBrush);

        EndPaint(hWnd, &paintStruct);
    }
    break;

    case WM_CLOSE:  // 창 종료 이벤트
        PostQuitMessage(0);  // 종료 메시지 전송
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // 윈도우 클래스 설정 및 등록
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"RectangleCollision";
    RegisterClass(&wc);

    // 윈도우 생성
    HWND hWnd = CreateWindow(wc.lpszClassName, L"202237010임수빈",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 400, NULL, NULL, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);  // 윈도우 표시

    // 메시지 루프 처리
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
