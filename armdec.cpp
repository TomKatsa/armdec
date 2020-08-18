#include <cstdio>
#include <stdint.h>
#include <iostream>
#include "Bits.hpp"
#include "armdec.hpp"


using std::cout;
using std::endl;


void GetRegisters(Bits& instruction, Registers& regstruct) {
    regstruct.Rn = instruction.Range(16, 20);
    regstruct.Rd = instruction.Range(12,16);
    regstruct.Rm = instruction.Range(0,4);
    regstruct.Rs = instruction.Range(8,12);
}

// Check the condition bits
std::string GetCondition(Bits& instruction) {
    return conditions[instruction.Range(28,32)];
}


std::string GetShiftType(Bits& instruction) {
    return shiftype[instruction.Range(5,7)];
}

int GetShiftAmount(Bits& instruction) {
    return instruction.Range(7, 12);
}

void DataProcImmediateShift(Bits& instruction) {
    Registers regs;
    GetRegisters(instruction, regs);
    std::string cond = GetCondition(instruction);
    int opcode = instruction.Range(21,25);
    std::string shiftype = GetShiftType(instruction);
    int shift = GetShiftAmount(instruction);
    cout << opcodes[opcode] << cond << " R" << regs.Rd << ", R";
    if (opcode == opcodes_enum::MOV) { // MOV takes only the second source operand
        cout << regs.Rm;
    }
    else {
        cout << regs.Rn << ", R" << regs.Rm;
    } 
    if (shift) {
        cout << ", " << shiftype << " #" << shift;
    }
    cout << endl;
}

void DataProcRegisterShift(Bits& instruction) {
    return;
}


void DecodeInstruction(uint32_t RawInstruction) {
    Bits CurrentInstruction(RawInstruction);
    if (CurrentInstruction.Range(25,28) == 0 && CurrentInstruction[4]==0) {
        DataProcImmediateShift(CurrentInstruction);
    }
    if (CurrentInstruction.Range(25, 28) == 0 && CurrentInstruction[4]==1) {
        DataProcRegisterShift(CurrentInstruction);
    }
}


void DecodeSection(const char* section, uint64_t size)  {
    uint8_t mode = ARM_MODE; // 2 for thumb mode?
    uint64_t i;
    for (i=0; i<size; i+=mode) {
        if (mode == ARM_MODE)
            DecodeInstruction(*(uint32_t*)(section + i));
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
