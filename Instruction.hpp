#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_
#include <sstream>
#include "Bits.hpp"
#include "mnemonics.hpp"

using std::ostringstream;

struct Registers {
    std::string Rd; // Destination
    std::string Rn; // Source 1
    std::string Rm; // Source 2
    std::string Rs; // Register shift
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
    void BranchImmediate();
    void BranchExchange();
    void SoftwareInterrupt();
    void Unknown();
    bool OnlyTwoOperands(int opcode_num);
};

#endif