#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Structure to hold product information
struct Product {
    int id;
    string name;
    int quantity;
    double price;
};

// Class for managing the product and inventory
class Inventory {
private:
    vector<Product> products;
    int lowStockThreshold;

public:
    Inventory(int threshold) : lowStockThreshold(threshold) {}

    // Function to add a new product
    void addProduct(int id, string name, int quantity, double price) {
        // Check if a product with the same ID already exists
        for (const auto &product : products) {
            if (product.id == id) {
                cout << "Error: Product with ID " << id << " already exists." << endl;
                return;
            }
        }
        // If ID is unique, add the product
        Product newProduct = {id, name, quantity, price};
        products.push_back(newProduct);
        cout << "Product added: " << name << endl;
    }

    // Function to update product details
    void updateProduct(int id, int newQuantity, double newPrice) {
        for (auto &product : products) {
            if (product.id == id) {
                product.quantity = newQuantity;
                product.price = newPrice;
                cout << "Product updated: " << product.name << endl;
                checkLowStock(product);
                return;
            }
        }
        cout << "Product ID not found." << endl;
    }

    // Function to delete a product
    void deleteProduct(int id) {
        for (auto it = products.begin(); it != products.end(); ++it) {
            if (it->id == id) {
                cout << "Product deleted: " << it->name << endl;
                products.erase(it);
                return;
            }
        }
        cout << "Product ID not found." << endl;
    }

    // Function to restock a product
    void restockProduct(int id, int quantity) {
        for (auto &product : products) {
            if (product.id == id) {
                product.quantity += quantity;
                cout << "Product restocked: " << product.name << " New Quantity: " << product.quantity << endl;
                return;
            }
        }
        cout << "Product ID not found." << endl;
    }

    // Function to sell a product
    void sellProduct(int id, int quantity) {
        for (auto &product : products) {
            if (product.id == id) {
                if (product.quantity >= quantity) {
                    product.quantity -= quantity;
                    double totalPrice = quantity * product.price;
                    cout << "Sold " << quantity << " of " << product.name << " for $" << totalPrice << endl;
                    checkLowStock(product);
                } else {
                    cout << "Insufficient stock for " << product.name << ". Available: " << product.quantity << endl;
                }
                return;
            }
        }
        cout << "Product ID not found." << endl;
    }

    // Function to check for low stock levels and alert
    void checkLowStock(const Product &product) {
        if (product.quantity < lowStockThreshold) {
            cout << "Alert: Low stock for " << product.name << " (ID: " << product.id << ") Current Quantity: " << product.quantity << endl;
        }
    }

    // Function to display all products
    void displayProducts() const {
        cout << "\nInventory List:" << endl;
        for (const auto &product : products) {
            cout << "ID: " << product.id << ", Name: " << product.name
                 << ", Quantity: " << product.quantity << ", Price: $" << product.price << endl;
        }
    }
};

// Main function with a simple menu
int main() {
    Inventory inventory(5);  // Set low stock threshold to 5
    int choice;

    while (true) {
        cout << "\n--- Inventory Management System ---" << endl;
        cout << "1. Add Product" << endl;
        cout << "2. Update Product" << endl;
        cout << "3. Delete Product" << endl;
        cout << "4. Restock Product" << endl;
        cout << "5. Sell Product" << endl;
        cout << "6. Display All Products" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 7) break;

        int id, quantity;
        double price;
        string name;

        switch (choice) {
            case 1:  // Add Product
                cout << "Enter product ID: ";
                cin >> id;
                cout << "Enter product name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter quantity: ";
                cin >> quantity;
                cout << "Enter price: ";
                cin >> price;
                inventory.addProduct(id, name, quantity, price);
                break;
            case 2:  // Update Product
                cout << "Enter product ID to update: ";
                cin >> id;
                cout << "Enter new quantity: ";
                cin >> quantity;
                cout << "Enter new price: ";
                cin >> price;
                inventory.updateProduct(id, quantity, price);
                break;
            case 3:  // Delete Product
                cout << "Enter product ID to delete: ";
                cin >> id;
                inventory.deleteProduct(id);
                break;
            case 4:  // Restock Product
                cout << "Enter product ID to restock: ";
                cin >> id;
                cout << "Enter quantity to add: ";
                cin >> quantity;
                inventory.restockProduct(id, quantity);
                break;
            case 5:  // Sell Product
                cout << "Enter product ID to sell: ";
                cin >> id;
                cout << "Enter quantity to sell: ";
                cin >> quantity;
                inventory.sellProduct(id, quantity);
                break;
            case 6:  // Display All Products
                inventory.displayProducts();
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    cout << "Program terminated." << endl;
    return 0;
}