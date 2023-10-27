#include <iostream>
 
int main() {
    int n = 0;
    int p = 0;
    int q = 0;
    int count = 0;
    std::cin >> n;
    for (int i = 0; i < n; i++){
        std::cin >> p;
        std::cin >> q;
        if (q - p >= 2){
            count += 1;
        }
    }
    std::cout << count;
    
    return 0;
}
