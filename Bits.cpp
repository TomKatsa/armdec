#include <stdint.h>
#include <stdio.h>
#include "Bits.hpp"


Bits::Bits(uint32_t num) : size(32) {
    this->internal_num = num;
}

unsigned char Bits::operator[](int index) {
    return 1 & (this->internal_num >> index);
}

int Bits::GetSize() {
    return this->size;
}

std::ostream& operator<<(std::ostream& os, Bits& b) {
    for (int i=0; i<b.GetSize(); i++) {
        os << static_cast<int>(b[i]);
    }
    return os;
}


uint32_t Bits::Range(int start, int end) {
    return ((1 << (end-start))-1) & (this->internal_num >> start);
}



