#include "unity.h"
#include "Node.h"
#include "InitNode.h"
#include "Rotation.h"
#include "RedBlackTree.h"
#include "CustomAssertion.h"
#include "CException.h"
#include "ErrorCode.h"

Node node1,node2,node3,node4 ,node5, node6, node7, node8, node9, node10, node11, node12, node13, node14, node15, node20, node22, node30, node40, node60;;

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
  resetNode(&node20, 20);
	resetNode(&node22, 22);
	resetNode(&node30, 30);
	resetNode(&node40, 40);
	resetNode(&node60, 60);
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
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', removeNode);
}

/**
 *       parent                     parent
 *        |                          |
 *        V                          v
 *       1 (b)   successor 1 (b)     // (DoubleBlack)
 *                 ---->            -
 */
void test_removeSuccessor_remove_successor_with_parent_10b(void)  {
  setNode(&node1, NULL, NULL, 'b');
  Node *parent = &node1;

  Node *removedNode = removeNextLargerSuccessor(&parent);
  TEST_ASSERT_NOT_NULL(removedNode);
  TEST_ASSERT_EQUAL(1, removedNode->data);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', removedNode);
  TEST_ASSERT_NULL(parent);
  TEST_ASSERT_EQUAL(1, isDoubleBlack(parent, removedNode));
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
  TEST_ASSERT_EQUAL(15, parent->data);
  TEST_ASSERT_EQUAL(10, removeNode->data);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node15);
}

/** 
 *         parent                         parent
 *           |                              |
 *           V                              v
 *          5(b)   successor  2(r)         5(b)
 *        /    \        ---->            /    \
 *    2(r)      -                      -       -
 */
void test_removeSuccessor_remove_successor_with_parent_5_and_right_child_is_NULL(void)  {
  setNode(&node2, NULL, NULL, 'r');
  setNode(&node5, &node2, NULL, 'b');
  Node *parent = &node5;

  Node *removedNode = removeNextLargerSuccessor(&parent);
  TEST_ASSERT_NOT_NULL(removedNode);
  TEST_ASSERT_EQUAL(2, removedNode->data);
  TEST_ASSERT_NOT_NULL(parent);
  TEST_ASSERT_EQUAL(5, parent->data);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', parent);
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

/**(case 1)
 *                 parent's left                      parent's left                     parent's left
 *                  |                                   |                                     |
 *                  V                                   v                                     v
 *                 5(b)       successor 1(b)           5(b)         restructure               8(b)
 *               /     \          ---->              //    \          ----->                /     \
 *           1(b)      8(b)                         -       8(b)                          5(b)    10(b)
 *          /    \    /    \                              /     \
 *        -       -  -      10(r)                        -       10(r)
 */
void test_removeNextLargerSuccessor_case1_with_root_5_and_right_child_8r_10b(void)  {
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node10, NULL, NULL, 'r');
  setNode(&node8, NULL, &node10, 'b');
  setNode(&node5, &node1, &node8, 'b');
  Node *parent = &node5;

  printf("start\n");
  Node *removedNode = removeNextLargerSuccessor(&parent);
  printf("end\n");
  TEST_ASSERT_NOT_NULL(removedNode);
  TEST_ASSERT_NOT_NULL(parent);
  TEST_ASSERT_EQUAL(1, removedNode->data);
  TEST_ASSERT_EQUAL(8, parent->data);
  TEST_ASSERT_EQUAL_NODE(&node5, &node10, 'b', parent);
  TEST_ASSERT_EQUAL_NODE(&node5, &node10, 'b', &node8);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node10);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
  
}

/** case 1b
 *                 parent->left                         parent->left
 *                  |                                   |
 *                  V                                   v
 *                 5(b)       successor 3(b)            6(b)
 *               /     \          ---->               /      \
 *           3(b)        7(b)                     5(b)        7(b)
 *          /    \      /    \                  /    \      /     \
 *         -      -  6(r)     -                -      -    -       -
 */
void test_removeNextLargerSuccessor_case1_with_root_5_one_red_sibling_and_two_black_nephews(void)  {
  setNode(&node6, NULL, NULL, 'r');
  setNode(&node7, &node6, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node5, &node3, &node7, 'b');
  Node *parent = &node5;

  Node *removedNode = removeNextLargerSuccessor(&parent);
  TEST_ASSERT_NOT_NULL(removedNode);
  TEST_ASSERT_EQUAL(3, removedNode->data);
  TEST_ASSERT_NOT_NULL(parent);
  TEST_ASSERT_EQUAL_NODE(&node5, &node7, 'b', parent);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node7);
}

/** (case 1)
 *                 parent->left                         parent->left
 *                  |                                   |
 *                  V                                   v
 *                 4(b)       successor 1(r)            4(b)
 *              /      \          ---->               /      \
 *          2(b)        7(b)                     2(b)        7(b)
 *        /    \       /    \                  /    \      /     \
 *      1(r)   3(r) 6(r)     8(r)            -      3(r)  6(r)    8(r)
 */
void test_removeNextLargerSuccessor_case1_with_root_4_one_black_sibling_two_red_nephews(void)  {
  setNode(&node1, NULL, NULL, 'r');
  setNode(&node3, NULL, NULL, 'r');
  setNode(&node6, NULL, NULL, 'r');
  setNode(&node8, NULL, NULL, 'r');
  setNode(&node2, &node1, &node3, 'b');
  setNode(&node7, &node6, &node8, 'b');
  setNode(&node4, &node2, &node7, 'b');
  Node *parent = &node4;

  Node *removedNode = removeNextLargerSuccessor(&parent);
  TEST_ASSERT_NOT_NULL(removedNode);
  TEST_ASSERT_EQUAL(1, removedNode->data);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', removedNode);
  TEST_ASSERT_NOT_NULL(parent);
  TEST_ASSERT_EQUAL(4, parent->data);
  TEST_ASSERT_EQUAL_NODE(&node2, &node7, 'b', parent);
  TEST_ASSERT_EQUAL_NODE(NULL, &node3, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node3);
  TEST_ASSERT_EQUAL_NODE(&node6, &node8, 'b', &node7);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node6);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node8);
}

/**case 2
 *             parent->left                         parent->left
 *                  |                                   |
 *                  V                                   v             promote double black
 *                 4(b)       successor 1(b)           4(b)           to 2(b) (case 2)
 *              /      \          ---->             /       \            ----->
 *          2(b)        7(b)                     2(b)       7(b)
 *        /    \       /    \                  //   \      /    \
 *    1(b)     3(b)  6(b)   8(b)              -     3(b) 6(b)   8(b)
 *
 *          parent->left                            parent->left
 *              |                                       |
 *              v                                       v//
 *             4(b)           colour flip              4(b)
 *          //     \          ------>                 /     \
 *      2(d)        7(b)                           2(b)     7(r)
 *    /     \      /    \                         /   \    /    \
 *   -      3(r)  6(b)   8(b)                    -   3(r) 6(b)  8(b)
 */
void xtest_removeNextLargerSuccessor_case2_with_root_4b_one_black_sibling_two_black_nephews(void){
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node6, NULL, NULL, 'b');
  setNode(&node8, NULL, NULL, 'b');
  setNode(&node2, &node1, &node3, 'b');
  setNode(&node7, &node6, &node8, 'b');
  setNode(&node4, &node2, &node7, 'b');
  Node *parent = &node4;

  printf("start\n");
  Node *removedNode = removeNextLargerSuccessor(&parent);
  printf("end\n");
  TEST_ASSERT_NOT_NULL(removedNode);
  TEST_ASSERT_EQUAL(1, removedNode->data);
  TEST_ASSERT_NOT_NULL(parent);
  TEST_ASSERT_EQUAL(4, parent->data);
  TEST_ASSERT_EQUAL_NODE(&node2, &node7, 'd', parent);
  TEST_ASSERT_EQUAL_NODE(NULL, &node3, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node3);
  TEST_ASSERT_EQUAL_NODE(&node6, &node8, 'r', &node7);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node6);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node8);
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
void xtest_removeNextLargerSuccessor_node_12b_5b_1r_15b_13r_should_remove_successor_1(void){
  setNode(&node1 , NULL   , NULL, 'r');
  setNode(&node13, NULL   , NULL, 'r');
  setNode(&node5 , &node1 , NULL, 'b');
  setNode(&node15, &node13, NULL, 'b');
  setNode(&node12, &node5 , &node15, 'b');
  Node *parent = &node12, *removeNode;

  printf("start\n");
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
void xtest_removeNextLargerSuccessor_node_12b_5b_1b_2r_15b_13r_should_remove_successor_1_and_promo_2b(void){
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




