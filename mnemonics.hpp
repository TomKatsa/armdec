#ifndef MNEMONICS_H_
#define MNEMONICS_H_
#include <iostream>

#define ARM_MODE 4
#define THUMB_MODE 2

// Array index is opcode number for the condition
const std::string conditions[] = {"EQ",
                            "NE",
                            "CS",
                            "CC",
                            "MI",
                            "PL",
                            "VS",
                            "VC",
                            "HI",
                            "LS",
                            "GE",
                            "LT",
                            "GT",
                            "LE",
                            "", // AL (always) can be left blank
                            "(bad)" };

// Array index is opcode number for the operation
const std::string opcodes[] = {"AND",
                         "EOR",
                         "SUB",
                         "RSB",
                         "ADD",
                         "ADC",
                         "SBC",
                         "RSC",
                         "TST",
                         "TEQ",
                         "CMP",
                         "CMN",
                         "ORR",
                         "MOV",
                         "BIC",
                         "MVN"
};

const std::string registers[] = {"R0","R1","R2","R3","R4","R5","R6","R7","R8","R9","R10","R11","R12","SP","LR","PC"};


const std::string shiftype[] = {"LSL", "LSR", "ASL", "ASR"};

enum opcodes_enum {AND,
                    EOR,
                    SUB,
                    RSB,
                    ADD,
                    ADC,
                    SBC,
                    RSC,
                    TST,
                    TEQ,
                    CMP,
                    CMN,
                    ORR,
                    MOV,
                    BIC,
                    NV
};



#endif