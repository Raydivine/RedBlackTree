#include "Rotations.h"
#include <stdio.h>

void rightRotate(Node **rootPtr){
	Node *node1, *node2, *childNode;

	childNode = *rootPtr;								//assign the 1st pointer to childNode
	node1 = childNode->left;
	node2 = childNode->left->right;			//assign the granChildNode (left->right)  to node2
  node1->right = childNode;						//pass the 1st pointer node to node1 right side
  node1->right->left = node2;					//pass the node2 to node1 (right->left)
  *rootPtr = node1;										//let the node1 become the root
}

void leftRotate(Node **rootPtr){
	Node *node1, *node2, *childNode;

	childNode = *rootPtr;								//assign the 1st pointer to childNode
	node1 = childNode->right;
	node2 = childNode->right->left;			//assign the granChildNode (right->left)  to node2
  node1->left = childNode;						//pass the 1st pointer node to node1 left  side
  node1->left->right = node2;					//pass the node2 to node1 (left->>right)
  *rootPtr = node1;										//let the node1 become the root
}

void leftRightRotate(Node **rootPtr){
  Node *node1, *node2;
  node1 = *rootPtr;
	node2 = node1->left;

  leftRotate(&node2);
  (*rootPtr)->left = node2;
  rightRotate(&(*rootPtr));
}

void rightLeftRotate(Node **rootPtr){
  Node *node1, *node2;
  node1 = *rootPtr;
	node2 = node1->right;

  rightRotate(&node2);
  (*rootPtr)->right = node2;
  leftRotate(&(*rootPtr));
}