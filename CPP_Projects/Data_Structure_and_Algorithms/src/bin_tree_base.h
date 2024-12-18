#ifndef BIN_TREE_BASE_H_
#define BIN_TREE_BASE_H_
#include <algorithm>
#include <cstddef>
#include <iostream>

#include "lk_queue.h"

using namespace std;

template <class ElemType, class NodeHandle>
class BinTreeBase {
 public:
  BinTreeBase();                                         // 构造函数
  virtual ~BinTreeBase();                                // 析构函数
  virtual NodeHandle GetRoot() const = 0;                // 获取根节点
  virtual bool NodeIsEmpty(NodeHandle hNode) const = 0;  // 判断节点是否为空

  // 获取节点的元素值
  virtual bool GetElem(NodeHandle hNode, ElemType& tElem) const = 0;
  // 设置节点的元素值
  virtual bool SetElem(NodeHandle hNode, const ElemType& tElem) = 0;
  virtual bool IsEmpty() const = 0;  // 判断二叉树是否为空

  // 获取左孩子节点
  virtual NodeHandle& GetLeftChild(NodeHandle hNode) const = 0;
  // 获取右孩子节点
  virtual NodeHandle& GetRightChild(NodeHandle hNode) const = 0;
  virtual NodeHandle GetParent(NodeHandle hNode) const = 0;  // 获取双亲节点
  virtual bool CreateBinTree(ElemType arrPreOrder[], ElemType arrInOrder[],
                             int nSize);  // 根据前序和中序序列创建二叉树
  // 插入左孩子
  virtual void InsertLeftChild(NodeHandle hNode, const ElemType& tElem);
  // 插入右孩子
  virtual void InsertRightChild(NodeHandle hNode, const ElemType& tElem);
  virtual void InOrder(void (*pVisit)(const ElemType&)) const;   // 中序遍历
  virtual void PreOrder(void (*pVisit)(const ElemType&)) const;  // 前序遍历
  virtual void PostOrder(void (*pVisit)(const ElemType&)) const;  // 后序遍历
  virtual void LevelOrder(void (*pVisit)(const ElemType&)) const;  // 层次遍历
  virtual int NodeCount() const;                    // 获取节点总数
  virtual void DeleteLeftChild(NodeHandle hNode);   // 删除左子树
  virtual void DeleteRightChild(NodeHandle hNode);  // 删除右子树
  virtual int Height() const;                       // 获取树的高度
  void DisplayTreeStructure();  // 以树形结构显示二叉树

 protected:
  int NodeCountsAux(NodeHandle hRoot) const;  // 辅助函数：获取节点总数
  virtual void DestroyAux(NodeHandle& hRoot);  // 辅助函数：销毁节点
  void PreOrderAux(
      NodeHandle hRoot,
      void (*pVisit)(const ElemType&)) const;  // 辅助函数：前序遍历
  void InOrderAux(NodeHandle hRoot,
                  void (*pVisit)(const ElemType&)) const;  // 辅助函数：中序遍历
  void PostOrderAux(
      NodeHandle hRoot,
      void (*pVisit)(const ElemType&)) const;  // 辅助函数：后序遍历
  int HeightAux(NodeHandle hRoot) const;  // 辅助函数：获取树的高度
  // 辅助函数：创建二叉树
  NodeHandle CreateBinTreeAux(NodeHandle hParent, ElemType* arrPre,
                              ElemType* arrIn, int nPreLeft, int nPreRight,
                              int nInLeft, int nInRight, bool bLeft);
  // 辅助函数：显示二叉树结构
  void DisplayTreeStructureAux(NodeHandle hRoot, int nLevel);
  virtual ElemType GetNode(NodeHandle hNode) const = 0;  // 获取节点元素值
  virtual void ReleaseNode(NodeHandle& hNode) = 0;       // 释放节点
  virtual NodeHandle CreateChildNode(NodeHandle hNode,
                                     bool bLeft) = 0;  // 创建子节点
};

template <class ElemType, class NodeHandle>
BinTreeBase<ElemType, NodeHandle>::BinTreeBase() {}

template <class ElemType, class NodeHandle>
BinTreeBase<ElemType, NodeHandle>::~BinTreeBase() {}

template <class ElemType, class NodeHandle>
void BinTreeBase<ElemType, NodeHandle>::PreOrder(  // 前序遍历
    void (*pVisit)(const ElemType&)) const {
  PreOrderAux(GetRoot(), pVisit);  // 从根节点开始遍历
}

template <class ElemType, class NodeHandle>
void BinTreeBase<ElemType, NodeHandle>::InsertLeftChild(NodeHandle hNode,
                                                        const ElemType& tElem) {
  if (NodeIsEmpty(hNode) || !NodeIsEmpty(GetLeftChild(hNode))) {
    return;  // 节点为空或左节点不为空
  }

  NodeHandle pLeftChild = CreateChildNode(hNode, true);  // 新建左节点
  // 创建新节点成功，设置其值
  if (!NodeIsEmpty(pLeftChild))
    SetElem(pLeftChild, tElem);
}

template <class ElemType, class NodeHandle>
void BinTreeBase<ElemType, NodeHandle>::InsertRightChild(
    NodeHandle hNode, const ElemType& tElem) {
  if (NodeIsEmpty(hNode) || !NodeIsEmpty(GetRightChild(hNode))) {
    return;  // 节点为空或右节点不为空
  }

  NodeHandle pRightChild = CreateChildNode(hNode, false);  // 新建右节点
  // 创建新节点成功，设置其值
  if (!NodeIsEmpty(pRightChild))
    SetElem(pRightChild, tElem);
}

template <class ElemType, class NodeHandle>
void BinTreeBase<ElemType, NodeHandle>::InOrder(  // 中序遍历
    void (*pVisit)(const ElemType&)) const {
  InOrderAux(GetRoot(), pVisit);  // 从根节点开始遍历
}

template <class ElemType, class NodeHandle>
void BinTreeBase<ElemType, NodeHandle>::PostOrder(  // 后序遍历
    void (*pVisit)(const ElemType&)) const {
  PostOrderAux(GetRoot(), pVisit);  // 从根节点开始遍历
}

template <typename ElemType, class NodeHandle>
void BinTreeBase<ElemType, NodeHandle>::LevelOrder(
    void (*pVisit)(const ElemType&)) const {
  LkQueue<ElemType> lqNodes;     // 存放节点的队列
  NodeHandle hNode = GetRoot();  // 获取根节点
  // 判断根节点是否为空，不为空则入队
  if (!NodeIsEmpty(hNode))
    lqNodes.InQueue(hNode);
  while (!lqNodes.IsEmpty()) {  // 队列不空则循环
    lqNodes.OutQueue(hNode);    // 先出队访问元素
    (*pVisit)(GetNode(hNode));
    // 入队该节点的左孩子
    if (!NodeIsEmpty(GetLeftChild(hNode))) {
      lqNodes.InQueue(GetLeftChild(hNode));
    }
    // 入队该节点的右孩子
    if (!NodeIsEmpty(GetRightChild(hNode))) {
      lqNodes.InQueue(GetRightChild(hNode));
    }
  }
}

template <class ElemType, class NodeHandle>
int BinTreeBase<ElemType, NodeHandle>::NodeCount() const {
  return NodeCountsAux(GetRoot());
}

template <class ElemType, class NodeHandle>
void BinTreeBase<ElemType, NodeHandle>::DeleteLeftChild(NodeHandle hNode) {
  if (NodeIsEmpty(hNode))
    return;  // 节点为空
  DestroyAux(GetLeftChild(hNode));
}

template <class ElemType, class NodeHandle>
void BinTreeBase<ElemType, NodeHandle>::DeleteRightChild(NodeHandle hNode) {
  if (NodeIsEmpty(hNode))
    return;  // 节点为空
  DestroyAux(GetRightChild(hNode));
}

template <class ElemType, class NodeHandle>
int BinTreeBase<ElemType, NodeHandle>::Height() const {
  return HeightAux(GetRoot());  // 从根节点开始计算树的高度
}

template <class ElemType, class NodeHandle>
void BinTreeBase<ElemType, NodeHandle>::DisplayTreeStructure() {
  DisplayTreeStructureAux(GetRoot(), 1);  // 展示二叉树
  std::cout << std::endl;
}

template <class ElemType, class NodeHandle>
int BinTreeBase<ElemType, NodeHandle>::NodeCountsAux(NodeHandle hRoot) const {
  if (NodeIsEmpty(hRoot))
    return 0;  // 空节点个数为 0
  return 1 + NodeCountsAux(GetLeftChild(hRoot)) +
         NodeCountsAux(GetRightChild(hRoot));
}

template <class ElemType, class NodeHandle>
void BinTreeBase<ElemType, NodeHandle>::DestroyAux(NodeHandle& hRoot) {
  if (NodeIsEmpty(hRoot))
    return;                          // 节点为空
  DestroyAux(GetLeftChild(hRoot));   // 销毁左子树
  DestroyAux(GetRightChild(hRoot));  // 销毁右子树
  ReleaseNode(hRoot);                // 释放节点
}

template <class ElemType, class NodeHandle>
void BinTreeBase<ElemType, NodeHandle>::PreOrderAux(  // 前序遍历辅助函数
    NodeHandle hRoot, void (*pVisit)(const ElemType&)) const {
  if (NodeIsEmpty(hRoot))
    return;                                   // 节点为空
  (*pVisit(GetNode(hRoot)));                  // 访问根节点
  PreOrderAux(GetLeftChild(hRoot), pVisit);   // 访问左子树
  PreOrderAux(GetRightChild(hRoot), pVisit);  // 访问右子树
}

template <class ElemType, class NodeHandle>
void BinTreeBase<ElemType, NodeHandle>::InOrderAux(  // 中序遍历辅助函数
    NodeHandle hRoot, void (*pVisit)(const ElemType&)) const {
  if (NodeIsEmpty(hRoot))
    return;                                  // 节点为空
  InOrderAux(GetLeftChild(hRoot), pVisit);   // 访问左子树
  (*pVisit(GetNode(hRoot)));                 // 访问根节点
  InOrderAux(GetRightChild(hRoot), pVisit);  // 访问右子树
}

template <class ElemType, class NodeHandle>
void BinTreeBase<ElemType, NodeHandle>::PostOrderAux(  // 后序遍历辅助函数
    NodeHandle hRoot, void (*pVisit)(const ElemType&)) const {
  if (NodeIsEmpty(hRoot))
    return;                                    // 节点为空
  PostOrderAux(GetLeftChild(hRoot), pVisit);   // 访问左子树
  PostOrderAux(GetRightChild(hRoot), pVisit);  // 访问右子树
  (*pVisit(PostElem(hRoot)));                  // 访问根节点
}

template <class ElemType, class NodeHandle>
int BinTreeBase<ElemType, NodeHandle>::HeightAux(NodeHandle hRoot) const {
  if (NodeIsEmpty(hRoot))
    return 0;  // 空二叉树高度为 0

  int nLeftHeight = HeightAux(GetLeftChild(hRoot));    // 左子树的高度
  int nRightHeight = HeightAux(GetRightChild(hRoot));  // 右子树的高度
  // 非空二叉树高度为左右子树的高度的最大值再加一
  return 1 + std::max(nLeftHeight, nRightHeight);
}

template <class ElemType, class NodeHandle>
NodeHandle BinTreeBase<ElemType, NodeHandle>::CreateBinTreeAux(
    NodeHandle hParent, ElemType* arrPre, ElemType* arrIn, int nPreLeft,
    int nPreRight, int nInLeft, int nInRight, bool bLeaf) {
  // 非法数据范围
  if (nInLeft > nInRight || nPreLeft > nPreRight)
    return NULL;

  // 创建根节点
  NodeHandle hRoot = CreateChildNode(hParent, bLeaf);
  SetElem(hRoot, arrPre[nPreLeft]);  // 设置根节点的元素

  // 寻找中序序列根节点的索引
  int nInRoot =
      std::find(arrIn + nInLeft, arrIn + nInRight + 1, arrPre[nPreLeft]);

  int nLeftSize = nInRoot - nInLeft;  // 左子树的大小

  CreateBinTreeAux(hRoot, arrPre, arrIn, nPreLeft + 1, nPreRight + nLeftSize,
                   nInLeft, nInRoot - 1, true);
  CreateBinTreeAux(hRoot, arrPre, arrIn, nPreLeft + nLeftSize + 1, nPreRight,
                   nInRoot + 1, nInRight, false);

  return hRoot;
}

template <class ElemType, class NodeHandle>
void BinTreeBase<ElemType, NodeHandle>::DisplayTreeStructureAux(
    NodeHandle hRoot, int nLevel) {
  if (NodeIsEmpty(hRoot))
    return;

  DisplayTreeStructureAux(GetRightChild(hRoot), nLevel + 1);  // 显示右子树

  std::cout << std::endl;
  for (int i = 0; i < nLevel * 2; ++i)
    std::cout << ' ';  // 打印缩进

  if (nLevel > 1) {
    std::cout << "    |";
  } else {
    std::cout << "----";
  }

  std::cout << " " << hRoot->m_tElem;  // 打印节点元素

  DisplayTreeStructureAux(GetLeftChild(hRoot), nLevel + 1);  // 显示左子树
}
#endif  // BIN_TREE_BASE_H_