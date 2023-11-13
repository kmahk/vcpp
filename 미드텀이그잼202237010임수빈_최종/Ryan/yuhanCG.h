#pragma once

void DrawRyan(HWND hWnd, HDC hdc, int left, int top, int right, int bottom) {
    int width = right - left;
    int height = bottom - top;

    // 귀를 그립니다.
    HBRUSH hEarBrush = CreateSolidBrush(RGB(255, 200, 15));
    SelectObject(hdc, hEarBrush);
    Ellipse(hdc, left, top, left + width / 2, top + height / 2);
    Ellipse(hdc, left + width / 2, top, right, top + height / 2);
    DeleteObject(hEarBrush);

    // 얼굴을 그립니다.
    HBRUSH hFaceBrush = CreateSolidBrush(RGB(255, 200, 15));
    SelectObject(hdc, hFaceBrush);
    Ellipse(hdc, left + width * 0.1, top + height * 0.1, right - width * 0.1, bottom - height * 0.1);
    DeleteObject(hFaceBrush);

    // 눈을 그립니다.
    HBRUSH hEyeBrush = CreateSolidBrush(RGB(0, 0, 0));
    SelectObject(hdc, hEyeBrush);
    Ellipse(hdc, left + width * 0.3, top + height * 0.4, left + width * 0.335, top + height * 0.435);
    Ellipse(hdc, right - width * 0.3, top + height * 0.4, right - width * 0.265, top + height * 0.435);
    DeleteObject(hEyeBrush);

    // 눈썹을 그립니다.
    HPEN hPen = CreatePen(PS_SOLID, 7, RGB(0, 0, 0));
    SelectObject(hdc, hPen);
    MoveToEx(hdc, left + width * 0.28, top + height * 0.35, NULL);
    LineTo(hdc, left + width * 0.39, top + height * 0.35);
    MoveToEx(hdc, right - width * 0.28, top + height * 0.35, NULL);
    LineTo(hdc, right - width * 0.39, top + height * 0.35);
    DeleteObject(hPen);

    // 코를 그립니다.
    HBRUSH hNoseBrush = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc, hNoseBrush);
    Ellipse(hdc, left + width * 0.45, top + height * 0.58, left + width * 0.5, top + height * 0.63);
    Ellipse(hdc, right - width * 0.45, top + height * 0.58, right - width * 0.5, top + height * 0.63);

    DeleteObject(hNoseBrush);
}


void DrawBonobono(HDC hdc, POINT ptStart, POINT ptEnd, int blink, int eyeWidth, int eyeHeight) {
    COLORREF rgbFace = RGB(127, 200, 255);
    COLORREF rgbMouth = RGB(255, 150, 255);
    // 얼굴을 그립니다.
    HBRUSH hFaceBrush = CreateSolidBrush(rgbFace);
    HPEN hFacePen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
    SelectObject(hdc, hFaceBrush);
    SelectObject(hdc, hFacePen);
    Ellipse(hdc, ptStart.x, ptStart.y + 20, ptEnd.x, ptEnd.y + 20);
    DeleteObject(hFaceBrush);
    DeleteObject(hFacePen);

    // 중앙 값을 계산합니다.
    int centerX = (ptStart.x + ptEnd.x) / 2;
    int centerY = ((ptStart.y + ptEnd.y) / 2) + 20;

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



    // DrawEyes 또는 DrawSpaceEyes 기능 통합
    if (blink == 0) {
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
    else {
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
}