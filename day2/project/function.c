#include "function.h"
int i; 
struct Product products[MAX_PRODUCTS];
int num_products = 0;

void addProduct() {
    if (num >= MAX_PRODUCTS) {
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
    setColor(12);
    printf("Enter product name: ");
    setColor(3);
    fgets(new_product.name, sizeof(new_product.name), stdin);
    new_product.name[strcspn(new_product.name, "\n")] = '\0';
    setColor(12);
    printf("Enter product price: ");
    setColor(3);
    scanf("%f", &new_product.price);
    setColor(12);
    printf("Enter product quantity: ");
    setColor(3);
    scanf("%d", &new_product.quantity);
    
    products[num] = new_product;
    num++;
    setColor(2);
    printf("Product has been added successfully!\n");
}
void displayProducts() {
    if (num == 0) {
        setColor(14);
        printf("No products available!\n");
        setColor(7);
        return;
    }

setColor(9);
printf("\n+------------+---------------------------------+------------+------------+\n");
setColor(3);
printf("| ID         | Product name                    | Price      | Quantity   |\n");
setColor(9);
printf("+------------+---------------------------------+------------+------------+\n");

for ( i = 0; i < num; i++) {
    setColor(9);
    printf("| %-10d | %-31s | %-10.2f | %-10d |\n", products[i].id, products[i].name, products[i].price, products[i].quantity);
    setColor(9);
    printf("+------------+---------------------------------+------------+------------+\n");
}

setColor(7);

}
void editProduct() {
    int id;
    setColor(14);
    printf("Enter the product ID to edit: ");
    setColor(7);
    scanf("%d", &id);
    getchar();

    for ( i = 0; i < num; i++) {
        if (products[i].id == id) {
        	setColor(9);
        	printf("| %-10d | %-31s | %-10.2f | %-10d |\n", products[i].id, products[i].name, products[i].price, products[i].quantity);
            setColor(11);
            printf("Product found: %s\n", products[i].name);
            setColor(14);
            printf("Enter new name (current: %s): ", products[i].name);
            setColor(7);
            fgets(products[i].name, sizeof(products[i].name), stdin);
            products[i].name[strcspn(products[i].name, "\n")] = '\0';
            
            setColor(14);
            printf("Enter new price: ");
            setColor(7);
            scanf("%f", &products[i].price);
            
            setColor(14);
            printf("Enter new quantity: ");
            setColor(7);
            scanf("%d", &products[i].quantity);

            setColor(2);
            printf("Product information has been updated!\n");
            setColor(9);
        	printf("| %-10d | %-31s | %-10.2f | %-10d |\n", products[i].id, products[i].name, products[i].price, products[i].quantity);
            return;
        }
    }

    setColor(12);
    printf("Product with ID %d not found!\n", id);
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



