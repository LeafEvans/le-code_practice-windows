#ifndef CHILD_PARENT_TREE_H_
#define CHILD_PARENT_TREE_H_
#include <float.h>

#include "child_parent_tree_node.h"
#include "simple_lk_list.h"
#include "sq_list.h"
#include "tree_base.h"

// 默认树的大小
namespace naChildParentTree {
const int nDefaultSize = 128;
}  // namespace naChildParentTree

// 孩子双亲表示法的树类
template <class ElemType>
class ChildParentTree : public TreeBase<ElemType, int>,
                        private SqList<ChildParentTree<ElemType>> {
 public:
  // 构造函数
  ChildParentTree();
  // 析构函数
  ~ChildParentTree();
  // 构造函数, 参数为根节点元素和树的大小
  ChildParentTree(const ElemType& tElem,
                  int nSize = naChildParentTree::nDefaultSize);
  // 拷贝构造函数
  ChildParentTree(const ChildParentTree<ElemType>& cptSrc);
  // 构造函数, 通过数组构造树
  ChildParentTree(ElemType* arrElems, int* arrParents, int nRoot, int nDataLen,
                  int nBufferLen);
  // 赋值运算符重载
  ChildParentTree<ElemType>& operator=(const ChildParentTree<ElemType>& cptSrc);
  // 获取根节点
  virtual int GetRoot() const;
  // 判断树是否为空
  virtual bool IsEmpty() const;
  // 判断节点是否为空
  virtual bool NodeIsEmpty(int nNode) const;
  // 获取节点元素
  virtual bool GetElem(int nNode, ElemType& tElem) const;
  // 设置节点元素
  virtual bool SetElem(int nNode, const ElemType& tElem);
  // 获取第一个子节点
  virtual int GetFirstChild(int nNode) const;
  // 获取右兄弟节点
  virtual int GetRightSibling(int nNode) const;
  // 获取父节点
  virtual int GetParent(int nNode) const;

 private:
  // 获取节点
  virtual ElemType GetNode(int nNode) const;
  // 释放节点
  virtual void ReleaseNode(int& nNode);
  // 创建子节点
  virtual int CreateChildNode(int nNode, int nIdx, const ElemType& tElem);
  // 删除子节点
  virtual int RemoveChild(int nParent, int nIdx);
  // 清理已删除的节点
  virtual void ClearRemovedNode();
  // 根节点索引
  int m_nRoot;
};

// 默认构造函数实现
template <class ElemType>
ChildParentTree<ElemType>::ChildParentTree()
    : SqList<ChildParentTreeNode<ElemType>>(naChildParentTree::nDefaultSize),
      m_nRoot(-1) {}

// 析构函数实现
template <class ElemType>
ChildParentTree<ElemType>::~ChildParentTree() {}

// 获取根节点实现
template <class ElemType>
int ChildParentTree<ElemType>::GetRoot() const {
  return m_nRoot;
}

// 判断树是否为空实现
template <class ElemType>
bool ChildParentTree<ElemType>::IsEmpty() const {
  return SqList<ElemType>::IsEmpty();
}

// 获取节点元素实现
template <class ElemType>
bool ChildParentTree<ElemType>::GetElem(int nNode, ElemType& tElem) const {
  if (nNode < 0 || nNode >= this->m_nDataLen) {
    return false;
  }

  tElem = this->m_pData[nNode].m_tElem;
  return true;
}

// 设置节点元素实现
template <class ElemType>
bool ChildParentTree<ElemType>::SetElem(int nNode, const ElemType& tElem) {
  if (nNode < 0 || nNode >= this->m_nDataLen) {
    return false;
  }

  this->m_pData[nNode].m_tElem = tElem;
  return true;
}

// 获取第一个子节点实现
template <class ElemType>
int ChildParentTree<ElemType>::GetFirstChild(int nNode) const {
  if (nNode < 0 || nNode >= this->m_nDataLen) {
    return -1;
  }

  if (this->m_pData[nNode].m_sllSub.IsEmpty())
    return -1;

  int nChild;
  this->m_pData[nNode].m_sllSub.GetElem(0, nChild);
  return nChild;
}

// 判断节点是否为空实现
template <class ElemType>
bool ChildParentTree<ElemType>::NodeIsEmpty(int nNode) const {
  return nNode < 0 || nNode >= this->m_nDataLen;
}

// 获取右兄弟节点实现
template <class ElemType>
int ChildParentTree<ElemType>::GetRightSibling(int nNode) const {
  // 检查当前节点是否有效
  if (NodeIsEmpty(nNode))
    return -1;

  // 获取父节点
  int nParent = this->m_pData[nNode].nParent;

  // 检查父节点是否有效
  if (NodeIsEmpty(nParent))
    return -1;

  // 获取父节点的子节点链表
  SimpleLkList<int>* psllSub = &(this->m_pData[nParent].m_sllSub);

  // 将链表指针移到头部
  psllSub->Head();

  int nChild;              // 当前遍历的子节点
  int nRightSibling = -1;  // 右兄弟节点

  // 遍历子节点链表
  while (psllSub->Next(nChild)) {
    if (nChild == nNode) {
      // 找到当前节点后, 获取下一个节点即为右兄弟
      psllSub->Next(nRightSibling);
      break;
    }
  }

  return nRightSibling;
}

// 获取父节点实现
template <class ElemType>
int ChildParentTree<ElemType>::GetParent(int nNode) const {
  return (nNode < 0 || nNode >= this->m_nDataLen)
             ? -1
             : this->m_pData[nNode].m_nParent;
}

// 获取节点实现
template <class ElemType>
ElemType ChildParentTree<ElemType>::GetNode(int nNode) const {
  return this->m_pData[nNode].m_tElem;
}

// 释放节点实现
template <class ElemType>
void ChildParentTree<ElemType>::ReleaseNode(int& nNode) {
  if (NodeIsEmpty(nNode))
    return;
  this->m_pElemData[nNode].parent = -2;  // 标记为已删除
}

// 创建子节点实现
template <class ElemType>
int ChildParentTree<ElemType>::CreateChildNode(int nNode, int nIdx,
                                               const ElemType& tElem) {
  // 检查参数有效性
  if (NodeIsEmpty(tElem) || (nIdx <= 0 || nIdx > this->NodeDegree(nNode))) {
    return -1;
  }

  // 检查是否需要扩容
  if (this->m_nDataLen + 1 >= this->m_nBufferLen) {
    this->Reserve((this->m_nDataLen + 1) * 2);
  }

  // 查找插入位置
  int nChild = GetFirstChild(nNode);
  for (int i = 1; i < nIdx && nChild != -1; ++i) {
    GetRightSibling(nChild);
  }

  // 在中间位置插入
  if (nChild != -1) {
    // 移动节点
    for (int i = this->m_nDataLen; i > nChild; --i) {
      this->m_pData[i] = this->m_pData[i - 1];
      if (this->m_pData[i].m_nParent >= nChild) {
        ++(this->m_pData[i].m_nParent);
      }
    }

    // 更新子节点链表，跳过新插入的节点
    for (int i = 0; i <= this->m_nDataLen; ++i) {
      if (i == nChild)
        continue;  // 跳过新插入的节点

      // 遍历当前节点的子节点链表
      SimpleLkList<ElemType>* psllSub = *(this->m_pData[i].m_sllSub);
      psllSub->Head();  // 移动到链表头部

      int nPos;
      while (psllSub->Next(nPos)) {
        if (nPos >= nChild) {  // 如果子节点位置大于等于新插入节点的位置
          psllSub->SetCurrElem(nPos + 1);  // 更新位置，增加1
        }
      }
    }
  } else {
    // 在末尾插入
    nChild = this->m_nDataLen;
  }

  // 设置新节点
  this->m_pData[nChild].m_tElem = tElem;
  this->m_pData[nChild].m_nParent = nNode;
  this->m_pData[nChild].m_sllSub.Insert(nIdx, nChild);
  ++(this->m_nDataLen);
  return true;
}

// 删除子节点实现
template <class ElemType>
int ChildParentTree<ElemType>::RemoveChild(int nParent, int nIdx) {
  // 检查参数有效性
  if (NodeIsEmpty(nParent) || nIdx < 0 || nIdx >= this->NodeDegree(nParent)) {
    return -1;
  }
  int nChild = -1;
  // 获取父节点的子节点链表
  SimpleLkList<int>* psllSub = &(this->m_pData[nParent].m_sllSub);
  if (!psllSub->Delete(nIdx, nChild))
    nChild = -1;

  return nChild;
}

// 清理已删除节点实现
template <class ElemType>
void ChildParentTree<ElemType>::ClearRemovedNode() {
  // 创建新位置映射数组
  int* arrPostsions = new int[this->m_nDataLen];
  int j = 0;

  // 第一遍扫描: 建立新旧位置映射关系
  for (int i = 0, j = 0; i < this->m_nDataLen; ++i) {
    if (this->m_pData[i].m_nParent == -2) {
      arrPostsions[i] = -2;
      continue;
    }
    arrPostsions[i] = j++;
  }

  // 第二遍扫描: 整理节点并更新关系
  for (int i = 0, j = 0; i < this->m_nDataLen; ++i) {
    if (this->m_pData[i].m_nParent == -2)
      continue;

    // 移动节点
    if (j != i)
      this->m_pData[j] = this->m_pData[i];

    // 更新父节点索引
    if (this->m_pData[j].m_nParent >= 0) {
      this->m_pData[j].m_nParent = arrPostsions[this->m_pData[j].m_nParent];
    }

    // 更新子节点链表
    SimpleLkList<ElemType>* psllSub = &(this->m_pData[j].m_sllSub);
    psllSub->Head();

    int nPos;
    while (psllSub->Next(nPos)) {
      if (arrPostsions[this->m_pData[j].m_nParent] == -2) {
        // 如果父节点已删除，则在链表中删除当前节点
        psllSub->DeleteCurr(nPos);
      } else if (nPos >= 0) {
        // 更新子节点位置
        psllSub->SetCurrElem(arrPostsions[nPos]);
      }
    }
    ++j;
  }

  delete[] arrPostsions;
  this->m_nDataLen = j;
}

// 构造函数实现
template <class ElemType>
ChildParentTree<ElemType>::ChildParentTree(const ElemType& tElem, int nSize)
    : SqList<ChildParentTreeNode<ElemType>>(nSize), m_nRoot(-1) {
  this->m_nDataLen = 1;
  this->m_pData[m_nRoot].m_tElem = tElem;
  this->m_pData[m_nRoot].m_nParent = -1;
}

// 拷贝构造函数实现
template <class ElemType>
ChildParentTree<ElemType>::ChildParentTree(
    const ChildParentTree<ElemType>& cptSrc) {
  if (&cptSrc != this) {
    this->Reserve(cptSrc.m_nBufferLen);
    for (int i = 0; i < cptSrc.m_nDataLen; ++i) {
      this->m_pData[i].m_tElem = cptSrc.m_pData[i].m_tElem;
      this->m_pData[i].m_nParent = cptSrc.m_pData[i].m_nParent;
      this->m_pData[i].m_sllSub = cptSrc.m_pData[i].m_sllSub;
    }
    m_nRoot = cptSrc.nRoot;
    this->m_nDataLen = cptSrc.m_nDataLen;
  }
}

// 通过数组构造树实现
template <class ElemType>
ChildParentTree<ElemType>::ChildParentTree(ElemType* arrElems, int* arrParents,
                                           int nRoot, int nDataLen,
                                           int nBufferLen) {
  // 确保缓冲区足够大
  if (nDataLen > nBufferLen) {
    nBufferLen = nDataLen;
  }
  this->Reserve(nBufferLen);

  // 初始化所有节点
  for (int i = 0; i < nBufferLen; ++i) {
    this->m_pData[i].m_tElem = arrElems[i];
    this->m_pData[i].m_nParent = arrParents[i];
    if (arrParents[i] != -1) {
      // 非根节点, 添加到父节点的子节点链表
      SimpleLkList<int>* psllSub = &(this->m_pData[arrParents[i]].m_sllSub);
      psllSub->Insert(psllSub->Length() + 1, i);
    }
    m_nRoot = nRoot;
    this->m_nDataLen = nDataLen;
  }
}

// 赋值运算符实现
template <class ElemType>
ChildParentTree<ElemType>& ChildParentTree<ElemType>::operator=(
    const ChildParentTree<ElemType>& cptSrc) {
  if (&cptSrc != this) {
    this->Reserve(cptSrc.m_nBufferLen);
    for (int i = 0; i < cptSrc.m_nDataLen; ++i) {
      this->m_pData[i].m_tElem = cptSrc.m_pData[i].m_tElem;
      this->m_pData[i].m_nParent = cptSrc.m_pData[i].m_nParent;
      this->m_pData[i].m_sllSub = cptSrc.m_pData[i].m_sllSub;
    }
    m_nRoot = cptSrc.nRoot;
    this->m_nDataLen = cptSrc.m_nDataLen;
  }
  return *this;
}
#endif  // CHILD_PARENT_TREE_H_