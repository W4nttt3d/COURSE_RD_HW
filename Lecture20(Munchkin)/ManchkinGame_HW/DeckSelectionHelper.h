#pragma once
#include <vector>
#include <algorithm>
#include <random>

template <typename T>
class DeckSelectionHelper
{
public:
    DeckSelectionHelper(const std::vector<T*>& database) : m_Database(database), m_randomEngine(std::random_device{}())
    {
        reset();
    }

    T* generate()
    {
        if (m_Used.empty())
        {
            reset();
        }

        T* result = m_Used.back();
        m_Used.pop_back();

        return result;
    }

private:
    void reset()
    {
        m_Used = m_Database;
        std::shuffle(m_Used.begin(), m_Used.end(), m_randomEngine);
    }

    std::vector<T*> m_Database;
    std::vector<T*> m_Used;
    std::default_random_engine m_randomEngine;
};
