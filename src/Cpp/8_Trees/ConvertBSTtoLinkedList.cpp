#include "binaryTree.h"
#include <stdio.h>

// ==================== Solution 1 ====================
void ConvertNode(BinaryTreeNode *pNode, BinaryTreeNode **pLastNodeInList);

BinaryTreeNode *Convert_Solution1(BinaryTreeNode *pRootOfTree) {
  BinaryTreeNode *pLastNodeInList = NULL;
  ConvertNode(pRootOfTree, &pLastNodeInList);

  // pLastNodeInList points to the last node in the doule-linked list,
  // but we are going to return the head node.
  BinaryTreeNode *pHeadOfList = pLastNodeInList;
  while (pHeadOfList != NULL && pHeadOfList->m_pLeft != NULL)
    pHeadOfList = pHeadOfList->m_pLeft;

  return pHeadOfList;
}

void ConvertNode(BinaryTreeNode *pNode, BinaryTreeNode **pLastNodeInList) {
  if (pNode == NULL)
    return;

  BinaryTreeNode *pCurrent = pNode;

  if (pCurrent->m_pLeft != NULL)
    ConvertNode(pCurrent->m_pLeft, pLastNodeInList);

  pCurrent->m_pLeft = *pLastNodeInList;
  if (*pLastNodeInList != NULL)
    (*pLastNodeInList)->m_pRight = pCurrent;

  *pLastNodeInList = pCurrent;

  if (pCurrent->m_pRight != NULL)
    ConvertNode(pCurrent->m_pRight, pLastNodeInList);
}

// ==================== Solution 2 ====================
BinaryTreeNode *Convert_Solution2(BinaryTreeNode *pRoot) {
  BinaryTreeNode *pNode = pRoot;

  BinaryTreeNode *pHead = NULL;
  BinaryTreeNode *pParent = NULL;

  while (pNode != NULL) {
    while (pNode->m_pLeft != NULL) {
      // right rotation
      BinaryTreeNode *pLeft = pNode->m_pLeft;
      pNode->m_pLeft = pLeft->m_pRight;
      pLeft->m_pRight = pNode;
      pNode = pLeft;

      if (pParent != NULL)
        pParent->m_pRight = pNode;
    }

    if (pHead == NULL)
      pHead = pNode;

    pParent = pNode;
    pNode = pNode->m_pRight;
  }

  // build double-linked list
  BinaryTreeNode *pNode1 = pHead;
  if (pNode1 != NULL) {
    BinaryTreeNode *pNode2 = pNode1->m_pRight;
    while (pNode2 != NULL) {
      pNode2->m_pLeft = pNode1;

      pNode1 = pNode2;
      pNode2 = pNode2->m_pRight;
    }
  }

  return pHead;
}

// ==================== Test code ====================
void Clone(BinaryTreeNode *pRoot, BinaryTreeNode **pCloned) {
  if (pRoot == NULL)
    return;

  *pCloned = CreateBinaryTreeNode(pRoot->m_nValue);

  BinaryTreeNode *pLeft = NULL;
  BinaryTreeNode *pRight = NULL;

  Clone(pRoot->m_pLeft, &pLeft);
  Clone(pRoot->m_pRight, &pRight);

  (*pCloned)->m_pLeft = pLeft;
  (*pCloned)->m_pRight = pRight;
}

void PrintDoubleLinkedList(BinaryTreeNode *pHeadOfList) {
  BinaryTreeNode *pNode = pHeadOfList;

  printf("The nodes from left to right are:\n");
  while (pNode != NULL) {
    printf("%d\t", pNode->m_nValue);

    if (pNode->m_pRight == NULL)
      break;
    pNode = pNode->m_pRight;
  }

  printf("\nThe nodes from right to left are:\n");
  while (pNode != NULL) {
    printf("%d\t", pNode->m_nValue);

    if (pNode->m_pLeft == NULL)
      break;
    pNode = pNode->m_pLeft;
  }

  printf("\n");
}

void DestroyList(BinaryTreeNode *pHeadOfList) {
  BinaryTreeNode *pNode = pHeadOfList;
  while (pNode != NULL) {
    BinaryTreeNode *pNext = pNode->m_pRight;

    delete pNode;
    pNode = pNext;
  }
}

void Test(char *testName, BinaryTreeNode *pRootOfTree) {
  if (testName != NULL)
    printf("========%s begins: ========\n", testName);

  BinaryTreeNode *pNewRoot = NULL;
  Clone(pRootOfTree, &pNewRoot);

  printf("======== Solution 1 ========\n");
  PrintTree(pRootOfTree);
  BinaryTreeNode *pHeadOfList1 = Convert_Solution1(pRootOfTree);
  PrintDoubleLinkedList(pHeadOfList1);

  printf("======== Solution 2 ========\n");
  PrintTree(pNewRoot);
  BinaryTreeNode *pHeadOfList2 = Convert_Solution2(pNewRoot);
  PrintDoubleLinkedList(pHeadOfList2);

  DestroyList(pHeadOfList2);

  printf("\n\n");
}

//            10
//         /      \
//        6        14
//       /\        /\
//      4  8     12  16
void Test1() {
  BinaryTreeNode *pNode10 = CreateBinaryTreeNode(10);
  BinaryTreeNode *pNode6 = CreateBinaryTreeNode(6);
  BinaryTreeNode *pNode14 = CreateBinaryTreeNode(14);
  BinaryTreeNode *pNode4 = CreateBinaryTreeNode(4);
  BinaryTreeNode *pNode8 = CreateBinaryTreeNode(8);
  BinaryTreeNode *pNode12 = CreateBinaryTreeNode(12);
  BinaryTreeNode *pNode16 = CreateBinaryTreeNode(16);

  ConnectTreeNodes(pNode10, pNode6, pNode14);
  ConnectTreeNodes(pNode6, pNode4, pNode8);
  ConnectTreeNodes(pNode14, pNode12, pNode16);

  Test("Test1", pNode10);

  DestroyList(pNode4);
}

//               5
//              /
//             4
//            /
//           3
//          /
//         2
//        /
//       1
void Test2() {
  BinaryTreeNode *pNode5 = CreateBinaryTreeNode(5);
  BinaryTreeNode *pNode4 = CreateBinaryTreeNode(4);
  BinaryTreeNode *pNode3 = CreateBinaryTreeNode(3);
  BinaryTreeNode *pNode2 = CreateBinaryTreeNode(2);
  BinaryTreeNode *pNode1 = CreateBinaryTreeNode(1);

  ConnectTreeNodes(pNode5, pNode4, NULL);
  ConnectTreeNodes(pNode4, pNode3, NULL);
  ConnectTreeNodes(pNode3, pNode2, NULL);
  ConnectTreeNodes(pNode2, pNode1, NULL);

  Test("Test2", pNode5);

  DestroyList(pNode1);
}

// 1
//  \
//   2
//    \
//     3
//      \
//       4
//        \
//         5
void Test3() {
  BinaryTreeNode *pNode1 = CreateBinaryTreeNode(1);
  BinaryTreeNode *pNode2 = CreateBinaryTreeNode(2);
  BinaryTreeNode *pNode3 = CreateBinaryTreeNode(3);
  BinaryTreeNode *pNode4 = CreateBinaryTreeNode(4);
  BinaryTreeNode *pNode5 = CreateBinaryTreeNode(5);

  ConnectTreeNodes(pNode1, NULL, pNode2);
  ConnectTreeNodes(pNode2, NULL, pNode3);
  ConnectTreeNodes(pNode3, NULL, pNode4);
  ConnectTreeNodes(pNode4, NULL, pNode5);

  Test("Test3", pNode1);

  DestroyList(pNode1);
}

// One node in a tree
void Test4() {
  BinaryTreeNode *pNode1 = CreateBinaryTreeNode(1);
  Test("Test4", pNode1);

  DestroyList(pNode1);
}

// empty
void Test5() { Test("Test5", NULL); }

int main(int argc, char *argv[]) {
  Test1();
  Test2();
  Test3();
  Test4();
  Test5();

  return 0;
}
