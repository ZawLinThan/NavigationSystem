#include <iostream>
#include "/Users/zawlinthan/Desktop/NavigationSystem/NavigationSystem/src/Data.h"

int main(){
    Data data("/Users/zawlinthan/Desktop/NavigationSystem/NavigationSystem/Data.txt");
    std::cout << "Enter 'STOP' to exit" << std::endl;
    while (true)
    {
        std::string from, to;
        std::cout << "From : ";
        std::getline(std::cin, from);
        std::cout << "To : ";
        std::getline(std::cin , to);
        if (from == "STOP" || to == "STOP") {break;}
        data.findPath(from, to);

        data.deleteOpenSet();
        data.deleteClosedSet();
    }
    return 0;
}