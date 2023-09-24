#include <iostream>
#include <windows.h>
#include <vector>

int main() {
    const int bufferSize = 128;//buffersize라는 정수 상수를 128로 설정한다.
    INPUT_RECORD inRecord[bufferSize];
    /*INPUT RECORD는 입력 이벤트를 나타내는 데이터 구조*/
    DWORD eventRead;
    /*DWORD는 양의 정수를 나타내는 데이터 구조
    eventRead는 입력 이벤트를 읽을때 그 값을 저장하는 변수*/
    std::vector<WORD> inVector;
    /*std::vector는 동적 배열을 의미함 이것을 사용해서 inVector라는 이름의 정수형 벡터를 선언함
    WORD는 정수형 데이터 유형*/

    //조작키 설명
    std::cout << "ESC를 누르면 종료됩니다.\n↓ → A : 아도겐! =o\n↓ ↓ S : 소류겐!\n↓ ← D : 타츠마키센푸~캬쿠!\n← → A : 무적방어~\n← ↓ S : 필살기~\n← ← D : 자폭!" << std::endl;

    while (true) {//무한루프, 프로그램이 종료될때까지 반복됨
        /*
        ReadConsoleInput: 콘솔에서 사용자 입력을 읽는 데 사용됨
        아래와 같은 인자를 가짐
        ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), inRecord, bufferSize, &eventRead);
        ReadConsoleInput:콘솔 입력 이벤트를 이 배열에 저장
        GetStdHandle(STD_INPUT_HANDLE): 표준 입력 핸들을 반환하는 함수로, 콘솔의 키보드 입력을 나타냅니다.
        inRecord: INPUT_RECORD 구조체 배열입니다.
        bufferSize: inRecord 배열의 크기입니다. 이 값은 inRecord 배열에 저장할 수 있는 입력 이벤트의 최대 개수를 나타냅니다.
        &eventRead: DWORD 형식의 변수에 대한 포인터입니다. 이 변수는 ReadConsoleInput 함수가 읽은 입력 이벤트의 수를 저장합니다.
        */
        ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), inRecord, bufferSize, &eventRead);

        for (DWORD i = 0; i < eventRead; i++) {//eventRead 변수에 저장된 입력 이벤트의 수만큼 반복하여 각 입력 이벤트를 처리합니다. 
            if (inRecord[i].EventType == KEY_EVENT) {//현재 입력 이벤트의 유형이 키 이벤트인지를 검사
                KEY_EVENT_RECORD keyEvent = inRecord[i].Event.KeyEvent;//현재 처리 중인 입력 이벤트를 키 이벤트로 캐스팅하고 이를 keyEvent 변수에 저장
                if (keyEvent.bKeyDown) {// 키를 누를 때마다 키 다운 이벤트를 감지하고, 각 키의 가상 키 코드를 inVector 벡터에 저장
                    WORD keyCode = keyEvent.wVirtualKeyCode;

                    inVector.push_back(keyCode);

                    if (inVector.size() >= 3) {//벡터에 저장된 키 코드가 3개 이상인 경우 아래 코드 블록이 실행
                        //가장 최근에 누른 3개의 키 코드를 추출하여 각각 prevKey, secondPrevKey, lastKey 변수에 저장
                        //-3, -2, -1은 각각 벡터의 끝에서 세 번째, 두 번째, 첫 번째 요소
                        WORD prevKey = inVector[inVector.size() - 3];
                        WORD secondPrevKey = inVector[inVector.size() - 2];
                        WORD lastKey = inVector[inVector.size() - 1];

                        //키 조합
                        switch (prevKey) {
                        case VK_DOWN:
                            switch (secondPrevKey) {
                            case VK_RIGHT:
                                if (lastKey == 'A') {
                                    std::cout << "아도겐!=0" << std::endl;
                                    inVector.clear();
                                }
                                break;
                            case VK_DOWN:
                                if (lastKey == 'S') {
                                    std::cout << "소류겐!" << std::endl;
                                    inVector.clear();
                                }
                                break;
                            case VK_LEFT:
                                if (lastKey == 'D') {
                                    std::cout << "타츠마키센푸~캬쿠!" << std::endl;
                                    inVector.clear();
                                }
                                break;
                            }
                            break;
                        case VK_LEFT:
                            switch (secondPrevKey) {
                            case VK_RIGHT:
                                if (lastKey == 'A') {
                                    std::cout << "무적방어~" << std::endl;
                                    inVector.clear();
                                }
                                break;
                            case VK_DOWN:
                                if (lastKey == 'S') {
                                    std::cout << "필살기~" << std::endl;
                                    inVector.clear();
                                }
                                break;
                            case VK_LEFT:
                                if (lastKey == 'D') {
                                    std::cout << "자폭!" << std::endl;
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
        //ESC를 누르면 종료됨
        if (GetAsyncKeyState(VK_ESCAPE)) {
            std::cout << "종료합니다." << std::endl;
            return 0;
        }
    }

    return 0;
}
