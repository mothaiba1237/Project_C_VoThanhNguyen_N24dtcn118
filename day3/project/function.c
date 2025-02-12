#include "function.h"
int i,j; 
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
        	printf("+------------+---------------------------------+------------+------------+\n");
        	printf("| %-10d | %-31s | %-10.2f | %-10d |\n", products[i].id, products[i].name, products[i].price, products[i].quantity);
        	printf("+------------+---------------------------------+------------+------------+\n");
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
            printf("+------------+---------------------------------+------------+------------+\n");
        	printf("| %-10d | %-31s | %-10.2f | %-10d |\n", products[i].id, products[i].name, products[i].price, products[i].quantity);
        	printf("+------------+---------------------------------+------------+------------+\n");
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
void deleteProduct() {
    int id, confirm, found = 0;

    system("cls");
    setColor(12);
    printf("\n========= DELETE PRODUCT =========\n");
    setColor(14);
    printf("Enter the product ID to delete: ");
    setColor(7);
    scanf("%d", &id);

    for ( i = 0; i < num; i++) {
        if (products[i].id == id) {
            found = 1;
            
            setColor(10);
            printf("\nProduct found: \n");
            printf("ID: %d, Name: %s, Price: %.2f, Quantity: %d\n",
                   products[i].id, products[i].name, products[i].price, products[i].quantity);
            
            setColor(12);
            printf("\nAre you sure you want to delete this product? (1: Yes, 2: No): ");
            setColor(7);
            scanf("%d", &confirm);

            if (confirm == 1) {
                for ( j = i; j < num - 1; j++) {
                    products[j] = products[j + 1];
                }
                num--;
                setColor(10);
                printf("Product deleted successfully!\n");
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
void sortProductsByID(int ascending) {
    for ( i = 0; i < num - 1; i++) {
        for ( j = i + 1; j < num; j++) {
            if ((ascending && products[i].id > products[j].id) || (!ascending && products[i].id < products[j].id)) {
                struct Product temp = products[i];
                products[i] = products[j];
                products[j] = temp;
            }
        }
    }
    setColor(10);
    printf("\nProduct list sorted successfully by ID!\n");
}

void sortProductsByPrice(int ascending) {
    for ( i = 0; i < num - 1; i++) {
        for ( j = i + 1; j < num; j++) {
            if ((ascending && products[i].price > products[j].price) || (!ascending && products[i].price < products[j].price)) {
                struct Product temp = products[i];
                products[i] = products[j];
                products[j] = temp;
            }
        }
    }
    setColor(10);
    printf("\nProduct list sorted successfully by Price!\n");
}





