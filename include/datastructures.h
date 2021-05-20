#include <random>
#include <memory>
#include <iostream>
#include <iomanip>

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
    	double _randomPrior()
    	{
			static std::default_random_engine e;
    		static std::uniform_real_distribution<double> dis(0.0, 1.0); 
    		return dis(e);
    	}

		nodePtr _rightRotation(nodePtr& root)
		{
			auto pivot = std::move(root->leftChild);	
			root->leftChild = std::move(pivot->rightChild);
			pivot->rightChild = std::move(root);

			return std::move(pivot);
		}

		nodePtr _leftRotation(nodePtr& root)
		{
			auto pivot = std::move(root->rightChild);
			root->rightChild = std::move(pivot->leftChild);
			pivot->leftChild = std::move(root);

			return std::move(pivot);
		}

		void _insertion(nodePtr& root, int key)
		{
			nodePtr node = std::make_unique<treapNode>(key, _randomPrior());				

			//for the first insertion
			if (root == nullptr) {root=std::move(node); return;}

			if (key > root->key) 
			{
				//insert on the right (bst property)
				_insertion(root->rightChild, key);

				//restoring heap property
				if (root->prior > root->rightChild->prior)
					root = _leftRotation(root);

				return;
			}

			//insert on the left(bst property)
			_insertion(root->leftChild, key);

			//restoring heap property
			if (root->prior > root->leftChild->prior)
				root = _rightRotation(root);

			return;
		}

		void _remove(nodePtr& root, int key)
		{
			if (root == nullptr) return;
			
			//navigate the tree until key is found
			if (key > root->key) 
				_remove(root->rightChild, key);
			else
				_remove(root->leftChild, key);

			if (key == root->key) 
			{
				if (!root->leftChild) {root = std::move(root->rightChild); return;}
				if (!root->rightChild) {root = std::move(root->leftChild); return;}

				//move the root to the leafs and then remove it
				if (root->leftChild->prior < root->rightChild->prior)
				{
					root = _rightRotation(root);
					_remove(root->rightChild, key);
				}
				else 
				{
						root = _leftRotation(root);
						_remove(root->leftChild, key);	
				}
			}
		}

		bool _search(const nodePtr& root, int key)
		{
			if(root == nullptr)
				return false;
			
			if (root->key == key)
				return true;

			if(key > root->key)
				_search(root->rightChild, key);
			else
				_search(root->leftChild, key);

			return false;
		}

		void _print(const std::string& prefix, const nodePtr& root, bool isLeft)
		{
			if(root == nullptr) return;

			std::cout << prefix;

			std::cout << (isLeft ? "├──" : "└──");

			//value of the node
			std::cout << std::setprecision(2);
			std::cout << "("<< root->key << " - " << root->prior << ")"<< std::endl;

			_print(prefix + (isLeft ? "|            " : "            "), root->leftChild, true);
			_print(prefix + (isLeft ? "|            " : "            "), root->rightChild, false);
		}
		
		nodePtr root;
	};
}
