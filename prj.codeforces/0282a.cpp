#include <iostream>
#include <string>
 
int main() {
    int n = 0;
    int count = 0;
    std::string s;
    std::cin >> n;
    for (int i = 0; i < n; i++){
        std::cin >> s;
        if (s.find("++") != std::string::npos){
            count += 1;
        }
        else if (s.find("--") != std::string::npos){
            count -= 1;
        }
    }
    std::cout << count;
 
    
    return 0;
}
