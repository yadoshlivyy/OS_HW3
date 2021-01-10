#include "Semaphore.hpp"

Semaphore::Semaphore() : value(0)
{
    if (pthread_cond_init(&condition, NULL) != 0)
    {
        cout << "unsucesfull condition initizlization" << endl;
    }
    if (pthread_mutex_init(&mutex, NULL) != 0)
    {
        cout << "unsucesfull mutex initizlization" << endl;
    }
    else
    {
        cout << "semaphore successfully created" << endl;
    }
}
Semaphore::Semaphore(unsigned val) : value(val)
{
    if (pthread_cond_init(&condition, NULL) != 0)
    {
        cout << "unsucesfull condition initizlization" << endl;
    }
    if (pthread_mutex_init(&mutex, NULL) != 0)
    {
        cout << "unsucesfull mutex initizlization" << endl;
    }
    else
    {
        cout << "semaphore successfully created" << endl;
    }
}
void Semaphore::up()
{
    MUTEX_LOCK(mutex);
    value++;
    if (value <= 0)
    {
        COND_SIGNAL(condition);
    }

    MUTEX_UNLOCK(mutex);
}
void Semaphore::down()
{
    MUTEX_LOCK(mutex);
    while (value < 0)
    {
        WAIT(condition, mutex);
    }
    value--;
    MUTEX_UNLOCK(mutex);
}