#ifndef CHILD_SIBLING_TREE_H_
#define CHILD_SIBLING_TREE_H_
#include <cstddef>

#include "child_sibling_tree_node.h"
#include "tree_base.h"

// 孩子兄弟表示法实现的树类
template <class ElemType>
class ChildSiblingTree
    : public TreeBase<ElemType, ChildSiblingTreeNode<ElemType>*> {
 public:
  ChildSiblingTree();   // 默认构造函数
  ~ChildSiblingTree();  // 析构函数

  // 构造函数,建立以 tElem 为根的树
  ChildSiblingTree(const ElemType& tElem);

  // 拷贝构造函数
  ChildSiblingTree(const ChildSiblingTree<ElemType>& cstSrc);

  // 构造函数,根据数组表示的树建立孩子兄弟树
  // arrElems: 结点数组
  // arrParents: 双亲数组,arrParents[i]表示 arrElems[i] 的双亲下标
  // nRoot: 根结点在数组中的下标
  // nDataLen: 数组长度
  ChildSiblingTree(ElemType* arrElems, int* arrParents, int nRoot,
                   int nDataLen);

  // 重载赋值运算符
  ChildSiblingTree<ElemType>& operator=(
      const ChildSiblingTree<ElemType>& cstSrc);

  virtual ChildSiblingTreeNode<ElemType>* GetRoot() const;  // 获取根结点
  virtual bool IsEmpty() const;  // 判断树是否为空
  virtual bool NodeIsEmpty(
      ChildSiblingTreeNode<ElemType>* pNode) const;  // 判断结点是否为空

  // 获取结点的数据元素
  virtual bool GetElem(ChildSiblingTreeNode<ElemType>* pNode,
                       ElemType& tElem) const;

  // 设置结点的数据元素
  virtual bool SetElem(ChildSiblingTreeNode<ElemType>* pNode,
                       const ElemType& tElem);

  // 获取结点的第一个孩子
  virtual ChildSiblingTreeNode<ElemType>* GetFirstChild(
      ChildSiblingTreeNode<ElemType>* pNode) const;

  // 获取结点的右兄弟
  virtual ChildSiblingTreeNode<ElemType>* GetRightSibling(
      ChildSiblingTreeNode<ElemType>* pNode) const;

  // 获取结点的双亲
  virtual ChildSiblingTreeNode<ElemType>* GetParent(
      ChildSiblingTreeNode<ElemType>* pNode) const;

 private:
  // 获取结点的数据元素值
  virtual ElemType GetNode(ChildSiblingTreeNode<ElemType>* pNode) const;

  // 释放结点所占用的空间
  virtual void ReleaseNode(ChildSiblingTreeNode<ElemType>*& pNode);

  // 创建子结点
  // pNode: 父结点指针
  // nIdx: 新结点在兄弟链表中的位置
  // tElem: 新结点的数据元素
  virtual ChildSiblingTreeNode<ElemType>* CreateChildNode(
      ChildSiblingTreeNode<ElemType>* pNode, int nIdx, const ElemType& tElem);

  // 删除子结点
  // pParent: 父结点指针
  // nIdx: 待删除结点在兄弟链表中的位置
  virtual ChildSiblingTreeNode<ElemType>* RemoveChild(
      ChildSiblingTreeNode<ElemType>* pParent, int nIdx);

  virtual void ClearRemovedNode();  // 清除已删除的结点

  // 获取双亲结点的辅助函数
  // pRoot: 当前子树的根结点
  // pNode: 待查找双亲的结点
  ChildSiblingTreeNode<ElemType>* GetParentAux(
      ChildSiblingTreeNode<ElemType>* pRoot,
      ChildSiblingTreeNode<ElemType>* pNode) const;

  // 复制树的辅助函数
  // pRoot: 待复制的子树根结点
  ChildSiblingTreeNode<ElemType>* CopyTreeAux(
      const ChildSiblingTreeNode<ElemType>* pRoot);

  // 根据数组创建树的辅助函数
  // arrElems: 结点数组
  // arrParents: 双亲数组
  // nRoot: 当前子树根结点的下标
  // nDataLen: 数组长度
  ChildSiblingTreeNode<ElemType>* CreateTreeAux(ElemType* arrElems,
                                                int* arrParents, int nRoot,
                                                int nDataLen);

  ChildSiblingTreeNode<ElemType>* m_pRoot;  // 根结点指针
};

template <class ElemType>
ChildSiblingTree<ElemType>::ChildSiblingTree() : m_pRoot(NULL) {}

template <class ElemType>
ChildSiblingTree<ElemType>::~ChildSiblingTree() {}

template <class ElemType>
ChildSiblingTree<ElemType>::ChildSiblingTree(const ElemType& tElem)
    : m_pRoot(new ChildSiblingTreeNode<ElemType>(tElem)) {}

template <class ElemType>
ChildSiblingTree<ElemType>::ChildSiblingTree(
    const ChildSiblingTree<ElemType>& cstSrc) {
  if (&cstSrc != this) {
    m_pRoot = CopyTreeAux(cstSrc.GetRoot());
  }
}

template <class ElemType>
ChildSiblingTree<ElemType>::ChildSiblingTree(ElemType* arrElems,
                                             int* arrParents, int nRoot,
                                             int nDataLen)
    : m_pRoot(arrElems, arrParents, nRoot, nDataLen) {}

template <class ElemType>
ChildSiblingTree<ElemType>& ChildSiblingTree<ElemType>::operator=(
    const ChildSiblingTree<ElemType>& cstSrc) {
  if (&cstSrc != this) {
    DestroyAux(m_pRoot);                      // 释放原树
    m_pRoot = CopyTreeAux(cstSrc.GetRoot());  // 复制新树
  }
  return *this;
}

template <class ElemType>
ChildSiblingTreeNode<ElemType>* ChildSiblingTree<ElemType>::GetRoot() const {
  return m_pRoot;
}

template <class ElemType>
bool ChildSiblingTree<ElemType>::IsEmpty() const {
  return !m_pRoot;
}

template <class ElemType>
bool ChildSiblingTree<ElemType>::NodeIsEmpty(
    ChildSiblingTreeNode<ElemType>* pNode) const {
  return !pNode;
}

template <class ElemType>
bool ChildSiblingTree<ElemType>::GetElem(ChildSiblingTreeNode<ElemType>* pNode,
                                         ElemType& tElem) const {
  if (!pNode)
    return false;
  tElem = pNode->m_tElem;
  return true;
}

template <class ElemType>
bool ChildSiblingTree<ElemType>::SetElem(ChildSiblingTreeNode<ElemType>* pNode,
                                         const ElemType& tElem) {
  if (!pNode)
    return false;
  pNode->m_tElem = tElem;
  return true;
}

template <class ElemType>
ChildSiblingTreeNode<ElemType>* ChildSiblingTree<ElemType>::GetFirstChild(
    ChildSiblingTreeNode<ElemType>* pNode) const {
  return pNode->m_pFirstChild;
}

template <class ElemType>
ChildSiblingTreeNode<ElemType>* ChildSiblingTree<ElemType>::GetRightSibling(
    ChildSiblingTreeNode<ElemType>* pNode) const {
  return pNode->m_pRightSibling;
}

template <class ElemType>
ChildSiblingTreeNode<ElemType>* ChildSiblingTree<ElemType>::GetParent(
    ChildSiblingTreeNode<ElemType>* pNode) const {
  return GetParentAux(GetRoot(), pNode);
}

template <class ElemType>
ElemType ChildSiblingTree<ElemType>::GetNode(
    ChildSiblingTreeNode<ElemType>* pNode) const {
  return pNode->m_tElem;
}

template <class ElemType>
void ChildSiblingTree<ElemType>::ReleaseNode(
    ChildSiblingTreeNode<ElemType>*& pNode) {
  if (pNode) {
    delete pNode;
    pNode = NULL;
  }
}

template <class ElemType>
ChildSiblingTreeNode<ElemType>* ChildSiblingTree<ElemType>::CreateChildNode(
    ChildSiblingTreeNode<ElemType>* pNode, int nIdx, const ElemType& tElem) {
  if (!pNode)
    return NULL;  // 父结点为空,返回NULL

  // 创建新结点
  ChildSiblingTreeNode<ElemType>* pNewNode =
      new ChildSiblingTreeNode<ElemType>();

  pNewNode->m_tElem = tElem;  // 设置数据元素

  // 作为第一个孩子插入
  if (nIdx == 0) {
    ChildSiblingTreeNode<ElemType>* pFirstNode = pNode->m_pFirstChild;
    pNode->m_pFirstChild = pNewNode;  // 新结点成为第一个孩子
    pNewNode->m_pRightSibling = pFirstNode;  // 原第一个孩子成为新结点的右兄弟
    return pNewNode;
  }

  // 在兄弟链表中查找插入位置
  ChildSiblingTreeNode<ElemType>* pCurrNode = pNode->m_pFirstChild;
  ChildSiblingTreeNode<ElemType>* pPreNode = NULL;
  int nPos = 0;
  while (pCurrNode) {
    ++nPos;
    if (nPos == nIdx) {
      pNewNode->m_pRightSibling = pCurrNode;  // 当前结点成为新结点的右兄弟
      if (pPreNode) {
        pPreNode->m_pRightSibling = pNewNode;  // 新结点成为前驱结点的右兄弟
      }
      return pNewNode;
    }
    pPreNode = pCurrNode;
    pCurrNode = pCurrNode->m_pRightSibling;
  }

  // 未找到指定位置,插入到链表末尾
  if (pPreNode) {
    pPreNode->m_pRightSibling = pNewNode;
  }

  return pNewNode;
}

template <class ElemType>
ChildSiblingTreeNode<ElemType>* ChildSiblingTree<ElemType>::RemoveChild(
    ChildSiblingTreeNode<ElemType>* pParent, int nIdx) {
  if (!pParent) {
    return NULL;
  }

  ChildSiblingTreeNode<ElemType>* pCurrNode = pParent->m_pFirstChild;

  // 删除第一个孩子
  if (nIdx == 0) {
    if (!pCurrNode)
      return NULL;  // 无孩子,返回NULL
    pParent->m_pFirstChild = pCurrNode->m_pRightSibling;
    pCurrNode->m_pRightSibling = NULL;  // 断开右兄弟链接
    return pCurrNode;
  }

  // 在兄弟链表中查找待删除结点
  ChildSiblingTreeNode<ElemType>* pPreNode = NULL;
  int nPos = 0;
  while (pCurrNode) {
    ++nPos;
    if (nPos == nIdx) {
      if (pPreNode) {
        // 从链表中删除当前结点
        pPreNode->m_pRightSibling = pCurrNode->m_pRightSibling;
      }
      pCurrNode->m_pRightSibling = NULL;
      return pCurrNode;
    }
    pPreNode = pCurrNode;
    pCurrNode = pCurrNode->m_pRightSibling;
  }

  return NULL;  // 未找到指定位置的结点
}

template <class ElemType>
void ChildSiblingTree<ElemType>::ClearRemovedNode() {}

template <typename ElemType>
ChildSiblingTreeNode<ElemType>* ChildSiblingTree<ElemType>::GetParentAux(
    ChildSiblingTreeNode<ElemType>* pRoot,
    ChildSiblingTreeNode<ElemType>* pNode) const {
  if (!pRoot)
    return NULL;  // 空树返回NULL

  // 遍历当前结点的所有孩子
  for (ChildSiblingTreeNode<ElemType>* pChild = GetFirstChild(pRoot); pChild;
       pChild = GetRightSibling(pNode)) {
    if (pChild == pNode)
      return pRoot;  // 找到目标结点,返回其双亲

    // 在子树中递归查找
    ChildSiblingTreeNode<ElemType>* pParent = GetParentAux(pChild, pNode);
    if (pParent)
      return pParent;  // 找到双亲,返回
  }

  return NULL;  // 未找到双亲
}

template <class ElemType>
ChildSiblingTreeNode<ElemType>* ChildSiblingTree<ElemType>::CopyTreeAux(
    const ChildSiblingTreeNode<ElemType>* pRoot) {
  if (!m_pRoot)
    return NULL;

  // 复制根结点
  ChildSiblingTreeNode<ElemType>* pNewRoot =
      new ChildSiblingTreeNode<ElemType>(pRoot->m_tElem);
  ChildSiblingTreeNode<ElemType>*pSubRoot, *pCurrNode;

  // 复制所有子树
  for (const ChildSiblingTreeNode<ElemType>* pChild = GetFirstChild(pRoot);
       pChild; pChild = GetRightSibling(pChild)) {
    pSubRoot = CopyTreeAux(pChild);
    if (!(pNewRoot->m_pFirstChild)) {
      pNewRoot->m_pFirstChild = pSubRoot;  // 作为第一个孩子
    } else {
      pCurrNode->m_pRightSibling = pSubRoot;  // 加入兄弟链表
    }
    pCurrNode = pSubRoot;
  }
}

template <class ElemType>
ChildSiblingTreeNode<ElemType>* ChildSiblingTree<ElemType>::CreateTreeAux(
    ElemType* arrElems, int* arrParents, int nRoot, int nDataLen) {
  if (nRoot < 0 || nRoot >= nDataLen)
    return NULL;

  // 创建根结点
  ChildSiblingTreeNode<ElemType>* pNewRoot =
      new ChildSiblingTree<ElemType>(arrElems[nRoot]);
  ChildSiblingTreeNode<ElemType>*pSubRoot, *pCurrNode;

  // 为当前结点创建子树
  for (int i; i < nDataLen; ++i) {
    if (arrParents[i] == nRoot) {
      pSubRoot = CreateTreeGAux(arrElems, arrParents, i, nDataLen);
      if (!(pNewRoot->m_pFirstChild)) {
        pNewRoot->m_pFirstChild = pSubRoot;  // 作为第一个孩子
      } else {
        pCurrNode->m_pRightSibling = pSubRoot;  // 加入兄弟链表
      }
      pCurrNode = pSubRoot;
    }
  }

  return pNewRoot;
}
#endif  // CHILD_SIBLING_TREE_H_