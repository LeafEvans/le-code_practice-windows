#ifndef INC_CHILD_PARENT_TREE_NODE_H_
#define INC_CHILD_PARENT_TREE_NODE_H_
#include "simple_lk_list.h"

template <class ElemType>
struct ChildParentTreeNode {
  ElemType m_tElem;
  SimpleLkList<int> m_sllSub;
  int m_nParent;

  ChildParentTreeNode() : m_nParent(-1) {}
  ChildParentTreeNode(const ElemType& tElem, int nParent = -1)
      : m_tElem(tElem), m_nParent(nParent) {}
};

#endif  // INC_CHILD_PARENT_TREE_NODE_H_