#ifndef RedBlackTree_H
#define RedBlackTree_H
#include "Node.h"

void  addRedBlackTree (Node **rootPtr, Node *newNode);
void _addRedBlackTree (Node **rootPtr, Node *newNode);
void ForceChildNodeToBlack    (Node **rootPtr);
void ForceChildNodeToRed      (Node **rootPtr);
void restructureUnBalanceTree( Node **rootPtr);
void caseSelect( Node **rootPtr);
Node *delRedBlackTree (Node **rootPtr, Node *newNode);
Node *_delRedBlackTree(Node **rootPtr, Node *newNode);
void NephewIsRedSiblingIsBlack(Node **rootPtr);  //case1
void NephewAndSiblingIsBlack  (Node **rootPtr);  //case2
void SiblingIsRed             (Node **rootPtr);  //case3
Node *removeNextLargerSuccessor  (Node **parentPtr);
Node *_removeNextLargerSuccessor (Node **parentPtr);


#endif // RedBlackTree_H
