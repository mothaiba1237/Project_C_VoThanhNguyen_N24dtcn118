#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

struct Product products[MAX_PRODUCTS];
int num = 0;
int i,j; 
char filePath[100];

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void getFilePath() {
    setColor(10);
    printf("Enter the file path for saving/loading products: ");
    setColor(7);
    scanf("%s", filePath);
}

int getValidIntInput(int* input, const char* prompt) {
    setColor(10);
    printf("%s", prompt);
    while (scanf("%d", input) != 1) {
        setColor(12);
        printf("Invalid input. Please enter an integer: ");
        setColor(7);
        while (getchar() != '\n');
    }
    return *input;
}

int getValidFloatInput(float* input, const char* prompt) {
    setColor(10);
    printf("%s", prompt);
    while (scanf("%f", input) != 1) {
        setColor(12);
        printf("Invalid input. Please enter a float value: ");
        setColor(7);
        while (getchar() != '\n');
    }
    return *input;
}

void addProduct() {
    struct Product newProduct;
    newProduct.id = num + 1;
    getValidIntInput(&newProduct.id, "Enter Product ID: ");
    setColor(10);
    printf("Enter Product Name: ");
    setColor(7);
    scanf("%s", newProduct.name);
    getValidFloatInput(&newProduct.price, "Enter Product Price: ");
    getValidIntInput(&newProduct.quantity, "Enter Product Quantity: ");
    products[num++] = newProduct;
    setColor(10);
    printf("Product added successfully.\n");
}

void displayProducts() {
    setColor(10);
    printf("\n========= Product List =========\n");
    setColor(7);
    for ( i = 0; i < num; i++) {
        printf("ID: %d, Name: %s, Price: %.2f, Quantity: %d\n", 
                products[i].id, products[i].name, products[i].price, products[i].quantity);
    }
}

void editProduct() {
    int productId;
    getValidIntInput(&productId, "Enter product ID to edit: ");
    if (productId > 0 && productId <= num) {
        struct Product* p = &products[productId - 1];
        setColor(10);
        printf("Editing Product: %s\n", p->name);
        setColor(7);
        printf("Enter new name: ");
        scanf("%s", p->name);
        getValidFloatInput(&p->price, "Enter new price: ");
        getValidIntInput(&p->quantity, "Enter new quantity: ");
        setColor(10);
        printf("Product updated successfully.\n");
    } else {
        setColor(12);
        printf("Invalid product ID.\n");
        setColor(7);
    }
}

void deleteProduct() {
    int productId;
    getValidIntInput(&productId, "Enter product ID to delete: ");
    if (productId > 0 && productId <= num) {
        for ( i = productId - 1; i < num - 1; i++) {
            products[i] = products[i + 1];
        }
        num--;
        setColor(10);
        printf("Product deleted successfully.\n");
    } else {
        setColor(12);
        printf("Invalid product ID.\n");
        setColor(7);
    }
}

void saveProductsToFile() {
    FILE *file = fopen(filePath, "wb");
    if (file != NULL) {
        fwrite(&num, sizeof(int), 1, file);
        fwrite(products, sizeof(struct Product), num, file);
        fclose(file);
        setColor(10);
        printf("Products saved to file.\n");
    } else {
        setColor(12);
        printf("Error opening file for saving.\n");
        setColor(7);
    }
}

void loadProductsFromFile() {
    FILE *file = fopen(filePath, "rb");
    if (file != NULL) {
        fread(&num, sizeof(int), 1, file);
        fread(products, sizeof(struct Product), num, file);
        fclose(file);
        setColor(10);
        printf("Products loaded from file.\n");
    } else {
        setColor(12);
        printf("Error opening file for loading.\n");
        setColor(7);
    }
}

void searchProductByName() {
    char name[50];
    setColor(10);
    printf("Enter product name to search: ");
    setColor(7);
    scanf("%s", name);
    setColor(10);
    printf("\nSearch Results:\n");
    setColor(7);
    int found = 0;
    for ( i = 0; i < num; i++) {
        if (strstr(products[i].name, name)) {
            printf("ID: %d, Name: %s, Price: %.2f, Quantity: %d\n", 
                    products[i].id, products[i].name, products[i].price, products[i].quantity);
            found = 1;
        }
    }
    if (!found) {
        setColor(12);
        printf("No products found.\n");
        setColor(7);
    }
}

void sortProductsByName(int ascending) {
    for ( i = 0; i < num - 1; i++) {
        for ( j = i + 1; j < num; j++) {
            int cmp = strcmp(products[i].name, products[j].name);
            if ((ascending && cmp > 0) || (!ascending && cmp < 0)) {
                struct Product temp = products[i];
                products[i] = products[j];
                products[j] = temp;
            }
        }
    }
    setColor(10);
    printf("Products sorted successfully.\n");
}

void showSortProduct() {
    int sortChoice;
    setColor(10);
    printf("\nSort Products:\n");
    setColor(7);
    printf("1. Sort by Name (Ascending)\n");
    printf("2. Sort by Name (Descending)\n");
    setColor(8);
    printf("Enter your choice: ");
    scanf("%d", &sortChoice);

    switch (sortChoice) {
        case 1:
            sortProductsByName(1);
            break;
        case 2:
            sortProductsByName(0);
            break;
        default:
            setColor(12);
            printf("Invalid choice.\n");
            setColor(7);
    }
}

void showDisplayProducts() {
    displayProducts();
}

