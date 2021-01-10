#ifndef UNTITLED_WORKER_THREAD_H
#define UNTITLED_WORKER_THREAD_H

#include "Thread.hpp"
#include "Game.hpp"
#include "TileJob.hpp"

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

class ThreadWorker : public Thread
{

    PCQueue<thread_tools> *jobs_base;
    thread_tools toolbox;

    void thread_workload() override;
    void reportFinished(double time);

public:
    ThreadWorker(uint thread_id, PCQueue<thread_tools> *jobs_base);
};

#endif