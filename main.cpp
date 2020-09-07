#include <cstdio>
#include <stdint.h>
#include <iostream>
#include "Bits.hpp"
#include "Instruction.hpp"
#include "mnemonics.hpp"


using std::cout;
using std::endl;


void DecodeSection(const char* section, uint64_t size)  {
    uint8_t mode = ARM_MODE; // 2 for thumb mode?
    uint64_t i;
    for (i=0; i<size; i+=mode) {
        if (mode == ARM_MODE) {
            uint32_t raw_bytes = *(uint32_t*)(section + i);
            Instruction instruction(raw_bytes);
            instruction.DecodeInstruction();
            cout << instruction.output.str();
        }
    }
}

int main(int argc, char const *argv[])
{
    // MOV R1, R2
    // ADDEQ R1, R1, R3
    // ANDLS R5, R5, R5
    // SUBGE R7, R6, R5
    // MOV R1, R1, LSL #1
    const char* section = "\x02\x10\xa0\xe1\x03\x10\x81\x00\x05\x50\x05\x90\x05\x70\x46\xa0\x81\x10\xa0\xe1";
    DecodeSection(section, 20);
    return 0;
}