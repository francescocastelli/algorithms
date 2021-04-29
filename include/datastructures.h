#include <random>
#include <memory>
#include <iostream>

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
											rightChild(nullptr)
			{}

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
			_insertion(root, root, key);
		}

		void print()
		{
			_print(root);
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

		void _insertion(nodePtr& root, nodePtr& parent, int key)
		{
			if(root == nullptr) 
			{
				nodePtr node = std::make_unique<treapNode>(key, _randomPrior());				

				if (parent == nullptr) {parent=std::move(node); return;}

				if(key > parent->key) 
				{
					parent->rightChild=std::move(node);
					if (parent->prior > parent->rightChild->prior)
						parent = _leftRotation(parent);

					return;
				}

				parent->leftChild=std::move(node);
				if (parent->prior > parent->leftChild->prior)
					parent = _rightRotation(parent);

				return;
			}

			if(key > root->key)
				_insertion(root->rightChild, root, key);
			else 
				_insertion(root->leftChild, root, key);
		}

		bool _search(nodePtr& root, int key)
		{
			if(root == nullptr)
				return false;
			else if (root->key == key)
				return true;

			if(key > root->key)
				_search(root->rightChild, key);
			else
				_search(root->leftChild, key);
		}

		void _print(nodePtr& root)
		{
			if(root == nullptr) return;

			std::cout << "p: " << root.get() << "  key: " << root->key<< "  prior: " << root->prior << "  l: " << root->leftChild.get() << "  r: " << root->rightChild.get() << '\n';

			_print(root->rightChild);
			_print(root->leftChild);
		}
		
		nodePtr root;
	};
}



