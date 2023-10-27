#include <iostream>
 
int main() {
    int n = 0;
    int a = 0;
    int flag = 1;
    std::cin >> n;
    for (int i = 0; i < n; i++){
        std::cin >> a;
        if (a == 1){
            std::cout << "HARD";
            flag = 0;
            break;
        }
    }
    if (flag){
        std::cout << "EASY";
    }
    
    return 0;
}