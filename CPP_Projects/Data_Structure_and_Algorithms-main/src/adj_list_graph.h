#ifndef ADJ_LIST_GRAPH_H_
#define ADJ_LIST_GRAPH_H_
#include "adj_list_graph_node.h"
#include "graph_base.h"

// 邻接表实现的图类，继承自GraphBase基类
template <class ElemType, class WeightType>
class AdjListGraph
    : public GraphBase<ElemType, AdjListGraphNode<ElemType, WeightType>,
                       WeightType> {
 public:
  // 构造函数，根据节点数组、节点数和图类型构造图
  AdjListGraph(ElemType* arrElems, int nNodeCount, GRAPH_TYPE eType);
  // 析构函数
  ~AdjListGraph();
  // 获取指定节点的第一个邻接节点
  virtual int FirstAdjNode(int nNode, WeightType& tWeight) const;
  // 获取指定节点的下一个邻接节点
  virtual int NextAdjNode(int nNode1, int nNode2, WeightType& tWeight) const;
  // 在两个节点之间插入一条边
  virtual void InsertEdge(int nNode1, int nNode2, WeightType tWeight);
  // 删除两个节点之间的边
  virtual void DeleteEdge(int nNode1, int nNode2);
  // 拷贝构造函数
  AdjListGraph(const AdjListGraph<ElemType, WeightType>& algSrc);

 private:
  // 获取节点的数据元素
  virtual void GetNodeElem(
      const AdjListGraphNode<ElemType, WeightType>& algnNode,
      ElemType& tElem) const;
  // 设置节点的数据元素
  virtual void SetNodeElem(AdjListGraphNode<ElemType, WeightType>& algnNode,
                           const ElemType& tElem);
};

// 构造函数实现
template <class ElemType, class WeightType>
AdjListGraph<ElemType, WeightType>::AdjListGraph(ElemType* arrElems,
                                                 int nNodeCount,
                                                 GRAPH_TYPE eType)
    : GraphBase<ElemType, AdjListGraphNode<ElemType, WeightType>, WeightType>(
          nNodeCount, eType) {
  // 初始化所有节点的数据元素
  for (int i = 0; i < nNodeCount; ++i)
    this->SetElem(i, arrElems[i]);
}

// 析构函数实现
template <class ElemType, class WeightType>
AdjListGraph<ElemType, WeightType>::~AdjListGraph() {}

// 拷贝构造函数实现
template <class ElemType, class WeightType>
AdjListGraph<ElemType, WeightType>::AdjListGraph(
    const AdjListGraph<ElemType, WeightType>& algSrc) {
  // 避免自我赋值
  if (&algSrc != this) {
    *this = algSrc;
  }
}

// 获取节点数据元素实现
template <class ElemType, class WeightType>
void AdjListGraph<ElemType, WeightType>::GetNodeElem(
    const AdjListGraphNode<ElemType, WeightType>& algnNode,
    ElemType& tElem) const {
  tElem = algnNode.m_tElem;
}

// 设置节点数据元素实现
template <class ElemType, class WeightType>
void AdjListGraph<ElemType, WeightType>::SetNodeElem(
    AdjListGraphNode<ElemType, WeightType>& algnNode, const ElemType& tElem) {
  algnNode.m_tElem = tElem;
}

// 插入边实现
template <class ElemType, class WeightType>
void AdjListGraph<ElemType, WeightType>::InsertEdge(int nNode1, int nNode2,
                                                    WeightType tWeight) {
  // 检查节点索引是否合法
  if (nNode1 < 0 || nNode1 >= this->m_nNodeCount || nNode2 < 0 ||
      nNode2 >= this->m_nNodeCount) {
    return;
  }

  // 如果是无权图，边的权重设为 1
  if (this->m_eType == UNDIR_GRAPH || this->m_eType == DIR_GRAPH) {
    tWeight = 1;
  }

  // 根据图的类型（有向/无向）插入边
  if (this->m_eType == UNDIR_GRAPH || this->m_eType == UNDIR_NETWORK) {
    // 无向图需要在两个方向都插入边
    if (this->m_arrNode[nNode1].InsertEdge(nNode2, tWeight) &&
        this->m_arrNode[nNode2].InsertEdge(nNode1, tWeight)) {
      ++(this->m_nEdgeCount);
    }
  } else {
    // 有向图只需要插入一条边
    if (this->m_arrNode[nNode1].InsertEdge(nNode2, tWeight)) {
      ++(this->m_nEdgeCount);
    }
  }
}

// 删除边实现
template <class ElemType, class WeightType>
void AdjListGraph<ElemType, WeightType>::DeleteEdge(int nNode1, int nNode2) {
  // 检查节点索引是否合法
  if (nNode1 < 0 || nNode1 >= this->m_nNodeCount || nNode2 < 0 ||
      nNode2 >= this->m_nNodeCount)
    return;

  // 根据图的类型（有向/无向）删除边
  if (this->m_eType == UNDIR_GRAPH || this->m_eType == UNDIR_NETWORK) {
    // 无向图需要删除两个方向的边
    if (this->m_arrNode[nNode1].DeleteEdge(nNode2) &&
        this->m_arrNode[nNode2].DeleteEdge(nNode1)) {
      --this->m_nEdgeCount;
    }
  } else {
    // 有向图只需要删除一条边
    if (this->m_arrNode[nNode1].DeleteEdge(nNode2)) {
      --this->m_nEdgeCount;
    }
  }
}

// 获取第一个邻接节点实现
template <class ElemType, class WeightType>
int AdjListGraph<ElemType, WeightType>::FirstAdjNode(
    int nNode, WeightType& tWeight) const {
  // 检查节点索引是否合法，不合法返回-1
  return (nNode < 0 || nNode >= this->m_nNodeCount)
             ? -1
             : this->m_arrNode[nNode].FirstEdge(tWeight);
}

// 获取下一个邻接节点实现
template <class ElemType, class WeightType>
int AdjListGraph<ElemType, WeightType>::NextAdjNode(int nNode1, int nNode2,
                                                    WeightType& tWeight) const {
  // 检查节点索引是否合法，不合法返回-1
  return nNode1 < 0 || nNode1 >= this->m_nNodeCount || nNode2 < 0 ||
                 nNode2 >= this->m_nNodeCount || nNode1 == nNode2
             ? -1
             : this->m_arrNode[nNode1].NextEdge(nNode2, tWeight);
}

#endif  // ADJ_LIST_GRAPH_H_