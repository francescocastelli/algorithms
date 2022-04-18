#include "skipList.h"
#include <iostream>

namespace datastruct 
{

SkipList::~SkipList()
{
    auto* curr = head;
    while (curr)
    {
        auto* next = curr->nexts[0];
        delete curr;
        curr = next;
    }
}

int SkipList::_pickLevel()
{
    return dist(gen);
}

SkipList::ListNode* SkipList::_makeNode(int key)
{
    return new ListNode(key, _pickLevel()); 
}

bool SkipList::search(int key)
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
        while (curr->nexts[i] && key > curr->nexts[i]->key)
           curr = curr->nexts[i];

        if (curr->nexts[i] && curr->nexts[i]->key == key)
            return true;
    }

    return false;
}

void SkipList::insert(int key)
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
            newNode->nexts.resize(headLevel + 1, nullptr);

        for (auto i = headLevel; i>=0; --i)
            newNode->nexts[i] = head;
        
        head = newNode;
        return;
    }

    // resize the head next vector to handle new levels
    if (headLevel < newLevel)
        head->nexts.resize(newLevel + 1, nullptr);

    auto* curr = head;
    for (auto i = headLevel; i >= 0; --i)
    {
        // move horizontally through list
        while (curr->nexts[i] && key > curr->nexts[i]->key)
           curr = curr->nexts[i];

        // insert newNode in curr level
        if (newLevel >= i)
        {
            newNode->nexts[i] = curr->nexts[i];
            curr->nexts[i] = newNode;
        }
    }
}

void SkipList::print()
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
