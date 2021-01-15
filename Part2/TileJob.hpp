#ifndef _TILE_JOB_H
#define _TILE_JOB_H
#include "GameTable.hpp"
// class that encapsulate a thread job
class TileJob
{
public:
    //  empty constructor
    TileJob() : old_table(nullptr), new_table(nullptr), start_row(0), end_row(0) {}
    //default game constructor
    TileJob(GameTable *old_table, GameTable *new_table, int start_row, int end_row, int phase) : old_table(old_table), new_table(new_table),
                                                                                                 start_row(start_row), end_row(end_row), phase(phase){};
    // default copy constructor
    TileJob(const TileJob &tile) = default;
    // default assignement operator
    TileJob &operator=(const TileJob &tile) = default;
    // executed job by Thread
    void fill_new_tile_job();

    ~TileJob() = default;

private:
    GameTable *old_table;
    GameTable *new_table;

    int start_row;

    int end_row;
    int phase;
};

#endif
