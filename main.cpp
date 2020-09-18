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
    // MOV R1, R2, LSL R3
    // MOV R2, #1024
    // ADD R3, R4, #31
    // LDR R1, [R0, #-15]
    // STRB R2, [R1, #200]
    const char* section = "\x02\x10\xa0\xe1"
                            "\x03\x10\x81\x00"
                            "\x05\x50\x05\x90"
                            "\x05\x70\x46\xa0"
                            "\x81\x10\xa0\xe1"
                            "\x12\x13\xa0\xe1"
                            "\x01\x2b\xa0\xe3"
                            "\x1f\x30\x84\xe2"
                            "\x0f\x00\x11\xe5"
                            "\xc8\x10\xc2\xe5";
    DecodeSection(section, 40);
    return 0;
}
