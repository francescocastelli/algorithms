#include "skipList.h"
#include <iostream>

namespace datastruct 
{

SkipList::~SkipList()
{
    auto* curr = head;
    while (curr)
    {
        auto* next = curr->getNext(0);
        delete curr;
        curr = next;
    }
}

inline int SkipList::_pickLevel() 
{
    return dist(gen);
}

inline SkipList::ListNode* SkipList::_makeNode(const int key) 
{
    return new ListNode(key, _pickLevel()); 
}

bool SkipList::search(const int key) const
{
    if (!head)
        return false;

    if (head->key == key)
        return true;

    auto headLevel = head->maxLevel();
    auto* curr = head;
    for (auto i = headLevel; i >= 0; --i)
    {
        // move horizontally through list
        while (curr->getNext(i) && key > curr->getNext(i)->key)
           curr = curr->getNext(i);

        if (curr->getNext(i) && curr->getNext(i)->key == key)
            return true;
    }

    return false;
}

void SkipList::insert(const int key)
{
    auto* newNode = _makeNode(key);

    if (!head)
    {
        head = newNode;
        return;
    }

    auto headLevel = head->maxLevel();
    auto newLevel = newNode->maxLevel();

    // update the head if necessary
    if (key < head->key)
    {
        if (newLevel < headLevel)
            newNode->resize(headLevel);

        for (auto i = headLevel; i>=0; --i)
            newNode->setNext(head, i);
        
        head = newNode;
        return;
    }

    // resize the head next vector to handle new levels
    if (headLevel < newLevel)
        head->resize(newLevel);

    auto* curr = head;
    for (auto i = headLevel; i >= 0; --i)
    {
        // move horizontally through list
        while (curr->getNext(i) && key > curr->getNext(i)->key)
           curr = curr->getNext(i);

        // insert newNode in curr level
        if (newLevel >= i)
        {
            newNode->setNext(curr->getNext(i), i);
            curr->setNext(newNode, i);
        }
    }
}

void SkipList::print() const
{
    if (!head)
    {
        std::cout << "empty" << std::endl;
        return;
    }


    for (auto i = head->maxLevel(); i >= 0; --i)
    {
        auto* curr = head;
        while (curr)
        {
           std::cout << "|| k: " << curr->key << " || -> ";
           curr = curr->nexts[i];
        }

        std::cout << "nullptr" << std::endl;
    }

}

} // namespace datastruct
