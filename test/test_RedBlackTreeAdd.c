#include "unity.h"
#include "Node.h"
#include "InitNode.h"
#include "Rotations.h"
#include "RedBlackTree.h"
#include "CustomAssertions.h"

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
  resetNode(&node22, 22);
  resetNode(&node30, 30);
  resetNode(&node40, 40);
  resetNode(&node60, 60);
}

void tearDown(void){

}


/**
 *    Root    add10     Root
 *    /	      --->      /
 *  NULL            10[b]
 */
void test_addRedBlackTree_add_10_to_empty_tree(void){
	setNode(&node10, NULL, NULL, 'r');
	Node *root = NULL;

	addRedBlackTree(&root,	&node10);
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_EQUAL_PTR(root, &node10);
	TEST_ASSERT_EQUAL_PTR(node10.left , NULL);
	TEST_ASSERT_EQUAL_PTR(node10.right, NULL);
	TEST_ASSERT_EQUAL(node10.color, 'b');
}

/**
 *    Root    add5    Root
 *    /       --->   	/
 *  10(b)           10(b)
 *                  /
 *                5(r)
 */
void test_addRedBlackTree_add_5_tree_with_root_10(void){
	setNode(&node10, NULL, NULL, 'b');
	setNode(&node5 , NULL, NULL, 'r');

	Node *root = &node10;
	addRedBlackTree(&root,	&node5);
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_EQUAL_PTR(root, &node10);
	TEST_ASSERT_EQUAL_PTR(node10.left , &node5);
	TEST_ASSERT_EQUAL_PTR(node10.right, NULL);
	TEST_ASSERT_EQUAL_PTR(node5.left  , NULL);
	TEST_ASSERT_EQUAL_PTR(node5.right , NULL);
	TEST_ASSERT_EQUAL(node10.color, 'b');
	TEST_ASSERT_EQUAL(node5.color , 'r');
}

/**
 *      Root                Root
 *        |	                |
 *        v	    add8			  v
 *      5(r)	------>     5(b)
 *        \                   \
 *                            8[r]
 */
void test_addRedBlackTree_add_8_tree_with_root_5(void){
	setNode(&node8, NULL	, NULL, 'r');
	setNode(&node5, NULL	, NULL, 'r');

	Node *root = &node5;
	addRedBlackTree(&root, &node8);
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_EQUAL_PTR(root, &node5);
	TEST_ASSERT_EQUAL_PTR(node8.left , NULL);
	TEST_ASSERT_EQUAL_PTR(node8.right, NULL);
	TEST_ASSERT_EQUAL_PTR(node5.left , NULL);
	TEST_ASSERT_EQUAL_PTR(node5.right, &node8);
	TEST_ASSERT_EQUAL(node5.color, 'b');
	TEST_ASSERT_EQUAL(node8.color, 'r');
}

/**
 *      Root                Root                            Root
 *      |                   |                               |
 *      V       add1        V     Rotate flip color         V
 *    5(b)    ------->    5[b]      --------->            3(b)
 *    /                   /                               /   \
 *  3[r]              3[r]                            1[r]    5[r]
 *                      /
 *                    1[r]
 */
void test_addRedBlackTree_add_1_tree_with_root_3_5_should_rotate(void){
	setNode(&node3, NULL  , NULL, 'r');
	setNode(&node1, NULL  , NULL, 'r');
	setNode(&node5, &node3, NULL, 'b');

	Node *root = &node5;
	addRedBlackTree(&root, &node1);
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_EQUAL_PTR(root, &node3);
	TEST_ASSERT_EQUAL_PTR(node3.left , &node1);
	TEST_ASSERT_EQUAL_PTR(node3.right, &node5);
	TEST_ASSERT_EQUAL_PTR(node1.left , NULL);
	TEST_ASSERT_EQUAL_PTR(node1.right, NULL);
	TEST_ASSERT_EQUAL_PTR(node5.left , NULL);
	TEST_ASSERT_EQUAL_PTR(node5.right, NULL);
	TEST_ASSERT_EQUAL(node5.color, 'r');
	TEST_ASSERT_EQUAL(node1.color, 'r');
	TEST_ASSERT_EQUAL(node3.color, 'b');
}

/**
 * Root->  	13(b)              		   13(b)  <-Root
 *         	  \        add 5        /	 \
 *             15(r)   ---->	    5(r)  15(r)
 */
void test_addRedBlackTree_add_5_to_tree_with_root_13_and_right_child_15(void)	{
	setNode(&node5, NULL, NULL, 'r');
	setNode(&node15, NULL, NULL, 'r');
	setNode(&node13, NULL, &node15, 'b');
	Node *root = &node13;

	addRedBlackTree(&root, &node5);
	TEST_ASSERT_EQUAL_PTR(root, &node13);
	TEST_ASSERT_EQUAL_NODE(&node5, &node15, 'b', &node13);
	TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node5);
	TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node15);
}

/**
 * Root->  	10(b)              		  10(b)  <-Root
 *         	/         add 20       /	\
 *       8(r)         ---->	     8(r)  20(r)
 *                   flip color
 */
void test_addRedBlackTree_add_20_to_tree_with_root_10_and_left_child_8(void){
	setNode(&node8, NULL, NULL, 'r');
	setNode(&node20, NULL, NULL, 'r');
	setNode(&node10, &node8, NULL, 'b');
	Node *root = &node10;

	addRedBlackTree(&root, &node20);

	TEST_ASSERT_EQUAL_PTR(root, &node10);
	TEST_ASSERT_EQUAL_NODE(&node8, &node20, 'b', &node10);
	TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node8);
	TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node20);
}

/**
 * 		Root								Root 													 Root
 *		 |					   			|																|
 *		V				 add4				V 		Rotate flip color					V
 *	 5(b)	   ------->    5[b]			--------->						4(b)
 *  /           				/										 						/	 \
 * 3[r]								3[r]													3[r]   5[r]
 *											\
 *											4[r]
 */
void test_addRedBlackTree_add_4_tree_with_root_3_5_should_rotate(void){
	setNode(&node3, NULL  , NULL, 'r');
	setNode(&node4, NULL  , NULL, 'r');
	setNode(&node5, &node3, NULL, 'b');

	Node *root = &node5;
	addRedBlackTree(&root, &node4);
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_EQUAL_PTR(root, &node4);
	TEST_ASSERT_EQUAL_PTR(node4.left , &node3);
	TEST_ASSERT_EQUAL_PTR(node4.right, &node5);
	TEST_ASSERT_EQUAL_PTR(node3.left , NULL);
	TEST_ASSERT_EQUAL_PTR(node3.right, NULL);
	TEST_ASSERT_EQUAL_PTR(node5.left , NULL);
	TEST_ASSERT_EQUAL_PTR(node5.right, NULL);
	TEST_ASSERT_EQUAL(node5.color, 'r');
	TEST_ASSERT_EQUAL(node3.color, 'r');
	TEST_ASSERT_EQUAL(node4.color, 'b');
}

/**
 * 		Root								Root 														Root
 *		 |					   			|																	|
 *		V				 add9				V 		Rotate flip and color		   V
 *	 5(b)	   ------->    5[b]					--------->				 8(b)
 *  		\           				\										 				 /	 \
 * 			8[r]								8[r]										 5[r]   9[r]
 *													  \
 *												   9[r]
 */
void test_addRedBlackTree_add_9_should_rotate_and_flip_color(void){
	setNode(&node9, NULL ,NULL	, 'r');
	setNode(&node8, NULL ,NULL	, 'r');
	setNode(&node5, NULL ,&node8,	'b');

	Node *root = &node5;
	addRedBlackTree(&root, &node9);
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_EQUAL_PTR(root, &node8);
	TEST_ASSERT_EQUAL_PTR(node8.left , &node5);
	TEST_ASSERT_EQUAL_PTR(node8.right, &node9);
	TEST_ASSERT_EQUAL_PTR(node5.left , NULL);
	TEST_ASSERT_EQUAL_PTR(node5.right, NULL);
	TEST_ASSERT_EQUAL_PTR(node9.left , NULL);
	TEST_ASSERT_EQUAL_PTR(node9.right, NULL);
	TEST_ASSERT_EQUAL(node5.color, 'r');
	TEST_ASSERT_EQUAL(node9.color, 'r');
	TEST_ASSERT_EQUAL(node8.color, 'b');
}

/**
 * 		Root								Root 														Root
 *		 |					   			|																	|
 *		V				 add7				V 		Rotate flip and color		   V
 *	 5(b)	   ------->    5[b]					--------->				 7(b)
 *  		\           				\										 				 /	 \
 * 			8[r]								8[r]										 5[r]   8[r]
 *													/
 *												7[r]
 */
void test_addRedBlackTree_add_7_should_rotate_and_flip_color(void){
	setNode(&node7, NULL ,NULL	, 'r');
	setNode(&node8, NULL ,NULL	, 'r');
	setNode(&node5, NULL ,&node8,	'b');

	Node *root = &node5;
	addRedBlackTree(&root, &node7);
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_EQUAL_PTR(root, &node7);
	TEST_ASSERT_EQUAL_PTR(node7.left , &node5);
	TEST_ASSERT_EQUAL_PTR(node7.right, &node8);
	TEST_ASSERT_EQUAL_PTR(node5.left , NULL);
	TEST_ASSERT_EQUAL_PTR(node5.right, NULL);
	TEST_ASSERT_EQUAL_PTR(node8.left , NULL);
	TEST_ASSERT_EQUAL_PTR(node8.right, NULL);
	TEST_ASSERT_EQUAL(node5.color, 'r');
	TEST_ASSERT_EQUAL(node8.color, 'r');
	TEST_ASSERT_EQUAL(node7.color, 'b');
}

/**
 * 		Root								Root 								 				Root
 *		 |					   			|														 |
 *		V				 add1				V 			   flip color		     V
 *	 4(b)	   ------->    4[b]				------------>		  4(r)
 *  /		\           		/		\										 			/	 \
 * 2[r]	7[r]					2[r]	7[r]										2[b]  7[b]
 *										/                             /
 *									1[r]													1[r]
 */
void test_addRedBlackTree_add_1_should_flip_color(void){
	setNode(&node2, NULL  , NULL, 'r');
	setNode(&node7, NULL  , NULL, 'r');
	setNode(&node1, NULL  , NULL, 'r');
	setNode(&node4, &node2, &node7, 'b');

	Node *root = &node4;
	_addRedBlackTree(&root, &node1);
  TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_EQUAL_PTR(root, &node4);
	TEST_ASSERT_EQUAL_PTR(node4.left , &node2);
	TEST_ASSERT_EQUAL_PTR(node4.right, &node7);
	TEST_ASSERT_EQUAL_PTR(node2.left , &node1);
	TEST_ASSERT_EQUAL_PTR(node2.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node1.left , NULL);
	TEST_ASSERT_EQUAL_PTR(node1.right, NULL);
	TEST_ASSERT_EQUAL_PTR(node7.left , NULL);
	TEST_ASSERT_EQUAL_PTR(node7.right , NULL);
	TEST_ASSERT_EQUAL(node4.color, 'r');
	TEST_ASSERT_EQUAL(node2.color, 'b');
	TEST_ASSERT_EQUAL(node7.color, 'b');
	TEST_ASSERT_EQUAL(node1.color, 'r');
}

/**
 * 		Root								Root 								 				Root
 *		 |					   			|														 |
 *		V				 add3			  V 			   flip color		     V
 *	 4(b)	   ------->    4[b]				------------>		  4(r)
 *  /		\           		/		\										 			/	 \
 * 2[r]	7[r]					2[r]	7[r]										2[b]  7[b]
 *											\															\
 *											3[r]													3[r]
 */
void test_addRedBlackTree_add_3_should_flip_color(void){
	setNode(&node2, NULL  , NULL, 'r');
	setNode(&node7, NULL  , NULL, 'r');
	setNode(&node3, NULL  , NULL, 'r');
	setNode(&node4, &node2, &node7, 'b');

	Node *root = &node4;
	_addRedBlackTree(&root, &node3);
  TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_EQUAL_PTR(root, &node4);
	TEST_ASSERT_EQUAL_PTR(node4.left , &node2);
	TEST_ASSERT_EQUAL_PTR(node4.right, &node7);
	TEST_ASSERT_EQUAL_PTR(node2.left , NULL);
	TEST_ASSERT_EQUAL_PTR(node2.right, &node3);
  TEST_ASSERT_EQUAL_PTR(node3.left , NULL);
	TEST_ASSERT_EQUAL_PTR(node3.right, NULL);
	TEST_ASSERT_EQUAL_PTR(node7.left , NULL);
	TEST_ASSERT_EQUAL_PTR(node7.right , NULL);
	TEST_ASSERT_EQUAL(node4.color, 'r');
	TEST_ASSERT_EQUAL(node2.color, 'b');
	TEST_ASSERT_EQUAL(node7.color, 'b');
	TEST_ASSERT_EQUAL(node3.color, 'r');
}

/**
 * 		Root								Root 								 		Root
 *		 |					   			|													|
 *		V				 add9				V 			flip color			  V
 *	 4(b)	   ------->    4[b]			-------->				4(r)
 *  /		\           		/		\										 /	 \
 * 3[r]	7[r]					3[r]	7[r]							3[b]   7[b]
 *														\												\
 *														9[r]										9[r]
 */
void test_addRedBlackTree_add_9_should_flip_color(void){
	setNode(&node3, NULL  , NULL, 'r');
	setNode(&node7, NULL  , NULL, 'r');
	setNode(&node9, NULL  , NULL, 'r');
	setNode(&node4, &node3, &node7, 'b');

	Node *root = &node4;
	_addRedBlackTree(&root, &node9);
  TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_EQUAL_PTR(root, &node4);
	TEST_ASSERT_EQUAL_PTR(node4.left , &node3);
	TEST_ASSERT_EQUAL_PTR(node4.right, &node7);
	TEST_ASSERT_EQUAL_PTR(node3.left , NULL);
	TEST_ASSERT_EQUAL_PTR(node3.right, NULL);
	TEST_ASSERT_EQUAL_PTR(node7.left , NULL);
  TEST_ASSERT_EQUAL_PTR(node7.right, &node9);
	TEST_ASSERT_EQUAL_PTR(node9.left , NULL);
	TEST_ASSERT_EQUAL_PTR(node9.right, NULL);
	TEST_ASSERT_EQUAL(node4.color, 'r');
	TEST_ASSERT_EQUAL(node3.color, 'b');
	TEST_ASSERT_EQUAL(node7.color, 'b');
	TEST_ASSERT_EQUAL(node9.color, 'r');
}

/**
 * 		Root								Root 								 		Root
 *		 |					   			|													|
 *		V				 add6				V 			flip color			  V
 *	 4(b)	   ------->    4[b]			-------->				4(r)
 *  /		\           		/		\										 /	 \
 * 3[r]	7[r]					3[r]	7[r]							3[b]   7[b]
 *													/                        /
 *												 6[r]									    6[r]
 */
void test_addRedBlackTree_add_6_should_flip_color(void){
	setNode(&node3, NULL  , NULL, 'r');
	setNode(&node7, NULL  , NULL, 'r');
	setNode(&node6, NULL  , NULL, 'r');
	setNode(&node4, &node3, &node7, 'b');

	Node *root = &node4;
	_addRedBlackTree(&root, &node6);
  TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_EQUAL_PTR(root, &node4);
	TEST_ASSERT_EQUAL_PTR(node4.left , &node3);
	TEST_ASSERT_EQUAL_PTR(node4.right, &node7);
	TEST_ASSERT_EQUAL_PTR(node3.left , NULL);
	TEST_ASSERT_EQUAL_PTR(node3.right, NULL);
	TEST_ASSERT_EQUAL_PTR(node7.left , &node6);
  TEST_ASSERT_EQUAL_PTR(node7.right, NULL);
	TEST_ASSERT_EQUAL_PTR(node9.left , NULL);
	TEST_ASSERT_EQUAL_PTR(node9.right, NULL);
	TEST_ASSERT_EQUAL(node4.color, 'r');
	TEST_ASSERT_EQUAL(node3.color, 'b');
	TEST_ASSERT_EQUAL(node7.color, 'b');
	TEST_ASSERT_EQUAL(node6.color, 'r');
}

/**
 * 		        Root								Root 								 		Root
 *		        |					   			  |													|
 *		        V				 add2				V 			flip color			  V
 *	        5(b)	   ------->    5[b]			-------->				5(b)
 *         /	 \           		  /		\										 /	 \
 *      3[b]	 7[b] 					3[b]	7[b]							3[r]   7[b]
 *	   /	 \	               /   \                   /   \
 *  1[r]   4[r]          1[r]     4[r]            1[b]    4[b]
 *												   \							          \
 *                           2[r]                     2[r]
 *
 */
void test_addRedBlackTree_add_2_should_flip_color(void){
	setNode(&node3, NULL  , NULL, 'b');
	setNode(&node7, NULL  , NULL, 'b');
	setNode(&node1, NULL  , NULL, 'r');
	setNode(&node4, NULL  , NULL, 'r');
	setNode(&node2, NULL  , NULL, 'r');
	setNode(&node5, &node3, &node7, 'b');
	setNode(&node3, &node1, &node4, 'b');

	Node *root = &node5;
	addRedBlackTree(&root, &node2);
  TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_EQUAL_PTR(root, &node5);
	TEST_ASSERT_EQUAL_PTR(node5.left , &node3);
	TEST_ASSERT_EQUAL_PTR(node5.right, &node7);
	TEST_ASSERT_EQUAL_PTR(node3.left , &node1);
	TEST_ASSERT_EQUAL_PTR(node3.right, &node4);
	TEST_ASSERT_EQUAL_PTR(node1.left , NULL);
  TEST_ASSERT_EQUAL_PTR(node1.right, &node2);
  TEST_ASSERT_EQUAL_PTR(node2.left , NULL);
	TEST_ASSERT_EQUAL_PTR(node2.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node4.left , NULL);
	TEST_ASSERT_EQUAL_PTR(node4.right, NULL);
	TEST_ASSERT_EQUAL_PTR(node7.left , NULL);
	TEST_ASSERT_EQUAL_PTR(node7.right, NULL);
	TEST_ASSERT_EQUAL(node5.color, 'b');
	TEST_ASSERT_EQUAL(node3.color, 'r');
	TEST_ASSERT_EQUAL(node7.color, 'b');
	TEST_ASSERT_EQUAL(node1.color, 'b');
	TEST_ASSERT_EQUAL(node4.color, 'b');
	TEST_ASSERT_EQUAL(node2.color, 'r');
}

/**
 *          Root                            Root                                      Root
 *            |                               |                                       |
 *            V             add6              V               flip color             V
 *          10(b)         ------->          10[b]             -------->           10(b)
 *         /	   \                          /     \                               /	   \
 *      2[r]	    13[r]                 2[r]        3[r]                      [b]       13[b]
 *      /   \	    /   \                /    \      /   \                     /	 \	    /   \
 *  1[b]   8[b]  11[b] 15[b]        1[b]   8[b]  11[b] 15[b]              1[b]   8[r]  11[b] 15[b]
 *          /	\						   							 /	\                                   /	\
 *       3[r]  9[r]                    3[r]  9[r]                             3[b]  9[b]
 *                                         \                                      \
 *                                        6[r]                                    6[r]
 *
 */
void test_addRedBlackTree_add_6_should_flip_color_for_multipleNode_testing(void){
	setNode(&node1 , NULL   , NULL    , 'b');
	setNode(&node11, NULL   , NULL    , 'b');
	setNode(&node15, NULL   , NULL    , 'b');
	setNode(&node3 , NULL   , NULL    , 'r');
	setNode(&node9 , NULL   , NULL    , 'r');
	setNode(&node6 , NULL   , NULL    , 'r');
	setNode(&node8 , &node3 , &node9  , 'b');
	setNode(&node2 , &node1 , &node8  , 'r');
	setNode(&node13, &node11, &node15 , 'r');
	setNode(&node10, &node2 , &node13 , 'b');

	Node *root = &node10;
	addRedBlackTree(&root, &node6);
  TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_EQUAL_PTR(root, &node10);
	TEST_ASSERT_EQUAL_PTR(node10.left , &node2);
	TEST_ASSERT_EQUAL_PTR(node10.right, &node13);
	TEST_ASSERT_EQUAL_PTR(node2.left  , &node1);
	TEST_ASSERT_EQUAL_PTR(node2.right , &node8);
  TEST_ASSERT_EQUAL_PTR(node13.left , &node11);
	TEST_ASSERT_EQUAL_PTR(node13.right, &node15);
  TEST_ASSERT_EQUAL_PTR(node8.left  , &node3);
	TEST_ASSERT_EQUAL_PTR(node8.right , &node9);
	TEST_ASSERT_EQUAL_PTR(node1.left  , NULL);
  TEST_ASSERT_EQUAL_PTR(node1.right , NULL);
  TEST_ASSERT_EQUAL_PTR(node6.left  , NULL);
	TEST_ASSERT_EQUAL_PTR(node6.right , NULL);
  TEST_ASSERT_EQUAL_PTR(node9.left  , NULL);
	TEST_ASSERT_EQUAL_PTR(node9.right , NULL);
	TEST_ASSERT_EQUAL_PTR(node11.left , NULL);
	TEST_ASSERT_EQUAL_PTR(node11.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node15.left , NULL);
	TEST_ASSERT_EQUAL_PTR(node15.right, NULL);
	TEST_ASSERT_EQUAL(node3.color , 'b');
	TEST_ASSERT_EQUAL(node9.color , 'b');
	TEST_ASSERT_EQUAL(node1.color , 'b');
	TEST_ASSERT_EQUAL(node2.color , 'b');
	TEST_ASSERT_EQUAL(node13.color, 'b');
	TEST_ASSERT_EQUAL(node11.color, 'b');
	TEST_ASSERT_EQUAL(node15.color, 'b');
	TEST_ASSERT_EQUAL(node10.color, 'b');
	TEST_ASSERT_EQUAL(node8.color , 'r');
	TEST_ASSERT_EQUAL(node6.color , 'r');
}




