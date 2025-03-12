//
// Place Holder Copyright Header
//

#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <thread>
#include <queue>
#include <vector>


using namespace std;


/// <summary>
/// Boiler-plate thread pool class for running various tasks in parallel. Parallelized tasks
/// will be added to a queue for the next available thread to grab and execute.
/// 
/// Can be initialized with custom thread count (pool size); otherwise, it will default to 
/// using the "hardware optimal" number of threads as defined by thread::hardware_concurrency.
/// </summary>
class ThreadPool
{
public:
    ThreadPool(size_t threadCount = thread::hardware_concurrency());
    ~ThreadPool();

    void queueTask(function<void()> task);
    void waitForCompletion();

private:
    vector<thread> m_pool;              // vector pool of threads
    queue<function<void()>> m_tasks;    // queue of tasks 

    mutex m_queueMutex;                 // mutex used to take/add tasks to the queue
    condition_variable m_taskPresent;   // condition threads wait on until notified of a task to execute
    condition_variable m_complete;      // condition used to notify when there are no more active tasks in the queue
    bool m_stop;                        // flag used to tell threads to end and close
    atomic<size_t> m_activeTasks;       // keeps track of number of active tasks

    void workerThread();
};


#endif // THREAD_POOL_H
