#ifndef SQ_BIN_TREE_NODE_H_
#define SQ_BIN_TREE_NODE_H_
#ifndef SQ_BIN_TREE_NODE_TYPE_
#define SQ_BIN_TREE_NODE_TYPE_
// 顺序二叉树节点类型
enum SqBinTreeNodeType { EMPTY_NODE, USED_NODE };
#endif  // SQ_BIN_TREE_NODE_TYPE_

template <class ElemType>
struct SqBinTreeNode {
  ElemType m_tElem;          // 元素数据
  SqBinTreeNodeType m_eTag;  // 节点状态标签

  // 默认构造函数，初始化为空节点
  SqBinTreeNode() : m_eTag(EMPTY_NODE) {}

  SqBinTreeNode(const ElemType& tElem, SqBinTreeNodeType eTag)
      : m_tElem(tElem), m_eTag(eTag) {}  // 带参数的构造函数
};
#endif  // SQ_BIN_TREE_NODE_H_