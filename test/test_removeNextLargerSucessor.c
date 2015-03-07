#include "unity.h"
#include "Node.h"
#include "InitNode.h"
#include "Rotation.h"
#include "RedBlackTree.h"
#include "CustomAssertion.h"
#include "CException.h"
#include "ErrorCode.h"

Node node1,node2,node3,node4 ,node5, node6, node7, node8, node9, node10, node11, node12, node13, node14, node15;

void setUp(void){
	resetNode(&node1, 1);
	resetNode(&node2, 2);
	resetNode(&node3, 3);
	resetNode(&node4, 4);
	resetNode(&node5, 5);
	resetNode(&node6, 6);
	resetNode(&node7, 7);
	resetNode(&node8, 8);
	resetNode(&node9, 9);
	resetNode(&node10, 10);
	resetNode(&node11, 11);
	resetNode(&node12, 12);
	resetNode(&node13, 13);
	resetNode(&node14, 14);
	resetNode(&node15, 15);
}

void tearDown(void){

}

/**
 *  parent's left              parent's left
 *     /         successor 10     /
 *  10(r)       ------------>   NULL
 */
void test_removeNextLargerSuccessor_given_10r_then_remove_the_node_and_do_nothing(void){
  setNode(&node10, NULL, NULL, 'r');
  Node *parent = &node10, *removeNode;

  removeNode = removeNextLargerSuccessor(&parent);
  TEST_ASSERT_NULL(parent);
  TEST_ASSERT_EQUAL_PTR(removeNode, &node10);
}

/**
 *   parent's left              parent's left
 *      /         successor 10     /
 *   10(b)       ------------>  15(b)
 *       \
 *      15(r)
 */
void test_removeNextLargerSuccessor_given_10b_15r_should_remove_successor_10_and_15b_become_root(void){
  setNode(&node15, NULL,    NULL, 'r');
  setNode(&node10, NULL, &node15, 'b');
  Node *parent = &node10, *removeNode;

  removeNode = removeNextLargerSuccessor(&parent);
  TEST_ASSERT_EQUAL_PTR(    parent, &node15);
  TEST_ASSERT_EQUAL_PTR(removeNode, &node10);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node15);
}

/**
 *
 *      parrent successor 5    parrent
 *        |     -------->       |
 *       12(b)                12(b)
 *      /   \                    \
 *    5(r)  14(r)                14(r)
 *
 */
void test_removeNextLargerSuccessor_with_12b_5r_18r_should_remove_successor_5(void){
  setNode(&node5 , NULL  , NULL   , 'r');
  setNode(&node14, NULL  , NULL   , 'r');
  setNode(&node12, &node5, &node14, 'b');
  Node *parent = &node12, *removeNode;

  removeNode = removeNextLargerSuccessor(&parent);
  TEST_ASSERT_EQUAL_PTR(removeNode, &node5);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node14);
  TEST_ASSERT_EQUAL_NODE(NULL, &node14, 'b', &node12);
}

/**
 *        parrent                         parent
 *          |         successor 1           |
 *        12(b)     ------------->        12(b)
 *       /    \                          /    \
 *    5(b)    15(b)                    5(b)   15(b)
 *    /       /                              /
 *  1(r)     13(r)                          13(r)
 */
void test_removeNextLargerSuccessor_node_12b_5b_1r_15b_13r_should_remove_successor_1(void){
  setNode(&node1 , NULL   , NULL, 'r');
  setNode(&node13, NULL   , NULL, 'r');
  setNode(&node5 , &node1 , NULL, 'b');
  setNode(&node15, &node13, NULL, 'b');
  setNode(&node12, &node5 , &node15, 'b');
  Node *parent = &node12, *removeNode;

  removeNode = removeNextLargerSuccessor(&parent);
  TEST_ASSERT_EQUAL_PTR(removeNode, &node1);
  TEST_ASSERT_EQUAL_PTR(parent, &node12);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(&node13, NULL, 'b', &node15);
  TEST_ASSERT_EQUAL_NODE(&node5, &node15, 'b', &node12);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node13);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
}

/**
 *        parrent                         parent
 *          |         successor 1           |
 *        12(b)     ------------->        12(b)
 *       /     \                          /    \
 *    5(b)      14(b)                   5(b)   14(b)
 *    /  \     /    \                   /  \    /   \
 *  1(b) 7(b)  13(b) 15(b)           2(b) 7(b) 13(b) 15(b)
 *    \
 *   2(r)
 */
void test_removeNextLargerSuccessor_node_12b_5b_1b_2r_15b_13r_should_remove_successor_1_and_promo_2b(void){
  setNode(&node2 , NULL   , NULL   , 'r');
  setNode(&node7 , NULL   , NULL   , 'b');
  setNode(&node13, NULL   , NULL   , 'b');
  setNode(&node15, NULL   , NULL   , 'b');
  setNode(&node1 , NULL   , &node2 , 'b');
  setNode(&node5 , &node1 , &node7 , 'b');
  setNode(&node14, &node13, &node15, 'b');
  setNode(&node12, &node5 , &node14, 'b');
  Node *parent = &node12, *removeNode;

  removeNode = removeNextLargerSuccessor(&parent);
  TEST_ASSERT_EQUAL_PTR(removeNode, &node1);
  TEST_ASSERT_EQUAL_PTR(parent, &node12);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node7);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node13);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node15);
  TEST_ASSERT_EQUAL_NODE(&node2 , &node7 , 'b', &node5 );
  TEST_ASSERT_EQUAL_NODE(&node13, &node15, 'b', &node14);
  TEST_ASSERT_EQUAL_NODE(&node5 , &node14, 'b', &node12);
}

/**
 *        parrent                         parent                                   parent
 *          |         successor 1           |                                         ||
 *        12(b)     ------------->        12(b)           ------------->            12(d)
 *       /     \                         //    \                                    /    \
 *    5(b)      14(b)                   5(d)   14(b)                              5(b)   14(r)
 *    /  \     /    \                     \    /   \                                \    /   \
 *  1(b) 7(b)  13(b) 15(b)               7(r) 13(b) 15(b)                         7(r) 13(b) 15(b)
 *
 */
void test_removeNextLargerSuccessor_node_12b_5b_1b_15b_13r_should_remove_successor_1_and_promo_double_black(void){
  setNode(&node1 , NULL   , NULL   , 'r');
  setNode(&node7 , NULL   , NULL   , 'b');
  setNode(&node13, NULL   , NULL   , 'b');
  setNode(&node15, NULL   , NULL   , 'b');
  setNode(&node5 , &node1 , &node7 , 'b');
  setNode(&node14, &node13, &node15, 'b');
  setNode(&node12, &node5 , &node14, 'b');
  Node *parent = &node12, *removeNode;

  removeNode = removeNextLargerSuccessor(&parent);
  TEST_ASSERT_EQUAL_PTR(removeNode, &node1);
  TEST_ASSERT_EQUAL_PTR(parent, &node12);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL  , 'r', &node7);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL  , 'b', &node13);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL  , 'b', &node15);
  TEST_ASSERT_EQUAL_NODE(NULL, &node7, 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(&node13, &node15, 'r', &node14);
  TEST_ASSERT_EQUAL_NODE(&node5, &node14, 'd', &node12);
}

