#ifndef _TILE_JOB_H
#define _TILE_JOB_H
#include "GameTable.hpp"

class Tile
{
public:
    Tile() : old_table(nullptr), new_table(nullptr), start_row(0), end_row(0) {}

    Tile(GameTable *old_table, GameTable *new_table, int start_row, int end_row) : old_table(old_table), new_table(new_table),
                                                                           start_row(start_row), end_row(end_row){};

    Tile(const Tile &tile) = default;

    Tile &operator=(const Tile &tile) = default;

    void fill_new_tile();

    ~Tile() = default;

private:
    GameTable *old_table;

    GameTable *new_table;

    int start_row;

    int end_row;
};

#endif