#include <memory>
#include <random>
#include <cstring>

namespace datastruct 
{

namespace {

template<typename T> 
class NodePtrVect;

template<typename T>
class NodePtrVect<T*>
{
public:
    NodePtrVect(int size) : _size (size) 
    {
        arr = new T*[size]{};
    }

    NodePtrVect(const NodePtrVect&) = delete;
    NodePtrVect& operator=(const NodePtrVect&) = delete;

    NodePtrVect(NodePtrVect&& n) = default; 
    NodePtrVect& operator=(NodePtrVect&& n) = default;

    ~NodePtrVect()
    {
        delete[] arr;
    }

    inline T*& operator[](int index) 
    {
        return arr[index];
    }

    void resize(int newSize) 
    {
        auto* _arr = new T*[newSize]{};
        std::memcpy(_arr, arr, _size * sizeof(T*));
        delete[] arr;
        _size = newSize;
        arr = _arr;
    }

    inline int size() const
    {
        return _size;
    }

private:
    int _size;
    T** arr;
};

}

class SkipList 
{
public:
    SkipList() : head (nullptr), 
                 gen (rd()), 
                 dist (_prob)
    {}

    ~SkipList();

    bool search(const int key) const;
    void insert(const int key);
    void print() const;

private:
    struct ListNode 
    {
        ListNode(int key, int levels) : key (key),
                                        nexts (levels+1)
        {}

        ListNode(const ListNode&) = delete;
        ListNode& operator=(const ListNode&) = delete;

        ListNode(ListNode&& n) = default; 
        ListNode& operator=(ListNode&& n) = default;

        ~ListNode() = default;

        inline ListNode* getNext(int level) { return nexts[level]; }
        inline void setNext(ListNode* nodePtr, int level) { nexts[level] = nodePtr; }
        inline void resize(int newLevel) { nexts.resize(newLevel + 1); }
        inline int maxLevel() { return nexts.size() - 1; }

        int key;
        NodePtrVect<ListNode*> nexts;
    };

    using ListNodePtr = ListNode*;

    ListNodePtr _makeNode(const int key);
    int _pickLevel();

    // head points always to max level
    ListNodePtr head;

    // random utils
    static constexpr auto _prob = 0.6;
    std::random_device rd;
    std::mt19937 gen;
    std::geometric_distribution<> dist;
};

} // namespace datastruct
