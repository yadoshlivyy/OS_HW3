#include "Semaphore.hpp"

Semaphore::Semaphore() : value(1) { ; }
Semaphore::Semaphore(unsigned val) : value(val) { ; }
void Semaphore::up()
{
    pthread_mutex_lock(&(mutex));
    value++;
    pthread_cond_broadcast(&(condition));
    pthread_mutex_unlock(&(mutex));
}
void Semaphore::down()
{
    pthread_mutex_lock(&(mutex));
    while (value == 0)
    {
        pthread_cond_wait(&(condition), &(mutex));
    }
    value--;
    pthread_mutex_unlock(&(mutex));
}