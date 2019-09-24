#include <iostream>

// using namespace std;  /* You can use this but BEWARE. */

using std::cout, std::endl; // Its like the "as" from python
// std::endl flushes the stream, "\n" doesn't 

// you can create a namespace by using:
namespace hello {
    //struct function_from_struct{

    //}
    void world(){
        // std::cout<< "Hello World!" << std::endl;
        // std::cout<< "Hello" + ' ' + string("World!") << std::endl; // this just prints World

        cout<< std::string("Hello") + ' ' + "World" + '!' << endl;
        // if the first operand of + is a std::string type,
        // all the strings and characters are converted to a std::string type and can be added

        // cout<< string("Hello") + ' ' + "World" + '!' + 2 << endl;
        // you can NOT add a number though, you get a really long error and some warnings about
        // a failed substitution

        return;
    }
} // name spaces are a way to encapsulate parts of the code

int main() {
    
    hello::world();    
   
    /* you DO NOT need to return something from main, it returns 0 by default */
}

//  https://linux.die.net/man/1/g++

// compiled with g++ -std=c++17 helloworld.cpp -o helloworld.out
// std lets you choose the ISO standard (c++17, c11, etc)
// useful flags:
//      -Wall -Wextra -ansi -pedantic -Wshadow -Weffc++
//      -DNDEBUG it stops the asserts executed by the std funcs, to make the code
//      -march=native for vectorization
//      https://caiorss.github.io/C-Cpp-Notes/compiler-flags-options.html