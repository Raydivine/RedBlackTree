#ifndef RedBlackTree_H
#define RedBlackTree_H
#include "Node.h"

void  addRedBlackTree (Node **rootPtr, Node *newNode);
void _addRedBlackTree (Node **rootPtr, Node *newNode);
Node *delRedBlackTree (Node **rootPtr, Node *newNode);
Node *_delRedBlackTree(Node **rootPtr, Node *newNode);
Node *NephewIsRedSiblingIsBlack(Node **rootPtr);  //case1
Node *NephewAndSiblingIsBlack  (Node **rootPtr);  //case2
Node *SiblingIsRed             (Node **rootPtr);  //case3
Node *ForceChildNodeToBlack    (Node **rootPtr);
Node *ForceChildNodeToRed      (Node **rootPtr);
Node *removeNextLargerSuccessor  (Node **parentPtr);
Node *_removeNextLargerSuccessor (Node **parentPtr);

#endif // RedBlackTree_H
