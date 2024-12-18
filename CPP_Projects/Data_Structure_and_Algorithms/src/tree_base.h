#ifndef TREE_BASE_H_
#define TREE_BASE_H_
#include <algorithm>
#include <iostream>

#include "lk_queue.h"

template <class ElemType, class NodeHandle>
class TreeBase {
 public:
  TreeBase();
  ~TreeBase();
  virtual NodeHandle GetRoot() const = 0;  // 获取根节点
  virtual bool IsEmpty() const = 0;        // 判断树是否为空
  virtual bool NodeIsEmpty(NodeHandle hNode) const = 0;  // 判断节点是否为空
  virtual bool GetElem(NodeHandle hNode,
                       ElemType& tElem) const = 0;  // 获取节点元素
  virtual bool SetElem(NodeHandle hNode,
                       const ElemType& tElem) const = 0;  // 设置节点元素
  virtual NodeHandle GetFirstChild(
      NodeHandle hNode) const = 0;  // 获取第一个子节点
  virtual NodeHandle GetRightSibling(
      NodeHandle hNode) const = 0;  // 获取右兄弟节点
  virtual NodeHandle GetParent(NodeHandle hNode) const = 0;  // 获取父节点
  virtual void PreOrder(void (*pVisit)(const ElemType&)) const;  // 前序遍历
  virtual void PostOrder(void (*pVisit)(const ElemType&)) const;  // 后序遍历
  virtual void LevelOrder(void (*pVisit)(const ElemType&)) const;  // 层次遍历
  virtual int NodeCount() const;                         // 获取节点数量
  virtual int NodeDegree(const NodeHandle hNode) const;  // 获取节点度数
  virtual int Degree() const;                            // 获取树的度数
  virtual bool InsertChild(NodeHandle hNode, int nIdx,
                           const ElemType& tElem);       // 插入子节点
  virtual bool DeleteChild(NodeHandle hNode, int nIdx);  // 删除子节点
  virtual int Height() const;                            // 获取树的高度
  virtual void DisplayTreeStructure();                   // 显示树的结构

 protected:
  void DesrtroyAux(NodeHandle& hRoot);  // 辅助销毁函数
  void PreOrderAux(const NodeHandle hRoot,
                   void (*pVisit)(const ElemType&)) const;  // 辅助前序遍历函数
  void PostOrderAux(const NodeHandle hRoot,
                    void (*pVisit)(const ElemType&)) const;  // 辅助后序遍历函数
  int NodeCountAux(const NodeHandle hRoot) const;  // 辅助获取节点数量函数
  int HeightAux(const NodeHandle hRoot) const;  // 辅助获取树的高度函数
  int DegreeAux(const NodeHandle hRoot) const;  // 辅助获取树的度数函数
  void DeleteAux(NodeHandle hRoot);             // 辅助删除函数
  void DisplayTreeStructureAux(NodeHandle hRoot,
                               int nLevel);  // 辅助显示树结构函数
  const NodeHandle GetParentAux(
      const NodeHandle hRoot,
      const NodeHandle pNode) const;  // 辅助获取父节点函数
  virtual ElemType GetNode(NodeHandle hNode) const = 0;  // 获取节点
  virtual void ReleaseNode(NodeHandle& hNode) = 0;       // 释放节点
  virtual NodeHandle CreateChildNode(NodeHandle hNode, int nIdx,
                                     const ElemType& tElem);  // 创建子节点
  virtual NodeHandle RemoveChild(NodeHandle hParent,
                                 int nIdx) = 0;  // 移除子节点
  virtual void ClearRemovedNode() = 0;           // 清除已移除的节点
};

template <class ElemType, class NodeHandle>
TreeBase<ElemType, NodeHandle>::TreeBase() {}

template <class ElemType, class NodeHandle>
TreeBase<ElemType, NodeHandle>::~TreeBase() {}

template <class ElemType, class NodeHandle>
void TreeBase<ElemType, NodeHandle>::PreOrderAux(
    const NodeHandle hRoot, void (*pVisit)(const ElemType&)) const {
  if (!NodeIsEmpty(hRoot)) {
    (*pVisit)(GetNode(hRoot));  // 访问根节点
    for (NodeHandle hChild = GetFirstChild(hRoot); !IsEmpty(hChild);
         hChild = GetRightSibling(hChild)) {
      PreOrderAux(hChild, pVisit);  // 递归访问子节点
    }
  }
}

template <class ElemType, class NodeHandle>
void TreeBase<ElemType, NodeHandle>::PostOrderAux(
    const NodeHandle hRoot, void (*pVisit)(const ElemType&)) const {
  if (!NodeIsEmpty(hRoot)) {
    for (NodeHandle hChild = GetFirstChild(hRoot); !IsEmpty(hChild);
         hChild = GetRightSibling(hChild)) {
      PostOrderAux(hChild, pVisit);  // 递归访问子节点
    }
    (*pVisit)(GetNode(hRoot));  // 访问根节点
  }
}

template <class ElemType, class NodeHandle>
void TreeBase<ElemType, NodeHandle>::PreOrder(
    void (*pVisit)(const ElemType&)) const {
  PreOrderAux(GetRoot(), pVisit);  // 调用辅助前序遍历函数
}

template <class ElemType, class NodeHandle>
void TreeBase<ElemType, NodeHandle>::PostOrder(
    void (*pVisit)(const ElemType&)) const {
  PostOrderAux(GetRoot(), pVisit);  // 调用辅助后序遍历函数
}

template <class ElemType, class NodeHandle>
void TreeBase<ElemType, NodeHandle>::LevelOrder(
    void (*pVisit)(const ElemType&)) const {
  LkQueue<ElemType> lqNodes;
  NodeHandle hNode = GetRoot();

  if (!NodeIsEmpty(hNode))
    lqNodes.InQueue(hNode);  // 根节点入队

  while (!lqNodes.IsEmpty()) {
    lqNodes.OutQueue(hNode);    // 节点出队
    (*pVisit)(GetNode(hNode));  // 访问节点
    for (NodeHandle hChild = GetFirstChild(hNode); !NodeIsEmpty(hChild);
         hChild = GetRightSibling(hNode)) {
      lqNodes.InQueue(hChild);  // 子节点入队
    }
  }
}

template <class ElemType, class NodeHandle>
int TreeBase<ElemType, NodeHandle>::NodeCountAux(const NodeHandle hRoot) const {
  if (NodeIsEmpty(hRoot))
    return 0;

  int nNodeCount = 1;  // 初始化节点数量为1

  for (NodeHandle hChild = GetFirstChild(hRoot); !NodeIsEmpty(hChild);
       hChild = GetRightSibling(hChild)) {
    nNodeCount += NodeCountAux(hChild);  // 递归计算子节点数量
  }

  return nNodeCount;
}

template <class ElemType, class NodeHandle>
int TreeBase<ElemType, NodeHandle>::NodeCount() const {
  return NodeCountAux(GetRoot());  // 调用辅助获取节点数量函数
}

template <class ElemType, class NodeHandle>
int TreeBase<ElemType, NodeHandle>::HeightAux(const NodeHandle hRoot) const {
  if (NodeIsEmpty(hRoot))
    return 0;

  int nSubHeight = 0;  // 初始化子树高度为0
  for (NodeHandle hChild = GetFirstChild(hRoot); !NodeIsEmpty(hChild);
       hChild = GetRightSibling(hChild)) {
    nSubHeight = std::max(nSubHeight, HeightAux(hChild));  // 递归计算子树高度
  }
  return nSubHeight + 1;  // 返回树的高度
}

template <class ElemType, class NodeHandle>
int TreeBase<ElemType, NodeHandle>::Height() const {
  return HeightAux(GetRoot());  // 调用辅助获取树的高度函数
}

template <class ElemType, class NodeHandle>
int TreeBase<ElemType, NodeHandle>::NodeDegree(const NodeHandle hNode) const {
  int nDegree = 0;  // 初始化度数为0
  for (NodeHandle hChild = GetFirstChild(hNode); !NodeIsEmpty(hChild);
       hChild = GetRightSibling(hChild)) {
    ++nDegree;  // 计算节点的度数
  }
  return nDegree;
}

template <class ElemType, class NodeHandle>
int TreeBase<ElemType, NodeHandle>::DegreeAux(const NodeHandle hRoot) const {
  if (NodeIsEmpty(hRoot))
    return 0;

  int nDegree = 0;     // 初始化度数为0
  int nSubDegree = 0;  // 初始化子树度数为0

  for (NodeHandle hChild = GetFirstChild(hRoot); !NodeIsEmpty(hChild);
       hChild = GetRightSibling(hChild)) {
    ++nDegree;  // 计算节点的度数
    nSubDegree = std::max(nSubDegree, DegreeAux(hChild));  // 递归计算子树度数
  }

  return std::max(nDegree, nSubDegree);  // 返回树的度数
}

template <class ElemType, class NodeHandle>
int TreeBase<ElemType, NodeHandle>::Degree() const {
  return DegreeAux(GetRoot());  // 调用辅助获取树的度数函数
}

template <class ElemType, class NodeHandle>
const NodeHandle TreeBase<ElemType, NodeHandle>::GetParentAux(
    const NodeHandle hRoot, const NodeHandle hNode) const {
  if (NodeIsEmpty(hRoot))
    return NULL;

  NodeHandle hChild = GetFirstChild(hRoot);
  while (!NodeIsEmpty(hChild)) {
    if (hChild == hNode)
      return hRoot;                                    // 找到父节点
    NodeHandle hParent = GetParentAux(hChild, hNode);  // 递归查找父节点
    if (hParent)
      return hParent;
    hChild = GetRightSibling(hChild);
  }

  return NULL;
}

template <class ElemType, class NodeHandle>
NodeHandle TreeBase<ElemType, NodeHandle>::GetParent(
    const NodeHandle hNode) const {
  return GetParentAux(GetRoot(), hNode);  // 调用辅助获取父节点函数
}

template <class ElemType, class NodeHandle>
bool TreeBase<ElemType, NodeHandle>::InsertChild(NodeHandle pNode, int nIdx,
                                                 const ElemType& tElem) {
  if (NodeIsEmpty(pNode) || nIdx <= 0 || nIdx > NodeDegree(pNode) + 1) {
    return false;
  }

  NodeHandle hNewNode = CreateChildNode(pNode, nIdx, tElem);  // 创建新子节点

  return !NodeIsEmpty(hNewNode);
}

template <class ElemType, class NodeHandle>
void TreeBase<ElemType, NodeHandle>::DeleteAux(NodeHandle hRoot) {
  if (NodeIsEmpty(hRoot))
    return;
  NodeHandle hChild = (NodeHandle)GetFirstChild(hRoot);
  while (!NodeIsEmpty(hChild)) {
    NodeHandle hNextChild = (NodeHandle)GetRightSibling(hChild);
    DeleteAux(hChild);  // 递归删除子节点
    hChild = hNextChild;
  }
  ReleaseNode(hRoot);  // 释放节点
}

template <class ElemType, class NodeHandle>
bool TreeBase<ElemType, NodeHandle>::DeleteChild(NodeHandle pNode, int nIdx) {
  if (NodeIsEmpty(pNode) || (nIdx <= 0 || nIdx > NodeDegree(pNode))) {
    return false;
  }

  NodeHandle hRemovedNode = RemoveChild(pNode, nIdx);  // 移除子节点

  if (NodeIsEmpty(hRemovedNode))
    return false;

  DeleteAux(hRemovedNode);  // 递归删除子节点
  ClearRemovedNode();       // 清除已移除的节点
  return true;
}

template <class ElemType, class NodeHandle>
void TreeBase<ElemType, NodeHandle>::DisplayTreeStructureAux(NodeHandle hRoot,
                                                             int nLevel) {
  if (NodeIsEmpty(hRoot) || NodeCount() == 0)
    return;

  if (nLevel > 1) {
    DisplayTreeStructureAux(GetRightSibling(hRoot),
                            nLevel - 1);  // 递归显示右兄弟节点
  }

  std::cout << std::endl;
  for (int i = 0; i < nLevel - 1; ++i)
    std::cout << "  ";  // 使用两个空格来缩进

  if (nLevel > 1) {
    std::cout << "    |";
  } else {
    std::cout << "----";
  }

  ElemType tElem;
  GetElem(hRoot, tElem);  // 获取节点元素
  std::cout << " " << tElem;

  for (NodeHandle hChild = GetFirstChild(hRoot); !NodeIsEmpty(hChild);
       hChild = GetRightSibling(hChild)) {
    DisplayTreeStructureAux(hChild, nLevel + 1);  // 递归显示子节点
  }
}

template <class ElemType, class NodeHandle>
void TreeBase<ElemType, NodeHandle>::DisplayTreeStructure() {
  DisplayTreeStructureAux(GetRoot(), 1);  // 调用辅助显示树结构函数
  std::cout << std::endl;
}

#endif  // TREE_BASE_H_