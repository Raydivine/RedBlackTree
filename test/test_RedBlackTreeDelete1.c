#include "unity.h"
#include "Node.h"
#include "InitNode.h"
#include "Rotation.h"
#include "RedBlackTree.h"
#include "CustomAssertion.h"
#include "CException.h"
#include "ErrorCode.h"

Node node1,node2,node3,node4 ,node5, node6, node7, node8, node9, node10, node11, node12, node13, node14, node15, node20, node22, node30, node40, node60;

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

/**rotation & flip color cases
 *               Root                               Root
 *                |                                  |
 *                v                                  v
 *              5(b)                               5(b)
 *            /    \           ---->             /     \
 *          2(r)    8(b)     remove 1        2(b)       8(b)
 *        /    \                                \
 *    1(b)      3(b)                             3(r)
 */
void test_delRedBlackTree_remove_1_without_rotation_but_flip_color_with_3_parents_and_2_childs(void) {
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node2, &node1, &node3, 'r');
  setNode(&node8, NULL, NULL, 'b');
  setNode(&node5, &node2, &node8, 'b');
  Node *root, *node;
  root = &node5;

  node = delRedBlackTree(&root, &node1);
  TEST_ASSERT_EQUAL_PTR(&node1, node);
  TEST_ASSERT_EQUAL_PTR(root, &node5);
  TEST_ASSERT_EQUAL_NODE(&node2, &node8, 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node3);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node8);
  TEST_ASSERT_EQUAL_NODE(NULL, &node3, 'b', &node2);

}

/**rotation & flip color cases
 *               Root                               Root
 *                |                                  |
 *                v                                  v
 *              5(b)                               5(b)
 *            /    \           ---->             /     \
 *          2(r)    8(b)     remove 3        2(b)       8(b)
 *        /    \                            /
 *    1(b)      3(b)                     1(r)
 */
void test_delRedBlackTree_remove_3_without_rotation_but_flip_color_with_3_parents_and_2_childs(void) {
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node2, &node1, &node3, 'r');
  setNode(&node8, NULL, NULL, 'b');
  setNode(&node5, &node2, &node8, 'b');
  Node *root, *node;
  root = &node5;

  node = delRedBlackTree(&root, &node3);
  TEST_ASSERT_EQUAL_PTR(&node3, node);
  TEST_ASSERT_EQUAL_PTR(root, &node5);
  TEST_ASSERT_EQUAL_NODE(&node2, &node8, 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(&node1, NULL, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node1);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node8);
}

/**rotation & flip color cases
 *               Root                               Root
 *                |                                  |
 *                v                                  v
 *              2(b)                               2(b)
 *            /    \           ---->             /     \
 *          1(b)    5(r)     remove 3        1(b)       5(b)
 *                 /    \                                 \
 *            3(b)      6(b)                               6(r)
 */
void test_delRedBlackTree_remove_3_without_rotation_but_flip_color_with_root_2_two_parents_and_two_childs(void) {
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node6, NULL, NULL, 'b');
  setNode(&node5, &node3, &node6, 'r');
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node2, &node1, &node5, 'b');
  Node *root, *node;
  root = &node2;
  
  node = delRedBlackTree(&root, &node3);
  TEST_ASSERT_EQUAL_PTR(&node3, node);
  TEST_ASSERT_EQUAL_PTR(root, &node2);
  TEST_ASSERT_EQUAL_NODE(&node1, &node5, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
  TEST_ASSERT_EQUAL_NODE(NULL, &node6, 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node6);
}

/**rotation & flip color cases
 *               Root                               Root
 *                |                                  |
 *                v                                  v
 *              2(b)                               2(b)
 *            /    \           ---->             /     \
 *          1(b)    5(r)     remove 6        1(b)       5(b)
 *                 /   \                              /
 *            3(b)      6(b)                      3(r)
 */
void test_delRedBlackTree_remove_6_without_rotation_but_flip_color_with_root_2_two_parents_and_two_childs(void) {
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node6, NULL, NULL, 'b');
  setNode(&node5, &node3, &node6, 'r');
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node2, &node1, &node5, 'b');
  Node *root, *node;
  root = &node2;

  node = delRedBlackTree(&root, &node6);
  TEST_ASSERT_EQUAL_PTR(&node6, node);
  TEST_ASSERT_EQUAL_PTR(root, &node2);
  TEST_ASSERT_EQUAL_NODE(&node1, &node5, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
  TEST_ASSERT_EQUAL_NODE(&node3, NULL, 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node3);
}

/**flip color cases
 *               Root                                   Root
 *                |                                      |
 *                v                                      v
 *              4(b)            remove 1                4(b)
 *            /      \           ---->               /       \
 *       2(r)          6(r)                      2(b)          6(b)
 *     /    \         /    \                        \         /   \
 * 1(b)      3(b) 5(b)      7(b)                     3(r)  5(b)     7(b)
 */
void test_delRedBlackTree_remove_1_without_rotation_but_flip_color_with_root_4_two_parents_and_4_childs(void) {
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node2, &node1, &node3, 'r');
  setNode(&node5, NULL, NULL, 'b');
  setNode(&node7, NULL, NULL, 'b');
  setNode(&node6, &node5, &node7, 'r');
  setNode(&node4, &node2, &node6, 'b');
  Node *root, *node;
  root = &node4;
  
  node = delRedBlackTree(&root, &node1);
  TEST_ASSERT_EQUAL_PTR(&node1, node);
  TEST_ASSERT_EQUAL_PTR(root, &node4);
  TEST_ASSERT_EQUAL_NODE(&node2, &node6, 'b', &node4);
  TEST_ASSERT_EQUAL_NODE(NULL, &node3, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node3);

  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node7);
  TEST_ASSERT_EQUAL_NODE(&node5, &node7, 'b', &node6);
}

/**flip color cases
 *               Root                                   Root
 *                |                                      |
 *                v                                      v
 *              4(b)            remove 3                4(b)
 *            /      \           ---->               /       \
 *       2(r)          6(r)                      2(b)          6(b)
 *     /    \         /    \                    /             /   \
 * 1(b)      3(b) 5(b)      7(b)             1(r)         5(b)     7(b)
 */
void test_delRedBlackTree_remove_3_without_rotation_but_flip_color_with_root_4_two_parents_and_4_childs(void) {
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node2, &node1, &node3, 'r');
  setNode(&node5, NULL, NULL, 'b');
  setNode(&node7, NULL, NULL, 'b');
  setNode(&node6, &node5, &node7, 'r');
  setNode(&node4, &node2, &node6, 'b');
  Node *root, *node;
  root = &node4;

  node = delRedBlackTree(&root, &node3);
  TEST_ASSERT_EQUAL_PTR(&node3, node);
  TEST_ASSERT_EQUAL_PTR(root, &node4);
  TEST_ASSERT_EQUAL_NODE(&node2, &node6, 'b', &node4);
  TEST_ASSERT_EQUAL_NODE(&node1, NULL, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node1);
  TEST_ASSERT_EQUAL_NODE(&node5, &node7, 'b', &node6);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node7);
}

/**flip color cases
 *               Root                                   Root
 *                |                                      |
 *                v                                      v
 *              4(b)            remove 5                4(b)
 *            /      \           ---->               /       \
 *       2(r)          6(r)                      2(b)         6(b)
 *     /    \         /    \                    /   \             \
 * 1(b)      3(b) 5(b)      7(b)            1(b)     3(b)          7(r)
 */
void test_delRedBlackTree_remove_5_without_rotation_but_flip_color_with_root_4_two_parents_and_4_childs(void) {
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node2, &node1, &node3, 'r');
  setNode(&node5, NULL, NULL, 'b');
  setNode(&node7, NULL, NULL, 'b');
  setNode(&node6, &node5, &node7, 'r');
  setNode(&node4, &node2, &node6, 'b');
  Node *root, *node;
  root = &node4;

  node = delRedBlackTree(&root, &node5);
  TEST_ASSERT_EQUAL_PTR(&node5, node);
  TEST_ASSERT_EQUAL_PTR(root, &node4);
  TEST_ASSERT_EQUAL_NODE(&node2, &node6, 'b', &node4);
  TEST_ASSERT_EQUAL_NODE(&node1, &node3, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node3);
  TEST_ASSERT_EQUAL_NODE(NULL, &node7, 'b', &node6);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node7);
}

/**flip color cases
 *               Root                                   Root
 *                |                                      |
 *                v                                      v
 *              4(b)            remove 7                4(b)
 *            /      \           ---->               /       \
 *       2(r)          6(r)                      2(r)          6(b)
 *     /    \         /    \                    /    \        /
 * 1(b)      3(b) 5(b)      7(b)            1(b)      3(b) 5(r)
 */
void test_delRedBlackTree_remove_7_without_rotation_but_flip_color_with_root_4_two_parents_and_4_childs(void) {
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node2, &node1, &node3, 'r');
  setNode(&node5, NULL, NULL, 'b');
  setNode(&node7, NULL, NULL, 'b');
  setNode(&node6, &node5, &node7, 'r');
  setNode(&node4, &node2, &node6, 'b');
  Node *root, *node;
  root = &node4;

  node = delRedBlackTree(&root, &node7);
  TEST_ASSERT_EQUAL_PTR(&node7, node);
  TEST_ASSERT_EQUAL_PTR(root, &node4);
  TEST_ASSERT_EQUAL_NODE(&node2, &node6, 'b', &node4);
  TEST_ASSERT_EQUAL_NODE(&node1, &node3, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node3);
  TEST_ASSERT_EQUAL_NODE(&node5, NULL, 'b', &node6);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node5);
}