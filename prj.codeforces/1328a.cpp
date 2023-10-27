#include <iostream>
#include <string>
 
int main() {
 
    int t = 0;
    int a = 0;
    int b = 0;
 
    std::cin >> t;
 
    for (int i = 0; i < t; i++){
        std::cin >> a;
        std::cin >> b;
        if (a % b == 0){
            std::cout << 0 << "\n";
        }
        else{
            std::cout << b - (a % b) << "\n";
        }
    }
    
    return 0;
}
