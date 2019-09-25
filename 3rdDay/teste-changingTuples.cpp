#include <iostream>
#include <tuple>

using std::tuple, std::get;
using std::cout, std::endl;

int main(){
    tuple<double, int> tupla (2.0, 1);
    cout << get<0>(tupla) << endl;
    get<0>(tupla) = 50.6;
    cout << get<0>(tupla) << endl;

}