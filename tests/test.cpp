#include "../include/datastructures.h"

int main()
{
	datastruct::RandomTreap treap;


	for ( int i = 0; i < 15 ; ++i)
		treap.insert(i);

	treap.print();
	std::cout << int(treap.search(15));
}
