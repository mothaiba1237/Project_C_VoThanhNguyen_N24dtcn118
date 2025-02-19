#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "function.h"
#include <string.h>

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

void showCategoryManagementMenu() {
    int choice;
    do {
        system("cls");
        setColor(12);
        printf("\n========= CATEGORY MANAGEMENT =========\n");
        setColor(14);
        printf("1. Add Category\n");
        printf("2. Display Categories\n");
        printf("3. Edit Category\n");
        printf("4. Delete Category\n");
        printf("5. Search Category by Name\n");
        printf("6. Sort Categories by Name\n");
        printf("7. Return to main menu\n");
        setColor(7);
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                showAddCategory();
                break;
            case 2:
                showDisplayCategories();
                break;
            case 3:
                showEditCategory();
                break;
            case 4:
                showDeleteCategory();
                break;
            case 5:
                showSearchCategory();
                break;
            case 6:
                showSortCategoryMenu();
                break;
            case 7:
                return;
            default:
                setColor(12);
                printf("Invalid choice! Please try again.\n");
                setColor(7);
        }
    } while (1);
}

void showProductManagementMenu() {
    int choice;
    do {
        system("cls");
        setColor(12);
        printf("\n========= PRODUCT MANAGEMENT =========\n");
        setColor(14);
        printf("1. Add Product\n");
        printf("2. Display Products\n");
        printf("3. Edit Product\n");
        printf("4. Delete Product\n");
        printf("5. Search Product by Name\n");
        printf("6. Sort Products by Name or Price\n");
        printf("7. Filter Products\n");
        printf("8. Return to main menu\n");
        setColor(7);
        printf("Enter your choice: ");
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
                showDeleteProduct();
                saveProductsToFile();
                break;
            case 5:
                searchProductByName();
                break;
            case 6:
                showSortProductMenu();
                break;
            case 7:
                showFilterMenu();
                break;
            case 8:
                return;
            default:
                setColor(12);
                printf("Invalid choice! Please try again.\n");
                setColor(7);
        }
    } while (1);
}

void showSortProductMenu() {
    int sortChoice;
    do {
        system("cls");
        setColor(12);
        printf("\n========= SORT PRODUCTS =========\n");
        setColor(14);
        printf("1. Sort by Name (Ascending)\n");
        printf("2. Sort by Name (Descending)\n");
        printf("3. Sort by Price (Ascending)\n");
        printf("4. Sort by Price (Descending)\n");
        printf("5. Return to product management menu\n");
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
        int back;
        scanf("%d", &back);
        if (back != 1) {
            return;
        }

    } while (1);
}

void showFilterMenu() {
    int choice;
    printf("\nFilter Products By:\n");
    printf("1. Category\n");
    printf("2. Price Range\n");
    printf("3. Return to product management\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        int category_id;
        printf("Enter Category ID: ");
        scanf("%d", &category_id);
        filterProductsByCategory(category_id);
    } else if (choice == 2) {
        float min_price, max_price;
        printf("Enter price range (min max): ");
        scanf("%f %f", &min_price, &max_price);
        filterProductsByPrice(min_price, max_price);
    }
}

int main() {
    loadCategoriesFromFile();
    loadProductsFromFile();

    int userType;
    setColor(12);
    printf("\n========================================\n");
    printf("           STORE MANAGEMENT SYSTEM\n");
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
        printf("\n========== MAIN MENU ==========\n");
        printf("1. Category Management\n");
        printf("2. Product Management\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        setColor(1);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                showCategoryManagementMenu();
                break;
            case 2:
                showProductManagementMenu();
                break;
            case 3:
                setColor(3);
                printf("Exiting the program!\n");
                saveCategoriesToFile();
                saveProductsToFile();
                break;
            default:
                setColor(12);
                printf("Invalid choice! Please try again.\n");
                setColor(7);
        }
    } while (choice != 3);

    return 0;
}

