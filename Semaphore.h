#pragma once

#include <mutex>
#include <condition_variable>

class Semaphore
{
public:
    Semaphore(const int nSize) : m_Count(nSize) {}

    void up()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        ++m_Count;
        m_CV.notify_one();
    }

    void down()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        while (m_Count == 0)
        {
            m_CV.wait(lock);
        }
        --m_Count;
    }

private:
    std::condition_variable m_CV;
    std::mutex m_mutex;
    int m_Count;
};

