#include <iostream>

int main(){
    std::string namePrompt ("Please enter your first name: ");
    std::string surnamePrompt("Please enter your last name: ");

    std::string name;
    std::string surname;

    std::cout <<  namePrompt << std::endl;
    std::cin >> name;
    std::cout << surnamePrompt << std::endl;
    std::cin >> surname;

    std::string fullName = name + " " + surname;

    std::cout << "Hello " << fullName << "!\n" << "Your name contains " << fullName.size() << " characters." << std::endl;
}