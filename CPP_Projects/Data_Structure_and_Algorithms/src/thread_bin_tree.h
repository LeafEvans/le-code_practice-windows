#ifndef THREAD_BIN_TREE_H_
#define THREAD_BIN_TREE_H_
#include "lk_bin_tree_base.h"
#include "node.h"

enum THREAD_ORDER {
  NO_THREAD_ORDER,    // 没有建立线索
  PRE_THREAD_ORDER,   // 先序线索
  IN_THREAD_ORDER,    // 中序线索
  POST_THREAD_ORDER,  // 后序线索
};

template <typename ElemType>
class ThreadBinTree
    : public LkBinTreeBase<ElemType, ThreadBinTreeNode<ElemType>> {
 public:
  ThreadBinTree();   // 默认构造函数
  ~ThreadBinTree();  // 析构函数
  virtual ThreadBinTreeNode<ElemType>* GetParent(
      ThreadBinTreeNode<ElemType>* pNode) const;  // 获取父节点
  virtual ThreadBinTreeNode<ElemType>* GetLeftChild(
      ThreadBinTreeNode<ElemType>* pNode) const;  // 获取左子节点
  virtual ThreadBinTreeNode<ElemType>* GetRightChild(
      ThreadBinTreeNode<ElemType>* pNode) const;  // 获取右子节点
  virtual void PreOrder(void (*pVisit)(const ElemType&)) const;  // 先序遍历
  virtual void InOrder(void (*pVisit)(const ElemType&)) const;   // 中序遍历
  virtual void PostOrder(void (*pVisit)(const ElemType&)) const;  // 后序遍历
  void PreThread();   // 先序线索化二叉树
  void InThread();    // 中序线索化二叉树
  void PostThread();  // 后序线索化二叉树

 protected:
  virtual void LinkParentChild(ThreadBinTreeNode<ElemType>* pParent,
                               ThreadBinTreeNode<ElemType>* pChild,
                               bool bLeft);  // 连接父子节点
  void PreThreadAux(
      ThreadBinTreeNode<ElemType>* pNode,
      ThreadBinTreeNode<ElemType>*& pPreNode);  // 先序线索化辅助函数
  void InThreadAux(
      ThreadBinTreeNode<ElemType>* pNode,
      ThreadBinTreeNode<ElemType>*& pPreNode);  // 中序线索化辅助函数
  void PostThreadAux(
      ThreadBinTreeNode<ElemType>* pNode,
      ThreadBinTreeNode<ElemType>*& pPreNode);  // 后序线索化辅助函数

 private:
  THREAD_ORDER m_eOrder;  // 当前线索化顺序
};

template <class ElemType>
ThreadBinTree<ElemType>::ThreadBinTree()
    : m_eOrder(NO_THREAD_ORDER) {}  // 构造函数初始化

template <class ElemType>
ThreadBinTree<ElemType>::~ThreadBinTree() {}  // 析构函数

template <class ElemType>
ThreadBinTreeNode<ElemType>* ThreadBinTree<ElemType>::GetParent(
    ThreadBinTreeNode<ElemType>* pNode) const {
  return pNode->m_pParent;  // 返回父节点
}

template <class ElemType>
void ThreadBinTree<ElemType>::LinkParentChild(
    ThreadBinTreeNode<ElemType>* pParent, ThreadBinTreeNode<ElemType>* pChild,
    bool bLeft) {
  if (!pParent)
    return;  // 如果父节点为空，直接返回

  if (bLeft) {
    pParent->m_pLeft = pChild;  // 设置左子节点
  } else {
    pParent->m_pRight = pChild;  // 设置右子节点
  }
  pChild->m_pParent = pParent;  // 设置子节点的父节点指针
}

template <class ElemType>
ThreadBinTreeNode<ElemType>* ThreadBinTree<ElemType>::GetLeftChild(
    ThreadBinTreeNode<ElemType>* pNode) const {
  return (pNode && pNode->m_eLeftTag == CHILD_PTR) ? pNode->m_pLeft
                                                   : NULL;  // 返回左子节点
}

template <class ElemType>
ThreadBinTreeNode<ElemType>* ThreadBinTree<ElemType>::GetRightChild(
    ThreadBinTreeNode<ElemType>* pNode) const {
  return (pNode && pNode->m_eRightTag == CHILD_PTR) ? pNode->m_pRight
                                                    : NULL;  // 返回右子节点
}

template <class ElemType>
void ThreadBinTree<ElemType>::PreOrder(void (*pVisit)(const ElemType&)) const {
  if (m_eOrder != PRE_THREAD_ORDER) {  // 如果不是先序线索化
    LkBinTreeBase<ElemType, ThreadBinTreeNode<ElemType>>::PreOrder(
        pVisit);  // 调用基类的先序遍历
    return;
  }

  ThreadBinTreeNode<ElemType>* pNode = this->GetRoot();  // 获取根节点
  while (pNode) {
    (*pVisit)(pNode->m_tElem);  // 访问节点
    pNode = (pNode->m_eLeftTag == CHILD_PTR) ? pNode->m_pLeft : pNode->m_pRight;
  }
}

template <class ElemType>
void ThreadBinTree<ElemType>::InOrder(void (*pVisit)(const ElemType&)) const {
  if (m_eOrder != IN_THREAD_ORDER) {  // 如果不是中序线索化
    LkBinTreeBase<ElemType, ThreadBinTreeNode<ElemType>>::InOrder(
        pVisit);  // 调用基类的中序遍历
    return;
  }

  ThreadBinTreeNode<ElemType>* pNode = this->GetRoot();  // 获取根节点

  while (pNode->m_eLeftTag == CHILD_PTR) {
    pNode = pNode->m_pLeft;  // 找到最左边的节点
  }

  while (pNode) {
    (*pVisit)(pNode->m_tElem);  // 访问节点

    if (pNode->m_eRightTag == THREAD_PTR) {
      pNode = pNode->m_pRight;  // 移动到右线索节点
    } else {
      pNode = pNode->m_pRight;  // 移动到右子节点
      while (pNode->m_pLeft == CHILD_PTR) {
        pNode = pNode->m_pLeft;  // 找到最左边的节点
      }
    }
  }
}

template <class ElemType>
void ThreadBinTree<ElemType>::PostOrder(void (*pVisit)(const ElemType&)) const {
  if (m_eOrder != POST_THREAD_ORDER) {  // 如果不是后序线索化
    LkBinTreeBase<ElemType, ThreadBinTreeNode<ElemType>>::PostOrder(
        pVisit);  // 调用基类的后序遍历
    return;
  }

  if (!this->GetRoot())
    return;  // 如果根节点为空，直接返回

  ThreadBinTreeNode<ElemType>* pNode = this->GetRoot();  // 获取根节点

  // 找到第一个后序遍历的节点
  while (pNode->m_eLeftTag == CHILD_PTR || pNode->m_eRightTag == CHILD_PTR) {
    pNode = (pNode->m_eLeftTag == CHILD_PTR) ? pNode->m_pLeft : pNode->m_pRight;
  }

  while (pNode) {
    (*pVisit)(pNode->m_tElem);  // 访问节点

    ThreadBinTreeNode<ElemType>* pParent = pNode->m_pParent;  // 获取父节点

    if (pNode->m_eRightTag == THREAD_PTR) {
      pNode = pNode->m_pRight;  // 移动到右线索节点
    } else if (pNode == this->GetRoot()) {
      pNode = NULL;  // 根节点说明是最后一个节点
    } else if (pParent->m_pRight == pNode ||  // 指定节点为其父节点的右孩子
               (pParent->m_pLeft == pNode &&  // 或为左孩子，且其右孩子为线索
                pParent->m_eRightTag == THREAD_PTR)) {
      pNode = pParent;  // 移动到父节点
    } else {
      pNode = pParent->m_pRight;  // 否则去右子树
      while (pNode->m_eLeftTag == CHILD_PTR ||
             pNode->m_eRightTag == CHILD_PTR) {
        pNode =  // 查看左孩子是否为
            (pNode->m_eLeftTag == CHILD_PTR) ? pNode->m_pLeft : pNode->m_pRight;
      }
    }
  }
}

template <class ElemType>
void ThreadBinTree<ElemType>::PreThread() {
  ThreadBinTreeNode<ElemType>* pPreNode = NULL;  // 设置最初的前驱为空
  PreThreadAux(this->GetRoot(), pPreNode);       // 先序线索化
  if (!GetRightChild(pPreNode)) {                // 如果获取不到右子树
    pPreNode->m_eRightTag = THREAD_PTR;          // 设置右子树为线索
  }
  m_eOrder = PRE_THREAD_ORDER;  // 设置为先序线索化
}

template <class ElemType>
void ThreadBinTree<ElemType>::InThread() {
  ThreadBinTreeNode<ElemType>* pPreNode = NULL;  // 设置最初的前驱为空
  InThreadAux(this->GetRoot(), pPreNode);        // 中序线索化
  if (!GetRightChild(pPreNode)) {
    pPreNode->m_eRightTag = THREAD_PTR;  // 设置右子树为线索
  }
  m_eOrder = IN_THREAD_ORDER;  // 设置为中序线索化
}

template <class ElemType>
void ThreadBinTree<ElemType>::PostThread() {
  ThreadBinTreeNode<ElemType>* pPreNode = NULL;  // 设置最初的前驱为空
  PostThreadAux(this->GetRoot(), pPreNode);      // 后序线索化
  if (!GetRightChild(pPreNode)) {
    pPreNode->m_eRightTag = THREAD_PTR;  // 设置右子树为线索
  }
  m_eOrder = POST_THREAD_ORDER;  // 设置为后序线索化
}

template <class ElemType>
void ThreadBinTree<ElemType>::PreThreadAux(
    ThreadBinTreeNode<ElemType>* pNode,
    ThreadBinTreeNode<ElemType>*& pPreNode) {
  if (!pNode)
    return;  // 空节点直接返回

  if (!GetLeftChild(pNode)) {        // 左孩子为空
    pNode->m_pLeft = pPreNode;       // 设置左孩子为前驱节点
    pNode->m_eLeftTag = THREAD_PTR;  // 设置左孩子线索
  }

  // 前驱结点存在且其右孩子不存在
  if (pPreNode && !GetRightChild(pPreNode)) {
    pPreNode->m_pRight = pNode;  // 前驱节点的后继设为当前节点
    pPreNode->m_eRightTag = THREAD_PTR;  // 设置右孩子线索
  }

  pPreNode = pNode;  // 更新前驱节点

  if (pNode->m_eLeftTag == CHILD_PTR) {  // 左孩子节点存在
    PreThreadAux(pNode, pPreNode);       // 遍历左子树
  }

  if (pNode->m_eRightTag == CHILD_PTR) {      // 右孩子节点存在
    PreThreadAux(pNode->m_pRight, pPreNode);  // 遍历右子树
  }
}

template <class ElemType>
void ThreadBinTree<ElemType>::InThreadAux(
    ThreadBinTreeNode<ElemType>* pNode,
    ThreadBinTreeNode<ElemType>*& pPreNode) {
  if (!pNode)
    return;  // 如果节点为空，直接返回

  // 线索化左子树
  if (pNode->m_eLeftTag == CHILD_PTR)
    InThreadAux(pNode->m_pLeft, pPreNode);

  // 如果左孩子为空，设置前驱节点
  if (!GetLeftChild(pNode)) {
    pNode->m_pLeft = pPreNode;
    pNode->m_eLeftTag = THREAD_PTR;  // 设置左孩子线索
  }

  // 如果前驱节点存在且其右孩子为空，设置后继节点
  if (pPreNode && !GetRightChild(pPreNode)) {
    pPreNode->m_pRight = pNode;
    pPreNode->m_eRightTag = THREAD_PTR;  // 设置右孩子线索
  }

  pPreNode = pNode;  // 更新前驱节点

  // 线索化右子树
  if (pNode->m_eRightTag == CHILD_PTR)
    InThreadAux(pNode->m_pRight, pPreNode);
}

template <class ElemType>
void ThreadBinTree<ElemType>::PostThreadAux(
    ThreadBinTreeNode<ElemType>* pNode,
    ThreadBinTreeNode<ElemType>*& pPreNode) {
  if (pNode)
    return;  // 如果节点不为空，则直接返回

  if (pNode->m_eLeftTag == CHILD_PTR) {
    PostThreadAux(pNode->m_pLeft, pPreNode);  // 线索化左子树
  }

  if (pNode->m_eRightTag == CHILD_PTR) {
    PostThreadAux(pNode->m_pRight, pPreNode);  // 线索化右子树
  }

  if (!GetLeftChild(pNode)) {
    pNode->m_pLeft = pPreNode;       // 设置左孩子为前驱节点
    pNode->m_eLeftTag = THREAD_PTR;  // 设置左孩子线索
  }

  if (pPreNode != NULL && !GetRightChild(pPreNode)) {
    pPreNode->m_pRight = pNode;
    pPreNode->m_eRightTag = THREAD_PTR;  // 设置右孩子线索
  }

  pPreNode = pNode;  // 更新前驱节点
}
#endif  // THREAD_BIN_TREE_H_