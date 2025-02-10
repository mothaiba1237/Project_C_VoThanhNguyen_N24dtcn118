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
        scanf("%s", email);
        printf("Enter Password: ");
        scanf("%s", password);
        
        if (strcmp(email, ADMIN_EMAIL) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
            setColor(10);
            printf("Login successful!\n");
            setColor(7);
            return 1;
        } else {
            setColor(12);
            printf("Incorrect email or password, please try again!\n");
            setColor(7);
        }
    }
}
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
int userType;
    setColor(12); 
    printf("\n========================================\n");
    printf("     PRODUCT MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    printf("\nSELECT ACCOUNT TYPE\n");
    printf("1. Admin\n");
    printf("2. Customer\n");
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
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
            	displayProducts(); 
                
                break;
            case 3:
            	editProduct();
                
                break;
            case 4:
               
                break;
            case 5:
                setColor(3);
                printf("Exiting the program!\n");
                break;
            default:
                setColor(12);
                printf("Invalid choice!\n");
                setColor(7);

        }
    } while (choice != 5);
	return 0;
}
