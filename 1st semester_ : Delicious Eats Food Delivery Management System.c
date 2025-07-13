#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structures
typedef struct {
    int id;
    char name[50];
    float price;
} Dish;

typedef struct {
    int id;
    int dishId;
    int quantity;
} Order;

// Global variables
Dish dishes[100];
Order orders[100];
int dishCount = 0, orderCount = 0;
float totalSales = 0;

// Function prototypes
void writeDataToFile();
void readDataFromFile();
void adminPanel();
void customerPanel();
void addDish();
void modifyDish();
void deleteDish();
void displayOrders();
void salesReport();
void placeOrder();
void cancelOrder();
void displayDishes();
int authenticateAdmin();

int main() {
    // Load data from files
    readDataFromFile();

    int choice;
    do {
        printf("\n=== Delivery Management System ===\n");
        printf("1. Admin Panel\n");
        printf("2. Customer Panel\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (authenticateAdmin()) {
                    adminPanel();
                } else {
                    printf("Invalid password! Access denied.\n");
                }
                break;
            case 2:
                customerPanel();
                break;
            case 3:
                // Save data to files
                writeDataToFile();
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 3);
    return 0;
}

// Function to authenticate admin
int authenticateAdmin() {
    char password[20], correctPassword[] = "2004";
    printf("Enter admin password: ");
    scanf("%s", password);
    return strcmp(password, correctPassword) == 0;
}

// Admin Panel
void adminPanel() {
    int choice;
    do {
        printf("\n=== Admin Panel ===\n");
        printf("1. Add New Dish\n");
        printf("2. Modify Existing Dish\n");
        printf("3. Delete Dish\n");
        printf("4. Display All Orders\n");
        printf("5. Sales Report\n");
        printf("6. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addDish(); break;
            case 2: modifyDish(); break;
            case 3: deleteDish(); break;
            case 4: displayOrders(); break;
            case 5: salesReport(); break;
            case 6: printf("Returning to Main Menu...\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (choice != 6);
}

// Customer Panel
void customerPanel() {
    int choice;
    do {
        printf("\n=== Customer Panel ===\n");
        printf("1. Place Order\n");
        printf("2. Cancel Order\n");
        printf("3. Display All Dishes\n");
        printf("4. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: placeOrder(); break;
            case 2: cancelOrder(); break;
            case 3: displayDishes(); break;
            case 4: printf("Returning to Main Menu...\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (choice != 4);
}

// Function to save data to files
void writeDataToFile() {
    FILE *dishFile = fopen("dishes.dat", "wb");
    FILE *orderFile = fopen("orders.dat", "wb");

    if (dishFile && orderFile) {
        // Write dish data
        fwrite(&dishCount, sizeof(int), 1, dishFile);
        fwrite(dishes, sizeof(Dish), dishCount, dishFile);

        // Write order data
        fwrite(&orderCount, sizeof(int), 1, orderFile);
        fwrite(orders, sizeof(Order), orderCount, orderFile);

        fclose(dishFile);
        fclose(orderFile);
        printf("Data saved successfully!\n");
    } else {
        printf("Error saving data!\n");
    }
}

// Function to read data from files
void readDataFromFile() {
    FILE *dishFile = fopen("dishes.dat", "rb");
    FILE *orderFile = fopen("orders.dat", "rb");

    if (dishFile && orderFile) {
        // Read dish data
        fread(&dishCount, sizeof(int), 1, dishFile);
        fread(dishes, sizeof(Dish), dishCount, dishFile);

        // Read order data
        fread(&orderCount, sizeof(int), 1, orderFile);
        fread(orders, sizeof(Order), orderCount, orderFile);

        fclose(dishFile);
        fclose(orderFile);
        printf("Data loaded successfully!\n");
    } else {
        printf("No previous data found, starting fresh!\n");
    }
}

// Admin Functions
void addDish() {
    printf("Enter dish ID: ");
    scanf("%d", &dishes[dishCount].id);
    printf("Enter dish name: ");
    scanf(" %[^\n]", dishes[dishCount].name);
    printf("Enter dish price: ");
    scanf("%f", &dishes[dishCount].price);
    dishCount++;
    printf("Dish added successfully!\n");
}

void modifyDish() {
    int id, found = 0;
    printf("Enter dish ID to modify: ");
    scanf("%d", &id);
    for (int i = 0; i < dishCount; i++) {
        if (dishes[i].id == id) {
            printf("Enter new name: ");
            scanf(" %[^\n]", dishes[i].name);
            printf("Enter new price: ");
            scanf("%f", &dishes[i].price);
            found = 1;
            printf("Dish modified successfully!\n");
            break;
        }
    }
    if (!found) printf("Dish not found!\n");
}

void deleteDish() {
    int id, found = 0;
    printf("Enter dish ID to delete: ");
    scanf("%d", &id);
    for (int i = 0; i < dishCount; i++) {
        if (dishes[i].id == id) {
            for (int j = i; j < dishCount - 1; j++) {
                dishes[j] = dishes[j + 1];
            }
            dishCount--;
            found = 1;
            printf("Dish deleted successfully!\n");
            break;
        }
    }
    if (!found) printf("Dish not found!\n");
}

void displayOrders() {
    printf("\n=== Orders ===\n");
    for (int i = 0; i < orderCount; i++) {
        printf("Order ID: %d, Dish ID: %d, Quantity: %d\n",
               orders[i].id, orders[i].dishId, orders[i].quantity);
    }
}

void salesReport() {
    printf("\n=== Sales Report ===\n");
    printf("Total Sales: $%.2f\n", totalSales);
}

// Customer Functions
void placeOrder() {
    int dishId, quantity, found = 0;
    printf("Enter dish ID to order: ");
    scanf("%d", &dishId);
    for (int i = 0; i < dishCount; i++) {
        if (dishes[i].id == dishId) {
            printf("Enter quantity: ");
            scanf("%d", &quantity);
            orders[orderCount].id = orderCount + 1;
            orders[orderCount].dishId = dishId;
            orders[orderCount].quantity = quantity;
            totalSales += dishes[i].price * quantity;
            orderCount++;
            found = 1;
            printf("Order placed successfully!\n");
            break;
        }
    }
    if (!found) printf("Dish not found!\n");
}

void cancelOrder() {
    int id, found = 0;
    printf("Enter order ID to cancel: ");
    scanf("%d", &id);
    for (int i = 0; i < orderCount; i++) {
        if (orders[i].id == id) {
            for (int j = 0; j < dishCount; j++) {
                if (dishes[j].id == orders[i].dishId) {
                    totalSales -= dishes[j].price * orders[i].quantity;
                    break;
                }
            }
            for (int j = i; j < orderCount - 1; j++) {
                orders[j] = orders[j + 1];
            }
            orderCount--;
            found = 1;
            printf("Order cancelled successfully!\n");
            break;
        }
    }
    if (!found) printf("Order not found!\n");
}

void displayDishes() {
    printf("\n=== Dishes ===\n");
    for (int i = 0; i < dishCount; i++) {
        printf("ID: %d, Name: %s, Price: $%.2f\n", dishes[i].id, dishes[i].name, dishes[i].price);
    }
}

