#pragma once
#include <iostream>
#include <stdexcept>
using namespace std;

class CartItem {
public:
    int productId;
    int qty;
    CartItem(): productId(0), qty(0) {}
    CartItem(int id, int q): productId(id), qty(q) {}
};

class Cart {
    CartItem items[20];
    int wishlist[20];
    int count;
    int wishlistCount;
public:
    Cart():count(0), wishlistCount(0){}
    
    void addItem(int pid,int q){
        for(int i=0;i<count;i++){
            if(items[i].productId==pid){
                items[i].qty+=q;
                return;
            }
        }
        if(count < 20) {
            items[count++] = CartItem(pid,q);
        }
    }

    void removeItem(int idx){
        if(idx<0 || idx>=count) throw std::out_of_range("Invalid cart index");
        for(int i=idx;i<count-1;i++) items[i] = items[i+1];
        count--;
    }

    void removeItemById(int pid){
        int idx = -1;
        for(int i=0;i<count;i++){
            if(items[i].productId == pid){
                idx = i;
                break;
            }
        }
        if(idx==-1) throw std::runtime_error("Product not found in cart");
        removeItem(idx);
    }

    void addToWishlist(int pid) {
        if(wishlistCount < 20) {
            for(int i=0; i<wishlistCount; i++) {
                if(wishlist[i] == pid) return;
            }
            wishlist[wishlistCount++] = pid;
        }
    }
    
    void removeFromWishlist(int pid) {
        for(int i=0; i<wishlistCount; i++) {
            if(wishlist[i] == pid) {
                for(int j=i; j<wishlistCount-1; j++) {
                    wishlist[j] = wishlist[j+1];
                }
                wishlistCount--;
                return;
            }
        }
    }
    
    bool isInWishlist(int pid) const {
        for(int i=0; i<wishlistCount; i++) {
            if(wishlist[i] == pid) return true;
        }
        return false;
    }

    int getCount() const { return count; }
    int getWishlistCount() const { return wishlistCount; }
    CartItem& getItem(int i) { return items[i]; }
    int getWishlistItem(int i) const { return wishlist[i]; }
    void clear() { count=0; }
    void clearWishlist() { wishlistCount=0; }
};
