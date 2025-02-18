#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <direct.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define MAX_CATEGORIES 50

// Struct definitions
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

// Global variables
extern Product products[MAX_PRODUCTS];
extern int num_products;

extern Category categories[MAX_CATEGORIES];
extern int num_categories;

// Category management functions
void loadCategoriesFromFile();
void saveCategoriesToFile();
void addCategory();
void displayCategories();
void editCategory();
void deleteCategory();
void searchCategoryByName();
void sortCategoriesByName();

// Product management functions
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

// UI functions
void setColor(int color);
void printCurrentDirectory();
void displayMenu();

// Data validation functions
int isValidProductData(Product product);
int isValidCategoryData(Category category);

// UI functions for category management
void showDisplayCategories();
void showAddCategory();
void showEditCategory();
void showDeleteCategory();
void showSearchCategory();
void showSortCategoryMenu();
void showCategoryManagementMenu();

// UI functions for product management
void showAddProduct();
void showDisplayProduct();
void showEditProduct();
void showDeleteProduct();
void showSortProductMenu();

#endif
