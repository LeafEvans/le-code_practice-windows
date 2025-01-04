#ifndef INC_BIN_AVL_TREE_H_
#define INC_BIN_AVL_TREE_H_
#include <cmath>
#include <istream>

#include "bin_avl_tree_node.h"
#include "lk_bin_tree_base.h"
#include "lk_stack.h"

// AVL树类模板,继承自二叉树基类
// ElemType: 节点数据类型
// KeyType: 关键字类型,用于查找和比较
template <typename ElemType, typename KeyType>
class BinAvlTree : public LkBinTreeBase<ElemType, BinAvlTreeNode<ElemType>> {
 public:
  // 构造和析构函数
  BinAvlTree();
  ~BinAvlTree();

  // 获取指定节点的父节点
  virtual BinAvlTreeNode<ElemType>* GetParent(
      BinAvlTreeNode<ElemType>* pNode) const;

  // 根据关键字查找节点
  BinAvlTreeNode<ElemType>* Search(const KeyType& tKey) const;

  // 插入新节点,返回是否成功
  bool Insert(const ElemType& tElem);

  // 删除指定关键字的节点,返回是否成功
  bool Delete(const KeyType& tKey);

 protected:
  // 链接父子节点关系
  virtual void LinkParentChild(BinAvlTreeNode<ElemType>* pParent,
                               BinAvlTreeNode<ElemType>* pChild, bool bLeft);

  // 递归查找父节点的辅助函数
  BinAvlTreeNode<ElemType>* GetParentAux(BinAvlTreeNode<ElemType>* pRoot,
                                         BinAvlTreeNode<ElemType>* pNode) const;

  // 删除节点的辅助函数
  void DeleteAux(const KeyType& tKey, BinAvlTreeNode<ElemType>*& pDelNode,
                 LkStack<BinAvlTreeNode<ElemType>*>& lspNode);

  // 查找节点的辅助函数,同时返回父节点
  BinAvlTreeNode<ElemType>* SearchAux(const KeyType& tKey,
                                      BinAvlTreeNode<ElemType>*& pParent) const;

  // 查找节点的辅助函数,同时记录路径
  BinAvlTreeNode<ElemType>* SearchAux(
      const KeyType& tKey, BinAvlTreeNode<ElemType>*& pParent,
      LkStack<BinAvlTreeNode<ElemType>*>& lspNode);

  // 左旋转操作
  void LeftRotate(BinAvlTreeNode<ElemType>*& pSubRoot);

  // 右旋转操作
  void RightRotate(BinAvlTreeNode<ElemType>*& pSubRoot);

  // 插入时的左平衡处理
  void InsertLeftBalance(BinAvlTreeNode<ElemType>*& pSubRoot);

  // 插入时的右平衡处理
  void InsertRightBalance(BinAvlTreeNode<ElemType>*& pSubRoot);

  // 插入后的平衡调整
  void InsertBalance(const ElemType& tElem,
                     LkStack<BinAvlTreeNode<ElemType>*>& lspNode);

  // 删除时的左平衡处理
  void DeleteLeftBalance(BinAvlTreeNode<ElemType>*& pSubRoot, bool& bIsShorter);

  // 删除时的右平衡处理
  void DeleteRightBalance(BinAvlTreeNode<ElemType>*& pSubRoot,
                          bool& bIsShorter);

  // 删除后的平衡调整
  void DeleteBalance(const KeyType& tKey,
                     LkStack<BinAvlTreeNode<ElemType>*>& lspNode);
};

// 构造函数
template <typename ElemType, typename KeyType>
BinAvlTree<ElemType, KeyType>::BinAvlTree() {}

// 析构函数
template <typename ElemType, typename KeyType>
BinAvlTree<ElemType, KeyType>::~BinAvlTree() {}

// 链接父子节点关系
template <typename ElemType, typename KeyType>
void BinAvlTree<ElemType, KeyType>::LinkParentChild(
    BinAvlTreeNode<ElemType>* pParent, BinAvlTreeNode<ElemType>* pChild,
    bool bLeft) {
  if (pParent) {  // 存在父节点
    if (bLeft) {  // 链接左孩子
      pParent->m_pLeftChild = pChild;
    } else {  // 链接右孩子
      pParent->m_pRightChild = pChild;
    }
  }
}

// 递归查找父节点的辅助函数
template <class ElemType, class KeyType>
BinAvlTreeNode<ElemType>* BinAvlTree<ElemType, KeyType>::GetParentAux(
    BinAvlTreeNode<ElemType>* pRoot, BinAvlTreeNode<ElemType>* pNode) const {
  if (pRoot == NULL) {
    return NULL;  // 空树
  } else if (pRoot->m_pLeftChild == pNode || pRoot->m_pRightChild == pNode) {
    return pRoot;  // 找到父节点
  }

  BinAvlTreeNode<ElemType>* pParent;

  // 递归查找左子树
  pParent = GetParentAux(pRoot->m_pLeftChild, pNode);
  if (pParent != NULL)
    return pParent;

  // 递归查找右子树
  pParent = GetParentAux(pRoot->m_pRightChild, pNode);
  if (pParent != NULL)
    return pParent;
}

// 获取指定节点的父节点
template <class ElemType, class KeyType>
BinAvlTreeNode<ElemType>* BinAvlTree<ElemType, KeyType>::GetParent(
    BinAvlTreeNode<ElemType>* pNode) const {
  return GetParentAux(this->GetRoot(), pNode);  // 从根节点开始查找父节点
}

// 查找节点的辅助函数,同时返回父节点
template <class ElemType, class KeyType>
BinAvlTreeNode<ElemType>* BinAvlTree<ElemType, KeyType>::SearchAux(
    const KeyType& tKey, BinAvlTreeNode<ElemType>*& pParent) const {
  BinAvlTreeNode<ElemType>* pNode = this->GetRoot();
  pParent = NULL;

  // 迭代查找节点,同时记录父节点
  while (pNode != NULL && pNode->m_tElem != tKey) {
    pParent = pNode;
    if (tKey < pNode->m_tElem) {
      pNode = pNode->m_pLeftChild;
    } else {
      pNode = pNode->m_pRightChild;
    }
  }

  return pNode;
}

// 查找节点的辅助函数,同时记录路径
template <class ElemType, class KeyType>
BinAvlTreeNode<ElemType>* BinAvlTree<ElemType, KeyType>::SearchAux(
    const KeyType& tKey, BinAvlTreeNode<ElemType>*& pParent,
    LkStack<BinAvlTreeNode<ElemType>*>& lspNode) {
  BinAvlTreeNode<ElemType>* pNode = this->GetRoot();
  pParent = NULL;

  // 迭代查找节点,同时记录路径和父节点
  while (pNode != NULL && pNode->m_tElem != tKey) {
    pParent = pNode;
    lspNode.Push(pNode);
    if (tKey < pNode->m_tElem) {
      pNode = pNode->m_pLeftChild;
    } else {
      pNode = pNode->m_pRightChild;
    }
  }

  return pNode;
}

// 根据关键字查找节点
template <class ElemType, class KeyType>
BinAvlTreeNode<ElemType>* BinAvlTree<ElemType, KeyType>::Search(
    const KeyType& tKey) const {
  BinAvlTreeNode<ElemType>* pParent;
  return SearchAux(tKey, pParent);
}

// 左旋转操作
template <class ElemType, class KeyType>
void BinAvlTree<ElemType, KeyType>::LeftRotate(
    BinAvlTreeNode<ElemType>*& pSubRoot) {
  // 保存当前子树根节点的右子节点作为新的子树根
  BinAvlTreeNode<ElemType>* pRightChild = pSubRoot->m_pRightChild;

  // 将新根节点的左子树挂接为原根节点的右子树
  pSubRoot->m_pRightChild = pRightChild->m_pLeftChild;

  // 将原根节点作为新根节点的左子节点
  pRightChild->m_pLeftChild = pSubRoot;

  // 更新子树的根节点
  pSubRoot = pRightChild;
}

// 右旋转操作
template <class ElemType, class KeyType>
void BinAvlTree<ElemType, KeyType>::RightRotate(
    BinAvlTreeNode<ElemType>*& pSubRoot) {
  // 保存当前子树根节点的左子节点作为新的子树根
  BinAvlTreeNode<ElemType>* pLeftChild = pSubRoot->m_pLeftChild;

  // 将新根节点的右子树挂接为原根节点的左子树
  pSubRoot->m_pLeftChild = pLeftChild->m_pRightChild;

  // 将原根节点作为新根节点的右子节点
  pLeftChild->m_pRightChild = pSubRoot;

  // 更新子树的根节点
  pSubRoot = pLeftChild;
}

// 插入时的左平衡处理
template <class ElemType, class KeyType>
void BinAvlTree<ElemType, KeyType>::InsertLeftBalance(
    BinAvlTreeNode<ElemType>*& pSubRoot) {
  // 获取失衡节点的左子节点
  BinAvlTreeNode<ElemType>* pLeftChild = pSubRoot->m_pLeftChild;

  switch (pLeftChild->m_eBalance) {
    case kLeftHeavy: {  // LL型失衡：左子树的左子树过高
      // 右旋恢复平衡
      pSubRoot->m_eBalance = kBalanced;
      pLeftChild->m_eBalance = kBalanced;
      RightRotate(pSubRoot);
      break;
    }

    case kRightHeavy: {  // LR型失衡：左子树的右子树过高
      // 获取左子节点的右子节点，该节点将在调整后成为子树的根
      BinAvlTreeNode<ElemType>* pLeftRightChild = pLeftChild->m_pRightChild;

      // 根据LR节点的平衡因子决定旋转后各节点的平衡状态
      switch (pLeftRightChild->m_eBalance) {
        case kLeftHeavy: {                     // LR-L：LR节点的左子树较高
          pSubRoot->m_eBalance = kRightHeavy;  // 旋转后原根节点右重
          pLeftChild->m_eBalance = kBalanced;  // 旋转后原左节点平衡
          break;
        }
        case kRightHeavy: {                     // LR-R：LR节点的右子树较高
          pSubRoot->m_eBalance = kBalanced;     // 旋转后原根节点平衡
          pLeftChild->m_eBalance = kLeftHeavy;  // 旋转后原左节点左重
          break;
        }
        case kBalanced: {                    // LR-C：LR节点的左右子树等高
          pSubRoot->m_eBalance = kBalanced;  // 旋转后两节点均平衡
          pLeftChild->m_eBalance = kBalanced;
          break;
        }
      }
      // LR调整后新根节点（原LR节点）必定平衡
      pLeftRightChild->m_eBalance = kBalanced;

      // 执行LR型双旋转
      LeftRotate(pLeftChild);
      RightRotate(pSubRoot);
    }
  }
}

// 插入时的右平衡处理
template <typename ElemType, typename KeyType>
void BinAvlTree<ElemType, KeyType>::InsertRightBalance(
    BinAvlTreeNode<ElemType>*& pSubRoot) {
  // 获取失衡节点的右子节点
  BinAvlTreeNode<ElemType> pRightChild = pSubRoot->m_pRightChild;

  switch (pRightChild.m_eBalance) {
    case kRightHeavy: {  // RR型失衡：右子树的右子树过高
      // 左旋恢复平衡
      pSubRoot->m_eBalance = kBalanced;
      pRightChild.m_eBalance = kBalanced;
      LeftRotate(pSubRoot);
      break;
    }

    case kLeftHeavy: {  // RL型失衡：右子树的左子树过高
      // 获取右子节点的左子节点，该节点将在调整后成为子树的根
      BinAvlTreeNode<ElemType>* pRightLeftChild = pRightChild.m_pLeftChild;

      // 根据RL节点的平衡因子决定旋转后各节点的平衡状态
      switch (pRightLeftChild->m_eBalance) {
        case kRightHeavy: {                     // RL-R：RL节点的左子树较高
          pSubRoot->m_eBalance = kLeftHeavy;    // 旋转后原根节点左重
          pRightChild->m_eBalance = kBalanced;  // 旋转后原右节点平衡
          break;
        }
        case kLeftHeavy: {                        // RL-L：RL节点的右子树较高
          pSubRoot->m_eBalance = kBalanced;       // 旋转后原根节点平衡
          pRightChild->m_eBalance = kRightHeavy;  // 旋转后原右节点右重
          break;
        }
        case kBalanced: {                    // RL-C：RL节点的左右子树等高
          pSubRoot->m_eBalance = kBalanced;  // 旋转后两节点平衡
          pRightChild.m_eBalance = kBalanced;
          break;
        }
      }

      // RL调整后新根节点（原RL节点）必定平衡
      pRightLeftChild->m_eBalance = kBalanced;

      // 执行RL型双旋转
      RightRotate(pRightChild);
      LeftRotate(pSubRoot);
    }
  }
}

// 插入后的平衡调整
template <typename ElemType, typename KeyType>
void BinAvlTree<ElemType, KeyType>::InsertBalance(
    const ElemType& tElem, LkStack<BinAvlTreeNode<ElemType>*>& lspNode) {
  bool bIsTaller = true;                     // 表示当前子树是否变高
  BinAvlTreeNode<ElemType>* pNode = NULL;    // 当前处理的节点
  BinAvlTreeNode<ElemType>* pParent = NULL;  // 当前节点的父节点

  // 从插入点向上回溯，检查并调整平衡性，直到树不再增高或到达根节点
  while (!lspNode.IsEmpty() && bIsTaller) {
    // 从栈中获取当前节点或其父节点
    lspNode.Pop(pNode);
    if (!lspNode.IsEmpty()) {
      lspNode.Top(pParent);
    } else {
      pParent = NULL;  // 如果栈为空，说明当前节点是根节点
    }

    // 确定新节点是在当前节点的左子树还是右子树中插入
    const bool bIsLeftChild = (tElem < pNode->m_tElem);
    const BalanceFactor eOldBalance = pNode->m_eBalance;
    // 计算新的平衡因子：左子树插入则-1，右子树插入则+1
    const BalanceFactor eNewBalance =
        static_cast<BalanceFactor>(eOldBalance + (bIsLeftChild ? -1 : 1));

    // 更新当前节点的平衡因子
    pNode->m_eBalance = eNewBalance;

    // 检查新的平衡因子是否在允许范围内（-1到1之间）
    if (std::abs(eNewBalance) <= 1) {
      // 如果原来是平衡的(0)，新高度会+1或-1树会变高
      bIsTaller = (eOldBalance == kBalanced);
      continue;
    }

    // 需要进行旋转调整的节点
    if (pParent != NULL) {
      // 确定当前节点是父节点的左孩子还是右孩子
      pNode = (pParent->m_pLeftChild == pNode) ? pParent->m_pLeftChild
                                               : pParent->m_pRightChild;
    }

    // 根据不平衡的类型选择相应的调整方法
    if (bIsLeftChild) {
      // LL或LR型失衡
      InsertLeftBalance(pNode);
    } else {
      // RR或RL型失衡
      InsertRightBalance(pNode);
    }

    // 如果是根节点，需要更新树的根
    if (pParent == NULL) {
      this->m_pRoot = pNode;
    }

    // 旋转调整后，树的高度不会继续增加
    bIsTaller = false;
  }
}

// 插入新节点
template <typename ElemType, typename KeyType>
bool BinAvlTree<ElemType, KeyType>::Insert(const ElemType& tElem) {
  BinAvlTreeNode<ElemType>* pParent;
  LkStack<BinAvlTreeNode<ElemType>*> lspNode;

  // 如果节点已存在则返回false
  if (SearchAux(tElem, pParent, lspNode))
    return false;

  // 创建新节点
  BinAvlTreeNode<ElemType>* pNode =
      new BinAvlTreeNode<ElemType>(tElem, kBalanced);

  // 插入新节点
  if (this->IsEmpty()) {
    this->m_pRoot = pNode;
  } else if (tElem < pParent->m_tElem) {
    pParent->m_pLeftChild = pNode;
  } else {
    pParent->m_pRightChild = pNode;
  }

  // 调整平衡
  InsertBalance(tElem, lspNode);
  return true;
}

// 删除时的左平衡处理
template <typename ElemType, typename KeyType>
void BinAvlTree<ElemType, KeyType>::DeleteLeftBalance(
    BinAvlTreeNode<ElemType>*& pSubRoot, bool& bIsShorter) {
  // 获取当前节点的右子节点，用于平衡调整
  BinAvlTreeNode<ElemType>* pRightChild = pSubRoot->m_pRightChild;

  switch (pRightChild->m_eBalance) {
    case kRightHeavy: {  // 情况1：右子树右偏，需要单左旋
      // 左旋恢复平衡
      pSubRoot->m_eBalance = kBalanced;
      pRightChild->m_eBalance = kBalanced;
      LeftRotate(pSubRoot);
      bIsShorter = true;  // 子树高度减小
      break;
    }
    case kBalanced: {  // 情况2：右子树平衡
      // 左旋后，原根节点右偏，新根节点左偏
      pSubRoot->m_eBalance = kRightHeavy;
      pRightChild->m_eBalance = kLeftHeavy;
      LeftRotate(pSubRoot);
      bIsShorter = false;  // 子树高度不变
      break;
    }
    case kLeftHeavy: {  // 情况3：右子树左偏，需要先右旋后左旋
      // 获取右子节点的左子节点，它将成为新的子树根
      BinAvlTreeNode<ElemType>* pRightLeftChild = pRightChild->m_pLeftChild;

      // 根据右-左子节点的平衡因子调整各节点的平衡状态
      switch (pRightLeftChild->m_eBalance) {
        case kLeftHeavy: {  // RL-L型
          pSubRoot->m_eBalance = kBalanced;
          pRightChild->m_eBalance = kRightHeavy;
          break;
        }
        case kBalanced: {  // RL-C型
          pSubRoot->m_eBalance = kBalanced;
          pRightChild->m_eBalance = kBalanced;
          break;
        }
        case kRightHeavy: {  // RL-R型
          pSubRoot->m_eBalance = kLeftHeavy;
          pRightChild->m_eBalance = kBalanced;
          break;
        }
      }
      // 新根节点平衡，子树高度减小
      pRightLeftChild->m_eBalance = kBalanced;
      bIsShorter = true;

      // 执行双旋转：先右旋后左旋
      RightRotate(pRightChild);
      LeftRotate(pSubRoot);
      break;
    }
  }
}

// 删除时的右平衡处理
template <typename ElemType, typename KeyType>
void BinAvlTree<ElemType, KeyType>::DeleteRightBalance(
    BinAvlTreeNode<ElemType>*& pSubRoot, bool& bIsShorter) {
  BinAvlTreeNode<ElemType>* pLeftChild = pSubRoot->m_pLeftChild;

  switch (pLeftChild->m_eBalance) {
    case kLeftHeavy: {  // 左子树左偏，需要单右旋
      pSubRoot->m_eBalance = kBalanced;
      pLeftChild->m_eBalance = kBalanced;
      RightRotate(pSubRoot);
      bIsShorter = true;  // 子树高度减小
      break;
    }
    case kBalanced: {  // 左子树平衡
      pSubRoot->m_eBalance = kLeftHeavy;
      pLeftChild->m_eBalance = kRightHeavy;
      RightRotate(pSubRoot);
      bIsShorter = false;  // 子树高度不变
      break;
    }
    case kRightHeavy: {  // 左子树右偏，需要先左旋后右旋
      BinAvlTreeNode<ElemType>* pLeftRightChild = pLeftChild->m_pRightChild;
      switch (pLeftRightChild->m_eBalance) {
        case kRightHeavy: {  // LR-R型
          pSubRoot->m_eBalance = kBalanced;
          pLeftChild->m_eBalance = kLeftHeavy;
          break;
        }
        case kBalanced: {  // LR-C型
          pSubRoot->m_eBalance = kBalanced;
          pLeftChild->m_eBalance = kBalanced;
          break;
        }
        case kLeftHeavy: {  // LR-L型
          pSubRoot->m_eBalance = kRightHeavy;
          pLeftChild->m_eBalance = kBalanced;
          break;
        }
      }
      pLeftRightChild->m_eBalance = kBalanced;
      bIsShorter = true;  // 子树高度减小

      // 执行双旋转：先左旋后右旋
      LeftRotate(pLeftChild);
      RightRotate(pSubRoot);
      break;
    }
  }
}

// 删除后的平衡调整
template <typename ElemType, typename KeyType>
void BinAvlTree<ElemType, KeyType>::DeleteBalance(
    const KeyType& tKey, LkStack<BinAvlTreeNode<ElemType>*>& lspNode) {
  bool bIsShorter = true;                    // 标记子树是否变矮
  BinAvlTreeNode<ElemType>* pNode = NULL;    // 当前处理的节点
  BinAvlTreeNode<ElemType>* pParent = NULL;  // 当前节点的父节点

  // 从删除点向上回溯，检查并调整平衡性
  while (!lspNode.IsEmpty() && bIsShorter) {
    // 获取当前节点
    lspNode.Pop(pNode);
    if (!lspNode.IsEmpty()) {
      lspNode.Top(pParent);
    } else {
      pParent = NULL;
    }

    // 确认删除的节点在当前节点的左子树还是右子树
    const bool bIsLeftChild = (tKey < pNode->m_tElem);
    const BalanceFactor eOldBalance = pNode->m_eBalance;
    // 计算新的平衡因子：左子树删除则+1，右子树删除则-1
    const BalanceFactor eNewBalance =
        static_cast<BalanceFactor>(eOldBalance + (bIsLeftChild ? 1 : -1));

    // 更新当前节点的平衡因子
    pNode->m_eBalance = eNewBalance;

    // 检查新的平衡因子
    if (std::abs(eOldBalance) == 1 && eNewBalance == kBalanced) {
      // 原本是偏重的，现在平衡了，树高度减小
      bIsShorter = true;
      continue;
    }

    if (std::abs(eNewBalance) <= 1) {
      // 新的平衡因子在允许范围内，不需要调整
      bIsShorter = false;
      continue;
    }

    // 需要进行旋转调整的节点
    if (pParent != NULL) {
      pNode = (pParent->m_pLeftChild == pNode) ? pParent->m_pLeftChild
                                               : pParent->m_pRightChild;
    }

    // 根据不平衡的类型选择相应的调整方法
    if (eNewBalance == kLeftHeavy) {
      // 左子树过高
      DeleteRightBalance(pNode, bIsShorter);
    } else {
      // 右子树过高
      DeleteLeftBalance(pNode, bIsShorter);
    }

    // 如果是根节点，需要更新树的根
    if (pParent == NULL)
      this->m_pRoot = pNode;
  }
}

// 删除节点的辅助函数
template <typename ElemType, typename KeyType>
void BinAvlTree<ElemType, KeyType>::DeleteAux(
    const KeyType& tKey, BinAvlTreeNode<ElemType>*& pDelNode,
    LkStack<BinAvlTreeNode<ElemType>*>& lspNode) {
  BinAvlTreeNode<ElemType>* pNode = NULL;
  BinAvlTreeNode<ElemType>* pParent = NULL;

  if (pDelNode->m_pLeftChild == NULL && pDelNode->m_pRightChild == NULL) {
    // 叶子节点直接删除
    delete pDelNode;
    pDelNode = NULL;
  } else if (pDelNode->m_pLeftChild == NULL) {
    // 只有右子树
    pNode = pDelNode->m_pRightChild;
    delete pDelNode;
    pDelNode = pNode;
  } else if (pDelNode->m_pRightChild == NULL) {
    // 只有左子树
    pNode = pDelNode->m_pLeftChild;
    delete pDelNode;
    pDelNode = pNode;
  } else {
    // 有两个子节点，查找左子树中的最大值（或右子树中的最小值）
    pParent = pDelNode;
    lspNode.Push(pParent);
    pNode = pDelNode->m_pLeftChild;

    // 查找左子树中的最大值
    while (pNode->m_pRightChild != NULL) {
      pParent = pNode;
      lspNode.Push(pParent);
      pNode = pNode->m_pRightChild;
    }

    pDelNode->m_tElem = pNode->m_tElem;

    if (pParent == pDelNode) {
      // 如果父节点就是要删除的节点
      DeleteAux(tKey, pParent->m_pLeftChild, lspNode);
    } else {
      // 否则删除右子节点
      DeleteAux(tKey, pParent->m_pRightChild, lspNode);
    }
    return;
  }

  DeleteBalance(tKey, lspNode);
}

template <typename ElemType, typename KeyType>
bool BinAvlTree<ElemType, KeyType>::Delete(const KeyType& tKey) {
  BinAvlTreeNode<ElemType>* pNode = NULL;
  BinAvlTreeNode<ElemType>* pParent = NULL;
  LkStack<BinAvlTreeNode<ElemType>*> lspNode;

  pNode = SearchAux(tKey, pParent, lspNode);

  if (!pNode)
    return false;

  if (!pParent) {
    DeleteAux(tKey, this->m_pRoot, lspNode);
  } else if (tKey < pParent->m_tElem) {
    DeleteAux(tKey, pParent->m_pLeftChild, lspNode);
  } else {
    DeleteAux(tKey, pParent->m_pRightChild, lspNode);
  }
}

#endif  // INC_BIN_AVL_TREE_H_