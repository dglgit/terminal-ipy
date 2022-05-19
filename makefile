$CC=g++

nt: ncurseTest.cpp
	g++ ncurseTest.cpp -o build/nt -lncurses
	./build/nt

tp: testPy.c
	gcc testPy.c -o build/tp -lpython3.8
	./build/tp
