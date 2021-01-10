

#ifndef __UNTITLED_WORKER_THREAD_H
#define __UNTITLED_WORKER_THREAD_H
#include "Game.hpp"
#include "Thread.hpp"

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
