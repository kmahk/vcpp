/*
기능 설명 : 보노보노 버튼을 한 번 누르면 보노보노가 그려집니다.
보노보노가 그려진 상태에서 스페이스바를 누르면 눈 모양이 바뀝니다.
보노보노 버튼을 한 번 더 누르면 보노보노가 지워집니다.

라이언 버튼을 누른 뒤 흰색(드래그 영역)영역에서 드래그하면 라이언이 그려집니다.
라이언 버튼을 한 번 더 누르면 라이언이 지워집니다.

마우스 커서가 흰색(드래그 영역)에 들어가면 십자가로 바뀌고 흰색(드래그영역) 밖으로 나오면 일반 모양으로 바뀝니다.
*/
#include <windows.h>
#include <tchar.h>
#include "yuhanCG.h"  // yuhanCG.h 헤더 파일을 포함합니다.

// 전역 변수
HINSTANCE hInst;
HWND hWnd;
HWND hButtonDraw, hButtonBox, hButtonCircle, hButtonBonobono, hButtonRyan;
POINT ptCircleStart = { 100, 100 }, ptCircleEnd = { 400, 400 };
BOOL spacePressed = FALSE; // 스페이스바 상태 추적을 위한 전역 변수
int blinkCounter = 0;  // 깜빡임 카운터 추가
BOOL faceDrawn = FALSE; // 얼굴을 그렸는지 확인하는 전역 변수
int DrawingShape = 1;


BOOL isDrawing = FALSE; // 드래그 그리기 상태
POINT ptStart, ptEnd; // 드래그 시작 및 끝점

// 함수 선언
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = CreateSolidBrush(RGB(255, 240, 200));
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hInstance = hInstance;
    wc.lpfnWndProc = WndProc;
    wc.lpszClassName = _T("MainWindow");
    wc.lpszMenuName = NULL;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    if (!RegisterClass(&wc)) return 0;

    hWnd = CreateWindow(_T("MainWindow"), _T("Drawing Application"), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 480, NULL, NULL, hInstance, NULL);

    if (!hWnd) return 0;

    hButtonDraw = CreateWindow(
        _T("BUTTON"), _T("Draw Cube"),
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        24, 32, 134.4, 64,
        hWnd, (HMENU)1, hInst, NULL);

    hButtonBox = CreateWindow(
        _T("BUTTON"), _T("Draw Box"),
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        24 + 134.4 + 16, 32, 134.4, 64,  // 16px 마진 추가
        hWnd, (HMENU)2, hInst, NULL);

    hButtonCircle = CreateWindow(
        _T("BUTTON"), _T("Draw Circle"),
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        24 + (134.4 + 16) * 2, 32, 134.4, 64,  // 16px 마진 추가
        hWnd, (HMENU)3, hInst, NULL);

    hButtonBonobono = CreateWindow(
        _T("BUTTON"), _T("Bonobono"),
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        24 + (134.4 + 16) * 3, 32, 134.4, 64,  // 16px 마진 추가
        hWnd, (HMENU)4, hInst, NULL);

    hButtonRyan = CreateWindow(
        _T("BUTTON"), _T("Ryan"),
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        24 + (134.4 + 16) * 4, 32, 134.4, 64,  // 16px 마진 추가
        hWnd, (HMENU)5, hInst, NULL);


    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_CREATE: {
        WNDCLASS wc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hbrBackground = CreateSolidBrush(RGB(255, 240, 200));
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wc.hInstance = hInst;
        wc.lpfnWndProc = WndProc;
        wc.lpszClassName = _T("MainWindow");
        wc.lpszMenuName = NULL;
        wc.style = CS_HREDRAW | CS_VREDRAW;
        if (!RegisterClass(&wc)) return 0;

        HBRUSH hBackgroundBrush = CreateSolidBrush(RGB(255, 240, 200));
        wc.hbrBackground = hBackgroundBrush;
        break;
    }
    case WM_SETCURSOR:
    {
        // 마우스 포인터의 위치를 얻습니다.
        POINT pt;
        GetCursorPos(&pt);
        ScreenToClient(hWnd, &pt);

        // 마우스가 지정된 사각형 안에 있는지 확인합니다.
        RECT rect = { 16, 116, 768, 424 };
        if (PtInRect(&rect, pt))
        {
            // 마우스가 사각형 안에 있으면 십자가 모양 커서로 변경합니다.
            SetCursor(LoadCursor(NULL, IDC_CROSS));
        }
        else
        {
            // 마우스가 사각형 밖에 있으면 기본 화살표 커서로 변경합니다.
            SetCursor(LoadCursor(NULL, IDC_ARROW));
        }
        return TRUE; // 메시지 처리 완료를 나타냅니다.
    }



    case WM_COMMAND:
        if (LOWORD(wParam) == 1) {
            DrawingShape = 1;
            InvalidateRect(hWnd, NULL, TRUE); // 화면 갱신
        }
        else if (LOWORD(wParam) == 2) {
            DrawingShape = 2;
            InvalidateRect(hWnd, NULL, TRUE); // 화면 갱신
        }
        else if (LOWORD(wParam) == 3) {
            DrawingShape = 3;
            InvalidateRect(hWnd, NULL, TRUE); // 화면 갱신
        }
        else if (LOWORD(wParam) == 4) {
            DrawingShape = 4;
            faceDrawn = !faceDrawn;
            InvalidateRect(hWnd, NULL, TRUE); // 화면 갱신
            SetFocus(hWnd); // 포커스를 메인 윈도우로 이동
        }
        else if (LOWORD(wParam) == 5) {
            isDrawing = !isDrawing;
            DrawingShape = 5;
            InvalidateRect(hWnd, NULL, TRUE); // 화면 갱신
            SetFocus(hWnd); // 포커스를 메인 윈도우로 이동
        }
        break;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // 배경을 다시 그립니다.
        RECT clientRect;
        GetClientRect(hWnd, &clientRect);
        HBRUSH hBackgroundBrush = CreateSolidBrush(RGB(255, 240, 200)); // 배경색을 생성
        FillRect(hdc, &clientRect, hBackgroundBrush); // 배경색을 적용

        // 클리핑 영역을 설정합니다.
        RECT rect2 = { 16, 116, 768, 424 };
        HRGN hRgn = CreateRectRgn(rect2.left, rect2.top, rect2.right, rect2.bottom);
        SelectClipRgn(hdc, hRgn);


        // 사각형의 크기를 지정합니다. 예를 들어 클라이언트 영역의 가운데에 그리고 싶다면
        int rectWidth = clientRect.right - 16;
        int rectHeight = clientRect.bottom - 16;
        int offsetX = (clientRect.right - rectWidth) / 2; // 가로 중앙 정렬을 위한 오프셋
        int offsetY = (clientRect.bottom - rectHeight) / 2; // 세로 중앙 정렬을 위한 오프셋

        // 테두리만 있는 사각형을 그릴 때는 HPEN을 사용합니다.
        HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // 1픽셀 두께의 검은색 펜
        HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH)); // 내부를 채우지 않음
        HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

        // 사각형을 그립니다.
        Rectangle(hdc, offsetX, offsetY, offsetX + rectWidth, offsetY + rectHeight);

        // 원래의 브러시와 펜으로 복구합니다.
        SelectObject(hdc, hOldBrush);
        SelectObject(hdc, hOldPen);

        // 생성한 펜을 삭제합니다.
        DeleteObject(hPen);

        // Define the coordinates of the rectangle
        RECT rect = { 16, 116, 768, 424 };

        // Create a white brush for the rectangle's fill
        HBRUSH hWhiteBrush = CreateSolidBrush(RGB(255, 255, 255));

        // Save the old brush
        HBRUSH hOldBrush1 = (HBRUSH)SelectObject(hdc, hWhiteBrush);

        // Draw the rectangle
        FillRect(hdc, &rect, hWhiteBrush);

        // Restore the old brush
        SelectObject(hdc, hOldBrush1);

        // Delete the white brush
        DeleteObject(hWhiteBrush);

        if (isDrawing) {
            // Ryan 그리기
            DrawRyan(hWnd, hdc, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);
        }

        if (faceDrawn) { // 버튼을 누를 때만 그립니다.
            int eyeWidth = (ptCircleEnd.x - ptCircleStart.x) / 10;
            int eyeHeight = (ptCircleEnd.y - ptCircleStart.y) / 7;

            // DrawBonobono 함수를 사용하여 얼굴과 눈을 그립니다.
            DrawBonobono(hdc, ptCircleStart, ptCircleEnd, spacePressed ? 1 : 0, eyeWidth, eyeHeight);
        }
        // 배경색 생성한 브러시를 해제
        DeleteObject(hBackgroundBrush);



        EndPaint(hWnd, &ps);
        break;
    }
    case WM_KEYDOWN: // 키보드 키가 눌릴 때
        if (wParam == VK_SPACE) // 스페이스바를 확인
        {
            spacePressed = TRUE;
            InvalidateRect(hWnd, NULL, TRUE); // 화면 갱신
        }
        break;
    case WM_KEYUP: // 키보드 키가 떼어질 때
        if (wParam == VK_SPACE) // 스페이스바를 확인
        {
            spacePressed = FALSE;
            InvalidateRect(hWnd, NULL, TRUE); // 화면 갱신
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_LBUTTONDOWN:
        if (isDrawing) {
            ptStart.x = LOWORD(lParam);
            ptStart.y = HIWORD(lParam);
            ptEnd = ptStart; // 초기화
            SetCapture(hWnd); // 마우스 캡처 시작
        }
        break;

    case WM_MOUSEMOVE:
        if (isDrawing && (wParam & MK_LBUTTON)) {
            ptEnd.x = LOWORD(lParam);
            ptEnd.y = HIWORD(lParam);
            InvalidateRect(hWnd, NULL, FALSE); // 영역 무효화
        }
        break;

    case WM_LBUTTONUP:
        if (isDrawing) {
            ReleaseCapture(); // 마우스 캡처 해제
            InvalidateRect(hWnd, NULL, FALSE); // 최종 그리기
        }
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}