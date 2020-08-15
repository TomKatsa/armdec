all: armdec.cpp Bits.cpp
	g++ -o armdec armdec.cpp Bits.cpp