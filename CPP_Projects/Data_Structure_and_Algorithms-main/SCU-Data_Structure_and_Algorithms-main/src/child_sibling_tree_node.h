#ifndef CHILD_SIBLING_TREE_NODE_H_
#define CHILD_SIBLING_TREE_NODE_H_
#include <cstddef>

template <class ElemType>
struct ChildSiblingTreeNode {
  ElemType m_tElem;
  ChildSiblingTreeNode<ElemType>* m_pFirstChild;
  ChildSiblingTreeNode<ElemType>* m_pRightSibling;

  ChildSiblingTreeNode() : m_pFirstChild(NULL), m_pRightSibling(NULL) {}
  ChildSiblingTreeNode(const ElemType& tElem,
                       ChildSiblingTreeNode<ElemType>* pFirstChild = NULL,
                       ChildSiblingTreeNode<ElemType>* pRightSibling = NULL)
      : m_tElem(tElem),
        m_pFirstChild(pFirstChild),
        m_pRightSibling(pRightSibling) {}
};
#endif  // CHILD_SIBLING_TREE_NODE_H_