#ifndef HUFFMAN_TREE_NODE_H_
#define HUFFMAN_TREE_NODE_H_

#include <cstddef>

template <class ElemType, class WeightType>
struct HuffmanTreeNode {
  HuffmanTreeNode()
      : m_pLeftChild(NULL),
        m_pRightChild(NULL),
        m_pParent(NULL) {}  // 默认构造函数

  HuffmanTreeNode(
      HuffmanTreeNode<ElemType, WeightType>* pLeftChild,
      HuffmanTreeNode<ElemType, WeightType>* pRightChild) {  // 带参数的构造函数
    m_pLeftChild = pLeftChild;
    if (pLeftChild) {
      m_pLeftChild->m_pParent = this;  // 设置左孩子的父节点
    }

    m_pRightChild = pRightChild;
    if (pRightChild) {
      m_pRightChild->m_pParent = this;  // 设置右孩子的父节点
    }

    m_pParent = NULL;
  }

  ~HuffmanTreeNode();  // 析构函数

  // 判断是否为叶子节点
  bool IsLeaf() { return !m_pLeftChild && !m_pRightChild; }

  HuffmanTreeNode<ElemType, WeightType>* m_pLeftChild;   // 左孩子指针
  HuffmanTreeNode<ElemType, WeightType>* m_pRightChild;  // 右孩子指针
  HuffmanTreeNode<ElemType, WeightType>* m_pParent;      // 父节点指针
  ElemType m_tElem;                                      // 元素数据
  WeightType m_tWeight;                                  // 权重数据
};

#endif  // HUFFMAN_TREE_NODE_H_