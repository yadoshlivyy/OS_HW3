#ifndef _TILE_JOB_H
#define _TILE_JOB_H
#include "GameTable.hpp"

class TileJob
{
public:
    TileJob() : old_table(nullptr), new_table(nullptr), start_row(0), end_row(0) {}

    TileJob(GameTable *old_table, GameTable *new_table, int start_row, int end_row) : old_table(old_table), new_table(new_table),
                                                                           start_row(start_row), end_row(end_row){};

    TileJob(const TileJob &tile) = default;

    TileJob &operator=(const TileJob &tile) = default;

    void fill_new_tile_job();

    ~TileJob() = default;

private:
    GameTable *old_table;

    GameTable *new_table;

    int start_row;

    int end_row;
};

#endif