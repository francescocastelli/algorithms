#include "datastructures.h"

int main()
{
	datastruct::RandomTreap treap;

	treap.insert(1);
	treap.insert(2);
	treap.insert(3);
	treap.insert(8);
	treap.insert(9);
	treap.insert(10);
	treap.insert(11);
	treap.print();
	std::cout << treap.search(1000);
}
