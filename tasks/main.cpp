#include <iostream>
#include "TMinStack.h"

int main() {
    TMinStack<int> s;

    std::cout << "Enter the numbers separated by spaces.\n" << "To finish, enter a letter.\n";

    int x;
    while (std::cin >> x) {
        s.push(x);
        s.print();
        std::cout << "min = " << s.min() << "\n\n";
    }

    std::cout << "\nNow we will show how the values of our stacks will change when elements are removed one by one:\n\n";
    while (!s.empty()) {
        s.pop();
        s.print();
        if (!s.empty()) {
            std::cout << "min = " << s.min() << "\n";
        }
        std::cout << "\n";
    }

    return 0;
}