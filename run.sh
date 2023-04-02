#!/bin/bash

g++ -Wall -o sudoku -std=c++17 -static Sudoku.cpp src/SudokuGen.cpp

./sudoku
