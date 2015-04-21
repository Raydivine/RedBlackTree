#include "ConditionChecking.h"
#include <stdio.h>

int gotChildNode(Node **rootPtr){
  Node *root = *rootPtr;
  if( root->left || root->right)
    return 1;
  return 0;
}

int noChildNode(Node **rootPtr){
  Node *root = *rootPtr;
  if( !root->left && !root->right)
    return 1;
  return 0;
}

int checkHowManyChildNode(Node *rootPtr){
  if( !rootPtr->left && !rootPtr->right)
    return 0;
  else if( rootPtr->left && rootPtr->right)
    return 2;
  return 1;
}

int checkWhichHasMoreChildNode(Node *rootPtr1, Node *rootPtr2){
  int left = checkHowManyChildNode(rootPtr1);
  int right = checkHowManyChildNode(rootPtr2);
  
  if(left>right)
    return 1;
  return 2;
}

int determineUnbalanceTree(Node **rootPtr){
  Node *root = *rootPtr;
  if(root->left && !(root->right)){
    if( gotChildNode( &(root->left)))
      return 1;
    return 0;
  }
  else if(root->right && !(root->left)){
    if( gotChildNode( &(root->right)))
      return 1;
    return 0;
  }
}

int isDoubleBlack(Node *rootPtr, Node *removedNode) {

  if((rootPtr == NULL ||  rootPtr->color == 'd')  &&  (removedNode->color == 'b' ||  removedNode->color == 'r'))
    return 1;
  else  return 0;
}

int bothChildNodeIsBlack(Node *rootPtr){
  if(rootPtr->left->color != 'b' || rootPtr->right->color != 'b')
    return 0;
  return 1;
}

