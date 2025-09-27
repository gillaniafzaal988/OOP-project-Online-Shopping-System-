#include <iostream>
#include <string>
using namespace std;

// Include headers in the correct order
#include "Product.h"
#include "Cart.h"
#include "Shop.h"
#include "User.h"

// Function to display welcome message
void displayWelcome() {
    cout << "========================================\n";
    cout << "      WELCOME TO OOP SHOP SYSTEM       \n";
    cout << "========================================\n";
}

// Function to display exit message
void displayExit() {
    cout << "========================================\n";
    cout << "    THANK YOU FOR USING OUR SYSTEM     \n";
    cout << "========================================\n";
}

int main() {
    Shop shop;
    
    // Create default users
    const int MAX_USERS = 20;
    User* users[MAX_USERS];
    int userCount = 0;

    // Create default admin and customer
    users[userCount++] = new Admin("admin", "123");
    users[userCount++] = new Customer("user", "123");

    displayWelcome();

    while(true) {
        int choice;
        cout << "\n=== MAIN MENU ===\n";
        cout << "1. Login\n";
        cout << "2. Signup (Customer)\n";
        cout << "3. View Product Catalog\n";
        cout << "4. Exit\n";
        cout << "Please enter your choice (1-4): ";
        cin >> choice;

        if(choice == 1) {
            string username, password;
            cout << "\n=== LOGIN ===\n";
            cout << "Username: "; 
            cin >> username;
            cout << "Password: "; 
            cin >> password;

            bool found = false;
            for(int i = 0; i < userCount; i++) {
                if(users[i]->checkLogin(username, password)) {
                    found = true;
                    cout << "\nLogin successful! Welcome, " << username << "!\n";
                    cout << "Role: " << users[i]->getRole() << endl;
                    users[i]->menu(shop);
                    break;
                }
            }
            if(!found) {
                cout << "Invalid username or password! Please try again.\n";
            }
        }
        else if(choice == 2) {
            if(userCount >= MAX_USERS) {
                cout << "User limit reached! Cannot create new account.\n";
                continue;
            }
            
            string username, password, confirmPassword;
            cout << "\n=== CUSTOMER REGISTRATION ===\n";
            cout << "New username: "; 
            cin >> username;
            
            // Check if username already exists
            bool usernameExists = false;
            for(int i = 0; i < userCount; i++) {
                if(users[i]->getUsername() == username) {
                    usernameExists = true;
                    break;
                }
            }
            
            if(usernameExists) {
                cout << "Username already exists! Please choose a different username.\n";
                continue;
            }
            
            cout << "New password: "; 
            cin >> password;
            cout << "Confirm password: "; 
            cin >> confirmPassword;
            
            if(password != confirmPassword) {
                cout << "Passwords do not match! Registration failed.\n";
                continue;
            }
            
            if(password.length() < 3) {
                cout << "Password must be at least 3 characters long! Registration failed.\n";
                continue;
            }
            
            users[userCount++] = new Customer(username, password);
            cout << "Customer registered successfully! You can now login.\n";
        }
        else if(choice == 3) {
            cout << "\n=== PUBLIC PRODUCT CATALOG ===\n";
            shop.listProducts();
            cout << "\nTotal products available: " << shop.getProductCount() << endl;
        }
        else if(choice == 4) {
            break;
        }
        else {
            cout << "Invalid choice! Please enter 1, 2, 3, or 4.\n";
            // Clear error state and ignore invalid input
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    // Display statistics before exiting
    displayExit();
    cout << "\nSystem Statistics:\n";
    cout << "==================\n";
    cout << "Total users: " << User::getUserCount() << endl;
    cout << "Total products in shop: " << shop.getProductCount() << endl;
    cout << "Total products created: " << Product::productCounter << endl;

    // Cleanup - delete all user objects
    for(int i = 0; i < userCount; i++) {
        delete users[i];
    }

    cout << "\nGoodbye! See you again soon!\n";
    return 0;
}
