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
        const auto m_queue_size = m_queue.size(); // Fix avoid getting size on every round
        int counter = 1;
        auto i = ++m_queue.begin(); // Fix iterating from second element
        while (counter<m_queue_size) // Fix index. Faster than iterator
        {
            const auto& val = *i; // Fix avoid copying twice
            if (val < min)
            {
                min = val;
                m_minIndex = counter;
            }
            ++i;
            ++counter;
        }
    }
    size_t len() const noexcept { return m_queue.size(); }
    void append(const T& item) { m_queue.emplace_back(item); m_minIndex = std::nullopt; }
    
private:
    std::vector<T> m_queue;
    std::optional<int> m_minIndex{};
};

