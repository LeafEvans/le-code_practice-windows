#ifndef SQ_BIN_TREE_H_
#define SQ_BIN_TREE_H_
#include "bin_tree_base.h"
#include "sq_bin_tree_node.h"
#include "sq_list.h"

namespace naSqBinTree {
const int kDefaultSize = 256;
};

template <class ElemType>
class SqBinTree : public BinTreeBase<ElemType, int>,
                  private SqList<SqBinTreeNode<ElemType>> {
 public:
  SqBinTree();  // 默认构造函数
  SqBinTree(const ElemType& tElem,
            int nSize = naSqBinTree::kDefaultSize);  // 带参数的构造函数
  ~SqBinTree();                                      // 析构函数
  SqBinTree(const SqBinTree<ElemType>& sbtSrc);      // 拷贝构造函数
  SqBinTree(SqBinTreeNode<ElemType>* arrNodes, int nRoot,
            int nSize = naSqBinTree::kDefaultSize);  // 带节点数组的构造函数
  SqBinTree<ElemType>& operator=(
      const SqBinTree<ElemType>& sbtSrc);     // 赋值运算符重载
  virtual int GetRoot() const;                // 获取根节点
  virtual bool NodeIsEmpty(int nNode) const;  // 判断节点是否为空
  virtual bool GetElem(int nNode, ElemType& tElem) const;  // 获取节点元素
  virtual bool SetElem(int nNode, const ElemType& tElem);  // 设置节点元素
  virtual bool IsEmpty() const;                 // 判断树是否为空
  virtual int& GetLeftChild(int nNode) const;   // 获取左孩子节点
  virtual int& GetRightChild(int nNode) const;  // 获取右孩子节点
  virtual int GetParent(int nNode) const;       // 获取父节点
  virtual bool CreateBinTree(ElemType* arrPre, ElemType* arrIn,
                             int nSize);  // 创建二叉树

 protected:
  virtual ElemType GetNode(int nNode) const;           // 获取节点元素
  virtual void ReleaseNode(int& nNode);                // 释放节点
  virtual int CreateChildNode(int nNode, bool bLeft);  // 创建子节点
  int m_nRoot;                                         // 根节点索引
  mutable int m_nLeftChild;                            // 左孩子索引
  mutable int m_nRightChild;                           // 右孩子索引
};

template <class ElemType>
SqBinTree<ElemType>::SqBinTree()
    : BinTreeBase<ElemType, int>(),
      SqList<SqBinTreeNode<ElemType>>(naSqBinTree::kDefaultSize) {
  this->m_nDataLen = naSqBinTree::kDefaultSize;  // 设置数据长度为默认大小
  std::fill(this->m_pData, this->m_pData + naSqBinTree::kDefaultSize,
            0);  // 初始化数据
  m_nRoot = 1;   // 设置根节点索引
}

template <class ElemType>
SqBinTree<ElemType>::SqBinTree(const ElemType& tElem, int nSize)
    : BinTreeBase<ElemType, int>(), SqList<SqBinTreeNode<ElemType>>(nSize) {
  this->m_nDataLen = nSize;                            // 设置数据长度
  std::fill(this->m_pData, this->m_pData + nSize, 0);  // 初始化数据
  m_nRoot = 1;                                         // 设置根节点索引
  // 设置根节点的值
  this->m_pData[m_nRoot].m_eTag = USED_NODE;
  this->m_pData[m_nRoot].m_tElem = tElem;
}

template <class ElemType>
SqBinTree<ElemType>::~SqBinTree() {}  // 析构函数

template <class ElemType>
SqBinTree<ElemType>::SqBinTree(const SqBinTree<ElemType>& sbtSrc) {
  if (&sbtSrc != this) {  // 如果不是同一个对象
    this->Clear();        // 清空数据
    // 拷贝数据
    std::copy(sbtSrc.m_pData, sbtSrc.m_pData + sbtSrc.m_nDataLen,
              this->m_pData);    // 拷贝数据
    m_nRoot = sbtSrc.GetRoot();  // 拷贝根节点索引
  }
}

template <class ElemType>
SqBinTree<ElemType>::SqBinTree(SqBinTreeNode<ElemType>* arrNodes, int nRoot,
                               int nSize)
    : SqList<SqBinTreeNode<ElemType>>(nSize) {
  this->m_nDataLen = nSize;  // 设置数据长度
  // 拷贝节点数组
  std::copy(arrNodes, arrNodes + nSize, this->m_pData);
  m_nRoot = nRoot;  // 设置根节点索引
}

template <class ElemType>
SqBinTree<ElemType>& SqBinTree<ElemType>::operator=(
    const SqBinTree<ElemType>& sbtSrc) {
  if (&sbtSrc != this) {  // 如果不是同一个对象
    this->Clear();        // 清空数据
    // 拷贝数据
    std::copy(sbtSrc.m_pData, sbtSrc.m_pData + sbtSrc.m_nDataLen,
              this->m_pData);    // 拷贝数据
    m_nRoot = sbtSrc.GetRoot();  // 拷贝根节点索引
  }
  return *this;  // 返回当前对象
}

template <class ElemType>
int SqBinTree<ElemType>::GetRoot() const {
  return m_nRoot;  // 返回根节点索引
}

template <class ElemType>
bool SqBinTree<ElemType>::NodeIsEmpty(int nNode) const {
  return (nNode < 1 || nNode > this->m_nDataLen ||
          this->m_pData[nNode].m_eTag == EMPTY_NODE);  // 判断节点是否为空
}

template <class ElemType>
int& SqBinTree<ElemType>::GetLeftChild(int nNode) const {
  m_nLeftChild = 2 * nNode;
  return m_nLeftChild;  // 返回左孩子节点索引的引用
}

template <class ElemType>
int& SqBinTree<ElemType>::GetRightChild(int nNode) const {
  m_nRightChild = 2 * nNode + 1;
  return m_nRightChild;  // 返回右孩子节点索引的引用
}

template <class ElemType>
int SqBinTree<ElemType>::GetParent(int nNode) const {
  return nNode / 2;  // 返回父节点索引
}

template <class ElemType>
bool SqBinTree<ElemType>::GetElem(int nNode, ElemType& tElem) const {
  if (NodeIsEmpty(nNode))
    return false;                        // 如果节点为空，返回 false
  tElem = this->m_pData[nNode].m_tElem;  // 获取节点元素
  return true;                           // 返回 true
}

template <class ElemType>
bool SqBinTree<ElemType>::SetElem(int nNode, const ElemType& tElem) {
  if (NodeIsEmpty(nNode))
    return false;                        // 如果节点为空，返回 false
  this->m_pData[nNode].m_tElem = tElem;  // 设置节点元素
  return true;                           // 返回 true
}

template <class ElemType>
bool SqBinTree<ElemType>::IsEmpty() const {
  return NodeIsEmpty(m_nRoot);  // 判断树是否为空
}

template <class ElemType>
ElemType SqBinTree<ElemType>::GetNode(int nNode) const {
  return this->m_pData[nNode].m_tElem;  // 获取节点元素
}

template <class ElemType>
void SqBinTree<ElemType>::ReleaseNode(int& nNode) {
  this->m_pData[nNode].m_eTag = EMPTY_NODE;  // 释放节点
}

template <class ElemType>
int SqBinTree<ElemType>::CreateChildNode(int nNode, bool bLeft) {
  if (nNode < 0) {
    return 1;  // 返回根节点索引
  } else if (NodeIsEmpty(nNode)) {
    return 0;  // 返回空节点索引
  }

  // 获取子节点索引
  int nChildNode = bLeft ? GetLeftChild(nNode) : GetRightChild(nNode);

  if (nChildNode >= this->m_nDataLen) {  // 如果子节点索引超出数据长度
    this->Reserve(nChildNode * 2);       // 扩展数据长度
    this->m_nDataLen = nChildNode + 1;  // 更新数据长度
  }
  this->m_pData[nChildNode].m_eTag = USED_NODE;  // 标记子节点为已使用
  return nChildNode;                             // 返回子节点索引
}

template <class ElemType>
bool SqBinTree<ElemType>::CreateBinTree(ElemType* arrPre, ElemType* arrIn,
                                        int nSize) {
  // 检查异常情况
  if (!arrPre || !arrIn || nSize < 1 || !this->Reserve(nSize + 1))
    return false;
  std::fill(this->m_pData, this->m_pData + nSize + 1, 0);  // 初始化数据
  // 创建二叉树
  m_nRoot = this->CreateBinTreeAux(-1, arrPre, arrIn, 0, nSize - 1, 0,
                                   nSize - 1, false);
}
#endif  // SQ_BIN_TREE_H_