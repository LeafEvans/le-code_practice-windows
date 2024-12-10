#ifndef _TREE_BASE_H_
#define _TREE_BASE_H_
#include <algorithm>
#include <iostream>

#include "lk_queue.h"

template <class ElemType, class NodeHandle>
class TreeBase {
 public:
  TreeBase();
  ~TreeBase();
  virtual NodeHandle GetRoot() const = 0;
  virtual bool IsEmpty() const = 0;
  virtual bool NodeIsEmpty(NodeHandle hNode) const = 0;
  virtual bool GetElem(NodeHandle hNode, ElemType& tElem) const = 0;
  virtual bool SetElem(NodeHandle hNode, const ElemType& tElem) const = 0;
  virtual NodeHandle GetFirstChild(NodeHandle hNode) const = 0;
  virtual NodeHandle GetRightSibling(NodeHandle hNode) const = 0;
  virtual NodeHandle GetParent(NodeHandle hNode) const = 0;
  virtual void PreOrder(void (*pVisit)(const ElemType&)) const;
  virtual void PostOrder(void (*pVisit)(const ElemType&)) const;
  virtual void LevelOrder(void (*pVisit)(const ElemType&)) const;
  virtual int NodeCount() const;
  virtual int NodeDegree(const NodeHandle hNode) const;
  virtual int Degree() const;
  virtual bool InsertChild(NodeHandle hNode, int nIdx, const ElemType& tElem);
  virtual bool DeleteChild(NodeHandle hNode, int nIdx);
  virtual int Height() const;
  virtual void DisplayTreeStructure();

 protected:
  void DesrtroyAux(NodeHandle& hRoot);
  void PreOrderAux(const NodeHandle hRoot,
                   void (*pVisit)(const ElemType&)) const;
  void PostOrderAux(const NodeHandle hRoot,
                    void (*pVisit)(const ElemType&)) const;
  int NodeCountAux(const NodeHandle hRoot) const;
  int HeightAux(const NodeHandle hRoot) const;
  int DegreeAux(const NodeHandle hRoot) const;
  void DeleteAux(NodeHandle hRoot);
  void DisplayTreeStructureAux(NodeHandle hRoot, int nLevel);
  const NodeHandle GetParentAux(const NodeHandle hRoot,
                                const NodeHandle pNode) const;
  virtual ElemType GetNode(NodeHandle hNode) const = 0;
  virtual void ReleaseNode(NodeHandle& hNode) = 0;
  virtual NodeHandle CreateChildNode(NodeHandle hNode, int nIdx,
                                     const ElemType& tElem);
  virtual NodeHandle RemoveChild(NodeHandle hParent, int nIdx) = 0;
  virtual void ClearRemovedNode() = 0;
};

template <class ElemType, class NodeHandle>
TreeBase<ElemType, NodeHandle>::TreeBase() {}

template <class ElemType, class NodeHandle>
TreeBase<ElemType, NodeHandle>::~TreeBase() {}

template <class ElemType, class NodeHandle>
void TreeBase<ElemType, NodeHandle>::PreOrderAux(
    const NodeHandle hRoot, void (*pVisit)(const ElemType&)) const {
  if (!NodeIsEmpty(hRoot)) {
    (*pVisit)(GetNode(hRoot));
    for (NodeHandle hChild = (NodeHandle)GetFirstChild(hRoot); !IsEmpty(hChild);
         hChild = (NodeHandle)GetRightSibling(hChild)) {
      PreOrderAux(hChild, pVisit);
    }
  }
}

template <class ElemType, class NodeHandle>
void TreeBase<ElemType, NodeHandle>::PostOrderAux(
    const NodeHandle hRoot, void (*pVisit)(const ElemType&)) const {
  if (!NodeIsEmpty(hRoot)) {
    for (NodeHandle hChild = (NodeHandle)GetFirstChild(hRoot); !IsEmpty(hChild);
         hChild = (NodeHandle)GetRightSibling(hChild)) {
      PostOrderAux(hChild, pVisit);
    }
    (*pVisit)(GetNode(hRoot));
  }
}

template <class ElemType, class NodeHandle>
void TreeBase<ElemType, NodeHandle>::PreOrder(
    void (*pVisit)(const ElemType&)) const {
  PreOrderAux(GetRoot(), pVisit);
}

template <class ElemType, class NodeHandle>
void TreeBase<ElemType, NodeHandle>::PostOrder(
    void (*pVisit)(const ElemType&)) const {
  PostOrderAux(GetRoot(), pVisit);
}

template <class ElemType, class NodeHandle>
void TreeBase<ElemType, NodeHandle>::LevelOrder(
    void (*pVisit)(const ElemType&)) const {
  LkQueue<ElemType> lqNodes;
  NodeHandle hNode = GetRoot();

  if (!NodeIsEmpty(hNode)) lqNodes.InQueue(hNode);

  while (!lqNodes.IsEmpty()) {
    lqNodes.OutQueue(hNode);
    (*pVisit)(GetNode(hNode));
    for (NodeHandle hChild = GetFirstChild(hNode); !NodeIsEmpty(hChild);
         hChild = GetRightSibling(hNode)) {
      lqNodes.InQueue(hChild);
    }
  }
}

template <class ElemType, class NodeHandle>
int TreeBase<ElemType, NodeHandle>::NodeCountAux(const NodeHandle hRoot) const {
  if (NodeIsEmpty(hRoot)) return 0;

  int nNodeCount = 1;

  for (NodeHandle hChild = GetFirstChild(hRoot); !NodeIsEmpty(hChild);
       hChild = GetRightSibling(hChild)) {
    nNodeCount += NodeCountAux(hChild);
  }

  return nNodeCount;
}

template <class ElemType, class NodeHandle>
int TreeBase<ElemType, NodeHandle>::NodeCount() const {
  return NodeCountAux(GetRoot());
}

template <class ElemType, class NodeHandle>
int TreeBase<ElemType, NodeHandle>::HeightAux(const NodeHandle hRoot) const {
  if (NodeIsEmpty(hRoot)) return 0;

  int nSubHeight = 0;
  for (NodeHandle hChild = GetFirstChild(hRoot); !NodeIsEmpty(hChild);
       hChild = GetRightSibling(hChild)) {
    nSubHeight = std::max(nSubHeight, HeightAux(hChild));
  }
  return nSubHeight + 1;
}

template <class ElemType, class NodeHandle>
int TreeBase<ElemType, NodeHandle>::Height() const {
  return HeightAux(GetRoot());
}

template <class ElemType, class NodeHandle>
int TreeBase<ElemType, NodeHandle>::NodeDegree(const NodeHandle hNode) const {
  int nDegree = 0;
  for (NodeHandle hChild = GetFirstChild(hNode); !NodeIsEmpty(hChild);
       hChild = GetRightSibling(hChild)) {
    ++nDegree;
  }
  return nDegree;
}

template <class ElemType, class NodeHandle>
int TreeBase<ElemType, NodeHandle>::DegreeAux(const NodeHandle hRoot) const {
  if (NodeIsEmpty(hRoot)) return 0;

  int nDegree = 0;
  int nSubDegree = 0;

  for (NodeHandle hChild = GetFirstChild(hRoot); !NodeIsEmpty(hChild);
       hChild = GetRightSibling(hChild)) {
    ++nDegree;
    nSubDegree = std::max(nSubDegree, DegreeAux(hChild));
  }

  return std::max(nDegree, nSubDegree);
}

template <class ElemType, class NodeHandle>
int TreeBase<ElemType, NodeHandle>::Degree() const {
  return DegreeAux(GetRoot());
}

template <class ElemType, class NodeHandle>
const NodeHandle TreeBase<ElemType, NodeHandle>::GetParentAux(
    const NodeHandle hRoot, const NodeHandle hNode) const {
  if (NodeIsEmpty(hRoot)) return NULL;

  NodeHandle hChild = GetFirstChild(hRoot);
  while (!NodeIsEmpty(hChild)) {
    if (hChild == hNode) return hRoot;
    NodeHandle hParent = GetParentAux(hChild, hNode);
    if (hParent) return hParent;
    hChild = GetRightSibling(hChild);
  }

  return NULL;
}

template <class ElemType, class NodeHandle>
NodeHandle TreeBase<ElemType, NodeHandle>::GetParent(
    const NodeHandle hNode) const {
  return GetParentAux(GetRoot(), hNode);
}

template <class ElemType, class NodeHandle>
bool TreeBase<ElemType, NodeHandle>::InsertChild(NodeHandle pNode, int nIdx,
                                                 const ElemType& tElem) {
  if (NodeIsEmpty(pNode) || nIdx <= 0 || nIdx > NodeDegree(pNode) + 1) {
    return false;
  }

  NodeHandle hNewNode = CreateChildNode(pNode, nIdx, tElem);

  return !NodeIsEmpty(hNewNode);
}

template <class ElemType, class NodeHandle>
void TreeBase<ElemType, NodeHandle>::DeleteAux(NodeHandle hRoot) {
  if (NodeIsEmpty(hRoot)) return;
  NodeHandle hChild = (NodeHandle)GetFirstChild(hRoot);
  while (!NodeIsEmpty(hChild)) {
    NodeHandle hNextChild = (NodeHandle)GetRightSibling(hChild);
    DeleteAux(hChild);
    hChild = hNextChild;
  }
  ReleaseNode(hRoot);
}

template <class ElemType, class NodeHandle>
bool TreeBase<ElemType, NodeHandle>::DeleteChild(NodeHandle pNode, int nIdx) {
  if (NodeIsEmpty(pNode) || (nIdx <= 0 || nIdx > NodeDegree(pNode))) {
    return false;
  }

  NodeHandle hRemovedNode = RemoveChild(pNode, nIdx);

  if (NodeIsEmpty(hRemovedNode)) return false;

  DeleteAux(hRemovedNode);
  ClearRemovedNode();
  return true;
}

template <class ElemType, class NodeHandle>
void TreeBase<ElemType, NodeHandle>::DisplayTreeStructureAux(NodeHandle hRoot,
                                                             int nLevel) {
  if (NodeIsEmpty(hRoot) || NodeCount() == 0) return;

  if (nLevel > 1) {
    DisplayTreeStructureAux(GetRightSibling(hRoot), nLevel - 1);
  }

  std::cout << std::endl;
  for (int i = 0; i < nLevel - 1; ++i) std::cout << "  ";  // 使用两个空格来缩进

  if (nLevel > 1) {
    std::cout << "    |";
  } else {
    std::cout << "----";
  }

  ElemType tElem;
  GetElem(hRoot, tElem);
  std::cout << " " << tElem;

  for (NodeHandle hChild = GetFirstChild(hRoot); !NodeIsEmpty(hChild);
       hChild = GetRightSibling(hChild)) {
    DisplayTreeStructureAux(hChild, nLevel + 1);
  }
}

template <class ElemType, class NodeHandle>
void TreeBase<ElemType, NodeHandle>::DisplayTreeStructure() {
  DisplayTreeStructureAux(GetRoot(), 1);
  std::cout << std::endl;
}

#endif  // _TREE_BASE_H_