#include "../include/datastructures.h"

int main()
{
	datastruct::RandomTreap treap;


	for ( int i = 0; i < 15 ; ++i)
		treap.insert(i);

	treap.print();
	std::cout << int(treap.search(15));
	treap.remove(10);
	treap.print();
	treap.remove(10);
	treap.print();
	treap.remove(2);
	treap.print();
	treap.remove(13);
	treap.print();
	treap.remove(1);
	treap.print();
	treap.remove(14);
	treap.print();
}
