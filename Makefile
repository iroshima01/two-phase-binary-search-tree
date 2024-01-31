program: array main build

array:
	g++ -std=c++11 -c SecondaryNode.cpp
	g++ -std=c++11 -c PrimaryNode.cpp
	g++ -std=c++11 -c TPBST.cpp

main:
	g++ -std=c++11 -c main.cpp

build:
	g++ main.o TPBST.o PrimaryNode.o SecondaryNode.o -o webstore