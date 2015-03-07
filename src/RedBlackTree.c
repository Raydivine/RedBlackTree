#include "RedBlackTree.h"
#include "Rotation.h"
#include <stdio.h>
#include "ErrorCode.h"

void addRedBlackTree(Node **rootPtr, Node *newNode){
	_addRedBlackTree(rootPtr, newNode);
  Node *root = *rootPtr;

  //Condition checking the structure of unbalance tree choose the rotation
  if(root->left && root->left->color =='r'){
     if(root->left->left  && root->left->left->color =='r'){
        rightRotate(&(*rootPtr));
        (*rootPtr)->right->color = 'r';
     }else if( root->left->right  && root->left->right->color =='r'){
        leftRightRotate(&(*rootPtr));
        (*rootPtr)->right->color = 'r';}
  }
  if(root->right && root->right->color =='r' ){
    if(root->right->right && root->right->right->color =='r'){
      leftRotate(&(*rootPtr));
      (*rootPtr)->left->color = 'r';
    }else if(root->right->left && root->right->left->color =='r'){
      rightLeftRotate(&(*rootPtr));
      (*rootPtr)->left->color = 'r';}
  }
  (*rootPtr)->color = 'b';
}

void _addRedBlackTree(Node **rootPtr, Node *newNode){
	Node *root = *rootPtr;
	if(root == NULL){
		*rootPtr = newNode;
		return;
	}
	if(newNode->data < root->data)
		_addRedBlackTree( &root->left ,	newNode);
	if(newNode->data > root->data)
		_addRedBlackTree( &root->right,	newNode);

  if(!( (*rootPtr)->right && (*rootPtr)->left) )  // if root->right && root-> left are null
    return;
    
  else if( root->left->color == root->right->color && ( root->left->left || root->left->right || root->right->right || root->right->left )){
    root->color = 'r';
  	root->left->color = 'b';
  	root->right->color = 'b';
    printf("in\n");
  }
}
 
Node *delRedBlackTree( Node **rootPtr, Node *newNode){
  Node *node =_delRedBlackTree(rootPtr, newNode);
  Node *root = *rootPtr;
     
  return node;
}

Node *_delRedBlackTree(Node **rootPtr, Node *newNode){
  Node *root = *rootPtr, *node , *successorNode;
  if(root == NULL)
    Throw(ERR_NODE_UNAVAIBLE);

  if(root->data == newNode->data){
    if(root->left || root->right){      //Checking is the removeNode has childNode
      successorNode = removeNextLargerSuccessor(&(*rootPtr)->right);
      successorNode->left  = (*rootPtr)->left;
      successorNode->right = (*rootPtr)->right;
      *rootPtr = successorNode;
    }
    else
    *rootPtr = NULL;
    return root;
  }
  if(newNode->data > (*rootPtr)->data)
    node = _delRedBlackTree( &root->right, newNode);
  if(newNode->data < (*rootPtr)->data)
    node = _delRedBlackTree( &root->left, newNode);

  if(root){
   if((root->right && ((root->right->right && root->right->right->color =='r')||(root->right->left && root->right->left->color =='r'))) ||
      (root->left  && ((root->left ->right && root->left ->right->color =='r')||(root->left ->left && root->left ->left->color =='r')))    )
      NephewIsRedSiblingIsBlack(&(*rootPtr)); //condition checking for enter case1
      
   else if((root->right &&!(root->right->right && root->right->left))||( root->left && !(root->left->left && root->left->right)))
      NephewAndSiblingIsBlack(&(*rootPtr));   //condition checking for enter case2

   else if((root->right && root->right->color == 'r') || (root->left && root->left->color == 'r'))
      SiblingIsRed(&(*rootPtr));              //condition checking for enter case3
  }
  return node;
}

//Function for handle case1
Node *NephewIsRedSiblingIsBlack(Node **rootPtr){
  Node *root = *rootPtr;
  char colour = root->color; //store the original root color

 //Condition checking the structure of unbalance tree choose the rotations
  if(root->right && root->right->color == 'b'){
    if(root->right->right && root->right->right->color =='r')
      leftRotate(&(*rootPtr));
    else if(root->right->left && root->right->left->color == 'r')
      rightLeftRotate(&(*rootPtr));
  }
  if(root->left && root->left->color == 'b'){
    if(root->left->left && root->left->left->color =='r')
      rightRotate(&(*rootPtr));
    else if(root->left->right && root->left->right->color =='r')
      leftRightRotate(&(*rootPtr));
  }
  ForceChildNodeToBlack(&(*rootPtr));
  (*rootPtr)->color = colour;
}

Node *ForceChildNodeToBlack(Node **rootPtr){
  if((*rootPtr)->left)
    (*rootPtr)->left->color  = 'b';
  if((*rootPtr)->right)
    (*rootPtr)->right->color = 'b';
}


//Function for handle case2
Node *NephewAndSiblingIsBlack(Node **rootPtr){
  Node *root = *rootPtr;

  if(root->left && root->left->color == 'd')
    root->left = NULL;
  if(root->right && root->right->color == 'd')
    root->right = NULL;
  if(root->color == 'r')
    root->color = 'b';
  else
    root->color = 'd';

 ForceChildNodeToRed( &(*rootPtr));
}

Node *ForceChildNodeToRed( Node **rootPtr){
  if((*rootPtr)->left)
    (*rootPtr)->left->color  = 'r';
  if((*rootPtr)->right)
    (*rootPtr)->right->color = 'r';
}

//Function for handle case3
Node *SiblingIsRed(Node **rootPtr){
  Node *root = *rootPtr;
  char colour = root->color; // store the original root color

  if(root->right){
    leftRotate(&(*rootPtr));
    (*rootPtr)->left->color = 'r';
    if((*rootPtr)->left && ((*rootPtr)->left->right) && ((*rootPtr)->left->right->right) )
    NephewIsRedSiblingIsBlack(&(*rootPtr)->left);  //enter case 1
    else
    NephewAndSiblingIsBlack(&(*rootPtr)->left);    //enter case 2
  }
  else if(root->left){
    rightRotate(&(*rootPtr));
    (*rootPtr)->right->color = 'r';
    if((*rootPtr)->right && ((*rootPtr)->right->left) && ((*rootPtr)->right->left->left))
    NephewIsRedSiblingIsBlack(&(*rootPtr)->left);  //enter case1
    else
    NephewAndSiblingIsBlack(&(*rootPtr)->right);   //enter case2
  }
  (*rootPtr)->color = colour;
}

Node *removeNextLargerSuccessor(Node **parentPtr){
  Node *parent = *parentPtr, *removeNode;

  if(parent->left == NULL && parent->right == NULL){
    removeNode = *parentPtr;
    *parentPtr = NULL;
  }
  else if(parent->left)
    removeNode = removeNextLargerSuccessor(&(*parentPtr)->left);
  else if(parent->right){
    removeNode = parent;
    *parentPtr = parent->right;
    (*parentPtr)->color = 'b';
  }
  if(parent)
    if(parent->left && parent->left->right && !parent->left->left) // got leftRightChild but doesn't has leftleftChild
      _removeNextLargerSuccessor(&parent);

  return removeNode;
}

Node *_removeNextLargerSuccessor(Node **parentPtr){
  Node *root = *parentPtr;
  if(root->left)
    _removeNextLargerSuccessor(&(*parentPtr)->left);

  if(root)
    root->color ='d';
  if(root->left)
    root->left->color ='b';
  if(root->right)
    root->right->color = 'r';
}
