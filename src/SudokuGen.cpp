#include "../include/SudokuGen.h"
#include <random>
#include <set>

Sudo::SudokuGen::SudokuGen() noexcept
: m_rows(9), m_cols(9), m_block_size(std::sqrt(m_rows*m_cols))
{
    m_grid = uintVec(m_rows, std::vector<uint>(m_cols, 0));
    fillValues();
}
Sudo::SudokuGen::SudokuGen(uintInitList2D const&& vals) noexcept
:m_rows(vals.size()), m_cols(vals.begin()->size()), m_block_size(std::sqrt(m_rows*m_cols))
{
    if (vals.size() != 9 || vals.begin()->size() != 9)
    {
        *this = SudokuGen();
    }
    else
    {
        m_grid = uintVec();
        for (auto&& x: vals)
        {
            std::vector<uint> row;
            for (auto&& y : x)
            {
                row.push_back(y);
            }
            m_grid.push_back(row);
        }
    }
}
Sudo::SudokuGen::SudokuGen(SudokuGen const& grid) noexcept
: m_rows(grid.m_rows), m_cols(grid.m_cols), m_block_size(grid.m_block_size)
{
    m_grid = uintVec();
    for (uint i = 0; i < grid.m_grid.size(); ++i)
    {
        std::vector<uint> row;
        for (uint j = 0; j < grid.m_grid[i].size(); ++j)
        {
            row.push_back(grid.m_grid[i][j]);
        }
        m_grid.push_back(row);
    }
}

void Sudo::SudokuGen::printMatrix() const noexcept
{
    printf("Printing matrix =>\n");
    for(auto& row : m_grid)
    {
        // Draw top border
        for(uint i = 0; i < m_rows; ++i)
        {
            printf("|---");
        }
        printf("|\n|");
        
        for(auto& col : row)
        {
            printf(" %d |", col);
        }
        printf("\n");
    }
    for(uint i = 0; i < m_cols; ++i)
    {
        printf("|---");
    }
    printf("|\n");
    return;
}
void Sudo::SudokuGen::printMatrixCSV() const noexcept
{
    printf("Printing matrix in CSV format =>\n");
    for(auto& row : m_grid)
    {    
        for(auto& col : row)
        {
            printf("%d,", col);
        }
        printf("\n");
    }
    printf("\n");
    return;
}
inline Sudo::uint Sudo::SudokuGen::seedInt() const noexcept
{
    static std::random_device rand_dev;
    std::mt19937 rng(rand_dev());
    std::uniform_int_distribution<uint> dist(1,9);
    return dist(rng);
}

inline bool Sudo::SudokuGen::isValidIndex(uint cellX, uint cellY) const noexcept
{
    if (cellX >= m_grid.size() || cellY >= m_grid[cellX].size())
        return false;
    return true;
}
inline bool Sudo::SudokuGen::isValidRow(uint cellX, uint cellY, uint value) const noexcept
{
    if (!isValidIndex(cellX, cellY))
        return false;
    for (uint j = 0; j < m_grid[cellX].size(); ++j)
    {
        if (m_grid[cellX][j] == value)
              return false;
    }
    return true;
}
inline bool Sudo::SudokuGen::isValidCol(uint cellX, uint cellY, uint value) const noexcept
{
    if (!isValidIndex(cellX, cellY))
        return false;
    for (uint i = 0; i < m_grid.size(); ++i)
    {
        if (m_grid[i][cellY] == value)
            return false;
    }
    return true;
}
inline bool Sudo::SudokuGen::isValidBlock(uint rowStart, uint colStart, uint value) const noexcept
{
    if (!isValidIndex(rowStart, colStart))
        return false;
    for (uint i = 0; i < static_cast<uint>(std::sqrt(m_rows)); ++i)
    {
        for (uint j = 0; j < static_cast<uint>(std::sqrt(m_cols)); ++j)
        {
            if (m_grid[rowStart+i][colStart+j] == value)
                return false;
        }
    }
    return true;
}
inline bool Sudo::SudokuGen::isValidValue(uint cellX, uint cellY, uint value) const noexcept
{
    if (!isValidIndex(cellX, cellY))
        return false;
    return isValidRow(cellX, cellY, value) &&
            isValidCol(cellX, cellY, value) && 
            isValidBlock(cellX - cellX % static_cast<uint>(std::sqrt(m_rows)),
                        cellY - cellY % static_cast<uint>(std::sqrt(m_cols)), value);
}
inline bool Sudo::SudokuGen::isValidBlock(uint rowStart, uint colStart) const noexcept
{
    if (!isValidIndex(rowStart, colStart))
        return false;
    std::set<uint> unique;
    for (uint i = 0; i < static_cast<uint>(std::sqrt(m_rows)); ++i)
    {
        for (uint j = 0; j < static_cast<uint>(std::sqrt(m_cols)); ++j)
        {
            if(unique.find(m_grid[rowStart+i][colStart+j]) == unique.end())
                unique.insert(m_grid[rowStart+i][colStart+j]);
        }
    }
    
    return unique.size() == 9;
}
inline bool Sudo::SudokuGen::validMatrix() const noexcept
{
    for (uint x = 0; x < static_cast<uint>(m_rows); x += static_cast<uint>(std::sqrt(m_rows)))
    {
        for (uint y = 0; y < static_cast<uint>(m_cols); y += static_cast<uint>(std::sqrt(m_cols)))
        {
            if(m_grid[x][y] == 0 || !isValidBlock(x, y))
                return false;
        }
    }
return true;
}

void Sudo::SudokuGen::fillDiagonal()  noexcept
{
    for(uint i = 0; i < static_cast<uint>(m_rows); i += 3)
        fillBlock(i,i);
}
void Sudo::SudokuGen::fillBlock(uint rowStart, uint colStart)  noexcept
{
    uint num = seedInt();
    for (uint i = 0; i < static_cast<uint>(std::sqrt(m_rows)); ++i)
    {
        for(uint j = 0; j < static_cast<uint>(std::sqrt(m_cols)); ++j)
        {
            while (!isValidBlock(rowStart, colStart, num))
                num = seedInt();
            m_grid[rowStart+i][colStart+j] = num;
        }
    }
}
void Sudo::SudokuGen::fillValues()  noexcept
{
    fillDiagonal();
    fillRemaining(0, 3);
}
inline bool Sudo::SudokuGen::fillRemaining(uint cellX, uint cellY)  noexcept
{
    uint const N = m_rows;
    uint const SRN = static_cast<uint>(std::sqrt(m_rows));
    
    // If index j >= 9 AND index i < 8
    if(cellY >= N && cellX < N - 1)
    {
        ++cellX;
        cellY = 0;
    }
    if(cellX >= N && cellY >= N)
        return true;
    
    if (cellX < SRN && cellY < SRN)
        cellY = SRN;
    else if (cellX < N - SRN)
    {
        if(cellY == static_cast<uint>(cellX/SRN) * SRN)
            cellY += SRN;
    }
    else 
        if (cellY == N - SRN)
        {
            ++cellX;
            cellY = 0;
            if(cellX >= N)
                return true;
        }
    
    for (uint num = 1; num <= N; ++num)
    {
       if(isValidValue(cellX, cellY, num))
        {
            m_grid[cellX][cellY] = num;
            if(fillRemaining(cellX, cellY+1))
                return true;
            m_grid[cellX][cellY] = 0;
        }
    }
    return false;
}

void Sudo::SudokuGen::checkValidity(char const* name, bool expectedValidity = true) const noexcept
{
    printf("RESULTS:\n[%s] => [IsValid = %s]\t [EXPECTS = %s]\n",
            name,
            (this->validMatrix() ? "TRUE" : "FALSE"),
            (expectedValidity ? "TRUE" : "FALSE")
    );
    printf("DONE\n\n\n");
}


