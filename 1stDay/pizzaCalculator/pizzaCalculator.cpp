#include <iostream>

struct pizzaRestaurant {
    struct sPizza;
    struct mPizza;
    struct lPizza;

    void cheapestPizzaPrice() {
        if( sAreaPerPrice >= mAreaPerPrice ) { 
            if( sAreaPerPrice >= lAreaPerPrice ) { // s > m
                std::cout << "Price: " << sPrice << std::endl; // s > m && s > l
            }
            else { // s > m
                std::cout << "Price: " << lPrice << std::endl; // s > m && l > s
            }
        }
        else { 
            if( mAreaPerPrice >= lAreaPerPrice ) { // m > s
                std::cout << "Price: " << mPrice << std::endl; // m > s && m > l
            }
            else {
                std::cout << "Price: " << lPrice << std::endl; // m > s && l > m
            }
        }
    }

};

struct sPizza {
    float s = 10.0f;
    float sPrice = 20;
    float sArea = s*s*pi;
    float sAreaPerPrice = sArea/sPrice;
};

struct mPizza {
    float m = 12.5f;
    float mPrice = 35;
    float mArea = m*m*pi;
    float mAreaPerPrice = mArea/mPrice;

};

struct lPizza {
    float l = 15.0f;
    float lPrice = 50;
    float lArea = l*l*pi;
    float lAreaPerPrice = lArea/lPrice;

};

struct pizza {
    float size;
    float price;
    float area;
    float areaPerPrice;
    // void init( float size, float price ) {
    // }
}


int main() {
    float pi = 3.14159f;

    //float s = 10f , m = 12.5f, l = 15f; // i CAN NOT do this!

    //float smallestPrice;
    //float smallPackPrice, mediumPackPrice, 

    //for(int i = 1; i <= 10; ++i) {
    //    for(int j = 1; j <= i; ++j) {

    //    }
    //    std::cout << "Para " << i << "pizza(s), o preço mais barato é o da pizza de " << smallestPrice << "dol." << endl;
    //}

}