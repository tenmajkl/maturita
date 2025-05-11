#include <stdio.h>

// todo union

typedef unsigned int uint_t;

int main(void) 
{
    // we first define mask and ip as array
    unsigned char _mask[4] = {255, 255, 240, 0};
    unsigned char _net[4] = {192, 124, 36, 10};

    // then we convert list of numbers into 4byte number (unsinged int)
    uint_t mask = *((uint_t*)_mask);
    uint_t net = *((uint_t*)_net);

    // then we perform operation to get subnet
    uint_t result = net & ~mask;
    // and then we turn our new net back to array of numbers
    unsigned char* subnet = (unsigned char*) &result;

    // pointer/bit aritmetics bitch, problem?

    printf("%i", subnet[3]);
}
