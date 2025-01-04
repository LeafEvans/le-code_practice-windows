#ifndef INC_BIN_SORT_TREE_H_
#define INC_BIN_SORT_TREE_H_
#include "bin_tree.h"
#include "bin_tree_node.h"

// 二叉排序树类模板，继承自二叉树类
template <class ElemType, class KeyType>
class BinSortTree : public BinTree<ElemType> {
 public:
  BinSortTree();   // 构造函数
  ~BinSortTree();  // 析构函数

  // 查找指定键值的节点
  BinTreeNode<ElemType>* Search(const KeyType& tKey) const;
  // 插入新元素
  bool Insert(const ElemType& tElem);
  // 删除指定键值的节点
  bool Delete(const KeyType& tKey);

 protected:
  // 辅助查找函数，返回节点及其父节点
  BinTreeNode<ElemType>* SearchAux(const KeyType& tKey,
                                   BinTreeNode<ElemType>*& pParent) const;
};

template <class ElemType, class KeyType>
BinSortTree<ElemType, KeyType>::BinSortTree() {}

template <class ElemType, class KeyType>
BinSortTree<ElemType, KeyType>::~BinSortTree() {}

template <class ElemType, class KeyType>
BinTreeNode<ElemType>* BinSortTree<ElemType, KeyType>::SearchAux(
    const KeyType& tKey, BinTreeNode<ElemType>*& pParent) const {
  BinTreeNode<ElemType>* pNode = this->GetRoot();  // 从根节点开始
  pParent = NULL;                                  // 初始化父节点为空

  // 遍历树寻找目标节点
  while (pNode != NULL && pNode->m_tElem != tKey) {
    pParent = pNode;  // 更新父节点
    if (tKey < pNode->m_tElem) {
      pNode = pNode->m_pLeftChild;  // 向左子树移动
    } else {
      pNode = pNode->m_pRightChild;  // 向右子树移动
    }
  }

  return pNode;  // 返回找到的节点或NULL
}

template <class ElemType, class KeyType>
BinTreeNode<ElemType>* BinSortTree<ElemType, KeyType>::Search(
    const KeyType& tKey) const {
  BinTreeNode<ElemType>* pParent;
  return SearchAux(tKey, pParent);  // 调用辅助查找函数
}

template <class ElemType, class KeyType>
bool BinSortTree<ElemType, KeyType>::Insert(const ElemType& tElem) {
  BinTreeNode<ElemType>* pParent;

  // 如果元素不存在，则插入
  if (SearchAux(tElem, pParent) == NULL) {
    BinTreeNode<ElemType>* pNewNode = new BinTreeNode<ElemType>(tElem);

    if (this->IsEmpty()) {
      this->m_pRoot = pNewNode;  // 如果数为空，设置新节点为根
    } else if (tElem < pParent->m_tElem) {
      pParent->m_pLeftChild = pNewNode;  // 插入到左子树
    } else {
      pParent->m_pRightChild = pNewNode;  // 插入到右子树
    }
  }

  return true;  // 插入成功
}

template <class ElemType, class KeyType>
bool BinSortTree<ElemType, KeyType>::Delete(const KeyType& tKey) {
  BinTreeNode<ElemType>* pDelParent = NULL;
  BinTreeNode<ElemType>* pDelNode = SearchAux(tKey, pDelParent);

  if (!pDelNode)
    return false;

  if (pDelNode->m_pLeftChild != NULL && pDelNode->m_pRightChild != NULL) {
    BinTreeNode<ElemType>* pParent = pDelNode;
    BinTreeNode<ElemType>* pNode = pDelNode->m_pRightChild;

    while (pNode->m_pLeftChild != NULL) {
      pParent = pNode;
      pNode = pNode->m_pLeftChild;
    }

    pDelNode->m_tElem = pNode->m_tElem;

    if (pParent == pDelNode) {
      pParent->m_pRightChild = pNode->m_pRightChild;
    } else {
      pParent->m_pLeftChild = pNode->m_pRightChild;
    }

    delete pNode;
    return true;
  }

  BinTreeNode<ElemType>* pChild = (pDelNode->m_pLeftChild != NULL)
                                      ? pDelNode->m_pLeftChild
                                      : pDelNode->m_pRightChild;

  if (pDelParent == NULL) {
    this->m_pRoot = pChild;
  } else if (pDelParent->m_pLeftChild == pDelParent) {
    pDelParent->m_pLeftChild = pChild;
  } else {
    pDelParent->m_pRightChild = pChild;
  }

  delete pDelNode;
  return true;
}
#endif  // INC_BIN_SORT_TREE_H_
