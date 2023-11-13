#pragma once

void DrawRyan(HWND hWnd, HDC hdc, int left, int top, int right, int bottom) {
    int width = right - left;
    int height = bottom - top;

    // �͸� �׸��ϴ�.
    HBRUSH hEarBrush = CreateSolidBrush(RGB(255, 200, 15));
    SelectObject(hdc, hEarBrush);
    Ellipse(hdc, left, top, left + width / 2, top + height / 2);
    Ellipse(hdc, left + width / 2, top, right, top + height / 2);
    DeleteObject(hEarBrush);

    // ���� �׸��ϴ�.
    HBRUSH hFaceBrush = CreateSolidBrush(RGB(255, 200, 15));
    SelectObject(hdc, hFaceBrush);
    Ellipse(hdc, left + width * 0.1, top + height * 0.1, right - width * 0.1, bottom - height * 0.1);
    DeleteObject(hFaceBrush);

    // ���� �׸��ϴ�.
    HBRUSH hEyeBrush = CreateSolidBrush(RGB(0, 0, 0));
    SelectObject(hdc, hEyeBrush);
    Ellipse(hdc, left + width * 0.3, top + height * 0.4, left + width * 0.335, top + height * 0.435);
    Ellipse(hdc, right - width * 0.3, top + height * 0.4, right - width * 0.265, top + height * 0.435);
    DeleteObject(hEyeBrush);

    // ������ �׸��ϴ�.
    HPEN hPen = CreatePen(PS_SOLID, 7, RGB(0, 0, 0));
    SelectObject(hdc, hPen);
    MoveToEx(hdc, left + width * 0.28, top + height * 0.35, NULL);
    LineTo(hdc, left + width * 0.39, top + height * 0.35);
    MoveToEx(hdc, right - width * 0.28, top + height * 0.35, NULL);
    LineTo(hdc, right - width * 0.39, top + height * 0.35);
    DeleteObject(hPen);

    // �ڸ� �׸��ϴ�.
    HBRUSH hNoseBrush = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc, hNoseBrush);
    Ellipse(hdc, left + width * 0.45, top + height * 0.58, left + width * 0.5, top + height * 0.63);
    Ellipse(hdc, right - width * 0.45, top + height * 0.58, right - width * 0.5, top + height * 0.63);

    DeleteObject(hNoseBrush);
}


void DrawBonobono(HDC hdc, POINT ptStart, POINT ptEnd, int blink, int eyeWidth, int eyeHeight) {
    COLORREF rgbFace = RGB(127, 200, 255);
    COLORREF rgbMouth = RGB(255, 150, 255);
    // ���� �׸��ϴ�.
    HBRUSH hFaceBrush = CreateSolidBrush(rgbFace);
    HPEN hFacePen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
    SelectObject(hdc, hFaceBrush);
    SelectObject(hdc, hFacePen);
    Ellipse(hdc, ptStart.x, ptStart.y + 20, ptEnd.x, ptEnd.y + 20);
    DeleteObject(hFaceBrush);
    DeleteObject(hFacePen);

    // �߾� ���� ����մϴ�.
    int centerX = (ptStart.x + ptEnd.x) / 2;
    int centerY = ((ptStart.y + ptEnd.y) / 2) + 20;

    // ���� ũ�⸦ �����մϴ�.
    int noseSize = (ptEnd.x - ptStart.x) / 10;

    // ���� �׸��ϴ�.
    int mouthWidth = noseSize;
    int mouthHeight = 2 * noseSize;
    HPEN hMouthPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
    HBRUSH hMouthBrush = CreateSolidBrush(rgbMouth);
    SelectObject(hdc, hMouthBrush);
    SelectObject(hdc, hMouthPen);
    Ellipse(hdc, centerX - mouthWidth / 2, centerY + noseSize, centerX + mouthWidth / 2, centerY + noseSize + mouthHeight);
    DeleteObject(hMouthBrush);
    DeleteObject(hMouthPen);

    // ��� ���� �׸��ϴ�.
    int whiteCircleRadius = 0.85 * noseSize;
    HPEN hWhiteCirclePen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0)); // ������ ��
    HBRUSH hWhiteCircleBrush = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc, hWhiteCircleBrush);
    SelectObject(hdc, hWhiteCirclePen);
    Ellipse(hdc, centerX - 1.5 * whiteCircleRadius, centerY, centerX + 0.5 * whiteCircleRadius, centerY + 2 * whiteCircleRadius);
    Ellipse(hdc, centerX - 0.5 * whiteCircleRadius, centerY, centerX + 1.5 * whiteCircleRadius, centerY + 2 * whiteCircleRadius);
    DeleteObject(hWhiteCircleBrush);
    DeleteObject(hWhiteCirclePen);

    // �ڸ� �׸��ϴ�.
    HPEN hNosePen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    HBRUSH hNoseBrush = CreateSolidBrush(RGB(0, 0, 0));
    SelectObject(hdc, hNoseBrush);
    SelectObject(hdc, hNosePen);
    Ellipse(hdc, centerX - noseSize, centerY - noseSize / 2, centerX + noseSize, centerY + 1.5 * noseSize);
    DeleteObject(hNoseBrush);
    DeleteObject(hNosePen);

    // ������ �׸��ϴ�.
    int whiskerLength = whiteCircleRadius / 2;
    int whiskerStartY = centerY + whiteCircleRadius; // y��ǥ ���� (��� �� �ٴڿ��� ����)
    HPEN hWhiskerPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    SelectObject(hdc, hWhiskerPen);

    // ���� ���� �׸��� (x��ǥ �ణ ����)
    MoveToEx(hdc, centerX - 1.5 * whiteCircleRadius, whiskerStartY, NULL);
    LineTo(hdc, centerX - 1.5 * whiteCircleRadius - whiskerLength - 10, whiskerStartY); // x��ǥ 10�ȼ� ����

    MoveToEx(hdc, centerX - 1.5 * whiteCircleRadius, whiskerStartY - whiteCircleRadius / 3, NULL);
    LineTo(hdc, centerX - 1.5 * whiteCircleRadius - whiskerLength - 8, whiskerStartY - whiteCircleRadius / 3); // x��ǥ 8�ȼ� ����

    // ������ ���� �׸��� (x��ǥ �ణ ����)
    MoveToEx(hdc, centerX + 1.5 * whiteCircleRadius, whiskerStartY, NULL);
    LineTo(hdc, centerX + 1.5 * whiteCircleRadius + whiskerLength + 10, whiskerStartY); // x��ǥ 10�ȼ� ����

    MoveToEx(hdc, centerX + 1.5 * whiteCircleRadius, whiskerStartY - whiteCircleRadius / 3, NULL);
    LineTo(hdc, centerX + 1.5 * whiteCircleRadius + whiskerLength + 8, whiskerStartY - whiteCircleRadius / 3); // x��ǥ 8�ȼ� ����

    DeleteObject(hWhiskerPen);



    // DrawEyes �Ǵ� DrawSpaceEyes ��� ����
    if (blink == 0) {
        // ���� �׸��ϴ�.

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

        // ���� �ݻ籤�� �߰��մϴ�.
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
        // ĳ���� ���� ��ġ ���
        int eyeOffsetX = eyeWidth * 3.5;
        int eyeOffsetY = eyeHeight * 2;

        // �۲� ����
        LOGFONT lf;
        ZeroMemory(&lf, sizeof(LOGFONT));
        lf.lfHeight = eyeHeight * 1.5;  // ���� ������ 2��� �۲� ũ�⸦ ����
        lf.lfWeight = FW_BOLD;        // ���� �۲� ����
        wcscpy_s(lf.lfFaceName, L"Arial"); // �۲� ������ "Arial"�� ����

        HFONT hNewFont = CreateFontIndirect(&lf);
        HFONT hOldFont = (HFONT)SelectObject(hdc, hNewFont); // �� �۲� ���� �� ���� �۲� ����

        // �ؽ�Ʈ ���� ����
        SetBkColor(hdc, RGB(127, 200, 255));

        // ���� �� ��ġ ��� �� '>' ���� �׸���
        int leftEyeX = centerX - eyeOffsetX + (eyeWidth / 2);
        int leftEyeY = centerY - eyeOffsetY + (eyeHeight / 10);
        TextOut(hdc, leftEyeX, leftEyeY, L">", 1);

        // ������ �� ��ġ ��� �� '<' ���� �׸���
        int rightEyeX = centerX + eyeOffsetX - (eyeWidth * 1.5);
        int rightEyeY = centerY - eyeOffsetY + (eyeHeight / 10);
        TextOut(hdc, rightEyeX, rightEyeY, L"<", 1);

        // ���� �۲÷� ���� �� �� �۲� ����
        SelectObject(hdc, hOldFont);
        DeleteObject(hNewFont);
    }
}