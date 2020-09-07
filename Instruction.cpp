#include "Instruction.hpp"
#include "mnemonics.hpp"

Instruction::Instruction(uint32_t raw) : raw_instruction(raw){

}

void Instruction::GetRegisters() {
    this->regstruct.Rn = this->raw_instruction.Range(16, 20);
    this->regstruct.Rd = this->raw_instruction.Range(12,16);
    this->regstruct.Rm = this->raw_instruction.Range(0,4);
    this->regstruct.Rs = this->raw_instruction.Range(8,12);
}

// Check the condition bits
std::string Instruction::GetCondition() {
    return conditions[this->raw_instruction.Range(28,32)];
}

std::string Instruction::GetShiftType() {
    return shiftype[this->raw_instruction.Range(5,7)];
}

int Instruction::GetShiftAmount() {
    return this->raw_instruction.Range(7, 12);
}



void Instruction::DataProcImmediateShift() {
    GetRegisters();
    std::string cond = GetCondition();
    int opcode = this->raw_instruction.Range(21,25);
    std::string shiftype = GetShiftType();
    int shift = GetShiftAmount();
    this->output << opcodes[opcode] << cond << " R" << this->regstruct.Rd << ", R";
    if (opcode == opcodes_enum::MOV) { // MOV takes only the second source operand
        output << this->regstruct.Rm;
    }
    else {
        output << this->regstruct.Rn << ", R" << this->regstruct.Rm;
    } 
    if (shift) {
        output << ", " << shiftype << " #" << shift;
    }
    output << std::endl;
}

void Instruction::DataProcRegisterShift() {
    GetRegisters();
    std::string cond = GetCondition();
    int opcode = this->raw_instruction.Range(21,25);
    std::string shiftype = GetShiftType();
    this->output << opcodes[opcode] << cond << " R" << this->regstruct.Rd << ", R";
    if (opcode == opcodes_enum::MOV) { // MOV takes only the second source operand
        output << this->regstruct.Rm;
    }
    else {
        output << this->regstruct.Rn << ", R" << this->regstruct.Rm;
    }
    output << ", " << shiftype << " R" << this->regstruct.Rs << std::endl;
    return;
}


void Instruction::DataProcImmediate() {
    GetRegisters();
    std::string cond = GetCondition();
    int opcode = this->raw_instruction.Range(21,25);
    int rotate_imm = this->raw_instruction.Range(8,12);
    int immed_8 = this->raw_instruction.Range(0, 8);
    // Rotate right in 32 bit space
    int value = (immed_8 >> rotate_imm*2) | (immed_8 << (32-rotate_imm*2));
    this->output << opcodes[opcode] << cond << " R";
    if (opcode == opcodes_enum::MOV) { // MOV takes only the second source operand
        output << this->regstruct.Rd;
    }
    else {
        output << this->regstruct.Rn << ", R" << this->regstruct.Rd;
    }
    output << ", #" << value << std::endl;
}

void Instruction::DecodeInstruction() {
    // xxxx000xxxxxxxxxxxxxxxxxxxx0xxxx
    if (this->raw_instruction.Range(25,28) == 0 && this->raw_instruction[4]==0) {
        DataProcImmediateShift();
    }
    // xxxx000xxxxxxxxxxxxxxxxxxxx1xxxx
    if (this->raw_instruction.Range(25, 28) == 0 && this->raw_instruction[4]==1) {
        DataProcRegisterShift();
    }
    if (this->raw_instruction.Range(25,28) == 0b001) {
        DataProcImmediate();
    }
}