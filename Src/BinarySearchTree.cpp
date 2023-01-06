/*
 * BinarySearchTree.cpp
 * COMP15
 * Spring 2021
 *
 * Implementation of the Binary Search Tree class.
 * Behaves like a standard BST except that it handles multiplicity
 * If you insert a number twice  and then remove it once, then it will
 * still be in the data structure
 */

#include <cstring>
#include <iostream>
#include <limits>

#include "BinarySearchTree.h"

using namespace std;

/* BinarySearchTree
  *
  * Purpose: to initialize the tree
  * Parameters: none
  * Returns: none
*/
BinarySearchTree::BinarySearchTree()
{
        root = nullptr;//set root to null
}

/* ~BinarySearchTree
  *
  * Purpose: walk over the tree and delete each node
  * Parameters: none
  * Returns: none
  * Notes: removes nodes for memory
*/
BinarySearchTree::~BinarySearchTree()
{
        // walk tree in post-order traversal and delete
        post_order_delete(root);
        root = nullptr;  // not really necessary, since the tree is going
                         // away, but might want to guard against someone
                         // using a pointer after deleting
}

/* post_order_delete
  *
  * Purpose: delete each node of the tree
  * Parameters: node to delete
  * Returns: none
  * Note: deletes the whole tree and frees memory
*/
void BinarySearchTree::post_order_delete(Node *node)
{
        if (node == nullptr) {
          return;
        }
        post_order_delete(node->left);//traverse through both sides of tree
        post_order_delete(node->right);
        delete node;
}

/* BinarySearchTree
  *
  * Purpose: helper function for copying the tree
  * Parameters: source binary search tree
  * Returns: none
*/
BinarySearchTree::BinarySearchTree(const BinarySearchTree &source)
{
        // use pre-order traversal to copy the tree
        root = pre_order_copy(source.root);
}

/* assignment overload
  *
  * Purpose: To copy over the orignial tree to a new tree
  * Parameters: source binary search tree
  * returns: the binary search tree
  * Note: the original tree is deleted the copied over to the new tree
*/
BinarySearchTree &BinarySearchTree::operator=(const BinarySearchTree &source)
{
        // check for self-assignment
        if (this != &source) {
          post_order_delete(root);// delete current tree if it exists
          root = pre_order_copy(source.root);// use pre-order traversal
        }
        return *this;
}
  
/* pre_order_copy
  *
  * Purpose: to copy over nodes in the tree
  * Parameters: the node to copy
  * Returns: the node that was copied
  * Note: node added to the tree
*/
BinarySearchTree::Node *BinarySearchTree::pre_order_copy(Node *node) const
{
        if (node == nullptr) {
          return nullptr;
        }
        Node *n = new Node;
        n->data = node->data;
        n->count = node->count;
        n->left = pre_order_copy(node->left);
        n->right = pre_order_copy(node->right);

        return n;
}

/* find_min
  *
  * Purpose: to traverse the left side of the tree and return the smallest node
  * Parameters: none
  * Returns: the nodes data
*/
int BinarySearchTree::find_min() const
{
        if (root == nullptr)
                return numeric_limits<int>::max(); // INT_MAX

        return find_min(root)->data;
}

/* find_min
  *
  * Purpose: to traverse the left side of the tree and return the smallest node
  * Parameters: none
  * Returns: the node
*/
BinarySearchTree::Node *BinarySearchTree::find_min(Node *node) const
{
        if (root->left == nullptr) { //return node if null
          return node;
        }
        if (node->left != nullptr) { //traverse left
          node = find_min(node->left);
        }
        return node;
}
/* find_max
  *
  * Purpose: to traverse right side of the tree and return max node data
  * Parameters: none
  * Returns: the nodes data
*/
int BinarySearchTree::find_max() const
{
        if (root == nullptr) {
          return numeric_limits<int>::max();
        }
        return find_max(root)->data;
}

/* find_max
  *
  * Purpose: to traverse right side of the tree and return max node data
  * Parameters: none
  * Returns: the nodes
*/
BinarySearchTree::Node *BinarySearchTree::find_max(Node *node) const
{
        if (root->right == nullptr) {//if right is null return node
          return node;
        }
        if (node->right != nullptr) {//traverse the right of the tree
          node = find_max(node->right);
        }
        return node;
}

/* contains
  *
  * Purpose: to check if the tree contains a node data
  * Parameters: the value of the node to check
  * Returns: a boolean true if found, false if not
*/
bool BinarySearchTree::contains(int value) const
{
        return contains(root, value);
}

/* contains
  *
  * Purpose: to check if the tree contains a node data
  * Parameters: the value of the node to check and the node
  * Returns: a boolean true if found, false if not
*/
bool BinarySearchTree::contains(Node *node, int value) const
{
        if (node == nullptr) {//if node is null false
          return false;
        }
        if (value == node->data) { //if node is found return true
          return true;
        }
        if (value < node->data) {//traverse left
          return contains(node->left, value);
        }
        if (value > node->data) {//traverse right
          return contains(node->right, value);
        }
        return true;
}

/* insert
  *
  * Purpose: to insert a value into the tree
  * Parameters: the value to insert
  * Return: none
  * Note: this is a helper funciton
*/
void BinarySearchTree::insert(int value)
{
        insert(root, nullptr, value);
}

/* insert
  *
  * Purpose: to insert a value into the tree
  * Parameters: the value to insert, the node, the parent node
  * Return: none
  * Note: this function allocates memory for a new node
*/
void BinarySearchTree::insert(Node *node, Node *parent, int value)
{
        if (node == nullptr) {//if node is null create new node
          Node *n = new Node;
          n->data = value;
          n->count = 1;
          n->right = nullptr;
          n->left = nullptr;
          if (root == nullptr) {//if empty tree make n the root
            root = n;
            root->left = nullptr;
            root->right = nullptr;
            return;
          }
          else if (n->data < parent->data) {//if nodes smaller than parent
            parent->left = n;
            return;
          }
          else if (n->data > parent->data) {//if node larger than parent
            parent->right = n;
            return;
          }
        }
        else if (value > node->data) {//traverse right
          insert(node->right, node, value);
        }
        else if (value < node->data) {//traverse left
          insert(node->left, node, value);
        }
        else if (value == node->data) {//if node exist add count
          node->count += 1;
          return;
        }
}

/* remove
  *
  * Purpose: removing a node in the tree
  * Parameters: the value to remove
  * Returns: true if removed, false if not in the tree
  * Note: this is a helper function
*/
bool BinarySearchTree::remove(int value)
{
        if (contains(value)) {//check if value is in the tree
        return remove(root, nullptr, value);
      }
        return false;
}

/* remove
  *
  * Purpose: removing a node in the tree
  * Parameters: the value to remove, the node to remove, the parent
  * Returns: true if removed
  * Note: memory is freed when node is removed
*/
bool BinarySearchTree::remove(Node *node, Node *parent, int value)
{
        if (node == nullptr) {//if node is null return false
          return false;
        }
        if (value > node->data) {//traverse right side of tree
          remove(node->right, node, value);
        }
        if (value < node->data) {//traverse left side of tree
          remove(node->left, node, value);
        }
        if (value == node->data) {//if node found
          if (node->count > 1) {//count greater than 1 decrement count
            node->count -= 1;
            return true;
          }
          if (node->count == 1) {//node count is 1 remove node
            node->count -= 1;
            //if leaf delete the leaf
            if (node->left == nullptr and node->right == nullptr) {
              if (parent->left == node) {
                parent->left = nullptr;//set parent left to null
              }
              if (parent->right == node) {
                parent->right = nullptr;//set parent right to null
              }
              delete node;
              return true;
            }
            //one right child in tree
            if (node->left == nullptr and node->right != nullptr) {
              if (parent->left == node) {
                parent->left = node->right;//set parent left to node right
              }
              if (parent->right == node) {
                parent->right = node->right;//set parent right to node right
              }
              delete node;
              return true;
            }
            //one left child
            if (node->right == nullptr and node->left != nullptr) {
              if (parent->left == node) {
                parent->left = node->left;//parent left to node left
              }
              if (parent->right == node) {
                parent->right = node->left;//parent right to node left
              }
              delete node;
              return true;
            }
            //two child case
            if (node->left != nullptr and node->right != nullptr) {
              Node *temp = find_min(node->right);//find right min
              node->data = temp->data;//set the data to node to replae data
              node->count = temp->count;
              remove(node->right, node, temp->data);//restructure tree
              return true;
            }
          }
        }
      return true;
}

/*tree_height
  *
  * Purpose: to get the height of the tree
  * Parameters: none
  * Return: height of the tree
*/
int BinarySearchTree::tree_height() const
{
        if(root == nullptr) {//if empty tree
          return -1;
        }
        if(root->left == nullptr and root->right == nullptr) {
          return 0;//if root
        }
        return tree_height(root);
}

/*tree_height
  *
  * Purpose: to get the height of the tree
  * Parameters: the node to traverse
  * Return: the height of the tree
*/
int BinarySearchTree::tree_height(Node *node) const
{
        if (node == nullptr) {//if node is null return -1
          return -1;
        }
        int right = tree_height(node->right) + 1;//go to right of tree
        int left = tree_height(node->left) + 1;//go to left of the tree
        if(right > left) {//compare lengths
          return right;
        }
        if (left > right) {//compare lengths
          return left;
        }
        if (left == right) {//if the lengths are the same
          return right;
        }
}

/* node_count
  *
  * Purpose: To return the total ndoes in tree
  * Parameters: none
  * Returns: the total number of nodes
  * Note: this is a helper function
*/
int BinarySearchTree::node_count() const
{
        return node_count(root);
}

/* node_count
  *
  * Purpose: To return the total ndoes in tree
  * Parameters: node to traverse
  * Returns: the total number of nodes
*/
int BinarySearchTree::node_count(Node *node) const
{
        if (root == nullptr) {//if empty tree
          return 0;
        }
        if (root->left == nullptr and root->right == nullptr) {//if one node
          return 1;
        }
        if (node == nullptr) {//if node is null
          return 0;
        }
        //traverse through left and right side and return num nodes
        return 1 + node_count(node->left) + node_count(node->right);
}

/* count_total
  *
  * Purpose: to return the total count even duplicates
  * Parameters: none
  * Return: the total count with duplicates
  * Note: this is a helper function
*/
int BinarySearchTree::count_total() const
{
        return count_total(root);
}

/* count_total
  *
  * Purpose: to return the total count even duplicates
  * Parameters: the node to traverse
  * Return: the total count with duplicates
*/
int BinarySearchTree::count_total(Node *node) const
{
        if (root == nullptr) {//if empty tree
          return 0;
        }
        if (root->left == nullptr and root->right == nullptr) {//one node
          return root->data;
        }
        if (node == nullptr) {//if node is null
          return 0;
        }
        int num = 0;
        if (node->count > 1) {//account for duplicates
          for (int i = 1; i < node->count; i++) {
            num += node->data;
          }
        }
        //return the total count with duplicates
        return num + node->data + count_total(node->left)
        + count_total(node->right);
}

BinarySearchTree::Node *BinarySearchTree::find_parent(Node *node,
                                                      Node *child) const
{
        if (node == nullptr)
                return nullptr;

        // if either the left or right is equal to the child,
        // we have found the parent
        if (node->left == child or node->right == child) {
                return node;
        }

        // Use the binary search tree invariant to walk the tree
        if (child->data > node->data) {
                return find_parent(node->right, child);
        } else {
                return find_parent(node->left, child);
        }
}

// use the printPretty helper to make the tree look nice
void BinarySearchTree::print_tree() const
{
        size_t      numLayers  = tree_height() + 1;
        size_t      levelWidth = 4;
        const char *rootPrefix = "-> ";

        // Need numLayers * levelWidth characters for each layer of tree.
        // Add an extra levelWidth characters at front to avoid if statement
        // 1 extra char for nul character at end
        char *start = new char[(numLayers + 1) * levelWidth + 1];

        print_tree(root, start + levelWidth, start + levelWidth, rootPrefix);
        delete[] start;
}

// Logic and Output Reference:
// https://www.techiedelight.com/c-program-print-binary-tree/
void BinarySearchTree::print_tree(Node *node, char *const currPos,
                                  const char *const fullLine,
                                  const char *const branch) const
{
        if (node == nullptr)
                return;

        // 4 characters + 1 for nul terminator
        using TreeLevel                    = char[5];
        static const int       levelLength = sizeof(TreeLevel) - 1;
        static const TreeLevel UP = ".-- ", DOWN = "`-- ", EMPTY = "    ",
                               CONNECT = "   |";
        // Copies prev into dest and advances dest by strlen(prev)
        auto set = [](char *dest, const char *prev) {
                size_t p = strlen(prev);
                return (char *)memcpy(dest, prev, p) + p;
        };

        print_tree(node->right, set(currPos, EMPTY), fullLine, UP);

        // Clear any characters that would immediate precede the "branch"
        // Don't need to check for root (i.e start of array),fullLine is padded
        set(currPos - levelLength, EMPTY);

        // Terminate fullLine at current level
        *currPos = '\0';

        std::cerr << fullLine << branch << node->data
                  << (node->count > 1 ? "*" : "") << endl;

        // Connect upper branch to parent
        if (branch == UP)
                set(currPos - levelLength, CONNECT);

        // Connect lower branch to parent
        print_tree(node->left, set(currPos, CONNECT), fullLine, DOWN);
}
