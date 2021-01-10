#ifndef __GAME_TABLE_H
#define __GAME_TABLE_H

#include "utils.hpp"
#include "Game.hpp"

//! COMMENT ALL
class GameTable
{
public:
    GameTable(const string &filename);

    GameTable(const GameTable &GameTable) = default;

    friend ostream &operator<<(ostream &os, const GameTable &GameTable);

    GameTable &operator=(const GameTable &GameTable) = default;

    int get_rows_num() const;

    int get_columns_num() const;

    ~GameTable() = default;

private:
    int columns_num;

    int rows_num;

    int_mat table;

    bool cell_is_alive(int x, int y) const;

    int cell_in_board_and_alive(int x, int y) const;

    friend class TileJob;
};
#endif