#include "include/SudokuGen.h"

int main(int const argc, char const* const* argv)
{
    Sudo::SudokuGen sg;
    sg.printMatrix();
    sg.checkValidity("SG", true);

    Sudo::SudokuGen valid {
        { 5, 3, 4,  6, 7, 8,  9, 1, 2 },
        { 6, 7, 2,  1, 9, 5,  3, 4, 8 },
        { 1, 9, 8,  3, 4, 2,  5, 6, 7 },

        { 8, 5, 9,  7, 6, 1,  4, 2, 3 },
        { 4, 2, 6,  8, 5, 3,  7, 9, 1 },
        { 7, 1, 3,  9, 2, 4,  8, 5, 6 },

        { 9, 6, 1,  5, 3, 7,  2, 8, 4 },
        { 2, 8, 7,  4, 1, 9,  6, 3, 5 },
        { 3, 4, 5,  2, 8, 6,  1, 7, 9 },
    };
    valid.printMatrix();
    valid.checkValidity("VALID", true);

    Sudo::SudokuGen invalid = {
        { 5, 3, 4,  6, 7, 8,  9, 1, 2 },
        { 6, 7, 2,  1, 9, 5,  3, 4, 8 },
        { 1, 9, 8,  3, 2, 2,  5, 6, 7 },

        { 8, 5, 9,  7, 6, 1,  4, 2, 3 },
        { 4, 2, 6,  8, 5, 3,  7, 9, 1 },
        { 7, 1, 3,  9, 2, 4,  8, 5, 6 },

        { 9, 6, 1,  5, 3, 7,  2, 8, 4 },
        { 2, 8, 7,  4, 1, 9,  6, 3, 5 },
        { 3, 4, 5,  2, 8, 6,  1, 7, 9 },
    };
    invalid.printMatrix();
    invalid.checkValidity("INVALID", false);

    Sudo::SudokuGen* defaultSG = new Sudo::SudokuGen;
    defaultSG->printMatrix();
    defaultSG->checkValidity("DEFAULTSG", true);

    Sudo::SudokuGen copySG {*defaultSG};
    copySG.printMatrix();
    copySG.checkValidity("COPYSG", true);

    delete defaultSG;
    copySG.printMatrix();
    copySG.checkValidity("COPYSG", true);
    copySG.printMatrixCSV();

    return 0;
}

