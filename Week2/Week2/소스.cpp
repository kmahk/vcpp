#include <stdio.h>
#include <conio.h>

int main() {
    printf("임수빈의 2주차 과제\n");

    while (1) {
        printf("command>");

        char command[100];
        int i = 0;
        char ch;

        while (1) {
            ch = _getch();

            if (ch == 27) {
                printf("프로그램을 종료합니다.\n");
                return 0;
            }
            else if (ch == '\r') {
                command[i] = '\0';
                break;
            }
            else {
                command[i] = ch;
                i++;
                putchar(ch);
            }
        }

        switch (command[0]) {
        case 'q':
            printf("\nq로 시작하는 Quintessential\n");
            break;
        case 'w':
            printf("\nw로 시작하는 Wonderful\n");
            break;
        case 'e':
            printf("\ne로 시작하는 Eloquent\n");
            break;
        case 'r':
            printf("\nr로 시작하는 Radiant\n");
            break;
        default:
            printf("\n잘못된 입력입니다.\n");
        }
    }
    return 0;
}
