#include <stdio.h>
#include <stdlib.h>
#include <windows.h> 
#include "function.h"
#include <string.h>
#include <conio.h>
#define ADMIN_EMAIL "admin@gmail.com"
#define ADMIN_PASSWORD "mothaiba"


void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int authenticateAdmin() {
    char email[50], password[50];
    int index;

    while (1) {
        setColor(11);
        printf("\nADMIN LOGIN\n");
        setColor(7);
        printf("Enter Email: ");
        setColor(8);
        scanf("%s", email);

        setColor(7);
        printf("Enter Password: ");
        setColor(8);
        
        index = 0;
        while (1) {
            char ch = getch();
            
            if (ch == 13) {
                password[index] = '\0';
                break;
            } else if (ch == 8 && index > 0) {
                printf("\b \b");
                index--;
            } else if (ch >= 32 && ch <= 126 && index < 49) {
                password[index++] = ch;
                printf("*");
            }
        }
        printf("\n");

        if (strcmp(email, ADMIN_EMAIL) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
            setColor(10);
            printf("Login successful!\n");
            return 1;
        } else {
            setColor(12);
            printf("Incorrect email or password, please try again!\n");
        }
    }
}

void showSortProduct() {
    int sortChoice, back;
    do {
        system("cls");
        setColor(12);
        printf("\n========= SORT PRODUCT LIST =========\n");
        setColor(14);
        printf("1. Sort by Name (Ascending)\n");
        printf("2. Sort by Name (Descending)\n");
        printf("3. Sort by Price (Ascending)\n");
        printf("4. Sort by Price (Descending)\n");
        printf("5. Return to main menu\n");
        printf("Enter your choice: ");
        setColor(7);
        scanf("%d", &sortChoice);

        switch (sortChoice) {
            case 1:
                sortProductsByName(1);
                break;
            case 2:
                sortProductsByName(0);
                break;
            case 3:
                sortProductsByPrice(1);
                break;
            case 4:
                sortProductsByPrice(0);
                break;
            case 5:
                return;
            default:
                setColor(12);
                printf("Invalid choice! Please try again.\n");
                setColor(7);
        }

        setColor(9);
        printf("\nSorted Product List:\n");
        displayProducts();
        
        setColor(14);
        printf("\n1. Return to sorting menu\n");
        printf("Enter your choice: ");
        scanf("%d", &back);

    } while (back == 1);
}
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {

loadProductsFromFile();

int userType;
setColor(12);
printf("\n========================================\n");
printf("           STORE MANAGEMENT\n");
printf("========================================\n");
printf("\nSELECT ACCOUNT TYPE\n");
printf("1. Admin\n");
printf("2. Customer\n");
printf("Enter your choice: ");
setColor(8);
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
    printf("5. ShowSortProduct\n"); 
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

