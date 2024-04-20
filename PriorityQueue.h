#pragma once
#include <vector>
#include <optional>

template <typename T>
class PriorityQueue
{
public:
    std::optional<T> min() 
    { 
        if (len() == 0) 
            return std::nullopt; 
        FindMin();
        return m_queue[m_minIndex.value()];
    }
    std::optional<T> pop()
    {
        if (len() == 0)
            return std::nullopt;
        T ret = m_queue[m_minIndex.value()];
        m_queue.erase(m_queue.begin() + m_minIndex.value());
        m_minIndex = std::nullopt;
        return ret;
    }
    void FindMin()
    {
        if (m_minIndex.has_value())
            return;
        auto min = m_queue[0];
        m_minIndex = 0;
        for (int i = 1; i < m_queue.size(); ++i)
        {
            auto val = m_queue[i];
            if (val < min)
            {
                min = val;
                m_minIndex = i;
            }
        }
    }
    size_t len() const noexcept { return m_queue.size(); }
    void append(const T& item) { m_queue.emplace_back(item); m_minIndex = std::nullopt; }
    
private:
    std::vector<T> m_queue;
    std::optional<int> m_minIndex{};
};

