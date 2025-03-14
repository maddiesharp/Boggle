//
// Place Holder Copyright Header
//

#include <cassert>

#ifdef _DEBUG
#include <iostream>
#endif

#include "ThreadPool.h"


using namespace std;


/// <summary>
/// Class constructor that initializes the thread pool. The size of the pool
/// is based on the provided thread count argument. This argument is optional.
/// If no arg is provided, it will default to the "hardware optimal" quantity
/// as defined by thread::hardware_concurrency.
/// </summary>
/// <param name="threadCount">optional param that specifies number of threads to create in the pool</param>
ThreadPool::ThreadPool(size_t threadCount) :
    m_pool(),
    m_tasks(),
    m_queueMutex(),
    m_cv(),
    m_stop(false)
{
    assert(threadCount > 0);

    #ifdef _DEBUG
        cout << "Thread pool size: " << threadCount << " threads.\n";
    #endif

    for (auto i = 0; i < threadCount; i++)
    {
        m_pool.emplace_back([this](){
            this->workerThread();
        });
    }
}


/// <summary>
/// Class destructor tha sets the stop flag and notifies all threads to finish. 
/// Once the threads have finished, it then joins all the threads to close them.
/// </summary>
ThreadPool::~ThreadPool()
{
    {
        lock_guard<mutex> lock(m_queueMutex);
        m_stop = true;
    }

    // notify all threads to stop and shut down
    m_cv.notify_all();

    // wait for all threads in the pool to finish and close them
    for (auto& thread : m_pool)
    {
        thread.join();
    }
}


/// <summary>
/// Adds the provided task to the queue for the next available thread
/// to take and execute. Once the task is moved to the queue, a notification
/// is sent out to a single thread waiting on the condition_variable m_cv.
/// </summary>
/// <param name="task">Lambda/function to execute</param>
void ThreadPool::queueTask(function<void()> task)
{
    {
        lock_guard<mutex> lock(m_queueMutex);
        m_tasks.push(move(task));
    }

    // notify a single thread that a task is ready to be processed
    m_cv.notify_one();
}


/// <summary>
/// Generic worker thread that is available in the overall thread pool. 
/// Waits until the mutex lock is acquired and there is an active task (or stop
/// request) to process.
/// </summary>
void ThreadPool::workerThread()
{
    while (true)
    {
        function<void()> task;

        // scoping block for mutex locks
        {
            // attempt/wait for access to the tasks queue
            unique_lock<mutex> lock(m_queueMutex);
            m_cv.wait(lock, [this] { return m_stop || !m_tasks.empty(); });

            // if signalled to stop and tasks are empty, close this worker
            if(m_stop && m_tasks.empty()) return;

            // acquire the next task and remove it from the queue
            task = move(m_tasks.front());
            m_tasks.pop();
        }

        task();
    }
}
