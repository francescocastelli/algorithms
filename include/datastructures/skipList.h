#include <memory>
#include <vector>

namespace datastruct 
{

class SkipList 
{
public:
    SkipList() : head (nullptr) {}

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
};

} // namespace datastruct
