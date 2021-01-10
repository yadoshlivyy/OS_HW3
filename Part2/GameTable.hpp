#ifndef __GAME_TABLE_H
#define __GAME_TABLE_H
#include "utils.hpp"
#include "../Part1/Headers.hpp"
#define RESET "\033[0m"
#define BLACK "\033[30m"   /* Black - 7 */
#define RED "\033[31m"     /* Red - 1*/
#define GREEN "\033[32m"   /* Green - 2*/
#define YELLOW "\033[33m"  /* Yellow - 3*/
#define BLUE "\033[34m"    /* Blue - 4*/
#define MAGENTA "\033[35m" /* Magenta - 5*/
#define CYAN "\033[36m"    /* Cyan - 6*/
static const char *colors[7] = {BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN};

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