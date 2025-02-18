#include "function.h"

struct Product products[MAX_PRODUCTS];
int num_products = 0;

struct Category categories[MAX_CATEGORIES];
int num_categories = 0;
Category categories[MAX_CATEGORIES];
int categoryCount = 0;
int i,j; 



void printCurrentDirectory() {
    char path[260];
    getcwd(path, sizeof(path));
    printf("Current working directory: %s\n", path);
}

void loadProductsFromFile() {
    FILE *file = fopen("data.bin", "rb");
    if (file == NULL) {
        printf("No previous data found. Starting fresh.\n");
        num_products = 0;
        return;
    }

    if (fread(&num_products, sizeof(int), 1, file) != 1) {
        printf("Error reading product count. Starting fresh.\n");
        num_products= 0;
        fclose(file);
        return;
    }

    if (fread(products, sizeof(struct Product), num_products, file) != num_products) {
        printf("Error reading product data. Some data may be missing.\n");
        num_products = 0; 
    }

    fclose(file);
}



void saveProductsToFile() {
    FILE *file = fopen("data.bin", "wb");
    if (file == NULL) {
        printf("Error: Unable to save data!\n");
        return;
    }

    if (fwrite(&num_products, sizeof(int), 1, file) != 1) {
        printf("Error saving product count!\n");
    }

    if (fwrite(products, sizeof(struct Product), num_products, file) != num_products) {
        printf("Error saving product data!\n");
    }

    fclose(file);
}





void addProduct() {
    if (num_products >= MAX_PRODUCTS) {
        setColor(12);
        printf("The product list is full!\n");
        setColor(7);
        return;
    }

    Product new_product;
    int is_duplicate;
    do {
        setColor(14);
        printf("Enter product ID (1 - 999): ");
        setColor(3);
        if (scanf("%d", &new_product.id) != 1) {
            while (getchar() != '\n');
            setColor(12);
            printf("Error: Invalid input! Please enter a number.\n");
            continue;
        }
        getchar();

        if (new_product.id < 1 || new_product.id > 999) {
            setColor(12);
            printf("Error: Product ID must be between 1 and 999!\n");
            continue;
        }

        is_duplicate = 0;
        for ( i = 0; i < num_products; i++) {
            if (products[i].id == new_product.id) {
                setColor(12);
                printf("Error: A product with this ID already exists!\n");
                is_duplicate = 1;
                break;
            }
        }
    } while (is_duplicate);

    do {
        setColor(14);
        printf("Enter product name (3 - 50 characters): ");
        setColor(3);
        fgets(new_product.name, sizeof(new_product.name), stdin);
        new_product.name[strcspn(new_product.name, "\n")] = '\0';

        int length = strlen(new_product.name);
        if (length < 3 || length > 50) {
            setColor(12);
            printf("Error: Product name must be between 3 and 50 characters!\n");
            continue;
        }

        is_duplicate = 0;
        for ( i = 0; i < num_products; i++) {
            if (strcmp(products[i].name, new_product.name) == 0) {
                setColor(12);
                printf("Error: A product with this name already exists!\n");
                is_duplicate = 1;
                break;
            }
        }
    } while (is_duplicate);

    setColor(14);
    printf("Enter product price: ");
    setColor(3);
    while (scanf("%f", &new_product.price) != 1 || new_product.price <= 0) {
        while (getchar() != '\n');
        setColor(12);
        printf("Error: Invalid price! Enter a valid number: ");
        setColor(3);
    }

    setColor(14);
    printf("Enter product quantity: ");
    setColor(3);
    while (scanf("%d", &new_product.quantity) != 1 || new_product.quantity < 0) {
        while (getchar() != '\n');
        setColor(12);
        printf("Error: Invalid quantity! Enter a valid number: ");
        setColor(3);
    }

    products[num_products++] = new_product;
    saveProductsToFile();

    setColor(2);
    printf("Product has been added successfully!\n");
    setColor(7);
}





void displayProducts() {
    if (num_products == 0) {
        setColor(14);
        printf("No products available!\n");
        setColor(7);
        return;
    }

    setColor(9);
    printf("\n+------------+---------------------------------+------------+------------+\n");
    setColor(9);
    printf("| ID         | Product Name                    | Price      | Quantity   |\n");
    setColor(9);
    printf("+------------+---------------------------------+------------+------------+\n");

    for (i = 0; i < num_products; i++) {
        setColor(9);
        printf("| %-10d | %-31s | %-10.2f$| %-10d |\n",
               products[i].id, products[i].name, products[i].price, products[i].quantity);
        printf("+------------+---------------------------------+------------+------------+\n");
    }

    setColor(7);
}



void editProduct() {
    int id, found = 0;
    setColor(14);
    printf("Enter the product ID to edit: ");
    setColor(3);
    scanf("%d", &id);
    getchar();

    for ( i = 0; i < num_products; i++) {
        if (products[i].id == id) {
            found = 1;
            setColor(10);
            printf("\nProduct found:\n");
            setColor(9);
            printf("+------------+---------------------------------+------------+------------+\n");
            printf("| ID         | Product Name                    | Price      | Quantity   |\n");
            printf("+------------+---------------------------------+------------+------------+\n");
            printf("| %-10d | %-31s | %-10.2f | %-10d |\n",
                   products[i].id, products[i].name, products[i].price, products[i].quantity);
            printf("+------------+---------------------------------+------------+------------+\n");

            do {
                setColor(11);
                printf("Enter new name (3 - 50 characters, current: %s): ", products[i].name);
                setColor(3);
                fgets(products[i].name, sizeof(products[i].name), stdin);
                products[i].name[strcspn(products[i].name, "\n")] = '\0';
            } while (strlen(products[i].name) < 3 || strlen(products[i].name) > 50);

            setColor(11);
            printf("Enter new price (current: %.2f): ", products[i].price);
            setColor(3);
            while (scanf("%f", &products[i].price) != 1 || products[i].price < 0) {
                printf("Invalid price! Enter a valid number: ");
                while (getchar() != '\n');
            }

            setColor(11);
            printf("Enter new quantity (current: %d): ", products[i].quantity);
            setColor(3);
            while (scanf("%d", &products[i].quantity) != 1 || products[i].quantity < 0) {
                printf("Invalid quantity! Enter a valid number: ");
                while (getchar() != '\n');
            }

            saveProductsToFile();

            setColor(2);
            printf("\nProduct information updated successfully!\n");
            return;
        }
    }
    if (!found) {
        setColor(12);
        printf("Product with ID %d not found!\n", id);
    }
    setColor(7);
}




void showAddProduct() {
    int back;
    do {
        system("cls");

        setColor(12);
        printf("\n========= ADD NEW PRODUCT =========\n");
        addProduct();
        
        setColor(14);
        printf("\n1. Return to main menu\n");
        printf("Enter your choice: ");
        scanf("%d", &back);
        
    } while (back != 1);
}




void showDisplayProducts() {
    int back;
    do {
        system("cls");

        setColor(12);
        printf("\n========= PRODUCT LIST =========\n");
        displayProducts();

        setColor(14);
        printf("\n1. Return to main menu\n");
        printf("Enter your choice: ");
        scanf("%d", &back);

    } while (back != 1);
}



void showEditProduct() {
    int back;
    do {
        system("cls");

        setColor(12);
        printf("\n========= EDIT PRODUCT =========\n");
        editProduct();
        
        setColor(14);
        printf("\n1. Return to main menu\n");
        printf("Enter your choice: ");
        scanf("%d", &back);
        
    } while (back != 1);
    
}



void deleteProduct(int productId) {
    int id, confirm, found = 0;

    system("cls");
    setColor(12);
    printf("\n========= DELETE PRODUCT =========\n");
    setColor(14);
    printf("Enter the product ID to delete: ");
    setColor(7);
    scanf("%d", &id);

    for (i = 0; i < num_products; i++) {
        if (products[i].id == id) {
            found = 1;

            setColor(10);
            printf("\nProduct found:\n");
            setColor(9);
            printf("+------------+---------------------------------+------------+------------+\n");
            printf("| ID         | Product Name                    | Price      | Quantity   |\n");
            printf("+------------+---------------------------------+------------+------------+\n");
            printf("| %-10d | %-31s | %-10.2f | %-10d |\n",
                   products[i].id, products[i].name, products[i].price, products[i].quantity);
            printf("+------------+---------------------------------+------------+------------+\n");

            setColor(12);
            printf("\nAre you sure you want to delete this product? (1: Yes, 2: No): ");
            setColor(7);
            scanf("%d", &confirm);

            if (confirm == 1) {
                for (j = i; j < num_products - 1; j++) {
                    products[j] = products[j + 1];
                }
                num_products--;
                setColor(10);
                printf("Product has been successfully deleted!\n");

                setColor(12);
                printf("\n========= UPDATED PRODUCT LIST =========\n");
                displayProducts();
            } else {
                setColor(14);
                printf("Deletion canceled.\n");
            }
            return;
        }
    }

    if (!found) {
        setColor(12);
        printf("Product with ID %d not found!\n", id);
    }
    setColor(7);
}




void showDeleteProduct() {
    int back;
    do {
        system("cls");

        setColor(12);
        printf("\n========= DELETE PRODUCT =========\n");
        deleteProduct(i);

        setColor(14);
        printf("\n1. Return to main menu\n");
        printf("Enter your choice: ");
        scanf("%d", &back);

    } while (back != 1);
}





void sortProductsByName(int ascending) {
    struct Product temp;
    for (i = 0; i < num_products - 1; i++) {
        for (j = i + 1; j < num_products; j++) {
            if ((ascending && strcmp(products[i].name, products[j].name) > 0) ||
                (!ascending && strcmp(products[i].name, products[j].name) < 0)) {
                temp = products[i];
                products[i] = products[j];
                products[j] = temp;
            }
        }
    }

    setColor(10);
    if (ascending)
        printf("\nProduct list sorted successfully by Name (A - Z)!\n");
    else
        printf("\nProduct list sorted successfully by Name (Z - A)!\n");

    displayProducts();
}




void searchProductByName() {
    char searchName[50];
    int found = 0;

    system("cls");
    printf("\n========= SEARCH PRODUCT =========\n");
    printf("Enter product name to search: ");
    getchar();  
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0';

    printf("\nSearch results:\n");
    printf("+------------+---------------------------------+------------+------------+\n");
    printf("| ID         | Product Name                    | Price      | Quantity   |\n");
    printf("+------------+---------------------------------+------------+------------+\n");

    for ( i = 0; i < num_products; i++) {
        if (strstr(products[i].name, searchName) != NULL) {
            printf("| %-10d | %-31s | %-10.2f | %-10d |\n",
                   products[i].id, products[i].name, products[i].price, products[i].quantity);
            printf("+------------+---------------------------------+------------+------------+\n");
            found = 1;
        }
    }

    if (!found) {
        printf("No products found with name containing '%s'!\n", searchName);
    }

    int back;
    printf("\n1. Return to main menu\n");
    printf("Enter your choice: ");
    scanf("%d", &back);
}
void sortProductsByPrice(int ascending) {
    struct Product temp;
    for (i = 0; i < num_products - 1; i++) {
        for (j = i + 1; j < num_products; j++) {
            if ((ascending && products[i].price > products[j].price) ||
                (!ascending && products[i].price < products[j].price)) {
                temp = products[i];
                products[i] = products[j];
                products[j] = temp;
            }
        }
    }

    setColor(10);
    if (ascending)
        printf("\nProduct list sorted successfully by Price (Low to High)!\n");
    else
        printf("\nProduct list sorted successfully by Price (High to Low)!\n");

    saveProductsToFile();
    displayProducts();
}





int is_valid_category(int id, char name[]) {
    if (id <= 0 || strlen(name) == 0) {
        return 0; // Không h?p l?
    }

    // Ki?m tra id ho?c tên b? trùng
    for ( i = 0; i < num_categories; i++) {
        if (categories[i].id == id || strcmp(categories[i].name, name) == 0) {
            return 0; // Trùng id ho?c tên
        }
    }

    return 1; // H?p l?
}

// Hàm hi?n th? danh sách danh m?c
void loadCategoriesFromFile() {
    FILE *file = fopen("categories.bin", "rb");
    if (file == NULL) {
        return;
    }
    fread(&num_categories, sizeof(int), 1, file);
    fread(categories, sizeof(Category), num_categories, file);
    fclose(file);
}

// Function to save categories to file
void saveCategoriesToFile() {
    FILE *file = fopen("categories.bin", "wb");
    if (file == NULL) {
        printf("Error saving categories!\n");
        return;
    }
    fwrite(&num_categories, sizeof(int), 1, file);
    fwrite(categories, sizeof(Category), num_categories, file);
    fclose(file);
}

// Function to display categories in a formatted table
void displayCategories() {
    if (num_categories == 0) {
        setColor(14);
        printf("No categories available!\n");
        setColor(7);
        return;
    }

    setColor(9);
    printf("\n+------------+----------------------------+\n");
    printf("| ID         | Category Name               |\n");
    printf("+------------+----------------------------+\n");
    for ( i = 0; i < num_categories; i++) {
        printf("| %-10d | %-26s |\n", categories[i].id, categories[i].name);
    }
    printf("+------------+----------------------------+\n");
    setColor(7);
}

// Function to add a category
void addCategory() {
    if (num_categories >= MAX_CATEGORIES) {
        setColor(12);
        printf("The category list is full!\n");
        setColor(7);
        return;
    }

    Category new_category;
    int is_duplicate;
    do {
        setColor(14);
        printf("Enter category ID (1 - 999): ");
        setColor(3);
        if (scanf("%d", &new_category.id) != 1) {
            while (getchar() != '\n');
            setColor(12);
            printf("Error: Invalid input! Please enter a number.\n");
            continue;
        }
        getchar();

        if (new_category.id < 1 || new_category.id > 999) {
            setColor(12);
            printf("Error: Category ID must be between 1 and 999!\n");
            continue;
        }

        is_duplicate = 0;
        for ( i = 0; i < num_categories; i++) {
            if (categories[i].id == new_category.id) {
                setColor(12);
                printf("Error: A category with this ID already exists!\n");
                is_duplicate = 1;
                break;
            }
        }
    } while (is_duplicate);

    do {
        setColor(14);
        printf("Enter category name (3 - 50 characters): ");
        setColor(3);
        fgets(new_category.name, sizeof(new_category.name), stdin);
        new_category.name[strcspn(new_category.name, "\n")] = '\0';

        int length = strlen(new_category.name);
        if (length < 3 || length > 50) {
            setColor(12);
            printf("Error: Category name must be between 3 and 50 characters!\n");
            continue;
        }
    } while (0);

    categories[num_categories++] = new_category;
    saveCategoriesToFile();

    setColor(2);
    printf("Category has been added successfully!\n");
    setColor(7);
}
void editCategory() {
    int id, found = 0;
    setColor(14);
    printf("Enter the category ID to edit: ");
    setColor(3);
    scanf("%d", &id);
    getchar();

    for ( i = 0; i < num_categories; i++) {
        if (categories[i].id == id) {
            found = 1;
            setColor(10);
            printf("\nCategory found:\n");
            setColor(9);
            printf("+------------+------------------------------+\n");
            printf("| ID         | Category Name                 |\n");
            printf("+------------+------------------------------+\n");
            printf("| %-10d | %-28s |\n", categories[i].id, categories[i].name);
            printf("+------------+------------------------------+\n");

            do {
                setColor(11);
                printf("Enter new name (3 - 50 characters, current: %s): ", categories[i].name);
                setColor(3);
                fgets(categories[i].name, sizeof(categories[i].name), stdin);
                categories[i].name[strcspn(categories[i].name, "\n")] = '\0';
            } while (strlen(categories[i].name) < 3 || strlen(categories[i].name) > 50);

            saveCategoriesToFile();

            setColor(2);
            printf("\nCategory information updated successfully!\n");
            return;
        }
    }
    if (!found) {
        setColor(12);
        printf("Category with ID %d not found!\n", id);
    }
    setColor(7);
}

void deleteCategory() {
    int id,k, found = 0;
    setColor(14);
    printf("Enter the category ID to delete: ");
    setColor(3);
    scanf("%d", &id);
    getchar();

    for ( i = 0; i < num_categories; i++) {
        if (categories[i].id == id) {
            found = 1;
            setColor(10);
            printf("\nCategory found:\n");
            setColor(9);
            printf("+------------+------------------------------+\n");
            printf("| ID         | Category Name                 |\n");
            printf("+------------+------------------------------+\n");
            printf("| %-10d | %-28s |\n", categories[i].id, categories[i].name);
            printf("+------------+------------------------------+\n");
            
            setColor(12);
            printf("Are you sure you want to delete category ID %d? (1: Yes, 2: No): ", id);
            setColor(7);
            int confirm;
            scanf("%d", &confirm);
            getchar();

            if (confirm == 1) {
                for ( j = 0; j < num_products; j++) {
                    if (products[j].category_id == id) {
                        for ( k = j; k < num_products - 1; k++) {
                            products[k] = products[k + 1];
                        }
                        num_products--;
                        j--;
                    }
                }
                
                for ( j = i; j < num_categories - 1; j++) {
                    categories[j] = categories[j + 1];
                }
                num_categories--;
                saveCategoriesToFile();
                saveProductsToFile();
                setColor(2);
                printf("Category and its products deleted successfully!\n");
            }
            return;
        }
    }
    setColor(12);
    printf("Category with ID %d not found!\n", id);
    setColor(7);
}

void searchCategoryByName() {
    char searchName[50];
    int found = 0;
    printf("Enter category name to search: ");
    getchar();
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0';

    printf("\nSearch results:\n");
    for ( i = 0; i < num_categories; i++) {
        if (strstr(categories[i].name, searchName) != NULL) {
            printf("ID: %d, Name: %s\n", categories[i].id, categories[i].name);
            found = 1;
        }
    }
    if (!found) {
        printf("No categories found with name containing '%s'!\n", searchName);
    }
}


void sortCategoriesByName() {
    Category temp;
    for ( i = 0; i < num_categories - 1; i++) {
        for ( j = i + 1; j < num_categories; j++) {
            if (strcmp(categories[i].name, categories[j].name) > 0) {
                temp = categories[i];
                categories[i] = categories[j];
                categories[j] = temp;
            }
        }
    }
    saveCategoriesToFile();
    setColor(2);
    printf("\nCategories sorted by name successfully!\n");
}

void filterProductsByCategory(int category_id) {
    int found = 0;

    printf("\nFiltering products by category ID: %d\n", category_id);
    printf("+------------+---------------------------------+------------+------------+\n");
    printf("| ID         | Product Name                   | Price      | Quantity   |\n");
    printf("+------------+---------------------------------+------------+------------+\n");

    // Loop through products and check if they belong to the selected category
    for ( i = 0; i < num_products; i++) {
        if (products[i].category_id == category_id) {
            printf("| %-10d | %-31s | %-10.2f | %-10d |\n", 
                   products[i].id, products[i].name, products[i].price, products[i].quantity);
            found = 1;
        }
    }

    // If no products found in the selected category
    if (!found) {
        printf("No products found in category ID %d.\n", category_id);
    }

    printf("+------------+---------------------------------+------------+------------+\n");
}
void filterProductsByPrice(float min_price, float max_price) {
    int found = 0;

    printf("\nFiltering products by price range (%.2f - %.2f):\n", min_price, max_price);
    printf("+------------+---------------------------------+------------+------------+\n");
    printf("| ID         | Product Name                   | Price      | Quantity   |\n");
    printf("+------------+---------------------------------+------------+------------+\n");

    // Loop through products and check if their price is within the given range
    for ( i = 0; i < num_products; i++) {
        if (products[i].price >= min_price && products[i].price <= max_price) {
            printf("| %-10d | %-31s | %-10.2f | %-10d |\n", 
                   products[i].id, products[i].name, products[i].price, products[i].quantity);
            found = 1;
        }
    }

    if (!found) {
        printf("No products found in the price range %.2f - %.2f.\n", min_price, max_price);
    }

    printf("+------------+---------------------------------+------------+------------+\n");
}



void showDisplayCategories() {
    int back;
    do {
        system("cls");
        setColor(12);
        printf("\n========= CATEGORY LIST =========\n");
        displayCategories();
        setColor(14);
        printf("\n1. Return to category management menu\n");
        printf("Enter your choice: ");
        scanf("%d", &back);
    } while (back != 1);
}

// Function to add a category screen
void showAddCategory() {
    int back;
    do {
        system("cls");
        setColor(12);
        printf("\n========= ADD NEW CATEGORY =========\n");
        addCategory();
        saveCategoriesToFile();
        setColor(14);
        printf("\n1. Return to category management menu\n");
        printf("Enter your choice: ");
        scanf("%d", &back);
    } while (back != 1);
}

// Function to edit a category screen
void showEditCategory() {
    int back;
    do {
        system("cls");
        setColor(12);
        printf("\n========= EDIT CATEGORY =========\n");
        editCategory();
        saveCategoriesToFile();
        setColor(14);
        printf("\n1. Return to category management menu\n");
        printf("Enter your choice: ");
        scanf("%d", &back);
    } while (back != 1);
}

// Function to delete a category screen
void showDeleteCategory() {
    int back;
    do {
        system("cls");
        setColor(12);
        printf("\n========= DELETE CATEGORY =========\n");
        deleteCategory();
        saveCategoriesToFile();
        setColor(14);
        printf("\n1. Return to category management menu\n");
        printf("Enter your choice: ");
        scanf("%d", &back);
    } while (back != 1);
}

// Function to search category screen
void showSearchCategory() {
    int back;
    do {
        system("cls");
        setColor(12);
        printf("\n========= SEARCH CATEGORY =========\n");
        searchCategoryByName();
        setColor(14);
        printf("\n1. Return to category management menu\n");
        printf("Enter your choice: ");
        scanf("%d", &back);
    } while (back != 1);
}
void showSortCategoryMenu() {
    int sortChoice;
    do {
        system("cls");
        setColor(12);
        printf("\n========= SORT CATEGORIES =========\n");
        setColor(14);
        printf("1. Sort by Name (Ascending)\n");
        printf("2. Sort by Name (Descending)\n");
        printf("3. Return to category management menu\n");
        printf("Enter your choice: ");
        setColor(7);
        scanf("%d", &sortChoice);

        switch (sortChoice) {
            case 1:
                sortCategoriesByName();
                break;
            case 2:
                // Implement descending sort function if needed
                break;
            case 3:
                return;
            default:
                setColor(12);
                printf("Invalid choice! Please try again.\n");
                setColor(7);
        }

        setColor(9);
        printf("\nSorted Category List:\n");
        displayCategories();

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
int isValidCategoryData(Category category) {
    if (category.id <= 0 || strlen(category.name) == 0) {
        printf("Invalid category data. Please enter valid information.\n");
        return 0;
    }
    for ( i = 0; i < num_categories; i++) {
        if (categories[i].id == category.id || strcmp(categories[i].name, category.name) == 0) {
            printf("Error: Category ID or Name already exists!\n");
            return 0;
        }
    }
    return 1;
}
