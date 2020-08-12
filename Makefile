all: armdec.cpp Bits.cpp
	g++ -o arm armdec.cpp Bits.cpp