#include <iostream>
#include "/Users/zawlinthan/Downloads/NavigationSystem/src/Data.h"

int main() {
    std::string start, end;
    std::cout << "From: ";
    std::cin >> start;
    std::cout << "To: ";
    std::cin >> end;

    Data myData("");
    myData.createGraph(start, end);
    return 0;
}
