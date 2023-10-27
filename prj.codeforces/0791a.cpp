#include <iostream>

int main(){
    int a, b;
    
    std::cin >> a >> b;
    int w1, w2;
    w1 = a;
    w2 = b;
    int years = 0;
    
    while(w1 <= w2){
        w1 *= 3;
        w2 *= 2;
        years += 1;
    }
    
    std::cout << years;
    
    return 0;
}
