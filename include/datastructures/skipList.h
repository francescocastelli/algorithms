#include <memory>
#include <random>
#include <cstring>
#include <assert.h>

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


struct Chunk 
{
    void init(std::size_t blockSize, unsigned char blocks)
    {
        pData_ = new unsigned char[blockSize * blocks];
        firstAvailableBlock_ = 0;
        blocksAvailable_ = blocks;
        unsigned char i = 0;
        unsigned char* p = pData_;
        for(; i != blocks; p += blockSize)
            *p = ++i;
    }

    void* allocate(std::size_t blockSize)
    {
        if (!blocksAvailable_) return 0;
        auto* pResult = 
            pData_ + (firstAvailableBlock_ * blockSize);
        firstAvailableBlock_ = *pResult;
        --blocksAvailable_;
        return pResult;
    }

    void deallocate(void* p, std::size_t blockSize)
    {
        assert(p >= pData_);
        auto* toRelease = static_cast<unsigned char*>(p);
        assert((toRelease - pData_) % blockSize == 0);
        *toRelease = firstAvailableBlock_;
        firstAvailableBlock_ = static_cast<unsigned char>(
                (toRelease - pData_) / blockSize);
        assert(firstAvailableBlock_ == (toRelease - pData_) / blockSize);
        ++blocksAvailable_;
    }


    void release()
    {
        delete[] pData_;
        firstAvailableBlock_ = 0;
        blocksAvailable_ = 0;
    }

    unsigned char* pData_;
    unsigned char 
        firstAvailableBlock_,
        blocksAvailable_;
};

class FixedAllocator 
{
public:
    void* allocate()
    {
        if(!allocChunk_ || allocChunk_->blocksAvailable_ == 0)
        {
            auto i = chunks_.begin();
            for(;; ++i)
            {
                 if (i == chunks_.end())
                 {
                     chunks_.reserve(chunks_.size()+1);
                     Chunk newChunk;
                     newChunk.init(blockSize_, numBlocks_);
                     chunks_.push_back(newChunk);
                     allocChunk_ = &chunks_.back();
                     deallocChunk_ = &chunks_.back();
                     break;
                 }
                 if (i->blocksAvailable_ > 0)
                 {
                     allocChunk_ = &*i;
                     break;
                 }
            }
        }
        return allocChunk_->allocate(blockSize_);
    }

    void deallocate(void* p)
    {
        assert(chunks_.size() > 0);

        if (!deallocChunk_)
        {
            deallocChunk_ = allocChunk_;
        }
        if (!owns(deallocChunk_, p))
        {
            auto left = chunks_.begin() + (deallocChunk_ - &chunks_[0]);
            auto right = chunks_.begin() + (deallocChunk_ - &chunks_[0]);

            for(;; --left, ++right)
            {
                // the pointer is not coming from a chunk in this allocator
                if (left < chunks_.begin() && right > chunks_.end())
                {
                    return;
                }
                if (owns(&*left, p))
                {
                    deallocChunk_ = &*left;
                    break;
                }
                if (owns(&*right, p))
                {
                    deallocChunk_ = &*right;
                    break;
                }
            }
        }

        deallocChunk_->deallocate(p, blockSize_);

        // check if chunk is empty
        if (deallocChunk_->blocksAvailable_ == 0)
        {
            if (chunks_.back().blocksAvailable_ == 0)
            {
                chunks_.pop_back();
                return;
            }
            
            std::swap(*deallocChunk_, chunks_.back());
            deallocChunk_ = nullptr;
        }
    }

    void release()
    {
        for(auto& c : chunks_)
        {
            c.release();
        }
    }

private:
    bool owns(Chunk* c, void* p)
    {
        return p > c->pData_ && 
               p < c->pData_ + blockSize_ * numBlocks_; 
    }

    std::size_t blockSize_;
    unsigned char numBlocks_;
    using Chunks = std::vector<Chunk>;
    Chunks chunks_;
    Chunk* allocChunk_;
    Chunk* deallocChunk_;
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
    static constexpr auto _prob = 0.5;
    std::random_device rd;
    std::mt19937 gen;
    std::geometric_distribution<> dist;
};

} // namespace datastruct
