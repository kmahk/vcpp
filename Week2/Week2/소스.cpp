#include <stdio.h>
#include <conio.h>

int main() {
    printf("�Ӽ����� 2���� ����\n");

    while (1) {
        printf("command>");

        char command[100];
        int i = 0;
        char ch;

        while (1) {
            ch = _getch();

            if (ch == 27) {
                printf("���α׷��� �����մϴ�.\n");
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
            printf("\nq�� �����ϴ� Quintessential\n");
            break;
        case 'w':
            printf("\nw�� �����ϴ� Wonderful\n");
            break;
        case 'e':
            printf("\ne�� �����ϴ� Eloquent\n");
            break;
        case 'r':
            printf("\nr�� �����ϴ� Radiant\n");
            break;
        default:
            printf("\n�߸��� �Է��Դϴ�.\n");
        }
    }
    return 0;
}
