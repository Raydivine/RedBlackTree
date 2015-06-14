#include "RedBlackTree.h"
#include "Rotations.h"
#include <stdio.h>
#include "ErrorCode.h"


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

int isDoubleBlack(Node *rootPtr, Node *removedNode){

  if((rootPtr == NULL ||  rootPtr->color == 'd')  &&  (removedNode->color == 'b' ||  removedNode->color == 'r'))
    return 1;
  else  return 0;
}

int bothChildNodeIsBlack(Node *rootPtr){
  if(rootPtr->left->color != 'b' || rootPtr->right->color != 'b')
    return 0;
  return 1;
}

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
  if(newNode->data == root->data)
    Throw(ERR_EQUIVALENT_NODE);
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

void ForceChildNodeToBlack(Node **rootPtr){
  if((*rootPtr)->left)
    (*rootPtr)->left->color  = 'b';
  if((*rootPtr)->right)
    (*rootPtr)->right->color = 'b';
}

void ForceChildNodeToRed( Node **rootPtr){
  if((*rootPtr)->left)
    (*rootPtr)->left->color  = 'r';
  if((*rootPtr)->right)
    (*rootPtr)->right->color = 'r';
}

Node *removeNextLargerSuccessor(Node **parentPtr){
  Node *parent = *parentPtr, *removeNode;

  if(parent->left == NULL && parent->right == NULL){
    removeNode = *parentPtr;
    *parentPtr = NULL;
  }
  else if(parent->left){
    removeNode = removeNextLargerSuccessor(&(*parentPtr)->left);
    if(isDoubleBlack((*parentPtr)->left, removeNode)) 
      caseSelectForSucessor(&(*parentPtr)); 
  }
  else{
    removeNode = parent;
    *parentPtr = parent->right;
    (*parentPtr)->color = parent->color;
  }
  return removeNode;
}

void caseSelectForSucessor( Node **rootPtr){

  Node *root = (*rootPtr)->right;
  if(root == NULL )
    return;
  
  if(root ){
    if(root->color == 'b'){
      if((root->right && root->right->color =='r')||(root->left  && root->left->color == 'r')){
        NephewIsRedSiblingIsBlack(&(*rootPtr)); 
        //printf("enter Sucessor case1\n");
      }
      else if(( root->right == NULL ||  root->right->color == 'b') && (root->left == NULL || root->left->color == 'b')){
        NephewAndSiblingIsBlack(&(*rootPtr));   
        //printf("enter Sucessor case2\n");
      }
    }
   else if(root->color == 'r' && (root->left||root->right)){
      SiblingIsRed(&(*rootPtr));   
       //printf("enter Sucessor case3\n");
   }
  }
}

Node *delRedBlackTree( Node **rootPtr, Node *newNode){
  Node *node =_delRedBlackTree(rootPtr, newNode);
  Node *root = *rootPtr;
  
  if(root != NULL)
    root->color = 'b';

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
    else *rootPtr = NULL;
    return root;
  }
  if(newNode->data > (*rootPtr)->data)
    node = _delRedBlackTree( &root->right, newNode);
  if(newNode->data < (*rootPtr)->data)
    node = _delRedBlackTree( &root->left, newNode);
  
  caseSelect(&(*rootPtr));
  return node;
}

void caseSelect( Node **rootPtr){
  Node *root = *rootPtr;

  if(root){  
    if( checkForEnterCase1(root) ){
     // printf("enter case1\n");
      NephewIsRedSiblingIsBlack(&(*rootPtr));  
    }
    else if( checkForEnterCase2(root) ){
   //   printf("enter case2\n");
      NephewAndSiblingIsBlack(&(*rootPtr));     
    }
    else if( checkForEnterCase3(root) ){
    //  printf("enter case3\n");
      SiblingIsRed(&(*rootPtr));       
    }
  }
}

int checkForEnterCase1( Node *root){
    if( root->left && !root->right && root->left->color =='b' ){
      if( (root->left ->right && root->left ->right->color =='r') || (root->left->left && root->left->left->color =='r') )
         return 1;
    }
    else if( root->right && !root->left && root->right->color =='b' ){
      if( (root->right->right && root->right->right->color =='r') || (root->right->left && root->right->left->color =='r') )
         return 1;
    }
    return 0;
}

int checkForEnterCase2( Node *root){
    if(root->left && !root->right){
      if( noChildNode( &(root->left) ) )
        return 1;  
    }
    else if( root->right && !root->left){
      if( noChildNode( &(root->right) ) )
        return 1;
    }
    return 0;
}

int checkForEnterCase3( Node *root){
    if(root->left && root->left->color =='r'){
      if( !root->right || root->right->color =='d')
        return 1;  
    }
    else if( root->right && root->right->color =='r'){
      if( !root->left || root->left->color =='d')
        return 1;
    }
    return 0;
}


//Function for handle case1
void NephewIsRedSiblingIsBlack(Node **rootPtr){
  Node *root = *rootPtr;
  char colour = root->color; //store the original root color

  restructureUnBalanceTreeWithoutColourFlopping( rootPtr);
  ForceChildNodeToBlack(&(*rootPtr));
  (*rootPtr)->color = colour;
}

//Function for handle case2
void NephewAndSiblingIsBlack(Node **rootPtr){
  Node *root = *rootPtr;
  
  if(root->color == 'b')
    root->color = 'd';
  else if(root->color == 'r') 
    root->color = 'b';
 
  if(root->left)
    root->left->color = (root->left->color == 'd')? 'b':'r';
  if(root->right)
    root->right->color = (root->right->color == 'd')? 'b':'r';
  
}

//Function for handle case3
void SiblingIsRed(Node **rootPtr){
  Node *root = *rootPtr;
  char colour = root->color; // store the original root color

  if( root->right ){
    leftRotate(&(*rootPtr));
    (*rootPtr)->left->color = 'r';
    
    if((*rootPtr)->left && ((*rootPtr)->left->right) && ((*rootPtr)->left->right->right) ){
      NephewIsRedSiblingIsBlack(&(*rootPtr)->left); 
     // printf("leftSide, enter case1\n");
    }
    else{
      NephewAndSiblingIsBlack(&(*rootPtr)->left);  
    //  printf("leftSide, enter case2\n");
    }
  }
  else if( root->left ){
    rightRotate(&(*rootPtr));
    (*rootPtr)->right->color = 'r';
    
    if((*rootPtr)->right && ((*rootPtr)->right->left) && ((*rootPtr)->right->left->left)){
      NephewIsRedSiblingIsBlack(&(*rootPtr)->right);  
     // printf("RightSide, enter case1\n");   
    }
    else{
      NephewAndSiblingIsBlack(&(*rootPtr)->right);   
     // printf("RightSide, enter case2\n"); 
    }
  }
  (*rootPtr)->color = colour;
}
