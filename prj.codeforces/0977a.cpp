#include <iostream>

int main(){
    int n, k;
    
    std::cin >> n >> k;
    int res = n;
    
    for(int i = 0; i < k; i++){
        if(res % 10 == 0){
            res = res / 10;
        }
        else{
            res = res - 1;
        }
    }
    
    std::cout << res;
    
    return 0;
}
