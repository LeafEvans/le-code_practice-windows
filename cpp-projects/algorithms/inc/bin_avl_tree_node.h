#ifndef INC_BIN_AVL_TREE_NODE_H_
#define INC_BIN_AVL_TREE_NODE_H_
#include <cstddef>

// 平衡因子枚举，用于表示节点的平衡状态
enum BalanceFactor {
  kLeftHeavy = -1,  // 左子树高于右子树
  kBalanced = 0,    // 左右子树等高
  kRightHeavy = 1   // 右子树高于左子树
};

// AVL树节点模板结构体
template <typename ElemType>
struct BinAvlTreeNode {

  ElemType m_tElem;             // 节点存储的元素
  BalanceFactor m_eBalance;       // 节点的平衡因子
  BinAvlTreeNode* m_pLeftChild;   // 指向左子节点的指针
  BinAvlTreeNode* m_pRightChild;  // 指向右子节点的指针

  // 默认构造函数，初始化节点
  BinAvlTreeNode()
      : m_tElem(),
        m_eBalance(kBalanced),
        m_pLeftChild(NULL),
        m_pRightChild(NULL) {}

  // 带参数的构造函数，用于初始化节点
  explicit BinAvlTreeNode(const ElemType& tElem,
                          BalanceFactor eBalance = kBalanced,
                          BinAvlTreeNode* pLeftChild = NULL,
                          BinAvlTreeNode* pRightChild = NULL)
      : m_tElem(tElem),
        m_eBalance(eBalance),
        m_pLeftChild(pLeftChild),
        m_pRightChild(pRightChild) {}
};

#endif  // INC_BIN_AVL_TREE_NODE_H_