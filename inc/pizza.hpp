const float pi = 3.14159f;

struct Spizza {
    float s;
    float price;
    float area;
    float areaPerPrice;
    float calculateArea() { return area = s*s*pi; }
    float calculateAreaPerPrice() { return areaPerPrice = area/price; }
};

struct Mpizza {
    float m;
    float price;
    float area;
    float areaPerPrice;
    float calculateArea() { return area = m*m*pi; }
    float calculateAreaPerPrice() { return areaPerPrice =  area/price; }

};

struct Lpizza {
    float l;
    float price;
    float area;
    float areaPerPrice;
    float calculateArea() { return area = l*l*pi; }
    float calculateAreaPerPrice() { return areaPerPrice =  area/price; }

};

struct Pizza {
    std::string sizec;
    float size;
    float price;
    float area;
    float areaPerPrice;
    float calculateArea() { return area = size*size*pi; }
    float calculateAreaPerPrice() { return areaPerPrice =  area/price; }
};


struct PizzaRestaurant {
    // Spizza small;
    // Mpizza medium;
    // Lpizza large;

    std::string name;
    Pizza *pizzas;
    Pizza cheapestPizza;

    // void calculateCheapestPizzaPrice() {
    //     if( small.areaPerPrice >= medium.areaPerPrice ) { 
    //         if( small.areaPerPrice >= large.areaPerPrice ) { // s > m
    //             std::cout << "Price: " << small.price << std::endl; // s > m && s > l
    //             cheapestPizza.size = small.s;
    //             cheapestPizza.price = small.price;
    //             cheapestPizza.calculateArea(); 
    //             cheapestPizza.calculateAreaPerPrice();
    //         }
    //         else { // s > m
    //             std::cout << "Price: " << large.price << std::endl; // s > m && l > s
    //             cheapestPizza.size = small.s;
    //             cheapestPizza.price = small.price; 
    //             cheapestPizza.calculateArea();
    //             cheapestPizza.calculateAreaPerPrice();
    //         }
    //     }
    //     else { 
    //         if( medium.areaPerPrice >= large.areaPerPrice ) { // m > s
    //             std::cout << "Price: " << medium.price << std::endl; // m > s && m > l
    //             cheapestPizza.size = medium.m;
    //             cheapestPizza.price = medium.price;
    //             cheapestPizza.calculateArea(); 
    //             cheapestPizza.calculateAreaPerPrice();
    //         }
    //         else {
    //             std::cout << "Price: " << large.price << std::endl; // m > s && l > m
    //             cheapestPizza.size = large.l;
    //             cheapestPizza.price = large.price;
    //             cheapestPizza.calculateArea(); 
    //             cheapestPizza.calculateAreaPerPrice();
    //         }
    //     }
    // }

};