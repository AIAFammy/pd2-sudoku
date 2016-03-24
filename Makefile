all: sudoku.o giveQuestion.cpp solve.cpp transform.cpp
	g++ -o giveQuestion giveQuestion.cpp sudoku.o
	g++ -o solve solve.cpp sudoku.o
	g++ -o transform transform.cpp sudoku.o

sudoku.o: sudoku.cpp sudoku.h
	g++ -c sudoku.cpp -o sudoku.o
