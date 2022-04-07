#include <memory>

namespace datastruct 
{
class RandomTreap
{
/* RandomTreaps are binary trees with two property:
* 		1. symmetric prop for the keys
* 		2. heap prop for the priorities
*
* 	so it's a bst wrt to the keys and nodes are also 
* 	ordered based on the priority values 
* 	( if x = parent(y) -> prior(x) < prior(y) )
*
* 	priorities are used to keep the tree balanced, 
* 	and so to reach complexity for the various operation
* 	in the O(logn). This is done by sampling priorities at
* 	random at every insertion, based on the fact that 
* 	inserting at random n element a bst will give an expected
* 	depth of 1.39*logn.
*/
public:
    RandomTreap() : root (nullptr) {}

		/* The running time is O(logn) since it 
		 * depends on the lenght of the longest path
		 * to the leafs, and we know that the expected
		 * depth should be O(logn).
		 */
		bool search(int key)
		{
			return _search(root, key);
		}

		/* Lemma: the expected number of rotations when inserting
		 * an element is 2. The complexity of insertion is O(logn)
		 *
		 * # of rotations = depth of x after being inserted as leaf +
		 * 					- depth of x after the rotations
		 */
		void insert(int key)
		{
			_insertion(root, key);
		}

		/* Also here we use the lemma of before, expected number of
		 * rotations is 2. Complexity of remove operation is O(logn)
		 */
		void remove(int key)
		{
			_remove(root, key);		
		}

		void print()
		{
			_print("", root, false);
		}

private:
		struct treapNode 
		{
			treapNode(int key, double prior) : key (key),
											prior (prior),
											leftChild(nullptr),
											rightChild(nullptr) {}

			int key;
			double prior;
			std::unique_ptr<treapNode> leftChild; 
			std::unique_ptr<treapNode> rightChild; 
		};

		using nodePtr = std::unique_ptr<treapNode>;
		nodePtr root;

    double _randomPrior();
		nodePtr _rightRotation(nodePtr& root);
		nodePtr _leftRotation(nodePtr& root);
		void _insertion(nodePtr& root, int key);
		void _remove(nodePtr& root, int key);
		bool _search(const nodePtr& root, int key);
		void _print(const std::string& prefix, const nodePtr& root, bool isLeft);
};

} //namespace datastruct
