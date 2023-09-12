#include <iostream>
#include <conio.h>

int main() {
    // 프로그램 시작
    std::cout << "임수빈의 VC++\n";

    while (true) {
        // 커맨드 입력받도록 UI출력
        std::cout << "command>";
        char command = _getch();
        std::cout << command << "\n";

        // 네 가지 커맨드에 대한 문자열 출력
        switch (command) {
        case 'q':
            std::cout << "q로 시작하는 Quintessential\n";
            break;
        case 'w':
            std::cout << "w로 시작하는 Wonderful\n";
            break;
        case 'e':
            std::cout << "e로 시작하는 Eloquent\n";
            break;
        case 'r':
            std::cout << "r로 시작하는 Radiant\n";
            break;
        case 27:  // ESC 키
            return 0;
        default:
            std::cout << "잘못된 입력입니다.\n";
        }
    }

    return 0;
}
