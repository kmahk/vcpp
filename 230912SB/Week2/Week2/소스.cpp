#include <iostream>
#include <conio.h>

int main() {
    // ���α׷� ����
    std::cout << "�Ӽ����� VC++\n";

    while (true) {
        // Ŀ�ǵ� �Է¹޵��� UI���
        std::cout << "command>";
        char command = _getch();
        std::cout << command << "\n";

        // �� ���� Ŀ�ǵ忡 ���� ���ڿ� ���
        switch (command) {
        case 'q':
            std::cout << "q�� �����ϴ� Quintessential\n";
            break;
        case 'w':
            std::cout << "w�� �����ϴ� Wonderful\n";
            break;
        case 'e':
            std::cout << "e�� �����ϴ� Eloquent\n";
            break;
        case 'r':
            std::cout << "r�� �����ϴ� Radiant\n";
            break;
        case 27:  // ESC Ű
            return 0;
        default:
            std::cout << "�߸��� �Է��Դϴ�.\n";
        }
    }

    return 0;
}
