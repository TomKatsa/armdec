all: main.cpp Bits.cpp Instruction.hpp
	g++ -o armdec main.cpp Bits.cpp Instruction.cpp