#include "TileJob.hpp"

void TileJob::fill_new_tile_job()
{
    int min_x = start_row;
    int max_x = end_row;
    int min_y = 0;
    int max_y = old_table->get_columns_num();
    for (int i = min_x; i <= max_x; i++)
    {
        for (int j = min_y; j < max_y; j++)
        {
            try
            {
                this->new_table->table[i][j] = this->old_table->cell_is_alive(i, j);
            }
            catch (std::exception &e)
            {
                printf("%s", e.what());
            }
        }
    }
    
}
