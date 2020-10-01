#include "Instruction.hpp"
#include "mnemonics.hpp"
#include <iomanip>

//#define DEBUG
#ifdef DEBUG
#define printdebug(...) printf(__VA_ARGS__)
#else
#define printdebug(x)
#endif

#define PADDING 10



using std::string;
using std::hex;
using std::dec;

Instruction::Instruction(uint32_t raw) : raw_instruction(raw){
        SetRegisters();
        SetCondition();
        PadOutput(PADDING);
}

void Instruction::SetRegisters() {
    this->regstruct.Rn = registers[this->raw_instruction.Range(16, 20)]; // operand
    this->regstruct.Rd = registers[this->raw_instruction.Range(12,16)]; // destination
    this->regstruct.Rm = registers[this->raw_instruction.Range(0,4)]; // operand
    this->regstruct.Rs = registers[this->raw_instruction.Range(8,12)]; // shift
}

// Check the condition bits
void Instruction::SetCondition() {
    this->condition = conditions[this->raw_instruction.Range(28,32)];
}


string Instruction::GetShiftType() {
    return shiftype[this->raw_instruction.Range(5,7)];
}

int Instruction::GetShiftAmount() {
    return this->raw_instruction.Range(7, 12);
}

int Instruction::GetOpcodeNum() {
    return this->raw_instruction.Range(21, 25);
}

opcodes_enum Instruction::GetConditionEnum() {
    return (opcodes_enum)this->raw_instruction.Range(28,32);
}

void Instruction::PadOutput(int num) {
    this->output << std::left << std::setw(num);
}

bool Instruction::OnlyTwoOperands(int opcode_num) {
    return (opcode_num == opcodes_enum::MOV 
            || opcode_num == opcodes_enum::TEQ 
            || opcode_num == opcodes_enum::TST
            || opcode_num == opcodes_enum::CMN
            || opcode_num == opcodes_enum::CMP);
}


void Instruction::DataProcShift() {
    int opcode_num = this->GetOpcodeNum();
    string shiftype = GetShiftType();
    this->output << (opcodes[opcode_num] + this->condition);
    this->output << this->regstruct.Rd << ", ";
    if (OnlyTwoOperands(opcode_num)) {
        output << this->regstruct.Rm;
    }
    else {
        output << this->regstruct.Rn << ", " << this->regstruct.Rm;
    }
    if (this->raw_instruction[4] == 0) {
        // Immediate value shift
        int shift = GetShiftAmount();
        if (shift) {
        output << ", " << shiftype << " #" << shift;
        }
    }
    else {
        // Register shift
        output << ", " << shiftype << " " << this->regstruct.Rs;
    }
    output << std::endl;
}



void Instruction::DataProcImmediate() {
    int opcode_num = this->GetOpcodeNum();
    int rotate_imm = this->raw_instruction.Range(8,12);
    int immed_8 = this->raw_instruction.Range(0, 8);
    // Rotate right in 32 bit space
    // value = immed_8 rotated right by 2*rotate
    int value = (immed_8 >> rotate_imm*2) | (immed_8 << (32-rotate_imm*2));
    this->output << (opcodes[opcode_num] + this->condition);
    if (OnlyTwoOperands(opcode_num)) {
        output << this->regstruct.Rd;
    }
    else {
        output << this->regstruct.Rd << ", " << this->regstruct.Rn;
    }
    output << ", #" << value << std::endl;
}


void Instruction::LoadStoreImmediateOffset() {
    string operation = (this->raw_instruction[20] == 0) ? "STR" : "LDR";
    int offset_12 = this->raw_instruction.Range(0, 12);
    // Check if B flag (unsigned byte or word) is on
    string b = ((this->raw_instruction[22] == 1) ? "B " : " ");
    this->output << (operation + b + this->condition);
    this->output <<  this->regstruct.Rn << ", " << "[" << this->regstruct.Rd;
    this->output << ", #" << ((this->raw_instruction[23] == 0) ? "-" : "");
    this->output << offset_12 << "]" << std::endl;
}



void Instruction::BranchImmediate() {
    int32_t offset_24 = this->raw_instruction.Range(0, 24);
    // Checking the 24th bit, to sign extend to 32 bit,
    // shift left 2 bits and add 8 (PC in ARM holds the address of 2 next instructions)
    if (this->raw_instruction[23] == 1)
    {
        offset_24 = ((offset_24 | 0xff000000) << 2) + 8;
    }
    else
    {
        offset_24 = (offset_24 << 2) + 8;
    }
    string operation =  ((this->raw_instruction[24] == 1) ? "BL" : "B" );
    this->output << (operation+this->condition);
    this->output <<  "#0x"  << std::hex << offset_24 << std::dec;
    this->output << "   @ " << offset_24 << std::endl;
}

void Instruction::BranchExchange() {
    string operation = ((this->raw_instruction[5] == 1) ? "BLX" : "BX");
    this->output << (operation+this->condition);
    this->output <<  this->regstruct.Rm << std::endl;
}

void Instruction::Unknown() {
    this->output << "(unknown)" << std::endl;
}

void Instruction::SoftwareInterrupt() {
    string operation = "SWI";
    this->output << (operation + this->condition);
    this->output << "#" << this->raw_instruction.Range(0, 24) << std::endl;

}

void Instruction::DecodeInstruction() {
    if (this->raw_instruction.Range(20, 28) == 0b00010010) {
        printdebug("!BRANCHEXCHANGE\n");
        BranchExchange();
    }
    // xxxx000xxxxxxxxxxxxxxxxxxxx?xxxx
    else if (this->raw_instruction.Range(25,28) == 0) {
        printdebug("!DPS\n");
        DataProcShift();
    }
    else if (this->raw_instruction.Range(25,28) == 0b001) {
        printdebug("!DPI\n");
        DataProcImmediate();
    }
    else if (this->raw_instruction.Range(25,28) == 0b010) {
        printdebug("!LSIO\n");
        LoadStoreImmediateOffset();
    }
    else if (this->raw_instruction.Range(25,28) == 0b101) {
        printdebug("!BRANCH\n");
        BranchImmediate();
    }
    else if (this->raw_instruction.Range(24, 28) == 0b1111) {
        printdebug("!SWI\n");
        SoftwareInterrupt();
    }
    else {
        printdebug("!UNKNOWN\n");
        Unknown();
    }

}