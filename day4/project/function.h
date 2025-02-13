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

extern struct Product products[MAX_PRODUCTS];
extern int num;

void setColor(int color);
void addProduct();
void displayProducts(); 
void editProduct();
void deleteProduct(); 
void showAddProduct();
void showDisplayProducts();
void showEditProducts(); 
void showDeleteProduct();
void loadProductsFromFile();
void saveProductsToFile();
void searchProductByName(); 



#endif
