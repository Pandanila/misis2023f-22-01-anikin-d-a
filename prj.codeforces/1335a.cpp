#include <iostream>
#include <string>
 
int main() {
 
    int t = 0;
    int n = 0;
 
    std::cin >> t;
 
    for (int i = 0; i < t; i++){
        std::cin >> n;
        std::cout << (n - 1) - (n / 2 + 1) + 1<< "\n";
    }
    
    return 0;
}
