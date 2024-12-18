#ifndef LK_BINARY_TREE_BASE_H_
#define LK_BINARY_TREE_BASE_H_
#include <cstddef>

#include "bin_tree_base.h"

// 链式二叉树基类模板，继承自二叉树基类
template <class ElemType, class NodeType>
class LkBinTreeBase : public BinTreeBase<ElemType, NodeType*> {
 public:
  LkBinTreeBase();   // 构造空二叉树
  ~LkBinTreeBase();  // 析构并释放所有节点
  // 拷贝构造函数，深拷贝源二叉树
  LkBinTreeBase(LkBinTreeBase<ElemType, NodeType>& lbtbSrc);
  LkBinTreeBase(NodeType* pRoot);        // 以指定节点为根构造二叉树
  LkBinTreeBase(const ElemType& tElem);  // 构造只有根节点的二叉树
  virtual NodeType* GetRoot() const;     // 获取根节点指针
  virtual bool NodeIsEmpty(NodeType* pNode) const;  // 判断节点是否为空
  // 获取节点的元素值，成功返回 true
  virtual bool GetElem(NodeType* pNode, ElemType& tElem) const;
  // 设置节点的元素值，成功返回 true
  virtual bool SetElem(NodeType* pNode, const ElemType& tElem);
  virtual bool IsEmpty() const;  // 判断是否为空树
  virtual NodeType*& GetLeftChild(NodeType* pNode) const;  // 获取左子节点指针
  virtual NodeType*& GetRightChild(NodeType* pNode) const;  // 获取右子节点指针
  virtual NodeType* GetParent(NodeType* pNode) const = 0;  // 获取父节点指针
  // 根据前序遍历序列和中序遍历序列构造二叉树
  virtual bool CreateBinTree(ElemType* arrPre, ElemType* arrIn, int nSize);
  // 赋值运算符重载，深拷贝源二叉树
  LkBinTreeBase<ElemType, NodeType>& operator=(
      const LkBinTreeBase<ElemType, NodeType>& lbtbSrc);

 protected:
  virtual ElemType GetNode(NodeType* pNode) const;  // 获取节点元素值
  virtual void ReleaseNode(NodeType*& pNode);       // 释放节点及其内存
  // 创建节点的左/右子节点
  virtual NodeType* CreateChildNode(NodeType* pNode, bool bLeft);
  // 建立父子节点之间的链接关系
  virtual void LinkParentChild(NodeType* pParent, NodeType* pChild, bool bLeft);
  NodeType* CopyTreeAux(const NodeType* pRoot);  // 辅助函数：复制整棵子树
  NodeType* m_pRoot;                             // 根节点指针
};

template <class ElemType, class NodeType>
LkBinTreeBase<ElemType, NodeType>::LkBinTreeBase() : m_pRoot(NULL) {}

template <class ElemType, class NodeType>
LkBinTreeBase<ElemType, NodeType>::~LkBinTreeBase() {
  if (m_pRoot) {
    this->DestroyAux(m_pRoot);  // 递归销毁所有节点
    m_pRoot = NULL;             // 根节点置空
  }
}

template <class ElemType, class NodeType>
LkBinTreeBase<ElemType, NodeType>::LkBinTreeBase(
    LkBinTreeBase<ElemType, NodeType>& lbtbSrc) {
  if (&lbtbSrc != this) {
    this->DestroyAux(m_pRoot);                 // 销毁当前树
    m_pRoot = CopyTreeAux(lbtbSrc.GetRoot());  // 复制源树
  }
}

template <class ElemType, class NodeType>
LkBinTreeBase<ElemType, NodeType>::LkBinTreeBase(NodeType* pRoot)
    : m_pRoot(CopyTreeAux(pRoot)) {}  // 复制整棵树

template <class ElemType, class NodeType>
LkBinTreeBase<ElemType, NodeType>::LkBinTreeBase(const ElemType& tElem) {
  m_pRoot = new NodeType;   // 创建根节点
  SetElem(m_pRoot, tElem);  // 设置根节点元素值
}

template <typename ElemType, typename NodeType>
NodeType* LkBinTreeBase<ElemType, NodeType>::GetRoot() const {
  return m_pRoot;  // 返回根节点指针
}

template <class ElemType, class NodeType>
bool LkBinTreeBase<ElemType, NodeType>::NodeIsEmpty(NodeType* pNode) const {
  return !pNode;  // 判断节点指针是否为空
}

template <class ElemType, class NodeType>
bool LkBinTreeBase<ElemType, NodeType>::GetElem(NodeType* pNode,
                                                ElemType& tElem) const {
  if (!pNode)
    return false;  // 空节点返回 false
  tElem = LkBinTreeBase<ElemType, NodeType>::GetNode(pNode);  // 获取节点元素值
  return true;  // 获取成功返回 true
}

template <class ElemType, class NodeType>
bool LkBinTreeBase<ElemType, NodeType>::IsEmpty() const {
  return !m_pRoot || (!GetLeftChild(m_pRoot) &&
                      !GetRightChild(m_pRoot));  // 根为空或无子节点
}

template <class ElemType, class NodeType>
NodeType*& LkBinTreeBase<ElemType, NodeType>::GetLeftChild(
    NodeType* pNode) const {
  return pNode->m_pLeftChild;  // 返回左子节点指针
}

template <class ElemType, class NodeType>
NodeType*& LkBinTreeBase<ElemType, NodeType>::GetRightChild(
    NodeType* pNode) const {
  return pNode->m_pRightChild;  // 返回右子节点指针
}

template <class ElemType, class NodeType>
bool LkBinTreeBase<ElemType, NodeType>::CreateBinTree(ElemType* arrPre,
                                                      ElemType* arrIn,
                                                      int nSize) {
  if (!arrPre || !arrIn || nSize < 1)
    return false;             // 参数检查
  this->DestroyAux(m_pRoot);  // 销毁原有树
  // 根据前序和中序遍历序列重建二叉树
  m_pRoot = this->CreateBinTreeAux(NULL, arrPre, arrIn, 0, nSize - 1, 0,
                                   nSize - 1, false);
  return true;  // 创建成功
}

template <class ElemType, class NodeType>
LkBinTreeBase<ElemType, NodeType>& LkBinTreeBase<ElemType, NodeType>::operator=(
    const LkBinTreeBase<ElemType, NodeType>& lbtbSrc) {
  if (&lbtbSrc != this) {
    this->DestroyAux(m_pRoot);                 // 销毁当前树
    m_pRoot = CopyTreeAux(lbtbSrc.GetRoot());  // 复制源树
  }
  return *this;
}

template <class ElemType, class NodeType>
bool LkBinTreeBase<ElemType, NodeType>::SetElem(NodeType* pNode,
                                                const ElemType& tElem) {
  if (!pNode)
    return false;          // 空节点返回 false
  pNode->m_tElem = tElem;  // 设置节点元素值
  return true;             // 设置成功返回 true
}

template <class ElemType, class NodeType>
void LkBinTreeBase<ElemType, NodeType>::ReleaseNode(NodeType*& pNode) {
  if (!pNode)
    return;      // 空节点直接返回
  delete pNode;  // 释放节点内存
  pNode = NULL;  // 指针置空
}

template <class ElemType, class NodeType>
NodeType* LkBinTreeBase<ElemType, NodeType>::CreateChildNode(NodeType* pNode,
                                                             bool bLeft) {
  if (!pNode) {  // 创建根节点
    NodeType* pRoot = new NodeType;
    return pRoot;
  }

  // 检查目标位置是否已有子节点
  if ((GetLeftChild(pNode) && bLeft) || (GetRightChild(pNode) && !bLeft)) {
    return NULL;
  }

  NodeType* pChild = new NodeType();        // 创建新子节点
  LinkParentChild(pNode, pChild, bLeft);  // 建立父子关系
  return pChild;                          // 返回新节点指针
}

template <class ElemType, class NodeType>
NodeType* LkBinTreeBase<ElemType, NodeType>::CopyTreeAux(
    const NodeType* pRoot) {
  if (pRoot == NULL)
    return NULL;  // 空树返回 NULL

  // 递归复制左右子树
  NodeType* pLeftChild = CopyTreeAux(GetLeftChild(pRoot));
  NodeType* pRightChild = CopyTreeAux(GetRightChild(pRoot));
  NodeType* pParent = new NodeType;
  SetElem(pParent, pRoot->m_tElem);              // 复制节点元素值
  LinkParentChild(pParent, pLeftChild, true);    // 连接左子树
  LinkParentChild(pParent, pRightChild, false);  // 连接右子树
  return pParent;                                // 返回子树根节点
}

#endif  // LK_BINARY_TREE_BASE_H_