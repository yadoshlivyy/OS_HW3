#include "GameTable.hpp"

GameTable::GameTable(const string &filename)
{
    vector<string> lines = utils::read_lines(filename);

    this->rows_num = lines.size();
    vector<string> first_line = utils::split(lines[0], ' ');
    this->columns_num = first_line.size();
    for (int i = 0; i < lines.size(); i++)
    {
        vector<string> line = utils::split(lines[i], ' ');
        vector<uint> row;
        for (const auto cell : line)
        {
            row.push_back(stoi(cell));
        }
        this->table.push_back(row);
    }
}

int GameTable::get_rows_num() const
{
    return this->rows_num;
}

int GameTable::get_columns_num() const
{
    return this->columns_num;
}
int GameTable::calculate_dominating(int x, int y) const
{
    int max = 0;
    int arr[7] = {0, 0, 0, 0, 0, 0, 0};
    if (cell_in_board_and_alive(x - 1, y - 1))
    {
        arr[table[x - 1][y - 1]] += 1;
    }
    if (cell_in_board_and_alive(x - 1, y))
    {
        arr[table[x - 1][y]] += 1;
    }
    if (cell_in_board_and_alive(x - 1, y + 1))
    {
        arr[table[x - 1][y + 1]] += 1;
    }
    if (cell_in_board_and_alive(x + 1, y - 1))
    {
        arr[table[x + 1][y - 1]] += 1;
    }
    if (cell_in_board_and_alive(x + 1, y))
    {
        arr[table[x + 1][y]] += 1;
    }
    if (cell_in_board_and_alive(x + 1, y + 1))
    {
        arr[table[x + 1][y + 1]] += 1;
    }
    if (cell_in_board_and_alive(x, y + 1))
    {
        arr[table[x][y + 1]] += 1;
    }
    if (cell_in_board_and_alive(x, y - 1))
    {
        arr[table[x][y - 1]] += 1;
    }
    for (int i = 0; i < 7; i++)
    {
        if (arr[i] * i > max)
        {
            max = arr[i] * i;
        }
        arr[i] = arr[i] * i;
    }
    for (int i=0; i < 7; i++)
    {
        if (arr[i] == max)
        {
            return i;
        }
    }
    return -1;
}
int GameTable::calculate_average(int x, int y) const
{
    int sum = table[x][y];
    int num = 1;
    if (cell_in_board_and_alive(x - 1, y - 1))
    {
        sum += table[x - 1][y - 1];
        num += 1;
    }
    if (cell_in_board_and_alive(x - 1, y))
    {
        sum += table[x - 1][y];
        num += 1;
    }
    if (cell_in_board_and_alive(x - 1, y + 1))
    {
        sum += table[x - 1][y + 1];
        num += 1;
    }
    if (cell_in_board_and_alive(x + 1, y - 1))
    {
        sum += table[x + 1][y - 1];
        num += 1;
    }
    if (cell_in_board_and_alive(x + 1, y))
    {
        sum += table[x + 1][y];
        num += 1;
    }
    if (cell_in_board_and_alive(x + 1, y + 1))
    {
        sum += table[x + 1][y + 1];
        num += 1;
    }
    if (cell_in_board_and_alive(x, y + 1))
    {
        sum += table[x][y + 1];
        num += 1;
    }
    if (cell_in_board_and_alive(x, y - 1))
    {
        sum += table[x][y - 1];
        num += 1;
    }
    
        return round(double(sum) / double(num));

}

int GameTable::cell_in_board_and_alive(int x, int y) const
{

    if (x >= rows_num || x < 0 || y < 0 || y >= columns_num)
    {
        return 0;
    }
    if (table[x][y])
    {
        return 1;
    }
    return 0;
}

int GameTable::cell_is_alive(int x, int y) const
{
    if (x < 0 || y < 0 || x >= rows_num || y >= columns_num)
    {
        throw std::invalid_argument("The cell is outside of the GameTable : x=" + std::to_string(x) + " y=" + std::to_string(y) + "\n");
    }
    int alive_neighbours = cell_in_board_and_alive(x - 1, y - 1) +
                           cell_in_board_and_alive(x - 1, y) +
                           cell_in_board_and_alive(x - 1, y + 1) +
                           cell_in_board_and_alive(x + 1, y - 1) +
                           cell_in_board_and_alive(x + 1, y) +
                           cell_in_board_and_alive(x + 1, y + 1) +
                           cell_in_board_and_alive(x, y - 1) +
                           cell_in_board_and_alive(x, y + 1);

    if (!table[x][y] && alive_neighbours == 3)
    {

        return calculate_dominating(x, y);
    }
    if (table[x][y] && (alive_neighbours == 2 || alive_neighbours == 3))
    {
        return table[x][y];
    }
    return 0;
}

ostream &operator<<(ostream &os, const GameTable &GameTable)
{
    int field_width = GameTable.columns_num;
    int field_height = GameTable.rows_num;
    os << u8"╔" << string(u8"═") * field_width << u8"╗" << endl;
    for (uint i = 0; i < field_height; ++i)
    {
        os << u8"║";
        for (uint j = 0; j < field_width; ++j)
        {
            if (GameTable.table[i][j] > 0)
                cout << colors[GameTable.table[i][j] % 7] << u8"█" << RESET;
            else
                cout << u8"░";
        }

        os << u8"║" << endl;
    }
    os << u8"╚" << string(u8"═") * field_width << u8"╝" << endl;
    return os;
}
