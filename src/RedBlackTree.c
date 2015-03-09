#include "RedBlackTree.h"
#include "Rotation.h"
#include <stdio.h>
#include "ErrorCode.h"

void restructureUnBalanceTree( Node **rootPtr){
  Node *root = *rootPtr;

  if( root->left && !(root->right) ){
     if( root->left->left && !(root->left->right) ){
        rightRotate(&(*rootPtr));
        (*rootPtr)->right->color = 'r';
     }else if( root->left->right && !(root->left->left) ){
        leftRightRotate(&(*rootPtr));
        (*rootPtr)->right->color = 'r';
      }      
  }
  else if(root->right  && !(root->left)  ){
    if( root->right->right  && !(root->right->left) ){
      leftRotate(&(*rootPtr));
      (*rootPtr)->left->color = 'r';
    }else if( root->right->left && !(root->right->right) ){
      rightLeftRotate(&(*rootPtr));
      (*rootPtr)->left->color = 'r';
     }       
  }
}

void restructureUnBalanceTreeWithoutColourFlopping( Node **rootPtr){
  Node *root = *rootPtr;

  if( root->left && !(root->right) ){
     if( root->left->left && !(root->left->right) )
        rightRotate(&(*rootPtr));
     else if( root->left->right && !(root->left->left) )
        leftRightRotate(&(*rootPtr));    
  }
  else if(root->right  && !(root->left)  ){
    if( root->right->right  && !(root->right->left) )
      leftRotate(&(*rootPtr));
    else if( root->right->left && !(root->right->right) )
      rightLeftRotate(&(*rootPtr));   
  }
}

void addRedBlackTree(Node **rootPtr, Node *newNode){

	_addRedBlackTree(rootPtr, newNode);
  restructureUnBalanceTree( rootPtr);
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
  }
}

int isDoubleBlack(Node *rootPtr, Node *removedNode) {

  if((rootPtr == NULL ||  rootPtr->color == 'd')  &&  (removedNode->color == 'b' ||  removedNode->color == 'r'))
    return 1;
  else  return 0;
}

Node *ForceChildNodeToBlack(Node **rootPtr){
  
  if((*rootPtr)->left)
    (*rootPtr)->left->color  = 'b';
  if((*rootPtr)->right)
    (*rootPtr)->right->color = 'b';
}

Node *ForceChildNodeToRed( Node **rootPtr){
  if((*rootPtr)->left)
    (*rootPtr)->left->color  = 'r';
  if((*rootPtr)->right)
    (*rootPtr)->right->color = 'r';
}

//Function for handle case1
Node *NephewIsRedSiblingIsBlack(Node **rootPtr){
  Node *root = *rootPtr;
  char colour = root->color; //store the original root color

  restructureUnBalanceTreeWithoutColourFlopping( rootPtr);
  ForceChildNodeToBlack(&(*rootPtr));
  (*rootPtr)->color = colour;
}

//Function for handle case2
Node *NephewAndSiblingIsBlack(Node **rootPtr){
  Node *root = *rootPtr;

  if(root->left)
    root->left->color = (root->left->color == 'd')? 'b':'r';
  if(root->right)
    root->right->color = (root->right->color == 'd')? 'b':'r';
  
  if(root->color == 'r')
    root->color = 'b';
  else
    root->color = 'd';

 ForceChildNodeToRed( &(*rootPtr));
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

void caseSelect( Node **rootPtr){

  Node *root = (*rootPtr)->right;
  if(root == NULL)
    return;
 
  if(root ){
    if(root->color == 'b'){
      if((root->right && root->right->color =='r')||(root->left  && root->left->color == 'r')){
        NephewIsRedSiblingIsBlack(&(*rootPtr)); //condition checking for enter case1
        printf("enter case1\n");
      }
      else if(( root->right == NULL ||  root->right->color == 'b') && (root->left == NULL || root->left->color == 'b')){
        NephewAndSiblingIsBlack(&(*rootPtr));   //condition checking for enter case2
        printf("enter case2\n");
      }
    }
   else if((root->right && root->right->color == 'r') || (root->left && root->left->color == 'r')){
      SiblingIsRed(&(*rootPtr));   
       printf("enter case3\n");
   }
  }
}

Node *removeNextLargerSuccessor(Node **parentPtr){
  Node *parent = *parentPtr, *removeNode;

  if(parent->left == NULL && parent->right == NULL){
    removeNode = *parentPtr;
    *parentPtr = NULL;
  }
  else if(parent->left){
    removeNode = removeNextLargerSuccessor(&(*parentPtr)->left);
    printf("parent: %d\n",parent->data);
    if(isDoubleBlack((*parentPtr)->left, removeNode)) 
      caseSelect(&(*parentPtr)); 
  }
  else{
    removeNode = parent;
    *parentPtr = parent->right;
    (*parentPtr)->color = parent->color;
  }


  return removeNode;
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

  if(root ){
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
