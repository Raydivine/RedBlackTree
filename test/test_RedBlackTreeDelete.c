#include "unity.h"
#include "Node.h"
#include "InitNode.h"
#include "Rotation.h"
#include "RedBlackTree.h"
#include "CustomAssertion.h"
#include "CException.h"
#include "ErrorCode.h"

Node node1,node2,node3,node4 ,node5, node6, node7, node8, node9, node10, node11, node12, node13, node14, node15, node20;

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
}

void tearDown(void){

}


/**
 *      Root
 *        |     remove2
 *       v     ------> Throw ERR_NODE_UNAVAIBLE
 *      1[b]
 */
void test_delRedBlackTree_given_remove_2_from_should_throw_error(void){
  CEXCEPTION_T err;
  setNode(&node1, NULL	, NULL, 'b');
  setNode(&node2, NULL	, NULL, 'b');

  Node *root = &node1;
  Try{
    delRedBlackTree( &root, &node2);
    TEST_FAIL_MESSAGE("Expected ERR_NODE_UNAVAIBLE");
  }Catch(err){
    TEST_ASSERT_EQUAL_MESSAGE(ERR_NODE_UNAVAIBLE, err, "Expected ERR_NODE_UNAVAIBLE");
  }
}

/**
 *      Root                Root
 *        |                  |
 *       v      remove1     v
 *      1[b]   ------>      NULL
 */
void test_delRedBlackTree_given_remove_1_from_with_root_1(void){
  setNode(&node1, NULL, NULL, 'b');
  Node *root = &node1, *node;

  node = delRedBlackTree( &root, &node1);
  TEST_ASSERT_EQUAL_PTR(node , &node1);
  TEST_ASSERT_NULL(root);
}

/**
 *      Root                Root
 *        |                  |
 *       v      remove4      v
 *      5[b]   ------>      5[b]
 *     /   \                  \
 *  4[b]    9[b]              9[b]
 */
void test_delRedBlackTree_given_remove_4_from_with_root_5(void){
  setNode(&node4, NULL,   NULL, 'b');
  setNode(&node9, NULL,   NULL, 'b');
  setNode(&node5, &node4, &node9, 'b');
  Node *root = &node5, *node;

  node = delRedBlackTree(&root, &node4);
  TEST_ASSERT_NOT_NULL(root);
  TEST_ASSERT_EQUAL(root, &node5);
  TEST_ASSERT_EQUAL(node5.right, &node9);
  TEST_ASSERT_NULL(node5.left);
  TEST_ASSERT_EQUAL_PTR(node , &node4);
}

// CASE 1(a)
/**   Root                    Root
 *       |                      |
 *       v                      v
 *      4(b)                  9(b)
 *         \       rotate      /   \
 *        9(b)  ---------> 4(b)   12(b)
 *           \
 *           12(r)
 */
void test_NephewIsRedSiblingIsBlack_should_leftRotate(void){
  setNode(&node12, NULL, NULL   , 'r');
  setNode(&node9 , NULL, &node12, 'b');
  setNode(&node4 , NULL, &node9 , 'b');
  Node *root = &node4;

  NephewIsRedSiblingIsBlack(&root);
  TEST_ASSERT_EQUAL_PTR(root, &node9);
  TEST_ASSERT_EQUAL_NODE(NULL  , NULL   , 'b', &node4);
  TEST_ASSERT_EQUAL_NODE(&node4, &node12, 'b', &node9);
  TEST_ASSERT_EQUAL_NODE(NULL  , NULL   , 'b', &node12);
}

// CASE 1(b)
/**        Root                   Root
 *           |                      |
 *          v                       v
 *         4(r)                   7(r)
 *            \       rotate      /   \
 *            9(b)  ---------> 4(b)   9(b)
 *           /
 *         7[r]
 */
void test_NephewIsRedSiblingIsBlack_should_rightLeftRotate(void){
  setNode(&node7 , NULL  , NULL   , 'r');
  setNode(&node9 , &node7, NULL   , 'b');
  setNode(&node4 , NULL  , &node9 , 'r');
  Node *root = &node4, *node;

  NephewIsRedSiblingIsBlack(&root);
  TEST_ASSERT_EQUAL_PTR(root, &node7);
  TEST_ASSERT_EQUAL_NODE(NULL  , NULL  , 'b', &node4);
  TEST_ASSERT_EQUAL_NODE(NULL  , NULL  , 'b', &node9);
  TEST_ASSERT_EQUAL_NODE(&node4, &node9, 'r', &node7);
}

// CASE 1(c)
/**         Root               Root
 *          |                  |
 *          v                 v
 *        5(r)               3(r)
 *       /      rotate      /   \
 *     3(b)  ---------> 2(b)   5(b)
 *     /
 *   2(r)
 */
void test_NephewIsRedSiblingIsBlack_should_rightRotate(void){
  setNode(&node2, NULL  , NULL, 'r');
  setNode(&node3, &node2, NULL, 'b');
  setNode(&node5, &node3, NULL, 'r');
  Node *root = &node5;

  NephewIsRedSiblingIsBlack(&root);
  TEST_ASSERT_EQUAL_PTR(root, &node3);
  TEST_ASSERT_EQUAL_NODE(NULL  , NULL  , 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL  , NULL  , 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(&node2, &node5, 'r', &node3);
}

// CASE 1(d)
/**         Root               Root
 *          |                  |
 *          v                 v
 *        5(r)               4(r)
 *       /      rotate      /   \
 *     3(b)  ---------> 3(b)   5(b)
 *        \
 *        4(r)
 */
void test_NephewIsRedSiblingIsBlack_should_leftRightRotate(void){
  setNode(&node4, NULL  ,   NULL, 'r');
  setNode(&node3, NULL  , &node4, 'b');
  setNode(&node5, &node3,   NULL, 'r');
  Node *root = &node5;

  NephewIsRedSiblingIsBlack(&root);
  TEST_ASSERT_EQUAL_PTR(root, &node4);
  TEST_ASSERT_EQUAL_NODE(NULL  , NULL  , 'b', &node3);
  TEST_ASSERT_EQUAL_NODE(NULL  , NULL  , 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(&node3, &node5, 'r', &node4);
}

// CASE 1(a) Full
/**        Root                     Root                  Root
 *           |                        |                     |
 *          v                         v                     v
 *         4(b)                     4(b)                  9(b)
 *        /    \      remove 3     //  \      rotate      /   \
 *      3(b)  9(b)  ---------->       9(r)  ---------> 4(b)   12(b)
 *               \                      \
 *                12(r)                  12(r)
 */
void test_delRedBlackTree_remove_3_from_tree_should_rotate_and_and_new_root_color_is_same_as_original_root_color(void){
  setNode(&node3 , NULL  , NULL   , 'b');
  setNode(&node12, NULL  , NULL   , 'r');
  setNode(&node9 , NULL  , &node12, 'b');
  setNode(&node4 , &node3, &node9 , 'b');
  Node *root = &node4, *node;

  node = delRedBlackTree(&root, &node3);
  TEST_ASSERT_EQUAL_PTR(node, &node3);
  TEST_ASSERT_EQUAL_PTR(root, &node9);
  TEST_ASSERT_EQUAL_NODE(NULL  , NULL   , 'b', &node4);
  TEST_ASSERT_EQUAL_NODE(&node4, &node12, 'b', &node9);
  TEST_ASSERT_EQUAL_NODE(NULL  , NULL   , 'b', &node12);
}

// CASE 1(b) Full
/**        Root                     Root                  Root
 *           |                        |                     |
 *          v                         v                     v
 *         4(b)                     4(b)                  7(b)
 *        /    \      remove 3    //    \     rotate      /   \
 *      3(b)  9(b)  ---------->       9(r)  ---------> 4(b)   9(b)
 *           /                       /
 *         7[r]                     7[r]
 */
void test_delRedBlackTree_remove_3_from_tree_should_rotate_and_and_new_root_should_change_to_r_color(void){
  setNode(&node3 , NULL  , NULL   , 'b');
  setNode(&node7 , NULL  , NULL   , 'r');
  setNode(&node9 , &node7, NULL   , 'b');
  setNode(&node4 , &node3, &node9 , 'b');
  Node *root = &node4, *node;

  node = delRedBlackTree(&root, &node3);
  TEST_ASSERT_EQUAL_PTR(node, &node3);
  TEST_ASSERT_EQUAL_PTR(root, &node7);
  TEST_ASSERT_EQUAL_NODE(NULL  , NULL  , 'b', &node4);
  TEST_ASSERT_EQUAL_NODE(NULL  , NULL  , 'b', &node9);
  TEST_ASSERT_EQUAL_NODE(&node4, &node9, 'b', &node7);
}

//CASE 2(a)
/**
 *      Root               Root
 *        |                  |
 *        v                  v
 *        |   dd black      ||
 *      2[b]  ----->      2[d]
 *     //  \                 \
 *        3[b]              3[r]
 */
void test_NephewAndSiblingIsBlack_change_2_to_double_black_change_3_to_red(void){
  setNode(&node1, NULL,   NULL, 'd');
  setNode(&node3, NULL,   NULL, 'b');
  setNode(&node2, &node1, &node3, 'b');
  Node *root = &node2, *node;

  node = NephewAndSiblingIsBlack(&root);
  TEST_ASSERT_EQUAL(root, &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL  , 'r', &node3);
  TEST_ASSERT_EQUAL_NODE(NULL, &node3, 'd', &node2);
}

//CASE 2(b)
/**
 *      Root               Root
 *        |                  |
 *        v                  v
 *        |   dd black      |
 *      2[r]  ----->      2[b]
 *     //  \                 \
 *        3[b]              3[r]
 */
void test_NephewAndSiblingIsBlack_change_2_to__black_change_3_to_red(void){
  setNode(&node1, NULL,   NULL, 'd');
  setNode(&node3, NULL,   NULL, 'b');
  setNode(&node2, &node1, &node3, 'r');
  Node *root = &node2, *node;

  node = NephewAndSiblingIsBlack(&root);
  TEST_ASSERT_EQUAL(root, &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL  , 'r', &node3);
  TEST_ASSERT_EQUAL_NODE(NULL, &node3, 'b', &node2);
}

//CASE 2(a) full
/**
 *      Root                  Root              Root
 *        |                     |                 |
 *        v                    v                  v
 *        |   remove1          |   dd black      ||
 *      2[b]   ------>       2[b]  ----->      2[d]
 *     /   \                //  \                 \
 *  1[b]    3[b]                3[b]              3[r]
 */
void test_delRedBlackTree_remove_1_should_change_2_to_double_black_change_3_to_red(void){
  setNode(&node1, NULL,   NULL, 'b');
  setNode(&node3, NULL,   NULL, 'b');
  setNode(&node2, &node1, &node3, 'b');
  Node *root = &node2, *node;

  node = delRedBlackTree(&root, &node1);
  TEST_ASSERT_EQUAL(root, &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL  , 'r', &node3);
  TEST_ASSERT_EQUAL_NODE(NULL, &node3, 'd', &node2);
}

//CASE 2(b) full
/**
 *      Root                  Root              Root
 *        |                     |                 |
 *        v                    v                  v
 *        |   remove1          |   dd black      |
 *      2[r]   ------>       2[r]  ----->      2[b]
 *     /   \                //  \                 \
 *  1[b]    3[b]                3[b]              3[r]
 */
void test_delRedBlackTree_remove_1_should_change_2_to_from_r_to_d_change_3_to_r(void){
  setNode(&node1, NULL,   NULL, 'b');
  setNode(&node3, NULL,   NULL, 'b');
  setNode(&node2, &node1, &node3, 'r');
  Node *root = &node2, *node;

  node = delRedBlackTree(&root, &node1);
  TEST_ASSERT_EQUAL(root, &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL  , 'r', &node3);
  TEST_ASSERT_EQUAL_NODE(NULL, &node3, 'b', &node2);
}

/**case 3(a)
 *                 Root                               Root                               Root
 *                 |                                   |                                 |
 *                 v                                   v                                 v
 *                 |                                  |                                  |
 *               2(b)          left-rotate          4(b)         Use Case 2            4(b)
 *             //     \           ---->            /    \           ---->            /      \
 *           (d)      4(r)                      2(r)    5(b)                      2(b)       5(b)
 *                    /    \                   //  \                                \
 *                3(b)     5(b)             (d)    3(b)                             3(r)
 */
void test_SiblingIsRed_should_remove_1_should_left_rotate(void) {
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node5, NULL, NULL, 'b');
  setNode(&node1, NULL, NULL, 'd');
  setNode(&node4, &node3, &node5, 'r');
  setNode(&node2, &node1, &node4, 'b');
  Node *root = &node2, *node;

  node = SiblingIsRed(&root);
  TEST_ASSERT_EQUAL_PTR(&node4, root);
  TEST_ASSERT_EQUAL_NODE(&node2, &node5, 'b', root);
  TEST_ASSERT_EQUAL_NODE(NULL, &node3, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node3);
}

/**case 3(a) full
 *                 Root                              Root                               Root                               Root
 *                 |                                  |                                   |                                 |
 *                 v                                  v                                   v                                 v
 *                 |                                  |                                  |                                  |
 *               2(b)           remove 1            2(b)          left-rotate          4(b)         Use Case 2            4(b)
 *             /   \            ---->            //     \           ---->            /    \           ---->            /      \
 *         1(b)     4(r)                       (d)       4(r)                    2(r)      5(b)                    2(b)        5(b)
 *                /     \                              /    \                   //   \                                \
 *             3(b)      5(b)                      3(b)      5(b)             (d)     3(b)                             3(r)
 */
void test_delRedBlackTree_remove_1_should_left_rotate_and_apply_case_2(void) {
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node5, NULL, NULL, 'b');
  setNode(&node4, &node3, &node5, 'r');
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node2, &node1, &node4, 'b');
  Node *root = &node2, *node;

  node = _delRedBlackTree(&root, &node1);
  TEST_ASSERT_EQUAL_PTR(&node1, node);
  TEST_ASSERT_EQUAL_PTR(&node4, root);
  TEST_ASSERT_EQUAL_NODE(&node2, &node5, 'b', root);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(NULL, &node3, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node3);
}

/** Case 3(b) Full
 *
 * root -> 10(b)                    10(b) <- root                    5(b) <- root                5(b) <- root
 *        /    \      remove 15    /   \\     right rotate          /   \         case2         /   \
 *      5(r)  15(b)  ----------> 5(r)  NULL   ---------->         1(b) 10(r)    ---------->  1(b) 10(b)
 *     /   \                    /   \                                   /  \\                      /
 *   1(b)  7(b)               1(b)  7(b)                            7(b) NULL                    7(r)
 */
void test_delRedBlackTree_remove_15_should_right_rotate_and_apply_case_2(void){
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node7, NULL, NULL, 'b');
  setNode(&node5, &node1, &node7, 'r');
  setNode(&node15, NULL, NULL, 'b');
  setNode(&node10, &node5, &node15, 'b');
  Node *root = &node10, *node;

  node = delRedBlackTree(&root, &node15);
  TEST_ASSERT_EQUAL_PTR(&node5, root);
  TEST_ASSERT_EQUAL_PTR(&node15, node);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
  TEST_ASSERT_EQUAL_NODE(&node7, NULL, 'b', &node10);
  TEST_ASSERT_EQUAL_NODE(&node1, &node10, 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node7);
}

/** Case 3(c) Full
 *
 *     10(b) <- root            10(b) <- root               15(b)  <- root           15(b) <- root
 *    /    \      remove 5     //   \         left rotate  /   \         case1       /   \
 *  5(b)  15(r)  ----------> NULL  15(r)    ----------> 10(r) 20(b)   ----------> 13(r) 20(b)
 *        /   \                    /   \                //  \                     /   \
 *     13(b) 20(b)              13(b) 20(b)           NULL 13(b)               10(b)  14(b)
 *         \                        \                          \
 *        14(r)                    14(r)                      14(r)
 */
void test_delRedBlackTree_remove_5_from_tree_with_5_10_13_14_15_20_nodes_with_case_3(void){
  setNode(&node5, NULL, NULL, 'b');
  setNode(&node14, NULL, NULL, 'r');
  setNode(&node13, NULL, &node14, 'b');
  setNode(&node20, NULL, NULL, 'b');
  setNode(&node15, &node13, &node20, 'r');
  setNode(&node10, &node5, &node15, 'b');
  Node *root = &node10, *node;

  node = delRedBlackTree(&root, &node5);
  TEST_ASSERT_EQUAL_PTR(&node15, root);
  TEST_ASSERT_EQUAL_PTR(&node5, node);
  TEST_ASSERT_EQUAL_NODE(&node13, &node20, 'b', &node15);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node14);
  TEST_ASSERT_EQUAL_NODE(&node10, &node14, 'r', &node13);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node20);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node10);
}

/**
 *      parent's left                      parent's left                    parent's left
 *            |                                 |                               |
 *            v                                 v                               v
 *         8(r)                               8(r)                            8(b)
 *       /     \        remove 10          /       \        color flip     /       \
 *    5(b)     10(b)   ------------>    5(b)       11(b)  ------------> 5(r)      11(r)
 *    /   \     /   \                  /   \       /                   /   \       /
 *  1(b) 7(b)  9(b) 11(b)            1(b) 7(b)  9(b)                 1(b) 7(b)  9(b)
 */
void test_delRedBlackTree_remove_10_should_replace_with_11(void){
  setNode(&node1 , NULL, NULL, 'b');
  setNode(&node7 , NULL, NULL, 'b');
  setNode(&node9 , NULL, NULL, 'b');
  setNode(&node11, NULL, NULL, 'b');
  setNode(&node10, &node9 , &node11, 'b');
  setNode(&node5 , &node1 , &node7 , 'b');
  setNode(&node8 , &node5 , &node10, 'r');
  Node *root = &node8, *removeNode;

  removeNode = delRedBlackTree(&root, &node10);
  TEST_ASSERT_EQUAL_PTR(&node8, root);
  TEST_ASSERT_EQUAL_PTR(&node10, removeNode);
  TEST_ASSERT_EQUAL_NODE(&node5, &node11, 'b', &node8);
  TEST_ASSERT_EQUAL_NODE(&node1, &node7 , 'r', &node5);
  TEST_ASSERT_EQUAL_NODE(&node9, NULL, 'r', &node11);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node9);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node7);
}

/**
 *      parent's left                      parent's left                    parent's left
 *            |                                 |                               |
 *            v                                 v                              v
 *         8(r)                              9(r)                            9(b)
 *       /     \        remove 8          /       \         color flip     /     \
 *    5(b)     10(b)   ------------>    5(b)      10(b)  ------------>  5(r)     10(r)
 *    /   \     /   \                  /   \         \                 /   \        \
 *  1(b) 7(b)  9(b) 11(b)            1(b) 7(b)        11(b)          1(b) 7(b)      11(b)
 */
void test_delRedBlackTree_remove_8_should_replace_with_9(void){
  setNode(&node1 , NULL, NULL, 'b');
  setNode(&node7 , NULL, NULL, 'b');
  setNode(&node9 , NULL, NULL, 'b');
  setNode(&node11, NULL, NULL, 'b');
  setNode(&node10, &node9 , &node11, 'b');
  setNode(&node5 , &node1 , &node7 , 'b');
  setNode(&node8 , &node5 , &node10, 'r');
  Node *root = &node8, *removeNode;

  removeNode = delRedBlackTree(&root, &node8);
  TEST_ASSERT_EQUAL_PTR(&node9, root);
  TEST_ASSERT_EQUAL_PTR(&node8, removeNode);
  TEST_ASSERT_EQUAL_NODE(&node5, &node10, 'b', &node9);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node7);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node11);
  TEST_ASSERT_EQUAL_NODE(NULL  , &node11, 'r', &node10); // fail this 2 line ,
  TEST_ASSERT_EQUAL_NODE(&node1, &node7 , 'r', &node5) ; // should enter case2  ,and flip the color from 'b' to 'r'
}