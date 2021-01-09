#ifndef _GLOBAL_H
#define _GLOBAL_H
/*--------------------------------------------------------------------------------
										Libraries
--------------------------------------------------------------------------------*/
// Data Structures:
#include <vector>
#include <string>
#include <queue>
#include <list>
#include <iterator>

// Streams  & Filesystem:
#include <fstream>
#include <iostream>
#include <sstream>

// Utility:
#include <cmath>
#include <cassert>
#include <chrono>
#include <algorithm>
#include <numeric>
#include <unistd.h>

// Threads & Synchronization:
#include <pthread.h>

/*--------------------------------------------------------------------------------
									   Typedefs
--------------------------------------------------------------------------------*/
using std::queue;
using std::string;
using std::vector;

using std::cerr;
using std::cout;
using std::endl;
using std::fstream;
using std::ifstream;
using std::istringstream;
using std::ostream;
using std::chrono::time_point;

typedef unsigned int uint;
typedef vector<vector<uint>> int_mat; // Use this as your Game Field

/*--------------------------------------------------------------------------------
								  Defines & Macros
--------------------------------------------------------------------------------*/

// our
#define MUTEX_LOCK(lock) pthread_mutex_lock(&(lock))
#define MUTEX_UNLOCK(lock) pthread_mutex_unlock(&(lock))
#define WAIT(cond, lock) pthread_cond_wait(&(cond), &(lock))
#define COND_SIGNAL(cond) pthread_cond_signal(&(cond))
#define COND_BROADCAST(cond) pthread_cond_broadcast(&(cond))

#define PRINT_BOARD true					// Boolean flag - Responsible for controling whether the board is printed or not
#define GEN_SLEEP_USEC 300000				// Default : 300000. The approximate time the board is displayed each generation in micro-seconds
#define DEF_MAT_DELIMITER ' '				// The seperator betweens 0s and 1s in your matrix input file
#define DEF_RESULTS_FILE_NAME "results.csv" // The filename of the results

// Macros - For your comfort
#define DEBUG 1
#define DEBUG_MES(mes) \
	if (DEBUG)         \
		cout << mes << endl;
#define user_error(mes, exp)              \
	if (!exp)                             \
	{                                     \
		cerr << "Fatal: " << mes << endl; \
		exit(1);                          \
	}

#endif
