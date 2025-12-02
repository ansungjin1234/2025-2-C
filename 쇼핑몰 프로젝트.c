#include <stdio.h>
#include <string.h>

#define PRODUCT_COUNT 5

typedef struct {
    char name[30];
    int price;
    int stock;
    int total_stocked_in;
    int total_sold;
} Product;

int main() {
    Product product_list[PRODUCT_COUNT];
    int menu, id, quantity, price;
    int idx;

    for (int i = 0; i < PRODUCT_COUNT; i++) {
        strcpy(product_list[i].name, "미입력");
        product_list[i].price = 0;
        product_list[i].stock = 0;
        product_list[i].total_stocked_in = 0;
        product_list[i].total_sold = 0;
    }

    while (1) {
        printf("\n[쇼핑몰 관리 프로그램]\n");
        printf("원하는 메뉴를 선택하세요.(1. 입고, 2. 판매, 3. 개별현황, 4. 전체현황, 5. 상품정보저장, 6. 상품정보가져오기, 7. 종료)\n");
        printf("메뉴 선택 : ");
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                printf("\n<< 입고메뉴실행 >>\n");
                printf("상품ID(1-%d) : ", PRODUCT_COUNT);
                scanf("%d", &id);

                if (id < 1 || id > PRODUCT_COUNT) {
                    printf("잘못된 상품 ID입니다. (1-%d)\n", PRODUCT_COUNT);
                    break;
                }
                idx = id - 1;

                printf("상품명 : ");
                scanf("%s", product_list[idx].name);

                printf("입고량 : ");
                scanf("%d", &quantity);
                if (quantity < 0) quantity = 0;

                printf("판매가격 : ");
                scanf("%d", &price);
                if (price < 0) price = 0;
                
                product_list[idx].price = price;
                product_list[idx].stock += quantity;
                product_list[idx].total_stocked_in += quantity;
                
                printf(">> 상품 ID %d (%s) %d개 입고 완료 (현재 재고: %d)\n", id, product_list[idx].name, quantity, product_list[idx].stock);
                break;

            case 2:
                printf("\n<< 판매메뉴실행 >>\n");
                printf("상품ID(1-%d) : ", PRODUCT_COUNT);
                scanf("%d", &id);

                if (id < 1 || id > PRODUCT_COUNT) {
                    printf("잘못된 상품 ID입니다. (1-%d)\n", PRODUCT_COUNT);
                    break;
                }
                idx = id - 1;

                if (strcmp(product_list[idx].name, "미입력") == 0) {
                    printf("<< 상품ID << %d는(은) 없음>>\n", id);
                    break;
                }

                printf("판매량 : ");
                scanf("%d", &quantity);

                if (quantity > product_list[idx].stock) {
                    printf("재고 부족! 현재 재고: %d개. %d개만 판매합니다.\n", product_list[idx].stock, product_list[idx].stock);
                    quantity = product_list[idx].stock;
                } else if (quantity < 0) {
                    quantity = 0;
                }

                product_list[idx].stock -= quantity;
                product_list[idx].total_sold += quantity;

                printf(">> 상품 ID %d (%s) %d개 판매 완료 (현재 재고: %d)\n", id, product_list[idx].name, quantity, product_list[idx].stock);
                break;

            case 3:
                printf("\n<< 개별상품정보 >>\n");
                printf("상품ID(1-%d) : ", PRODUCT_COUNT);
                scanf("%d", &id);

                if (id < 1 || id > PRODUCT_COUNT) {
                    printf("잘못된 상품 ID입니다. (1-%d)\n", PRODUCT_COUNT);
                    break;
                }
                idx = id - 1;

                if (strcmp(product_list[idx].name, "미입력") == 0) {
                    printf("<< 상품ID << %d는(은) 등록되지 않은 상품입니다.>>\n", id);
                    break;
                }

                printf("--- 상품 ID %d 정보 ---\n", id);
                printf("상품명: %s\n", product_list[idx].name);
                printf("판매가격: %d원\n", product_list[idx].price);
                printf("현재재고: %d개\n", product_list[idx].stock);
                printf("총 입고량: %d개\n", product_list[idx].total_stocked_in);
                printf("총 판매량: %d개\n", product_list[idx].total_sold);
                long long total_sales_amount = (long long)product_list[idx].total_sold * product_list[idx].price;
                printf("총 판매금액: %lld원\n", total_sales_amount);
                printf("-----------------------\n");
                break;

            case 4:
                printf("\n<< 전체상품정보 >>\n");

                printf("현재 재고수량 : ");
                for (int i = 0; i < PRODUCT_COUNT; i++) {
                    printf("%d ", product_list[i].stock);
                }
                printf("\n");

                int total_sale_all = 0;
                int total_store_all = 0;
                long long total_sales_amount_all = 0;

                for (int i = 0; i < PRODUCT_COUNT; i++) {
                    total_sale_all += product_list[i].total_sold;
                    total_store_all += product_list[i].total_stocked_in;
                    total_sales_amount_all += (long long)product_list[i].total_sold * product_list[i].price;
                }

                printf("총 판매량 : %d ", total_sale_all);
                if (total_store_all > 0)
                    printf("(판매율 %.2f%%)\n", (double)total_sale_all / total_store_all * 100.0);
                else
                    printf("(판매율 0.00%%)\n");
                
                printf("총 판매금액 : %lld원\n", total_sales_amount_all);

                if (total_store_all > 0) {
                    int maxID = 0, minID = 0;
                    for (int i = 1; i < PRODUCT_COUNT; i++) {
                        if (product_list[i].total_sold > product_list[maxID].total_sold) maxID = i;
                        if (product_list[i].total_sold < product_list[minID].total_sold) minID = i;
                    }
                    printf("가장 많이 판매된 상품 : ID %d (상품명: %s, 판매량: %d)\n", maxID + 1, product_list[maxID].name, product_list[maxID].total_sold);
                    printf("가장 적게 판매된 상품 : ID %d (상품명: %s, 판매량: %d)\n", minID + 1, product_list[minID].name, product_list[minID].total_sold);
                } else {
                    printf("아직 판매된 상품이 없습니다.\n");
                }

                printf("--- 재고 부족 상품 ---\n");
                int low_stock_count = 0;
                for (int i = 0; i < PRODUCT_COUNT; i++) {
                    if (strcmp(product_list[i].name, "미입력") != 0 && product_list[i].stock <= 2) {
                        printf("상품 ID %d (상품명: %s) : 재고 %d개\n", i + 1, product_list[i].name, product_list[i].stock);
                        low_stock_count++;
                    }
                }
                if (low_stock_count == 0) {
                    printf("재고 부족 상품이 없습니다.\n");
                }
                break;

            case 5:
                {
                    FILE *fp = fopen("products.dat", "wb");
                    if (fp == NULL) {
                        printf("파일을 여는 데 실패했습니다.\n");
                        break;
                    }
                    fwrite(product_list, sizeof(Product), PRODUCT_COUNT, fp);
                    fclose(fp);
                    printf(">> 상품 정보가 'products.dat'에 저장되었습니다.\n");
                }
                break;

            case 6:
                {
                    FILE *fp = fopen("products.dat", "rb");
                    if (fp == NULL) {
                        printf("저장된 'products.dat' 파일을 찾을 수 없습니다.\n");
                        break;
                    }
                    fread(product_list, sizeof(Product), PRODUCT_COUNT, fp);
                    fclose(fp);
                    printf(">> 'products.dat'에서 상품 정보를 불러왔습니다.\n");
                }
                break;

            case 7:
                printf("프로그램을 종료합니다.\n");
                return 0;

            default:
                printf("잘못된 메뉴 선택입니다. (1-7)\n");
        }
    }
}
