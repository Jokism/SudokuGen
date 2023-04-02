#pragma once
#ifndef SUDOKU_GEN_H
#define SUDOKU_GEN_H
#include <vector>

namespace Sudo {
    using uint = unsigned int;
    using uintVec = std::vector<std::vector<uint>>;
    using uintInitList2D = std::initializer_list<std::initializer_list<uint>>;
    class SudokuGen 
    {
        private:
            uint m_rows;
            uint m_cols;
            uint m_block_size;
            uintVec m_grid;

        public:
            SudokuGen() noexcept;
            SudokuGen(uintInitList2D const&& vals) noexcept;
            SudokuGen(SudokuGen const& grid) noexcept;
            ~SudokuGen() = default;

            void printMatrix() const noexcept;
            void printMatrixCSV() const noexcept;
            inline bool validMatrix() const  noexcept;
            void fillValues() noexcept;
            void checkValidity(char const* name, bool expectedValidity) const noexcept;

        protected:
            inline uint seedInt() const noexcept;

            inline bool isValidRow(uint cellX, uint cellY, uint value) const noexcept;
            inline bool isValidCol(uint cellX, uint cellY, uint value) const noexcept;
            inline bool isValidBlock(uint rowStart, uint colStart, uint value) const noexcept;
            inline bool isValidValue(uint cellX, uint cellY, uint value) const noexcept;
            inline bool isValidBlock(uint rowStart, uint colStart) const noexcept;
            inline bool isValidIndex(uint cellX, uint cellY) const noexcept;

            void fillDiagonal() noexcept;
            void fillBlock(uint rowStart, uint colStart) noexcept;          
            bool fillRemaining(uint cellX, uint cellY) noexcept;
    };
}

#endif