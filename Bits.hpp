#ifndef BITS_H_
#define BITS_H_

#include <stdint.h>
#include <iostream>


class Bits {

    private:
    int size;
    uint32_t internal_num;


    public:
    Bits(uint32_t num);
    int GetSize(void);
    unsigned char operator[](int index);
    uint32_t Range(int start, int end);

};

std::ostream& operator<<(std::ostream& os, Bits& b);


#endif