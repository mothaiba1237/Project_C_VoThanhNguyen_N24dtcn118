#include <stdio.h>
#include <stdlib.h>
#include "function.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int userType;

    getFilePath();
    loadProductsFromFile();

    setColor(12);
    printf("\n========================================\n");
    printf("           STORE MANAGEMENT\n");
    printf("========================================\n");
    printf("\nSELECT ACCOUNT TYPE\n");
    printf("1. Admin\n");
    printf("2. Customer\n");
    setColor(8);
    printf("Enter your choice: ");
    scanf("%d", &userType);

    if (userType == 1) {
        if (!authenticateAdmin()) {
            return 0;
        }
    } else {
        setColor(14);
        printf("You are accessing with customer privileges.\n");
        setColor(7);
        return 0;
    }

    int choice;
    do {
        setColor(10);
        printf("\n========== CATEGORY MANAGEMENT MENU ==========\n");
        printf("1. Add product\n");
        printf("2. Display product list\n");
        printf("3. Edit product information\n");
        printf("4. Delete product information\n");
        printf("5. Show sorted product list\n");
        printf("6. Search Product\n");
        printf("7. Exit\n");
        printf("\n==============================================\n");
        printf("Enter your choice: ");
        setColor(1);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                showAddProduct();
                saveProductsToFile();
                break;
            case 2:
                showDisplayProducts();
                break;
            case 3:
                showEditProduct();
                saveProductsToFile();
                break;
            case 4:
                deleteProduct();
                saveProductsToFile();
                break;
            case 5:
                showSortProduct();
                break;
            case 6:
                searchProductByName();
                break;
            case 7:
                setColor(3);
                printf("Exiting the program!\n");
                saveProductsToFile();
                break;
            default:
                setColor(12);
                printf("Invalid choice!\n");
                setColor(7);
        }
    } while (choice != 7);

    return 0;
}

