#include "PCQueue.hpp"



template <typename T>
void PCQueue<T>::push(const T &item)
{
    writer_inside = true;
    MUTEX_LOCK(lock);
    queue.push(item);
    writer_inside = false;
    COND_BROADCAST(condition);
    MUTEX_UNLOCK(lock);
    token.up();
}

template <typename T>
T PCQueue<T>::pop()
{
    token.down();
    T return_value;
    MUTEX_LOCK(lock);
    while (writer_inside)
    {
        WAIT(condition, lock);
    }
    return_value = queue.front();
    queue.pop();
    MUTEX_UNLOCK(lock);
    return return_value;
}