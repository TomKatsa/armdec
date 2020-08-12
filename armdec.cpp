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
    Bits CurrentInstruction(instruction);
    int cond = CurrentInstruction.Range(28,32);
    return conditions[cond];
}


void DataProcImmediateShift(Bits& instruction) {
    Registers regs;
    GetRegisters(instruction, regs);
    std::string cond = GetCondition(instruction);
    int opcode = instruction.Range(21,25);
    cout << opcodes[opcode] << cond << " R" << regs.Rd << ", R";
    if (opcode == opcodes_enum::MOV) {
        cout << regs.Rm;
    }
    else {
        cout << regs.Rn << ", R" << regs.Rm << endl;
    } 
}


void IdentifyInstruction(uint32_t RawInstruction) {
    Bits CurrentInstruction(RawInstruction);
    if (CurrentInstruction.Range(25,28) == 0 && CurrentInstruction[4]==0) {
        DataProcImmediateShift(CurrentInstruction);
    }
}

int main(int argc, char const *argv[])
{
    const char* binary = "\x02\x10\xa0\xe1"; // MOV R1, R2
    IdentifyInstruction(*(uint32_t*)binary);
    return 0;
}
