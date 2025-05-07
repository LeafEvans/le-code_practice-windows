#ifndef INC_ADJ_LIST_GRAPH_NODE_H_
#define INC_ADJ_LIST_GRAPH_NODE_H_
#include "simple_lk_list.h"

// 图的边结构体，包含目标节点编号和边的权重
template <class WeightType>
struct AdjListGraphEdge {
  int m_nNode;           // 目标节点编号
  WeightType m_tWeight;  // 边的权重
};

// 图的节点类，包含节点数据和邻接表
template <class ElemType, class WeightType>
class AdjListGraphNode {
 public:
  AdjListGraphNode();   // 构造函数
  ~AdjListGraphNode();  // 析构函数

  // 边操作相关方法
  bool InsertEdge(int nNode, WeightType tWeight);  // 插入一条边
  bool DeleteEdge(int nNode);                      // 删除一条边
  int FirstEdge(WeightType& tWeight) const;        // 获取第一条边的目标节点
  int NextEdge(int nPreNode,
               WeightType& tWeight) const;  // 获取指定节点的下一条边的目标节点

  // 赋值运算符重载
  AdjListGraphNode<ElemType, WeightType>& operator=(
      const AdjListGraphNode<ElemType, WeightType> algnSrc);

  ElemType m_tElem;                 // 节点数据
  SimpleLkList<ElemType> m_sllAdj;  // 邻接表
};

template <class ElemType, class WeightType>
AdjListGraphNode<ElemType, WeightType>::AdjListGraphNode() {}

template <class ElemType, class WeightType>
AdjListGraphNode<ElemType, WeightType>::~AdjListGraphNode() {}

// 赋值运算符实现
template <class ElemType, class WeightType>
AdjListGraphNode<ElemType, WeightType>&
AdjListGraphNode<ElemType, WeightType>::operator=(
    const AdjListGraphNode<ElemType, WeightType> algnSrc) {
  m_tElem = algnSrc.m_tElem;    // 复制节点数据
  m_sllAdj = algnSrc.m_sllAdj;  // 复制邻接表
}

// 插入一条边
template <class ElemType, class WeightType>
bool AdjListGraphNode<ElemType, WeightType>::InsertEdge(int nNode,
                                                        WeightType tWeight) {
  SimpleLkList<AdjListGraphEdge<WeightType>>* psllAdj = &m_sllAdj;
  psllAdj->Head();
  AdjListGraphEdge<WeightType> algeElem;

  while (psllAdj->Next(algeElem)) {
    if (algeElem.m_nNode == nNode) {
      return false;
    }
  }

  algeElem.m_nNode = nNode;
  algeElem.m_tWeight = tWeight;
  psllAdj->AddTail(algeElem);
  return true;
}

// 删除一条边
template <class ElemType, class WeightType>
bool AdjListGraphNode<ElemType, WeightType>::DeleteEdge(int nNode) {
  SimpleLkList<AdjListGraphEdge<WeightType>>*psllAdj = &m_sllAdj;
  psllAdj->Head();
  AdjListGraphEdge<WeightType> algeElem;

  while (psllAdj->Next(algeElem)) {
    if (algeElem.m_nNode == nNode) {
      psllAdj->DeleteCurr(algeElem);
      return true;
    }
  }

  return false;
}

// 获取第一条边的目标节点
template <class ElemType, class WeightType>
int AdjListGraphNode<ElemType, WeightType>::FirstEdge(
    WeightType& tWeight) const {
  SimpleLkList<AdjListGraphEdge<WeightType>>* psllAdj = &m_sllAdj;
  if (psllAdj->IsEmpty())
    return -1;  // 邻接表为空

  psllAdj->Head();
  AdjListGraphEdge<WeightType> algeElem;

  if (!psllAdj->Next(algeElem))
    return -1;  // 获取首条边失败

  tWeight = algeElem.m_tWeight;
  return algeElem.nNode;  // 返回首条边的目标节点
}

// 获取指定节点的下一条边的目标节点
template <class ElemType, class WeightType>
int AdjListGraphNode<ElemType, WeightType>::NextEdge(
    int nPreNode, WeightType& tWeight) const {
  SimpleLkList<AdjListGraphEdge<WeightType>>* psllAdj = &m_sllAdj;
  if (psllAdj->IsEmpty()) {
    return -1;  // 邻接表为空
  }

  AdjListGraphEdge<WeightType> algeElem;

  // 处理连续调用的情况：当前位置正好是目标节点
  if (psllAdj->GetCurrElem(algeElem) && nPreNode == algeElem.m_nNode) {
    if (psllAdj->Next(algeElem)) {
      tWeight = algeElem.m_tWeight;
      return algeElem.m_nNode;
    }
    return -1;  // 无后继边
  }

  // 从头查找目标节点的下一条边
  psllAdj->Head();
  while (psllAdj->Next(algeElem)) {
    if (algeElem.m_nNode == nPreNode) {
      if (psllAdj->Next(algeElem)) {
        tWeight = algeElem.m_tWeight;
        return algeElem.m_nNode;
      }
      break;  // 目标节点是最后一个节点
    }
  }

  return -1;  // 未找到目标节点或无后继边
}
#endif  // INC_ADJ_LIST_GRAPH_NODE_H_