#ifndef _QUEUEL_H
#define _QUEUEL_H
#include "Headers.hpp"
#include "Semaphore.hpp"

// Single Producer - Multiple Consumer queue
template <typename T>
class PCQueue
{

public:
    // Blocks while queue is empty. When queue holds items, allows for a single
    // thread to enter and remove an item from the front of the queue and return it.
    // Assumes multiple consumers.
    T pop();

    // Allows for producer to enter with *minimal delay* and push items to back of the queue.
    // Hint for *minimal delay* - Allow the consumers to delay the producer as little as possible.
    // Assumes single producer
    void push(const T &item);

private:
    queue<T> queue_pc;
    pthread_mutex_t lock;
    pthread_cond_t condition;
    bool writer_inside = false;
    Semaphore token;
    // Add your class memebers here
};
template <typename T>
void PCQueue<T>::push(const T &item)
{
    writer_inside = true;
    MUTEX_LOCK(lock);
    queue_pc.push(item);
    writer_inside = false;
    COND_BROADCAST(condition);
    MUTEX_UNLOCK(lock);
    token.up();
}

template <typename T>
T PCQueue<T>::pop()
{
    T return_value;
    token.down();

    MUTEX_LOCK(lock);
    while (writer_inside)
    {
        WAIT(condition, lock);
    }
    return_value = queue_pc.front();
    queue_pc.pop();
    MUTEX_UNLOCK(lock);
    return return_value;
}
#endif