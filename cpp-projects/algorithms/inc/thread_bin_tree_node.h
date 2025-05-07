#ifndef INC_THREAD_BIN_TREE_NODE_H_
#define INC_THREAD_BIN_TREE_NODE_H_
#include <cstddef>

#ifndef PTR_TAG_TYPE_
#define PTR_TAG_TYPE_
// 指针类型标志：CHILD_PTR(0) 表示指向孩子节点的指针，THREAD_PTR(1)
// 表示指向线索节点的指针
enum PtrTagType { CHILD_PTR, THREAD_PTR };
#endif  // PTR_TAG_TYPE_

template <class ElemType>
struct ThreadBinTreeNode {
  ElemType m_tElem;                        // 元素数据
  ThreadBinTreeNode<ElemType>* m_pLeft;    // 左子节点指针
  ThreadBinTreeNode<ElemType>* m_pRight;   // 右子节点指针
  ThreadBinTreeNode<ElemType>* m_pParent;  // 父节点指针
  PtrTagType m_eLeftTag;                   // 左指针标志
  PtrTagType m_eRightTag;                  // 右指针标志

  ThreadBinTreeNode(const ElemType& tElem = ElemType(),
                    ThreadBinTreeNode<ElemType>* pLeft = NULL,
                    ThreadBinTreeNode<ElemType>* pRight = NULL,
                    ThreadBinTreeNode<ElemType>* pParent = NULL,
                    PtrTagType eLeftTag = CHILD_PTR,
                    PtrTagType eRightTag = CHILD_PTR)
      : m_tElem(tElem),
        m_pLeft(pLeft),
        m_pRight(pRight),
        m_pParent(pParent),
        m_eLeftTag(eLeftTag),
        m_eRightTag(eRightTag) {}  // 带参数构造函数，初始化节点
};
#endif  // INC_THREAD_BIN_TREE_NODE_H_