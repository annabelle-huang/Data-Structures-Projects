/*
 * Filename: AVLTree.cpp
 * CPSC 223 HW 5
 * Annabelle Huang
 * April 17th, 2023
 * Contains: Implementation of AVL Trees for CPSC 223
 * Part of: Homework assignment "AVL Trees" for CPSC 223
 */

#include <iostream>

#include "AVLTree.h"
#include "pretty_print.h"

using namespace std;

/*
 * Input: data (the value to store), multiplicity of the node, height of the
 *      node, left and right child pointers
 * Returns: avl tree node.
 * Does: creates a new node with values given as input parameter
 */
static Node *new_node(int data, int multiplicity, int height, Node *left, Node *right)
{
    Node *node = new Node();

    node->data = data;
    node->count = multiplicity;
    node->height = height;
    node->left = left;
    node->right = right;

    return node;
}

/*
 * Input: data (the value to store)
 * Returns: avl tree node.
 * Does: calls a helper function to create a new node with default
 *        values parameter
 */
static Node *new_node(int data)
{
    return new_node(data, 1, 0, NULL, NULL);
}

/********************************
 * BEGIN PUBLIC AVLTREE SECTION *
 ********************************/

/*
   constructor for AVLTree
 */
AVLTree::AVLTree()
{
    root = NULL;
}

/* 
   copy constructor for AVLTree
 */
AVLTree::AVLTree(const AVLTree &source)
{
    this->root = pre_order_copy(source.root);
}

/*
   AVLTree destructor
 */
AVLTree::~AVLTree()
{
    post_order_delete(root);
}

/*
   assignment overload
 */
AVLTree &AVLTree::operator=(const AVLTree &source)
{
    if (this == &source) 
        return *this;
    post_order_delete(root);
    root = pre_order_copy(source.root);
    return *this;
}

int AVLTree::find_min() const
{
    return find_min(root)->data;
}

int AVLTree::find_max() const
{
    return find_max(root)->data;
}

bool AVLTree::contains(int value) const
{
    return contains(root, value);
}

void AVLTree::insert(int value)
{
    root = insert(root, value);
}

void AVLTree::remove(int value)
{
    root = remove(root, value);
}

int AVLTree::tree_height() const
{
    return tree_height(root);
}

int AVLTree::node_count() const
{
    return node_count(root);
}

int AVLTree::count_total() const
{
    return count_total(root);
}

void AVLTree::print_tree() const
{
    print_pretty(root, 1, 0, std::cout);
}

/*************************
 * BEGIN PRIVATE SECTION *
 *************************/

/*
 * Input: node
 * Returns: minimum value in this
 * Does: Searches this for its minimum value, and returns it. Behavior
 *      is undefined if this is empty
 */
Node *AVLTree::find_min(Node *node) const
{
    if (node == NULL) { 
        return NULL;
    }
    else if (node->left == NULL) {
        return node;
    }
    return find_min(node->left);
}

/*
 * Input: n/a
 * Returns: the maximum value in this
 * Does: Searches this for its maximum value, and returns it. Behavior
 *      is undefined if this is empty
 */
Node *AVLTree::find_max(Node *node) const
{
    if (node == NULL) { 
        return NULL;
    }
    else if (node->right == NULL) {
        return node;
    }
    return find_max(node->right);
}

/*
 * Input: int value - value to search for
 * Returns: true if there is a node in this with data = value, false
 *      otherwise
 * Does: searches the tree for value
 */
bool AVLTree::contains(Node *node, int value) const
{
    if (node == NULL) {
        return false;
    }
    else if (value > node->data) {
        return contains(node->right, value);
    }
    else if (value < node->data) {
        return contains(node->left, value);
    }
    else {
        return true;
    }
}

/*
 * Input: int value - value to insert
 * Returns: N/A
 * Does: Inserts value into this, either by creating a new node or, if
 *      value is already in this, by incrementing that node's count
 */
Node *AVLTree::insert(Node *node, int value)
{
    /* BST insertion start */
    if (node == NULL)
    {
        return new_node(value);
    }
    else if (value < node->data)
    {
        node->left = insert(node->left, value);
    }
    else if (value > node->data)
    {
        node->right = insert(node->right, value);
    }
    else if (value == node->data)
    {
        node->count++;
        return node;
    }
    /* BST insertion ends */

    /* AVL maintenance start */
    node->height = 1 + max(tree_height(node->left), tree_height(node->right));
    node = balance(node);
    /* AVL maintenace end */

    return node;
}

/*
 * Input: int value - the value to remove
 * Returns: N/A
 * Does: Removes value from the tree. If a node's count is greater than
 *      1, the count is decremented and the node is not removed. Nodes
 *      with a count of 1 are removed according to the algorithm
 *      discussed in class, with arbitrary decisions made in the same way
 *      as the reference implementation.
 */
Node *AVLTree::remove(Node *node, int value)
{
    /* BST removal begins */
    if (node == NULL)
    {
        return NULL;
    }

    Node *root = node;
    if (value < node->data)
    {
        node->left = remove(node->left, value);
    }
    else if (value > node->data)
    {
        node->right = remove(node->right, value);
    }
    else
    {
        // We found the value. Remove it.
        if (node->count > 1)
        {
            node->count--;
        }
        else
        {
            if (node->left == NULL && node->right == NULL)
            {
                root = NULL;
                delete node;
                return root;
            }
            else if (node->left != NULL && node->right == NULL)
            {
                root = node->left;
                node->left = NULL;
                delete node;
            }
            else if (node->left == NULL && node->right != NULL)
            {
                root = node->right;
                node->right = NULL;
                delete node;
            }
            else
            {
                Node *replacement = find_min(node->right);
                root->data = replacement->data;
                root->count = replacement->count;
                replacement->count = 1;
                root->right = remove(root->right, replacement->data);
            }
        }
    }
    /* BST removal ends */

    /* AVL maintenance begins */
    if (root != NULL)
    {
        root->height = 1 + max(tree_height(root->left), tree_height(root->right));
        root = balance(root);
    }
    /* AVL maintenance ends */

    return root;
}

/*
 * Input: N/A
 * Returns: the height of this
 * Does: computes and returns the height of this tree.
 */
int AVLTree::tree_height(Node *node) const
{
    if (node == NULL) { 
        return -1;
    }
    else {
        return (max(tree_height(node->right), tree_height(node->left)) + 1);
    }
}

/*
 * Input: N/A
 * Returns: The number of nodes in this tree
 * Does: Counts and returns the number of nodes in this
 */
int AVLTree::node_count(Node *node) const
{
    if (node == NULL) 
        return 0;
    return (1 + node_count(node->left) + node_count(node->right));
}

/*
 * Input: N/A
 * Returns: the total of all node values, including duplicates.
 * Does: Computes and returns the sum of all nodes and duplicates in
 *      this
 */
int AVLTree::count_total(Node *node) const
{
    if (node == NULL) 
        return 0;
    return ((node->data * node->count) + count_total(node->left) + count_total(node->right));
}

/*
 * Input: Node node - a pointer to the root of the tree to copy
 * Returns: a deep copy of the tree rooted at node
 * Does: Performs a pre-order traversal of the tree rooted at node to
 *      create a deep copy of it
 */
Node *AVLTree::pre_order_copy(Node *node) const
{
    if (node == NULL)
    {
        return NULL;
    }
    Node *new_node = new Node();

    *new_node = *node;
    new_node->left = pre_order_copy(node->left);
    new_node->right = pre_order_copy(node->right);
    return new_node;
}

/*
 * Input: Node node - a pointer to the root of the tree to delete
 * Returns: N/A
 * Does: Performs a post-order traversal of the tree rooted at node to
 *      delete every node in that tree
 */
void AVLTree::post_order_delete(Node *node)
{
    if (node == NULL) return;
    post_order_delete(node->left);
    post_order_delete(node->right);
    delete node;
}

/*
 * Input: Node root - a node of the avl tree.
 * Returns: the balanced subtree.
 * Does: If unbalanced, balances the tree rooted at node.
 */
Node *AVLTree::balance(Node *node)
{
        if (height_diff(node) > 1) {
            if (height_diff(node->left) < 0) {
                node->left = left_rotate(node->left);
                return right_rotate(node);
            }
            else {
                return right_rotate(node);
            }
        }
        else if (height_diff(node) < -1) {
            if (height_diff(node->right) > 0) {
                node->right = right_rotate(node->right);
                return left_rotate(node);
            }
            else {
                return left_rotate(node);
            }
        }
        else {
            return node;
        }

}

/*
 * Input: Node node - a node of the avl tree.
 * Returns: pointer to the root of rotated tree.
 * Does: right rotate tree rooted at node
 */
Node *AVLTree::right_rotate(Node *node)
{
    Node *future_root = new Node();
    future_root = node->left;
    node->left = future_root->right;
    future_root->right = node;
    return future_root;
}

/*
 * Input: Node node - a node of the avl tree.
 * Returns: pointer to the root of rotated tree.
 * Does: left rotate tree rooted at node
 */
Node *AVLTree::left_rotate(Node *node)
{
    Node *future_root = new Node();
    future_root = node->right;
	node->right = future_root->left;
	future_root->left = node;
    return future_root;
}

/*
 * Input: Node node - a node of the avl tree.
 * Returns: integer value signifying the height difference.
 * Does: calculates the difference in the height of the left and child
 *       subtree of node
 */
int AVLTree::height_diff(Node *node) const
{
    return (tree_height(node->left) - tree_height(node->right));
}

/*
 * Input: Node node - the root of the tree in which to search
 *        Node child - a pointer to the the node to search for
 * Returns: a pointer to the parent of child in the tree rooted at
 *      node, or NULL if child is not in that tree
 * Does: Searches the tree rooted at node for child, then returns
 *      that node's parent.
 */
Node *AVLTree::find_parent(Node *node, Node *child) const
{
    if (node == NULL)
        return NULL;

    // if either the left or right is equal to the child,
    // we have found the parent
    if (node->left == child or node->right == child)
    {
        return node;
    }

    // Use the binary search tree invariant to walk the tree
    if (child->data > node->data)
    {
        return find_parent(node->right, child);
    }
    else
    {
        return find_parent(node->left, child);
    }
}
