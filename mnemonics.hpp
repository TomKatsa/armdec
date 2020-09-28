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