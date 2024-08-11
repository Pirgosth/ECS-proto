#ifndef SOFTDELETECONTAINER_H_INCLUDED
#define SOFTDELETECONTAINER_H_INCLUDED

#include <vector>

template <typename T>
class SoftDeleteContainer
{
private:
    unsigned int m_elementCount;
    std::vector<T> m_elementsBuffer;
    std::vector<unsigned int> m_elements;

    unsigned int m_lastElementErased;
    unsigned int m_erasedCount;

public:
    SoftDeleteContainer();
    unsigned int push_back(T value);
    bool erase(unsigned int index);
    unsigned int size();
    bool isAlive(unsigned int index);
    std::vector<T> getElements();
};

template <typename T>
inline SoftDeleteContainer<T>::SoftDeleteContainer() : m_elementCount(0), m_lastElementErased(0), m_erasedCount(0) {}

template <typename T>
inline unsigned int SoftDeleteContainer<T>::push_back(T value)
{
    if (m_erasedCount > 0)
    {
        auto insertedId = m_lastElementErased;
        m_elementsBuffer[insertedId] = value;
        
        m_lastElementErased = m_elements[m_lastElementErased];
        m_elements[insertedId] = insertedId;
        --m_erasedCount;

        return insertedId;
    }
    else
    {
        auto insertedId = m_elementCount++;
        m_elements.push_back(insertedId);
        m_elementsBuffer.push_back(std::move(value));

        return insertedId;
    }    
}

template <typename T>
inline bool SoftDeleteContainer<T>::erase(unsigned int index)
{
    if (index >= m_elements.size())
        return false;

    if (m_erasedCount != 0)
    {
        m_elements[index] = m_lastElementErased;
        m_elements[m_lastElementErased] = index;
    }

    m_lastElementErased = index;
    m_erasedCount++;

    return true;
}

template <typename T>
inline unsigned int SoftDeleteContainer<T>::size()
{
    return m_elements.size();
}

template <typename T>
inline bool SoftDeleteContainer<T>::isAlive(unsigned int index)
{
    return m_erasedCount == 0 || (m_lastElementErased != index && m_elements[index] == index);
}

template <typename T>
inline std::vector<T> SoftDeleteContainer<T>::getElements()
{
    std::vector<T> aliveElements;
    auto erasedHead = m_lastElementErased;
    auto remainingErased = m_erasedCount;
    for (unsigned int i = 0; i < m_elements.size(); i++)
    {
        if (remainingErased > 0 && erasedHead == i)
        {
            --remainingErased;
            erasedHead = m_elements[erasedHead];
            continue;
        }

        aliveElements.push_back(m_elementsBuffer[i]);
    }

    return aliveElements;
}

#endif // SOFTDELETECONTAINER_H_INCLUDED
