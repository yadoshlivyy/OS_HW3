#ifndef __GAMERUN_H
#define __GAMERUN_H
#include "../Part1/Headers.hpp"
#include "../Part1/Semaphore.hpp"
#include "../Part1/PCQueue.hpp"
#include "Thread.hpp"
#include "TileJob.hpp"
#include "GameTable.hpp"

/*--------------------------------------------------------------------------------
								  Species colors
------------------------------------------
--------------------------------------*/
// #define RESET "\033[0m"
// #define BLACK "\033[30m"   /* Black - 7 */
// #define RED "\033[31m"	   /* Red - 1*/
// #define GREEN "\033[32m"   /* Green - 2*/
// #define YELLOW "\033[33m"  /* Yellow - 3*/
// #define BLUE "\033[34m"	   /* Blue - 4*/
// #define MAGENTA "\033[35m" /* Magenta - 5*/
// #define CYAN "\033[36m"	   /* Cyan - 6*/
// static const char *colors[7] = {BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN};
/*--------------------------------------------------------------------------------
								  Auxiliary Structures
--------------------------------------------------------------------------------*/

struct game_params
{
	// All here are derived from ARGV, the program's input parameters.
	uint n_gen;
	uint n_thread;
	string filename;
	bool interactive_on;
	bool print_on;
};
// all the info that thread need to execute task correctly
struct thread_tools
{
	Semaphore *report_alert;
	int *reported_workers;
	uint num_of_workers;
	bool suicide;
	vector<double> *tile_hist;
	Semaphore *report_lock;
	TileJob tile;
};
/*--------------------------------------------------------------------------------
									Class Declaration
--------------------------------------------------------------------------------*/
// incapsulation of thread logic
class ThreadWorker : public Thread
{

	PCQueue<thread_tools> *jobs;
	thread_tools toolbox;

	void thread_workload() override
	{
		while (true)
		{
			toolbox = jobs->pop();

			if (toolbox.suicide)
			{
				break;
			}
			auto work_start = std::chrono::system_clock::now();
			toolbox.tile.fill_new_tile_job();
			auto work_end = std::chrono::system_clock::now();
			jobFinishedAlert((double)std::chrono::duration_cast<std::chrono::microseconds>(work_end - work_start).count());
		}
	}

	void jobFinishedAlert(double time)
	{
		toolbox.report_lock->down();
		*toolbox.reported_workers += 1;
		if (*toolbox.reported_workers == toolbox.num_of_workers)
		{
			toolbox.report_alert->up();
		}
		toolbox.tile_hist->push_back(time);
		toolbox.report_lock->up();
	};

public:
	ThreadWorker(uint thread_id, PCQueue<thread_tools> *jobs) : Thread(thread_id), jobs(jobs){};
};

class Game
{
public:
	Game(game_params);
	~Game() = default;
	void run();								// Runs the game
	const vector<double> gen_hist() const;	// Returns the generation timing histogram
	const vector<double> tile_hist() const; // Returns the tile timing histogram
	uint thread_num() const;				//Returns the effective number of running threads = min(thread_num, field_height)

protected: // All members here are protected, instead of private for testing purposes
	// See Game.cpp for details on these three functions
	void _init_game();
	void _step(uint curr_gen);
	void _destroy_game();
	inline void print_board(const char *header);

	uint m_gen_num;				   // The number of generations to run
	uint m_thread_num;			   // Effective number of threads = min(thread_num, field_height)
	vector<double> m_tile_hist;	   // Shared Timing history for tiles: First (2 * m_gen_num) cells are the calculation durations for tiles in generation 1 and so on.
								   // Note: In your implementation, all m_thread_num threads must write to this structure.
	vector<double> m_gen_hist;	   // Timing history for generations: x=m_gen_hist[t] iff generation t was calculated in x microseconds
	vector<Thread *> m_threadpool; // A storage container for your threads. This acts as the threadpool.

	bool interactive_on; // Controls interactive mode - that means, prints the board as an animation instead of a simple dump to STDOUT
	bool print_on;		 // Allows the printing of the board. Turn this off when you are checking performance (Dry 3, last question)

	
	bool game_is_running_now;
	uint temp_value_thread_num;
	string filename;
	GameTable *prev;
	GameTable *next;
	PCQueue<thread_tools> jobs;
	Semaphore mutex_report;
	Semaphore workers_mutex;
};
#endif
