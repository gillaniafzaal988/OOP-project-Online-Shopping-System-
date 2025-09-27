#pragma once
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Product {
public:
    int id;
    string name;
    string category;
    double price;
    int stock;
    static int productCounter;

    Product(): id(0), price(0), stock(0) {}
    Product(int i, string n, string c, double p, int s): 
        id(i), name(n), category(c), price(p), stock(s) {
        productCounter++;
    }

    void display() const {
        cout << setw(5) << id
             << setw(15) << name
             << setw(15) << category
             << setw(10) << fixed << setprecision(2) << price
             << setw(8) << stock << endl;
    }
    
    void applyDiscount(double percentage) {
        if(percentage > 0 && percentage <= 100) {
            price = price * (1 - percentage/100);
        }
    }
};

int Product::productCounter = 0;
