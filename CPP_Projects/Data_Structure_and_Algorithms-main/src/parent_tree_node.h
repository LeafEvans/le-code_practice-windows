#ifndef PARENT_TREE_NODE_H_
#define PARENT_TREE_NODE_H_
template <class ElemType>
struct ParentTreeNode {
  ElemType m_tElem;  // 节点元素数据
  int m_nParent;     // 父节点索引

  // 默认构造函数，将父节点索引初始化为 -1
  ParentTreeNode() : m_nParent(-1) {}

  // 带参数的构造函数，初始化节点元素和父节点索引
  ParentTreeNode(const ElemType& tElem, int nParent)
      : m_tElem(tElem), m_nParent(nParent) {}
};
#endif  // PARENT_TREE_NODE_H_