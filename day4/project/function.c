#include "function.h"
#define FILE_PATH "D:\\project\\data.bin"
int i,j; 
struct Product products[MAX_PRODUCTS];
int num_products = 0;

void printCurrentDirectory() {
    char path[260];
    getcwd(path, sizeof(path));
    printf("Current working directory: %s\n", path);
}

void saveProductsToFile() {
    FILE *file = fopen(FILE_PATH, "wb");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }
    fwrite(&num_products, sizeof(int), 1, file);
    fwrite(products, sizeof(struct Product), num_products, file);
    fclose(file);
    printf("Products saved successfully!\n");
}

void loadProductsFromFile() {
    FILE *file = fopen(FILE_PATH, "rb");
    if (file == NULL) {
        printf("No existing data found. Creating a new data file...\n");
        file = fopen(FILE_PATH, "wb");
        if (file == NULL) {
            perror("Error creating file");
            return;
        }
        fclose(file);
        return;
    }
    fread(&num_products, sizeof(int), 1, file);
    fread(products, sizeof(struct Product), num_products, file);
    fclose(file);
    printf("Products loaded successfully!\n");
}

void checkFilePath() {
    printCurrentDirectory();
    FILE *file = fopen(FILE_PATH, "rb");
    if (file == NULL) {
        printf("File %s not found. Make sure the path is correct.\n", FILE_PATH);
    } else {
        printf("File %s found successfully!\n", FILE_PATH);
        fclose(file);
    }
}

void addProduct() {
    if (num_products >= MAX_PRODUCTS) {
        setColor(12);
        printf("The product list is full!\n");
        setColor(7);
        return;
    }

    struct Product new_product;
    
    setColor(12);
    printf("Enter product ID: ");
    setColor(3);
    scanf("%d", &new_product.id);
    getchar();

    for (i = 0; i < num_products; i++) {
        if (products[i].id == new_product.id) {
            setColor(12);
            printf("Error: A product with this ID already exists!\n");
            setColor(7);
            return;
        }
    }

    do {
        setColor(12);
        printf("Enter product name (3 - 50 characters): ");
        setColor(3);
        fgets(new_product.name, sizeof(new_product.name), stdin);
        new_product.name[strcspn(new_product.name, "\n")] = '\0';

        int length = strlen(new_product.name);

        if (length < 3 || length > 50) {
            setColor(12);
            printf("Error: Product name must be between 3 and 50 characters!\n");
        } else {
            int duplicate = 0;
            for (i = 0; i < num_products; i++) {
                if (strcmp(products[i].name, new_product.name) == 0) {
                    setColor(12);
                    printf("Error: A product with this name already exists!\n");
                    duplicate = 1;
                    break;
                }
            }
            if (!duplicate) break;
        }
    } while (1);

    setColor(12);
    printf("Enter product price: ");
    setColor(3);
    scanf("%f", &new_product.price);

    setColor(12);
    printf("Enter product quantity: ");
    setColor(3);
    scanf("%d", &new_product.quantity);

    products[num_products] = new_product;
    num_products++;

    saveProductsToFile();

    setColor(2);
    printf("Product has been added successfully!\n");
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
    setColor(3);
    printf("| ID         | Product Name                    | Price      | Quantity   |\n");
    setColor(9);
    printf("+------------+---------------------------------+------------+------------+\n");

    for (i = 0; i < num_products; i++) {
        setColor(9);
        printf("| %-10d | %-31s | %-10.2f | %-10d |\n",
               products[i].id, products[i].name, products[i].price, products[i].quantity);
        printf("+------------+---------------------------------+------------+------------+\n");
    }

    setColor(7);
}

void editProduct() {
    int id, found = 0;
    setColor(14);
    printf("Enter the product ID to edit: ");
    setColor(7);
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

            // Ki?m tra ð? dài h?p l? và tránh trùng tên s?n ph?m
            char newName[50];
            do {
                setColor(11);
                printf("Enter new name (3 - 50 characters, current: %s): ", products[i].name);
                setColor(7);
                fgets(newName, sizeof(newName), stdin);
                newName[strcspn(newName, "\n")] = '\0';

                int length = strlen(newName);
                if (length < 3 || length > 50) {
                    setColor(12);
                    printf("Error: Product name must be between 3 and 50 characters!\n");
                    continue;
                }

                int duplicate = 0;
                for ( j = 0; j < num_products; j++) {
                    if (j != i && strcmp(products[j].name, newName) == 0) {
                        setColor(12);
                        printf("Error: A product with this name already exists!\n");
                        duplicate = 1;
                        break;
                    }
                }
                if (!duplicate) {
                    strcpy(products[i].name, newName);
                    break;
                }
            } while (1);

            setColor(11);
            printf("Enter new price (current: %.2f): ", products[i].price);
            setColor(7);
            while (scanf("%f", &products[i].price) != 1 || products[i].price < 0) {
                printf("Invalid price! Enter a valid number: ");
                while (getchar() != '\n');
            }

            setColor(11);
            printf("Enter new quantity (current: %d): ", products[i].quantity);
            setColor(7);
            while (scanf("%d", &products[i].quantity) != 1 || products[i].quantity < 0) {
                printf("Invalid quantity! Enter a valid number: ");
                while (getchar() != '\n');
            }

            saveProductsToFile();

            setColor(2);
            printf("\nProduct information updated successfully!\n");
            setColor(9);
            printf("+------------+---------------------------------+------------+------------+\n");
            printf("| %-10d | %-31s | %-10.2f | %-10d |\n",
                   products[i].id, products[i].name, products[i].price, products[i].quantity);
            printf("+------------+---------------------------------+------------+------------+\n");

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
void deleteProduct() {
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
        deleteProduct();

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










