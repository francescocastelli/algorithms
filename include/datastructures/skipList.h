#include <memory>
#include <vector>
#include <random>

namespace datastruct 
{

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
                                        nexts (levels+1, nullptr)
        {}

        ListNode(const ListNode&) = delete;
        ListNode& operator=(const ListNode&) = delete;

        ListNode(ListNode&& n) = default; 
        ListNode& operator=(ListNode&& n) = default;

        ~ListNode() = default;

        int maxLevel() { return nexts.size() - 1; }

        int key;
        std::vector<ListNode*> nexts;
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
