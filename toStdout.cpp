#include <iostream>
#include <random>
#include "cusRandom.hpp"

std::random_device rd;

int main() {
    std::ios_base::sync_with_stdio(false);
    
    customRandom<unsigned long long> mc_engine(rd());
    
    while (std::cout.good()) {
        unsigned long long raw_val = mc_engine.gen();
        
        std::cout.write(reinterpret_cast<const char*>(&raw_val), sizeof(unsigned long long));
        std::cout.flush();
    }
    return 0;
}

