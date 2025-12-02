#include <stdio.h>
#include <string.h>

#define PRODUCT_COUNT 5
#define LEN 50  

int main() {
    int total_stocked_in[PRODUCT_COUNT] = {0};
    int total_sold[PRODUCT_COUNT] = {0};
    int stock[PRODUCT_COUNT] = {0};
    int price[PRODUCT_COUNT] = {0};
    long long total_sales_amount[PRODUCT_COUNT] = {0};

    char name[PRODUCT_COUNT][LEN] = {"상품1", "상품2", "상품3", "상품4", "상품5"}; 
    
    int total_stocked_in_all = 0;   
    int total_sold_all = 0; 

    int menu;

    while (1) {
        printf("\n[쇼핑몰 관리 프로그램]\n");
        printf("원하는 메뉴를 선택하세요. (1. 입고, 2. 판매, 3. 개별현황, 4. 전체현황, 5. 종료)\n> ");
        scanf("%d", &menu);

        if (menu == 1) {  
            int id, quantity, p; 
            printf("입고할 상품 ID 입력(1~5): ");
            scanf("%d", &id);
            if (id < 1 || id > PRODUCT_COUNT) {
                printf("잘못된 ID입니다.\n");
                continue;
            }

            printf("%s의 입고 수량 입력: ", name[id - 1]);
            scanf("%d", &quantity);
            
            total_stocked_in[id - 1] += quantity;
            stock[id - 1] += quantity;
            total_stocked_in_all += quantity;

            if (price[id - 1] == 0) {
                printf("%s의 판매가격 입력: ", name[id - 1]);
                scanf("%d", &p);
                price[id - 1] = p;
            }

            printf("%s 입고 완료! (현재 재고: %d, 가격: %d원)\n", 
                   name[id - 1], stock[id - 1], price[id - 1]);

        } else if (menu == 2) {  
            int id, quantity;
            printf("판매할 상품 ID 입력(1~5): ");
            scanf("%d", &id);
            if (id < 1 || id > PRODUCT_COUNT) {
                printf("잘못된 ID입니다.\n");
                continue;
            }

            if (stock[id - 1] == 0) {
                printf("%s (ID %d) : 재고가 없습니다!\n", name[id - 1], id);
                continue;
            }

            printf("%s의 판매 수량 입력: ", name[id - 1]);
            scanf("%d", &quantity);
            
            if (stock[id - 1] >= quantity) {
                total_sold[id - 1] += quantity;
                stock[id - 1] -= quantity;
                total_sold_all += quantity;
                
                total_sales_amount[id - 1] += (long long)quantity * price[id - 1]; 
                
                printf("%s 판매 완료! (남은 재고: %d, 총매출: %lld원)\n",
                       name[id - 1], stock[id - 1], total_sales_amount[id - 1]);
            } else {
                printf("%s (ID %d) : 재고부족!\n", name[id - 1], id);
            }

        } else if (menu == 3) {  
            int id;
            printf("조회할 상품 ID 입력(1~5): ");
            scanf("%d", &id);
            if (id < 1 || id > PRODUCT_COUNT) {
                printf("잘못된 ID입니다.\n");
                continue;
            }
            printf("\n[개별 상품 현황]\n");
            printf("ID %d\n상품명: %s\n가격: %d원\n재고: %d\n판매량: %d\n총매출: %lld원\n",
                   id, name[id - 1], price[id - 1], stock[id - 1],
                   total_sold[id - 1], total_sales_amount[id - 1]);

        } else if (menu == 4) {  
            long long total_sales_amount_all = 0;
            printf("\n[전체 상품 현황]\n");
            
            for (int i = 0; i < PRODUCT_COUNT; i++) {
                printf("ID %d | 상품명: %-6s | 가격: %5d원 | 재고: %3d | 판매량: %3d | 매출: %6lld원\n",
                       i + 1, name[i], price[i], stock[i], total_sold[i], total_sales_amount[i]);
                total_sales_amount_all += total_sales_amount[i];
            }
            printf("전체 총매출 합계: %lld원\n", total_sales_amount_all);

        } else if (menu == 5) {  
            printf("프로그램을 종료합니다.\n");
            break;
        } else {
            printf("잘못된 선택입니다.\n");
        }
    }

    return 0;
}
