@echo off
call "g++.exe" -Wall -o sudoku.exe -std=c++17 -static Sudoku.cpp src/SudokuGen.cpp
call sudoku.exe
