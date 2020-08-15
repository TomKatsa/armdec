#ifndef ARMDEC_H_
#define ARMDEC_H_
#include <iostream>

#define ARM_MODE 4
#define THUMB_MODE 2

// Array index is opcode number for the condition
std::string conditions[] = {"EQ",
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
std::string opcodes[] = {"AND",
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
                    MVN
};


struct Registers {
    int Rd; // Destination
    int Rn; // Source 1
    int Rm; // Source 2
    int Rs; // Register shift
};

#endif