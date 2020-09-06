#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_
#include <sstream>
#include "Bits.hpp"

using std::ostringstream;

struct Registers {
    int Rd; // Destination
    int Rn; // Source 1
    int Rm; // Source 2
    int Rs; // Register shift
};


class Instruction {
    private:
    Registers regstruct;
    Bits raw_instruction;

    public:
    ostringstream output;
    Instruction(uint32_t);
    void GetRegisters();
    std::string GetCondition();
    std::string GetShiftType();
    int GetShiftAmount();
    void DataProcImmediateShift();
    void DataProcRegisterShift();
    void DecodeInstruction();
};

#endif