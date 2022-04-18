#include <memory>
#include <vector>
#include <random>

namespace datastruct 
{

class SkipList 
{
public:
    SkipList() : head (nullptr), 
                 rd (),
                 gen (rd()), 
                 dist (_prob)
    {}

    ~SkipList();

    bool search(int key);
    void insert(int key);
    void print();

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

    ListNode* _makeNode(int key);
    int _pickLevel();

    ListNode* head;

    static constexpr auto _prob = 0.5;
    std::random_device rd;
    std::mt19937 gen;
    std::geometric_distribution<> dist;
};

} // namespace datastruct
