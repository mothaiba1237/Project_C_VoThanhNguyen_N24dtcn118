#include <stdio.h>
#include <stdlib.h>
#include <windows.h> 
#include "function.h"
#include <string.h>
#define ADMIN_EMAIL "admin@gmail.com"
#define ADMIN_PASSWORD "mothaiba"

struct Product products[MAX_PRODUCTS];
int num = 0;

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int authenticateAdmin() {
    char email[50], password[50];
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
        scanf("%s", password);
        
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
        printf("1. Sort by ID (Ascending)\n");
        printf("2. Sort by ID (Descending)\n");
        printf("3. Sort by Price (Ascending)\n");
        printf("4. Sort by Price (Descending)\n");
        printf("5. Return to main menu\n");
        printf("Enter your choice: ");
        setColor(7);
        scanf("%d", &sortChoice);

        switch (sortChoice) {
            case 1:
                sortProductsByID(1);
                break;
            case 2:
                sortProductsByID(0);
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
                break;
            case 2:
            	showDisplayProducts(); 
                
                break;
            case 3:
            	showEditProduct();
                
                break;
            case 4:
            	deleteProduct(); 
                break;
            case 5:
            	showSortProduct();
            	break;
            case 6:
			    break; 
            case 7:
                setColor(3);
                printf("Exiting the program!\n");
                break;
            default:
                setColor(12);
                printf("Invalid choice!\n");
                setColor(7);

        }
    } while (choice != 7);
	return 0;
}
