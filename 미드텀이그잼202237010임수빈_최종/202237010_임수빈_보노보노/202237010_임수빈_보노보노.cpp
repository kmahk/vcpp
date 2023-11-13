#include <windows.h>
#include <tchar.h>

// Global variables
HINSTANCE hInst;
HWND hWnd;
HWND hButtonDraw, hButtonBox, hButtonCircle, hButtonBonobono, hButtonRyan;
POINT ptCircleStart = { 100, 100 }, ptCircleEnd = { 400, 400 };
BOOL spacePressed = FALSE; // 스페이스바 상태 추적을 위한 전역 변수
BOOL faceDrawn = FALSE; // 얼굴을 그렸는지 확인하는 전역 변수
int DrawingShape = 1;
COLORREF rgbFace = RGB(127, 200, 255);
COLORREF rgbMouth = RGB(255, 150, 255);

// Function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void DrawFace(HDC hdc, POINT ptStart, POINT ptEnd);
void DrawEyes(HDC hdc, int centerX, int centerY, int eyeWidth, int eyeHeight);
void DrawSpaceEyes(HDC hdc, int centerX, int centerY, int eyeWidth, int eyeHeight);

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
        24+134.4+16, 32, 134.4, 64,  // 16px 마진 추가
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
            return TRUE; // 메시지 처리 완료를 나타냅니다.
        }
        break; // 다른 처리를 위해 break를 사용합니다.
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
            DrawingShape = 5;
            // Ryan button clicked
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


        // 사각형의 크기를 지정합니다. 예를 들어 클라이언트 영역의 가운데에 그리고 싶다면
        int rectWidth = clientRect.right -16;
        int rectHeight = clientRect.bottom-16;
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

        if (faceDrawn) // 버튼을 누를 때만 그립니다.
        {
            DrawFace(hdc, ptCircleStart, ptCircleEnd); // 얼굴 그리기
            if (!spacePressed)
            {
                DrawEyes(hdc, (ptCircleStart.x + ptCircleEnd.x) / 2, (ptCircleStart.y + ptCircleEnd.y) / 2,
                    (ptCircleEnd.x - ptCircleStart.x) / 10, (ptCircleEnd.y - ptCircleStart.y) / 7);
            }
            else
            {
                DrawSpaceEyes(hdc, (ptCircleStart.x + ptCircleEnd.x) / 2, (ptCircleStart.y + ptCircleEnd.y) / 2,
                    (ptCircleEnd.x - ptCircleStart.x) / 10, (ptCircleEnd.y - ptCircleStart.y) / 7);
            }
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

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void DrawFace(HDC hdc, POINT ptStart, POINT ptEnd)
{
    // 얼굴을 그립니다.
    HBRUSH hFaceBrush = CreateSolidBrush(rgbFace);
    HPEN hFacePen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
    SelectObject(hdc, hFaceBrush);
    SelectObject(hdc, hFacePen);
    Ellipse(hdc, ptStart.x, ptStart.y+20, ptEnd.x, ptEnd.y+20);
    DeleteObject(hFaceBrush);
    DeleteObject(hFacePen);

    // 중앙 값을 계산합니다.
    int centerX = (ptStart.x + ptEnd.x) / 2;
    int centerY = ((ptStart.y + ptEnd.y) / 2)+20;

    // 코의 크기를 정의합니다.
    int noseSize = (ptEnd.x - ptStart.x) / 10;

    // 입을 그립니다.
    int mouthWidth = noseSize;
    int mouthHeight = 2 * noseSize;
    HPEN hMouthPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
    HBRUSH hMouthBrush = CreateSolidBrush(rgbMouth);
    SelectObject(hdc, hMouthBrush);
    SelectObject(hdc, hMouthPen);
    Ellipse(hdc, centerX - mouthWidth / 2, centerY + noseSize, centerX + mouthWidth / 2, centerY + noseSize + mouthHeight);
    DeleteObject(hMouthBrush);
    DeleteObject(hMouthPen);

    // 흰색 원을 그립니다.
    int whiteCircleRadius = 0.85 * noseSize;
    HPEN hWhiteCirclePen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0)); // 검은색 펜
    HBRUSH hWhiteCircleBrush = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc, hWhiteCircleBrush);
    SelectObject(hdc, hWhiteCirclePen);
    Ellipse(hdc, centerX - 1.5 * whiteCircleRadius, centerY, centerX + 0.5 * whiteCircleRadius, centerY + 2 * whiteCircleRadius);
    Ellipse(hdc, centerX - 0.5 * whiteCircleRadius, centerY, centerX + 1.5 * whiteCircleRadius, centerY + 2 * whiteCircleRadius);
    DeleteObject(hWhiteCircleBrush);
    DeleteObject(hWhiteCirclePen);

    // 코를 그립니다.
    HPEN hNosePen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    HBRUSH hNoseBrush = CreateSolidBrush(RGB(0, 0, 0));
    SelectObject(hdc, hNoseBrush);
    SelectObject(hdc, hNosePen);
    Ellipse(hdc, centerX - noseSize, centerY - noseSize / 2, centerX + noseSize, centerY + 1.5 * noseSize);
    DeleteObject(hNoseBrush);
    DeleteObject(hNosePen);

    // 수염을 그립니다.
    int whiskerLength = whiteCircleRadius / 2;
    int whiskerStartY = centerY + whiteCircleRadius; // y좌표 낮춤 (흰색 원 바닥에서 시작)
    HPEN hWhiskerPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    SelectObject(hdc, hWhiskerPen);

    // 왼쪽 수염 그리기 (x좌표 약간 증가)
    MoveToEx(hdc, centerX - 1.5 * whiteCircleRadius, whiskerStartY, NULL);
    LineTo(hdc, centerX - 1.5 * whiteCircleRadius - whiskerLength - 10, whiskerStartY); // x좌표 10픽셀 증가

    MoveToEx(hdc, centerX - 1.5 * whiteCircleRadius, whiskerStartY - whiteCircleRadius / 3, NULL);
    LineTo(hdc, centerX - 1.5 * whiteCircleRadius - whiskerLength - 8, whiskerStartY - whiteCircleRadius / 3); // x좌표 8픽셀 증가

    // 오른쪽 수염 그리기 (x좌표 약간 감소)
    MoveToEx(hdc, centerX + 1.5 * whiteCircleRadius, whiskerStartY, NULL);
    LineTo(hdc, centerX + 1.5 * whiteCircleRadius + whiskerLength + 10, whiskerStartY); // x좌표 10픽셀 감소

    MoveToEx(hdc, centerX + 1.5 * whiteCircleRadius, whiskerStartY - whiteCircleRadius / 3, NULL);
    LineTo(hdc, centerX + 1.5 * whiteCircleRadius + whiskerLength + 8, whiskerStartY - whiteCircleRadius / 3); // x좌표 8픽셀 감소

    DeleteObject(hWhiskerPen);
}

// 눈을 그리는 함수
void DrawEyes(HDC hdc, int centerX, int centerY, int eyeWidth, int eyeHeight)
{
    // 눈을 그립니다.

    HPEN hEyePen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    HBRUSH hEyeBrush = CreateSolidBrush(RGB(0, 0, 0));
    SelectObject(hdc, hEyeBrush);
    SelectObject(hdc, hEyePen);
    int eyeOffsetX = eyeWidth * 3.5;
    int eyeOffsetY = eyeHeight * 2;
    Ellipse(hdc, centerX - eyeOffsetX, centerY - eyeOffsetY, centerX - eyeOffsetX + eyeWidth, centerY - eyeOffsetY + eyeHeight);
    Ellipse(hdc, centerX + eyeOffsetX - eyeWidth, centerY - eyeOffsetY, centerX + eyeOffsetX, centerY - eyeOffsetY + eyeHeight);
    DeleteObject(hEyeBrush);
    DeleteObject(hEyePen);

    // 눈의 반사광을 추가합니다.
    HBRUSH hHighlightBrush = CreateSolidBrush(RGB(255, 255, 255));
    HPEN hHighlightPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
    SelectObject(hdc, hHighlightBrush);
    SelectObject(hdc, hHighlightPen);
    int highlightSize = eyeWidth / 3;
    int highlightOffsetX = eyeWidth / 3.3;
    int highlightOffsetY = eyeHeight / 2.8;
    Ellipse(hdc, centerX - eyeOffsetX + highlightOffsetX, centerY - eyeOffsetY + highlightOffsetY,
        centerX - eyeOffsetX + highlightOffsetX + highlightSize, centerY - eyeOffsetY + highlightOffsetY + highlightSize);
    Ellipse(hdc, centerX + eyeOffsetX - eyeWidth + highlightOffsetX, centerY - eyeOffsetY + highlightOffsetY,
        centerX + eyeOffsetX - eyeWidth + highlightOffsetX + highlightSize, centerY - eyeOffsetY + highlightOffsetY + highlightSize);
    DeleteObject(hHighlightBrush);
    DeleteObject(hHighlightPen);
}

// 스페이스바가 눌렸을 때 눈을 그리는 함수
void DrawSpaceEyes(HDC hdc, int centerX, int centerY, int eyeWidth, int eyeHeight)
{
    // 캐릭터 눈의 위치 계산
    int eyeOffsetX = eyeWidth * 3.5;
    int eyeOffsetY = eyeHeight * 2;

    // 글꼴 생성
    LOGFONT lf;
    ZeroMemory(&lf, sizeof(LOGFONT));
    lf.lfHeight = eyeHeight * 1.5;  // 눈의 높이의 2배로 글꼴 크기를 설정
    lf.lfWeight = FW_BOLD;        // 굵은 글꼴 설정
    wcscpy_s(lf.lfFaceName, L"Arial"); // 글꼴 유형을 "Arial"로 설정

    HFONT hNewFont = CreateFontIndirect(&lf);
    HFONT hOldFont = (HFONT)SelectObject(hdc, hNewFont); // 새 글꼴 선택 및 이전 글꼴 저장

    // 텍스트 배경색 설정
    SetBkColor(hdc, RGB(127, 200, 255));

    // 왼쪽 눈 위치 계산 및 '>' 문자 그리기
    int leftEyeX = centerX - eyeOffsetX + (eyeWidth / 2);
    int leftEyeY = centerY - eyeOffsetY + (eyeHeight / 10);
    TextOut(hdc, leftEyeX, leftEyeY, L">", 1);

    // 오른쪽 눈 위치 계산 및 '<' 문자 그리기
    int rightEyeX = centerX + eyeOffsetX - (eyeWidth * 1.5);
    int rightEyeY = centerY - eyeOffsetY + (eyeHeight / 10);
    TextOut(hdc, rightEyeX, rightEyeY, L"<", 1);

    // 이전 글꼴로 복원 및 새 글꼴 삭제
    SelectObject(hdc, hOldFont);
    DeleteObject(hNewFont);
}