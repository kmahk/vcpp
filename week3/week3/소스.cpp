#include <iostream>
#include <windows.h>
#include <vector>

int main() {
    const int bufferSize = 128;//buffersize��� ���� ����� 128�� �����Ѵ�.
    INPUT_RECORD inRecord[bufferSize];
    /*INPUT RECORD�� �Է� �̺�Ʈ�� ��Ÿ���� ������ ����*/
    DWORD eventRead;
    /*DWORD�� ���� ������ ��Ÿ���� ������ ����
    eventRead�� �Է� �̺�Ʈ�� ������ �� ���� �����ϴ� ����*/
    std::vector<WORD> inVector;
    /*std::vector�� ���� �迭�� �ǹ��� �̰��� ����ؼ� inVector��� �̸��� ������ ���͸� ������
    WORD�� ������ ������ ����*/

    //����Ű ����
    std::cout << "ESC�� ������ ����˴ϴ�.\n�� �� A : �Ƶ���! =o\n�� �� S : �ҷ���!\n�� �� D : Ÿ����Ű��Ǫ~ļ��!\n�� �� A : �������~\n�� �� S : �ʻ��~\n�� �� D : ����!" << std::endl;

    while (true) {//���ѷ���, ���α׷��� ����ɶ����� �ݺ���
        /*
        ReadConsoleInput: �ֿܼ��� ����� �Է��� �д� �� ����
        �Ʒ��� ���� ���ڸ� ����
        ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), inRecord, bufferSize, &eventRead);
        ReadConsoleInput:�ܼ� �Է� �̺�Ʈ�� �� �迭�� ����
        GetStdHandle(STD_INPUT_HANDLE): ǥ�� �Է� �ڵ��� ��ȯ�ϴ� �Լ���, �ܼ��� Ű���� �Է��� ��Ÿ���ϴ�.
        inRecord: INPUT_RECORD ����ü �迭�Դϴ�.
        bufferSize: inRecord �迭�� ũ���Դϴ�. �� ���� inRecord �迭�� ������ �� �ִ� �Է� �̺�Ʈ�� �ִ� ������ ��Ÿ���ϴ�.
        &eventRead: DWORD ������ ������ ���� �������Դϴ�. �� ������ ReadConsoleInput �Լ��� ���� �Է� �̺�Ʈ�� ���� �����մϴ�.
        */
        ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), inRecord, bufferSize, &eventRead);

        for (DWORD i = 0; i < eventRead; i++) {//eventRead ������ ����� �Է� �̺�Ʈ�� ����ŭ �ݺ��Ͽ� �� �Է� �̺�Ʈ�� ó���մϴ�. 
            if (inRecord[i].EventType == KEY_EVENT) {//���� �Է� �̺�Ʈ�� ������ Ű �̺�Ʈ������ �˻�
                KEY_EVENT_RECORD keyEvent = inRecord[i].Event.KeyEvent;//���� ó�� ���� �Է� �̺�Ʈ�� Ű �̺�Ʈ�� ĳ�����ϰ� �̸� keyEvent ������ ����
                if (keyEvent.bKeyDown) {// Ű�� ���� ������ Ű �ٿ� �̺�Ʈ�� �����ϰ�, �� Ű�� ���� Ű �ڵ带 inVector ���Ϳ� ����
                    WORD keyCode = keyEvent.wVirtualKeyCode;

                    inVector.push_back(keyCode);

                    if (inVector.size() >= 3) {//���Ϳ� ����� Ű �ڵ尡 3�� �̻��� ��� �Ʒ� �ڵ� ����� ����
                        //���� �ֱٿ� ���� 3���� Ű �ڵ带 �����Ͽ� ���� prevKey, secondPrevKey, lastKey ������ ����
                        //-3, -2, -1�� ���� ������ ������ �� ��°, �� ��°, ù ��° ���
                        WORD prevKey = inVector[inVector.size() - 3];
                        WORD secondPrevKey = inVector[inVector.size() - 2];
                        WORD lastKey = inVector[inVector.size() - 1];

                        //Ű ����
                        switch (prevKey) {
                        case VK_DOWN:
                            switch (secondPrevKey) {
                            case VK_RIGHT:
                                if (lastKey == 'A') {
                                    std::cout << "�Ƶ���!=0" << std::endl;
                                    inVector.clear();
                                }
                                break;
                            case VK_DOWN:
                                if (lastKey == 'S') {
                                    std::cout << "�ҷ���!" << std::endl;
                                    inVector.clear();
                                }
                                break;
                            case VK_LEFT:
                                if (lastKey == 'D') {
                                    std::cout << "Ÿ����Ű��Ǫ~ļ��!" << std::endl;
                                    inVector.clear();
                                }
                                break;
                            }
                            break;
                        case VK_LEFT:
                            switch (secondPrevKey) {
                            case VK_RIGHT:
                                if (lastKey == 'A') {
                                    std::cout << "�������~" << std::endl;
                                    inVector.clear();
                                }
                                break;
                            case VK_DOWN:
                                if (lastKey == 'S') {
                                    std::cout << "�ʻ��~" << std::endl;
                                    inVector.clear();
                                }
                                break;
                            case VK_LEFT:
                                if (lastKey == 'D') {
                                    std::cout << "����!" << std::endl;
                                    inVector.clear();
                                }
                                break;
                            }
                            break;
                        }
                    }
                }
            }
        }
        //ESC�� ������ �����
        if (GetAsyncKeyState(VK_ESCAPE)) {
            std::cout << "�����մϴ�." << std::endl;
            return 0;
        }
    }

    return 0;
}
