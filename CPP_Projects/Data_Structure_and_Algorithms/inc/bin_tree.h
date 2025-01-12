#ifndef INC_BIN_TREE_H_
#define INC_BIN_TREE_H_
#include "bin_tree_node.h"
#include "lk_bin_tree_base.h"

template <class ElemType>
class BinTree : public LkBinTreeBase<ElemType, BinTreeNode<ElemType>> {
 public:
  BinTree();   // 构造函数
  ~BinTree();  // 析构函数
  // 获取指定节点的父节点
  virtual BinTreeNode<ElemType>* GetParent(BinTreeNode<ElemType>* pNode) const;

 protected:
  // 建立父子节点之间的连接关系
  virtual void LinkParentChild(BinTreeNode<ElemType>* pParent,
                               BinTreeNode<ElemType>* pChild, bool bLeft);
  // 递归查找指定节点的父节点的辅助函数
  BinTreeNode<ElemType>* GetParentAux(BinTreeNode<ElemType>* pRoot,
                                      BinTreeNode<ElemType>* pNode) const;
};

template <class ElemType>
BinTree<ElemType>::BinTree() {}

template <class ElemType>
BinTree<ElemType>::~BinTree() {}

template <class ElemType>
BinTreeNode<ElemType>* BinTree<ElemType>::GetParent(
    BinTreeNode<ElemType>* pNode) const {
  return GetParentAux(this->GetRoot(), pNode);  // 从根节点开始递归查找父节点
}

template <class ElemType>
void BinTree<ElemType>::LinkParentChild(BinTreeNode<ElemType>* pParent,
                                        BinTreeNode<ElemType>* pChild,
                                        bool bLeft) {
  if (!pParent)
    return;

  if (bLeft) {
    pParent->m_pLeftChild = pChild;
  } else {
    pParent->m_pRightChild = pChild;
  }
}

template <class ElemType>
BinTreeNode<ElemType>* BinTree<ElemType>::GetParentAux(
    BinTreeNode<ElemType>* pRoot, BinTreeNode<ElemType>* pNode) const {
  if (pRoot == NULL) {
    return NULL;
  } else if (pRoot->m_pLeftChild == pNode || pRoot->m_pRightChild == pNode) {
    return pRoot;
  }

  BinTreeNode<ElemType>* pParent;

  pParent = GetParentAux(pRoot->m_pLeftChild, pNode);
  if (pParent != NULL)
    return pParent;

  pParent = GetParentAux(pRoot->m_pRightChild, pNode);
  if (pParent != NULL)
    return pParent;
}

#endif  // INC_BIN_TREE_H_