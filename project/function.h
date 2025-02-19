#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <direct.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define MAX_CATEGORIES 50


typedef struct Product {
    int id;
    char name[50];
    float price;
    int quantity;
    int category_id;
} Product;

typedef struct Category {
    int id;
    char name[50];
} Category;


extern Product products[MAX_PRODUCTS];
extern int num_products;

extern Category categories[MAX_CATEGORIES];
extern int num_categories;


void loadCategoriesFromFile();
void saveCategoriesToFile();
void addCategory();
void displayCategories();
void editCategory();
void deleteCategory();
void searchCategoryByName();
void sortCategoriesByName();


void loadProductsFromFile();
void saveProductsToFile();
void addProduct();
void displayProducts();
void editProduct();
void deleteProduct();
void searchProductByName();
void sortProductsByName(int ascending);
void sortProductsByPrice(int ascending);
void filterProductsByCategory(int category_id);
void filterProductsByPrice(float min_price, float max_price);
void showFilterMenu();


void setColor(int color);
void printCurrentDirectory();
void displayMenu();


int isValidProductData(Product product);
int isValidCategoryData(Category category);


void showDisplayCategories();
void showAddCategory();
void showEditCategory();
void showDeleteCategory();
void showSearchCategory();
void showSortCategoryMenu();
void showCategoryManagementMenu();


void showAddProduct();
void showDisplayProduct();
void showEditProduct();
void showDeleteProduct();
void showSortProductMenu();

#endif
