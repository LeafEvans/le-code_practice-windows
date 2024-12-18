#ifndef PARENT_TREE_H_
#define PARENT_TREE_H_
#include <memory.h>

#include "node.h"
#include "sq_list.h"
#include "tree_base.h"

namespace naParentTree {
const int kDefaultSize = 128;  // 默认大小
}  // namespace naParentTree

template <class ElemType>
class ParentTree : public TreeBase<ElemType, int>,
                   private SqList<ParentTreeNode<ElemType>> {
 public:
  ParentTree();
  ~ParentTree();
  ParentTree(const ElemType& tElem,
             int nBufferLen = naParentTree::kDefaultSize);
  ParentTree(const ParentTree<ElemType>& ptSrc);
  ParentTree(ElemType* arrElems, int* arrParents, int nRoot, int nDataLen,
             int nBufferLen);
  ParentTree<ElemType>& operator=(const ParentTree<ElemType>& ptSrc);
  virtual int GetRoot() const;
  virtual bool IsEmpty() const;
  virtual bool NodeIsEmpty(int nNode) const;
  virtual bool GetElem(int nNode, ElemType& tElem) const;
  virtual bool SetElem(int nNode, const ElemType& tElem);
  virtual int GetFirstChild(int nNode) const;
  virtual int GetRightSibling(int nNode) const;
  virtual int GetParent(int nNode) const;

 private:
  virtual ElemType GetNode(int nNode) const;
  virtual void ReleaseNode(int& nNode);
  virtual int CreateChildNode(int nNode, int nIdx, const ElemType& tElem);
  virtual int RemoveChild(int nParent, int nIdx);
  virtual void ClearRemovedNode();
  int m_nRoot;  // 根节点索引
};

template <class ElemType>
ParentTree<ElemType>::ParentTree()
    : SqList<ParentTreeNode<ElemType>>(naParentTree::kDefaultSize),
      m_nRoot(-1) {}  // 构造函数，初始化根节点为-1

template <class ElemType>
ParentTree<ElemType>::~ParentTree() {}  // 析构函数

template <class ElemType>
int ParentTree<ElemType>::GetRoot() const {
  return m_nRoot;  // 获取根节点索引
}

template <class ElemType>
bool ParentTree<ElemType>::IsEmpty() const {
  return SqList<ElemType>::IsEmpty();  // 判断树是否为空
}

template <class ElemType>
bool ParentTree<ElemType>::GetElem(int nNode, ElemType& tElem) const {
  if (nNode < 0 || nNode >= this->m_nDataLen)
    return false;                        // 节点索引不合法
  tElem = this->m_pData[nNode].m_tElem;  // 获取节点元素
  return true;
}

template <class ElemType>
bool ParentTree<ElemType>::SetElem(int nNode, const ElemType& tElem) {
  if (nNode < 0 || nNode >= this->m_nDataLen)
    return false;                        // 节点索引不合法
  this->m_pData[nNode].m_tElem = tElem;  // 设置节点元素
  return true;
}

template <class ElemType>
int ParentTree<ElemType>::GetFirstChild(int nNode) const {
  for (int i = 0; i < this->m_nDataLen; ++i) {
    if (this->m_pData[i].m_nParent == nNode) {
      return i;  // 返回第一个子节点的索引
    }
  }
  return -1;  // 没有子节点
}

template <class ElemType>
bool ParentTree<ElemType>::NodeIsEmpty(int nNode) const {
  return nNode < 0 || nNode >= this->m_nDataLen;  // 判断节点是否为空
}

template <class ElemType>
int ParentTree<ElemType>::GetRightSibling(int nNode) const {
  for (int i = nNode + 1; i < this->m_nDataLen; ++i) {
    if (this->m_pData[nNode].m_nParent == this->m_pData[i].m_nParent) {
      return i;  // 返回右兄弟节点的索引
    }
  }
  return -1;  // 没有右兄弟节点
}

template <class ElemType>
int ParentTree<ElemType>::GetParent(int nNode) const {
  return (nNode < 0 || nNode >= this->m_nDataLen)
             ? -1
             : this->m_pData[nNode].m_nParent;  // 获取父节点索引
}

template <class ElemType>
ElemType ParentTree<ElemType>::GetNode(int nNode) const {
  return this->m_pData[nNode];  // 获取节点
}

template <class ElemType>
void ParentTree<ElemType>::ReleaseNode(int& nNode) {
  if (NodeIsEmpty(nNode))
    return;                             // 节点为空，直接返回
  this->m_pData[nNode].m_nParent = -2;  // 释放节点，将父节点设为-2
}

template <class ElemType>
int ParentTree<ElemType>::CreateChildNode(int nNode, int nIdx,
                                          const ElemType& tElem) {
  if (NodeIsEmpty(nNode) || nIdx <= 0 || nIdx > this->NodeDegree(nNode) + 1) {
    return -1;  // 参数不合法，返回-1
  }

  // 检查是否需要扩展存储空间
  if (this->m_nDataLen + 1 >= this->m_nBufferLen) {
    this->Reserve((this->m_nDataLen + 1) * 2);  // 扩展存储空间为当前的两倍
  }

  // 找到第nIdx个孩子的位置
  int nChild = GetFirstChild(nNode);
  for (int i = 1; i < nIdx && nChild != -1; ++i) {
    GetRightSibling(nChild);  // 逐个查找右兄弟
  }

  if (nChild != -1) {  // 在中间位置插入新节点
    // 将nChild及其后的节点向后移动一个位置
    std::copy(this->m_pData + nChild, this->m_pData + this->m_nDataLen,
              this->m_pData + nChild + 1);

    // 更新受影响节点的父节点索引
    for (int i = nChild + 1; i <= this->m_nDataLen; ++i) {
      if (this->m_pData[i].m_nParent >= nChild) {
        ++(this->m_pData[i].m_nParent);
      }
    }
  } else {
    nChild = this->m_nDataLen;  // 在末尾插入新节点
  }

  // 设置新节点的数据
  this->m_pData[nChild].m_tElem = tElem;    // 设置节点元素值
  this->m_pData[nChild].m_nParent = nNode;  // 设置父节点索引

  ++(this->m_nDataLen);  // 增加节点数
  return nChild;         // 返回新节点的索引
}

template <class ElemType>
int ParentTree<ElemType>::RemoveChild(int nParent, int nIdx) {
  if (NodeIsEmpty(nParent) || nIdx <= 0 || nIdx >= this->NodeDegree(nParent)) {
    return -1;  // 参数不合法，返回-1
  }

  int nChild = GetFirstChild(nParent);
  for (int i = 1; i < nIdx && nChild != -1; ++i) {
    nChild = GetRightSibling(nChild);  // 逐个查找右兄弟
  }

  return nChild;  // 返回要移除的子节点索引
}

template <class ElemType>
ParentTree<ElemType>::ParentTree(const ElemType& tElem, int nBufferLen)
    : SqList<ParentTreeNode<ElemType>>(nBufferLen), m_nRoot(0) {
  this->m_nDataLen = 1;
  this->m_pData[m_nRoot].m_tElem = tElem;
  this->m_pData[m_nRoot].m_nParent = -1;  // 初始化根节点
}

template <class ElemType>
void ParentTree<ElemType>::ClearRemovedNode() {
  int* arrPostions = new int[this->m_nDataLen];  // 创建位置数组
  int j = 0;

  for (int i = 0, j = 0; i < this->m_nDataLen; ++i) {
    if (this->m_pData[i].m_nParent == -2) {
      arrPostions[i] = -2;  // 标记已移除节点
      continue;
    }
    arrPostions[i] = j++;  // 更新位置数组
  }

  for (int i = 0, j = 0; i < this->m_nDataLen; ++i) {
    if (this->m_pData[i].m_nParent == -2)
      continue;

    if (j != i) {
      this->m_pData[j] = this->m_pData[i];  // 移动节点
    }

    if (this->m_pData[j].m_nParent >= 0) {
      this->m_pData[j].m_nParent =
          arrPostions[this->m_pData[j].m_nParent];  // 更新父节点索引
    }

    ++j;
  }

  delete[] arrPostions;  // 释放位置数组
  this->m_nDataLen = j;  // 更新节点数
}

template <class ElemType>
ParentTree<ElemType>::ParentTree(const ParentTree<ElemType>& ptSrc) {
  if (&ptSrc != this) {
    this->Reserve(ptSrc.m_nBufferLen);  // 预留空间
    std::copy(ptSrc.m_pData, ptSrc.m_pData + ptSrc.m_nDataLen,
              this->m_pData);             // 复制数据
    m_nRoot = ptSrc.m_nRoot;              // 复制根节点
    this->m_nDataLen = ptSrc.m_nDataLen;  // 复制节点数
  }
}

template <class ElemType>
ParentTree<ElemType>::ParentTree(ElemType* arrElems, int* arrParents, int nRoot,
                                 int nDataLen, int nBufferLen) {
  if (nDataLen > nBufferLen)
    nDataLen = nBufferLen;  // 数据长度不能超过缓冲区长度

  this->Reserve(nBufferLen);  // 预留空间

  for (int i = 0; i < nDataLen; ++i) {
    this->m_pData[i].m_tElem = arrElems[i];      // 复制元素
    this->m_pData[i].m_nParent = arrParents[i];  // 复制父节点索引
  }
  m_nRoot = nRoot;              // 设置根节点
  this->m_nDataLen = nDataLen;  // 设置数据长度
}

template <class ElemType>
ParentTree<ElemType>& ParentTree<ElemType>::operator=(
    const ParentTree<ElemType>& ptSrc) {
  if (&ptSrc != this) {
    this->Reserve(ptSrc.m_nBufferLen);  // 预留空间
    std::copy(ptSrc.m_pData, ptSrc.m_pData + ptSrc.m_nDataLen,
              this->m_pData);             // 复制数据
    m_nRoot = ptSrc.m_nRoot;              // 复制根节点
    this->m_nDataLen = ptSrc.m_nDataLen;  // 复制节点数
  }
  return *this;
}

#endif  // PARENT_TREE_H_