#ifndef BIN_TREE_NODE_H_
#define BIN_TREE_NODE_H_
#include <cstddef>

// 二叉树节点结构
template <class ElemType>
struct BinTreeNode {
  ElemType m_tElem;                      // 元素数据
  BinTreeNode<ElemType>* m_pLeftChild;   // 指向左孩子的指针
  BinTreeNode<ElemType>* m_pRightChild;  // 指向右孩子的指针

  BinTreeNode() : m_pLeftChild(NULL), m_pRightChild(NULL) {}  // 默认构造函数

  BinTreeNode(const ElemType& tElem, BinTreeNode<ElemType>* pLeftChild,
              BinTreeNode<ElemType>* pRightChild)  // 带参数的构造函数
      : m_tElem(tElem), m_pLeftChild(pLeftChild), m_pRightChild(pRightChild) {}
};
#endif  // BIN_TREE_NODE_H_