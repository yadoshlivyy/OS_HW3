#include "Game.hpp"

/*--------------------------------------------------------------------------------
								
--------------------------------------------------------------------------------*/
void Game::run()
{
	if (game_is_running_now)
	{
		//TODO comment change
		return;
	}
	_init_game(); // Starts the threads and all other variables you need
	print_board("Initial Board");
	for (uint i = 0; i < m_gen_num; ++i)
	{
		auto gen_start = std::chrono::system_clock::now();
		_step(i); // Iterates a single generation
		auto gen_end = std::chrono::system_clock::now();
		m_gen_hist.push_back((double)std::chrono::duration_cast<std::chrono::microseconds>(gen_end - gen_start).count());
		print_board(nullptr);
	} // generation loop
	print_board("Final Board");
	game_is_running_now = false;
	_destroy_game();
}

Game::Game(game_params param) : jobs(), report_mutex(1), workers_report(), m_tile_hist(), m_gen_hist(), m_threadpool(), prev(nullptr), next(nullptr)
{
	filename = param.filename;
	m_gen_num = param.n_gen;
	interactive_on = param.interactive_on;
	print_on = param.print_on;
	game_is_running_now = false;
	m_thread_num_tmp = param.n_thread;
}

const vector<double> Game ::gen_hist() const
{
	return m_gen_hist;
}

const vector<double> Game ::tile_hist() const
{
	return m_tile_hist;
}

uint Game::thread_num() const
{
	if (m_thread_num_tmp >= prev->get_rows_num())
	{
		return prev->get_rows_num();
	}
	return m_thread_num_tmp;
}
void Game::_init_game()
{
	if (game_is_running_now)
	{
		return;
	}
	prev = new GameTable(filename);
	next = new GameTable(*prev);
	m_thread_num = thread_num();
	for (int i = 0; i < m_thread_num; i++)
	{
		auto newWorker = new ThreadWorker(i, &jobs);
		m_threadpool.push_back(newWorker);
	}
	for (auto worker : m_threadpool)
	{
		worker->start();
	}
	game_is_running_now = true;
}

void Game::_step(uint curr_gen)
{
	if (!game_is_running_now)
	{
		return;
	}
	int rowsForEach = prev->get_rows_num() / m_thread_num;
	int currRow = 0, reported = 0, nextRow = 0;
	thread_tools toolbox = {&workers_report, &reported, m_thread_num, false, &m_tile_hist, &report_mutex};
	for (int i = 0; i < m_thread_num; i++)
	{
		nextRow = currRow + rowsForEach;
		//in case it is the last iteration, we need to add the rest of the raws, if there is any
		if (i == m_thread_num - 1)
		{
			nextRow += prev->get_rows_num() - (rowsForEach * m_thread_num);
		}
		TileJob tile(prev, next, currRow, nextRow - 1,1);
		toolbox.tile = tile;
		jobs.push(toolbox);
		currRow = nextRow;
	}
	//wait for workers to finish
	workers_report.down();

	GameTable *tmp = prev;
	prev = next;
	next = tmp;
}

void Game::_destroy_game()
{
	if (!game_is_running_now)
	{
		return;
	}
	for (int i = 0; i < m_thread_num - 1; i++)
	{
		thread_tools toolbox;
		toolbox.suicide = true;
		jobs.push(toolbox);
	}
	for (uint i = 0; i < m_thread_num; ++i)
	{
		m_threadpool[i]->join();
	}
	delete next;
	delete prev;
	for (auto worker : m_threadpool)
	{
		delete worker;
	}
}

/*--------------------------------------------------------------------------------
								
--------------------------------------------------------------------------------*/
inline void Game::print_board(const char *header)
{

	if (print_on)
	{

		// Clear the screen, to create a running animation
		if (interactive_on)
			system("clear");

		// Print small header if needed
		if (header != nullptr)
			cout << "<------------" << header << "------------>" << endl;

		cout << *prev;

		// Display for GEN_SLEEP_USEC micro-seconds on screen
		if (interactive_on)
			usleep(GEN_SLEEP_USEC);
	}
}

/* Function sketch to use for printing the board. You will need to decide its placement and how exactly 
	to bring in the field's parameters. 

		cout << u8"╔" << string(u8"═") * field_width << u8"╗" << endl;
		for (uint i = 0; i < field_height ++i) {
			cout << u8"║";
			for (uint j = 0; j < field_width; ++j) {
                if (field[i][j] > 0)
                    cout << colors[field[i][j] % 7] << u8"█" << RESET;
                else
                    cout << u8"░";
			}
			cout << u8"║" << endl;
		}
		cout << u8"╚" << string(u8"═") * field_width << u8"╝" << endl;
*/
