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

    void insert(int key);

private:
    struct ListNode 
    {
        ListNode(int key, int levels) : key (key),
                                       maxLevel (levels),
                                       nexts (levels, nullptr)
        {}

        ListNode(const ListNode&) = delete;
        ListNode& operator=(const ListNode&) = delete;

        ListNode(ListNode&& n) = default; 
        ListNode& operator=(ListNode&& n) = default;

        ~ListNode() = default;

        int key;
        int maxLevel;
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
