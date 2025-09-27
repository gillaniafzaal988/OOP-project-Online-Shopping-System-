#pragma once
#include <iostream>
#include <string>
#include "Shop.h"

using namespace std;

class User {
protected:
    string username;
    string password;
    string role;
    static int userCount;
public:
    User(string u="", string p="", string r="Customer")
        : username(u), password(p), role(r) { userCount++; }

    virtual void menu(Shop &shop) = 0;

    string getUsername() const { return username; }
    string getRole() const { return role; }
    bool checkLogin(const string &u, const string &p) const { return u==username && p==password; }
    static int getUserCount() { return userCount; }
    
    virtual ~User() {}
};

int User::userCount = 0;

class Customer : public User {
    Cart cart;
public:
    Customer(string u="", string p="", string r="Customer") : User(u,p,r) {}

    void menu(Shop &shop) override {
        int choice;
        do {
            cout << "\n-- Customer Menu --\n";
            cout << "1. Show All Products\n";
            cout << "2. Search Products\n";
            cout << "3. Show Products by Category\n";
            cout << "4. Add to Cart\n";
            cout << "5. View Cart\n";
            cout << "6. Remove from Cart\n";
            cout << "7. Add to Wishlist\n";
            cout << "8. View Wishlist\n";
            cout << "9. Remove from Wishlist\n";
            cout << "10. Checkout\n";
            cout << "11. Logout\nChoice: ";
            cin >> choice;
            try {
                if(choice == 1) shop.listProducts();
                else if(choice == 2) {
                    string keyword;
                    cout << "Enter search keyword: "; 
                    cin.ignore();
                    getline(cin, keyword);
                    shop.searchProducts(keyword);
                }
                else if(choice == 3) {
                    string category;
                    cout << "Enter category: ";
                    cin.ignore();
                    getline(cin, category);
                    shop.listProductsByCategory(category);
                }
                else if(choice == 4) {
                    shop.listProducts();
                    int pid, qty;
                    cout << "Enter product id: "; cin >> pid;
                    cout << "Enter quantity: "; cin >> qty;
                    shop.addToCart(cart, pid, qty);
                }
                else if(choice == 5) shop.viewCart(cart);
                else if(choice == 6) {
                    int pid;
                    cout << "Enter product id to remove from cart: "; cin >> pid;
                    shop.removeFromCart(cart, pid);
                }
                else if(choice == 7) {
                    shop.listProducts();
                    int pid;
                    cout << "Enter product id to add to wishlist: "; cin >> pid;
                    cart.addToWishlist(pid);
                    cout << "Product added to wishlist!\n";
                }
                else if(choice == 8) shop.viewWishlist(cart);
                else if(choice == 9) {
                    int pid;
                    cout << "Enter product id to remove from wishlist: "; cin >> pid;
                    cart.removeFromWishlist(pid);
                    cout << "Product removed from wishlist!\n";
                }
                else if(choice == 10) shop.checkout(cart);
                else if(choice == 11) cout << "Logging out...\n";
                else cout << "Invalid choice!\n";
            } catch(exception &e) {
                cout << "Error: " << e.what() << endl;
            }
        } while(choice != 11);
    }
};

class Admin : public User {
public:
    Admin(string u="", string p="", string r="Admin") : User(u,p,r) {}

    void menu(Shop &shop) override {
        int choice;
        do {
            cout << "\n-- Admin Menu --\n";
            cout << "1. List Products\n";
            cout << "2. Add Product\n";
            cout << "3. Remove Product\n";
            cout << "4. Restock Product\n";           // NEW
            cout << "5. Check Product Stock\n";       // NEW
            cout << "6. Apply Category Discount\n";
            cout << "7. Show Sales Report\n";
            cout << "8. Generate Complete Report\n";
            cout << "9. Generate Stock Report\n";
            cout << "10. Generate Category Report\n";
            cout << "11. Generate Low Stock Report\n";
            cout << "12. Logout\nChoice: ";
            cin >> choice;
            try {
                if(choice == 1) shop.listProducts();
                else if(choice == 2) {
                    string name, category; double price; int stock;
                    cout << "Product Name: "; cin >> name;
                    cout << "Category: "; cin >> category;
                    cout << "Price: $"; cin >> price;
                    cout << "Initial Stock: "; cin >> stock;
                    shop.addProduct(name, category, price, stock);
                    cout << "Product added successfully!\n";
                }
                else if(choice == 3) {
                    shop.listProducts();
                    int pid;
                    cout << "Enter product ID to remove: "; cin >> pid;
                    shop.removeProductById(pid);
                    cout << "Product removed successfully!\n";
                }
                else if(choice == 4) {  // NEW: Restock product
                    shop.listProducts();
                    int pid, qty;
                    cout << "Enter product ID to restock: "; cin >> pid;
                    cout << "Enter quantity to add: "; cin >> qty;
                    shop.restockProduct(pid, qty);
                }
                else if(choice == 5) {  // NEW: Check product stock
                    shop.listProducts();
                    int pid;
                    cout << "Enter product ID to check: "; cin >> pid;
                    shop.checkProductStock(pid);
                }
                else if(choice == 6) {
                    string category; double percentage;
                    cout << "Enter category: "; cin >> category;
                    cout << "Enter discount percentage (0-100): "; cin >> percentage;
                    shop.applyCategoryDiscount(category, percentage);
                }
                else if(choice == 7) shop.showSalesReport();
                else if(choice == 8) shop.generateCompleteReport();
                else if(choice == 9) shop.generateStockReport();
                else if(choice == 10) shop.generateCategoryReport();
                else if(choice == 11) {
                    int threshold;
                    cout << "Enter low stock threshold (default 10): ";
                    cin >> threshold;
                    shop.generateLowStockReport(threshold);
                }
                else if(choice == 12) cout << "Logging out...\n";
                else cout << "Invalid choice!\n";
               
            } catch(exception &e) {
                cout << "Error: " << e.what() << endl;
            }
        } while(choice != 12);
    }
};
