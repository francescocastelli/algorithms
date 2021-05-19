#include <random>
#include <memory>
#include <iostream>
#include <iomanip>

namespace datastruct 
{
	class RandomTreap
	{
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

		bool search(int key)
		{
			return _search(root, key);
		}

		void insert(int key)
		{
			//if (_search(root, key) == true) return;
			_insertion(root, key);
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

			if(key > root->key) 
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
