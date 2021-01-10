#include "ThreadWorker.hpp"

// ThreadWorker ::ThreadWorker(uint thread_id, PCQueue<thread_tools> *jobs_base) : Thread(thread_id), jobs_base(jobs_base) {}

// void ThreadWorker ::thread_workload()
// {
//     while (true)
//     {
//         toolbox = jobs_base->pop();
//         if (toolbox.suicide)
//         {
//             break;
//         }
//         auto work_start = std::chrono::system_clock::now();
//         toolbox.tile.fill_new_tile_job();
//         auto work_end = std::chrono::system_clock::now();
//         reportFinished((double)std::chrono::duration_cast<std::chrono::microseconds>(work_end - work_start).count());
//     }
// }

void ThreadWorker ::reportFinished(double time)
{
    toolbox.report_lock->down();
    *toolbox.reported_workers += 1;
    if (*toolbox.reported_workers == toolbox.num_of_workers)
    {
        toolbox.report_alert->up();
    }
    toolbox.tile_hist->push_back(time);
    toolbox.report_lock->up();
}