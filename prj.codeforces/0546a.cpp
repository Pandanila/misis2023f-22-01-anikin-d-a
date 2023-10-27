#include <iostream>

int main(){
    int k, n, w;
    
    std::cin >> k >> n >> w;
    int count = 0;
    
    for (int i = 1; i <= w; i++){
        count += i;
    }
    if (count * k > n){
        std::cout << count * k - n;
    }
    else{
        std::cout << 0;
    }
    
    return 0;
}
