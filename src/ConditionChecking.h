#ifndef ConditionChecking_H
#define ConditionChecking_H
#include "Node.h"

int gotChildNode(Node **rootPtr);
int noChildNode(Node **rootPtr);
int checkHowManyChildNode(Node *rootPtr);
int checkWhichHasMoreChildNode(Node *rootPtr1, Node *rootPtr2);
int determineUnbalanceTree(Node **rootPtr);
int isDoubleBlack(Node *rootPtr, Node *removedNode);
int bothChildNodeIsBlack(Node *rootPtr);
