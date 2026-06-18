#include "cusRandom.hpp"
#include <iostream>

extern "C" {
    #include "unif01.h"
    #include "bbattery.h"
}

customRandom<uint32_t> rng(1488813230);

extern "C" unsigned int my_generator (void) {
    return rng.gen();
}

int main (void) {
    std::cout << "Starting the BigCrush Test" << std::endl;

    unif01_Gen *gen;
    gen = unif01_CreateExternGenBits("Xorinter", my_generator);

    bbattery_BigCrush(gen);

    unif01_DeleteExternGenBits(gen);
    return 0;
}


