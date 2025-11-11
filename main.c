#include <stdio.h>

#define SIZE 5

int main() {
    int stock_in[SIZE] = {0};
    int stock_out[SIZE] = {0};
    int inventory[SIZE] = {0};
    int menu;

    while (1) {
        printf("\n[쇼핑몰 관리 프로그램]\n");
        printf("> 원하는 메뉴를 선택하세요. (1. 입고, 2. 판매, 3. 상품현황, 4. 종료)\n> ");
        scanf("%d", &menu);

        if (menu == 1) {
            int option;
            printf("> (입력) 입고수량 입력: 전체 1, 개별 2 선택\n> ");
            scanf("%d", &option);

            if (option == 1) {
                printf("> (입력) 전체 상품 입고수량 입력 (공백으로 구분, %d개):\n> ", SIZE);
                for (int i = 0; i < SIZE; i++) {
                    int in;
                    scanf("%d", &in);
                    stock_in[i] += in;
                    inventory[i] += in;
                }
            } else if (option == 2) {
                int id, in;
                printf("> (입력) 상품 ID (1~%d): ", SIZE);
                scanf("%d", &id);
                printf("> (입력) 입고수량: ");
                scanf("%d", &in);
                if (id >= 1 && id <= SIZE) {
                    stock_in[id - 1] += in;
                    inventory[id - 1] += in;
                } else {
                    printf(">>> 잘못된 ID입니다.\n");
                }
            }

        } else if (menu == 2) {
            int option;
            printf("> (입력) 판매수량 입력: 전체 1, 개별 2 선택\n> ");
            scanf("%d", &option);

            if (option == 1) {
                printf("> (입력) 전체 상품 판매수량 입력 (공백으로 구분, %d개):\n> ", SIZE);
                for (int i = 0; i < SIZE; i++) {
                    int out;
                    int IP;
                    scanf("%d", &IP);
                    printf("상품ID 입력 : ", IP);
                    scanf("%d", &out);
                    if (inventory[i] >= out) {
                        stock_out[i] += out;
                        inventory[i] -= out;
                    } else {
                        printf(">>> 상품 ID %d: 재고 부족, 판매 실패 (현재 재고 %d)\n", i + 1, inventory[i]);
                    }
                }
            } else if (option == 2) {
                int id, out;
                printf("> (입력) 상품 ID (1~%d): ", SIZE);
                scanf("%d", &id);
                printf("> (입력) 판매수량: ");
                scanf("%d", &out);
                if (id >= 1 && id <= SIZE) {
                    if (inventory[id - 1] >= out) {
                        stock_out[id - 1] += out;
                        inventory[id - 1] -= out;
                    } else {
                        printf(">>> 상품 ID %d: 재고 부족, 판매 실패 (현재 재고 %d)\n", id, inventory[id - 1]);
                    }
                } else {
                    printf(">>> 잘못된 ID입니다.\n");
                }
            }

        } else if (menu == 3) {
            printf("\n상품현황\n");
            printf("ID\t입고\t판매\t재고\n");
            for (int i = 0; i < SIZE; i++) {
                printf("%d\t%d\t%d\t%d\n", i + 1, stock_in[i], stock_out[i], inventory[i]);
            }

        } else if (menu == 4) {
            printf("프로그램을 종료합니다.\n");
            break;

        } else {
            printf("잘못된 메뉴 선택입니다.\n");
        }
    }

    return 0;
}
