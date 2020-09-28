#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_
#include <sstream>
#include "Bits.hpp"
#include "mnemonics.hpp"

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
    std::string condition;

    public:
    ostringstream output;
    Instruction(uint32_t);
    void SetRegisters();
    void SetCondition();
    opcodes_enum GetConditionEnum();
    std::string GetShiftType();
    int GetShiftAmount();
    int GetOpcodeNum();
    void DataProcImmediateShift();
    void DataProcRegisterShift();
    void DecodeInstruction();
    void DataProcImmediate();
    void LoadStoreImmediateOffset();
    void Branch();
    bool OnlyTwoOperands(int opcode_num);
};

#endif