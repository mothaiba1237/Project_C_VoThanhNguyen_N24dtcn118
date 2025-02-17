#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MAX_PRODUCTS 100

struct Product {
    int id;
    char name[50];
    float price;
    int quantity;
};

void setColor(int color);
void getFilePath();
int getValidIntInput(int* input, const char* prompt);
int getValidFloatInput(float* input, const char* prompt);

void addProduct();
void displayProducts();
void editProduct();
void deleteProduct();
void saveProductsToFile();
void loadProductsFromFile();
void searchProductByName();
void sortProductsByName(int ascending);
void showSortProduct();
void showDisplayProducts();

#endif

