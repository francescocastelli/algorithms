#include "skipList.h"

namespace datastruct 
{

int SkipList::_pickLevel()
{
    return dist(gen);
}

SkipList::ListNode* SkipList::_makeNode(int key)
{
    return new ListNode(key, _pickLevel());
}

void SkipList::insert(int key)
{
    auto* newNode = _makeNode(key);
    auto newLevel = newNode->maxLevel;

    if ( !head )
    {
        head = newNode;
        return;
    }

    // resize the head next vector to handle new levels
    if ( head->maxLevel < newLevel )
    {
        head->nexts.resize(newLevel+1, nullptr);
    }

    auto currLevel = head->maxLevel;
    auto* curr = head;

    for (auto i = currLevel; i > 0; --i)
    {
        // move horizontally through list
        while ( curr->nexts[currLevel] && key > curr->nexts[currLevel]->key )
        {
           curr = curr->nexts[currLevel];
        }

        // insert newNode in curr level
        if (newLevel >= currLevel)
        {
            newNode->nexts[currLevel] = curr->nexts[currLevel];
            curr->nexts[currLevel] = newNode;
        }
    }
}

} // namespace datastruct
