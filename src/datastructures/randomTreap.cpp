#include "randomTreap.h"
#include <iostream>
#include <iomanip>
#include <memory>
#include <random>

namespace datastruct
{

double RandomTreap::_randomPrior()
{
    static std::default_random_engine e;
    static std::uniform_real_distribution<double> dis(0.0, 1.0); 
    return dis(e);
}

RandomTreap::nodePtr RandomTreap::_rightRotation(RandomTreap::nodePtr& root)
{
  auto pivot = std::move(root->leftChild);	
  root->leftChild = std::move(pivot->rightChild);
  pivot->rightChild = std::move(root);

  return std::move(pivot);
}

RandomTreap::nodePtr RandomTreap::_leftRotation(RandomTreap::nodePtr& root)
{
  auto pivot = std::move(root->rightChild);
  root->rightChild = std::move(pivot->leftChild);
  pivot->leftChild = std::move(root);

  return std::move(pivot);
}

void RandomTreap::_insertion(RandomTreap::nodePtr& root, int key)
{
  RandomTreap::nodePtr node = std::make_unique<treapNode>(key, _randomPrior());				

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

void RandomTreap::_remove(RandomTreap::nodePtr& root, int key)
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

bool RandomTreap::_search(const RandomTreap::nodePtr& root, int key)
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

void RandomTreap::_print(const std::string& prefix, const RandomTreap::nodePtr& root, bool isLeft)
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

} // namespace datastruct
