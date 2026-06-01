#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: squarer <number>" << std::endl;
        return 1;
    }
    
    int num = std::atoi(argv[1]);
    std::cout << "C++ Engine: " << num << " squared is " << (num * num) << std::endl;
    return 0;
}
