#include <iostream>
#include "../../inc/pizza.hpp"


int main() {

    PizzaRestaurant toppza;

    // float s = 10f, m = 12.5f, l = 15f; // i CAN NOT do this!
    // float sPrice = ;  
    // float mPrice = ;
    // float lPrice = ; // this is the right way

    toppza.small.s = 17.5f; // /* /* exercicio c++ primer */ */
    toppza.small.price = 43.0f;
    toppza.small.calculateArea();
    toppza.small.calculateAreaPerPrice();

    toppza.medium.m = 20.0f;
    toppza.medium.price = 48.0f;
    toppza.medium.calculateArea();
    toppza.medium.calculateAreaPerPrice();

    toppza.large.l = 22.5f;
    toppza.large.price = 58.0f;
    toppza.large.calculateArea();
    toppza.large.calculateAreaPerPrice();

    toppza.calculateCheapestPizzaPrice();
    std::cout << "Size: " << (toppza.cheapestPizza.size) << std::endl;

    //float smallestPrice;
    //float smallPackPrice, mediumPackPrice, 

    //for(int i = 1; i <= 10; ++i) {
    //    for(int j = 1; j <= i; ++j) {
    //    }
    //    std::cout << "Para " << i << "pizza(s), o preço mais barato é o da pizza de " << smallestPrice << "dol." << endl;
    //}
}