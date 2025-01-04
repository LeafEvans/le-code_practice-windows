#ifndef INC_ADJ_MATRIX_GRAPH_H_
#define INC_ADJ_MATRIX_GRAPH_H_
#include "graph_base.h"
#include "lk_stack.h"
#include "matrix.h"

template <class ElemType, class WeightType>
class AdjMatrixGraph : public GraphBase<ElemType, ElemType, WeightType> {
 public:
  AdjMatrixGraph(ElemType* arrNode, int nNodeCount, GRAPH_TYPE eType);
  ~AdjMatrixGraph();
  virtual int FirstAdjNode(int nNode, WeightType& tWeight) const;
  virtual int NextAdjNode(int nNode1, int nNode2, WeightType& tWeight) const;
  virtual void InsertEdge(int nNode1, int nNode2, WeightType tWeight = 1);
  virtual void DeleteEdge(int nNode1, int nNode2);
  AdjMatrixGraph(const AdjMatrixGraph<ElemType, WeightType>& amgSrc);
  AdjMatrixGraph<ElemType, WeightType>& operator=(
      const AdjMatrixGraph<ElemType, WeightType>& amgSrc);
  bool Floyd(Matrix<WeightType>& mtxPathLen, Matrix<int>& mtxPreNode) const;
  bool PrintFloyd(Matrix<WeightType>& mtxPathLen,
                  Matrix<int>& mtxPreNode) const;

 private:
  virtual void GetNodeElem(const ElemType& tNode, ElemType& tElem) const;
  virtual void SetNodeElem(ElemType& tNode, const ElemType& tElem);
  WeightType m_tNoEdgeWeight;    // 无边的权值
  Matrix<WeightType> m_mtxEdge;  // 边矩阵
};

template <class ElemType, class WeightType>
AdjMatrixGraph<ElemType, WeightType>::AdjMatrixGraph(ElemType* arrNode,
                                                     int nNodeCount,
                                                     GRAPH_TYPE eType)
    : GraphBase<ElemType, ElemType, WeightType>(nNodeCount, eType),
      m_tNoEdgeWeight((eType == DIR_NETWORK || eType == UNDIR_NETWORK)
                          ? 0
                          : this->InfniteWeight()),
      m_mtxEdge(nNodeCount, nNodeCount) {
  for (int i = 0; i < nNodeCount; ++i) {
    this->SetElem(i, arrNode[i]);
  }

  for (int i = 0; i < nNodeCount; ++i) {
    for (int j = 0; j < nNodeCount; ++j) {
      m_mtxEdge(i, j) = m_tNoEdgeWeight;
    }
  }
}

template <class ElemType, class WeightType>
AdjMatrixGraph<ElemType, WeightType>::~AdjMatrixGraph() {}

template <class ElemType, class WeightType>
AdjMatrixGraph<ElemType, WeightType>::AdjMatrixGraph(
    const AdjMatrixGraph<ElemType, WeightType>& amgSrc) {
  if (&amgSrc != this) {
    GraphBase<ElemType, ElemType, WeightType>::operator=(amgSrc);
    m_tNoEdgeWeight = amgSrc.m_tNoEdgeWeight;
    m_mtxEdge = amgSrc.m_mtxEdge;
  }
}

template <class ElemType, class WeightType>
AdjMatrixGraph<ElemType, WeightType>&
AdjMatrixGraph<ElemType, WeightType>::operator=(
    const AdjMatrixGraph<ElemType, WeightType>& amgSrc) {
  if (&amgSrc != this) {
    GraphBase<ElemType, ElemType, WeightType>::operator=(amgSrc);
    m_tNoEdgeWeight = amgSrc.m_tNoEdgeWeight;
    m_mtxEdge = amgSrc.m_mtxEdge;
  }
  return *this;
}

template <class ElemType, class WeightType>
void AdjMatrixGraph<ElemType, WeightType>::GetNodeElem(const ElemType& tNode,
                                                       ElemType& tElem) const {
  tElem = tNode;
}

template <class ElemType, class WeightType>
void AdjMatrixGraph<ElemType, WeightType>::SetNodeElem(ElemType& tNode,
                                                       const ElemType& tElem) {
  tNode = tElem;
}

template <class ElemType, class WeightType>
void AdjMatrixGraph<ElemType, WeightType>::InsertEdge(int nNode1, int nNode2,
                                                      WeightType tWeight) {
  if (nNode1 < 0 || nNode1 >= this->m_nNodeCount || nNode2 < 0 ||
      nNode2 >= this->m_nNodeCount)
    return;

  // 如果是无向图或有向图，权重设为1
  if (this->m_eType == UNDIR_GRAPH || this->m_eType == DIR_GRAPH)
    tWeight = 1;

  if (m_mtxEdge(nNode1, nNode2) == m_tNoEdgeWeight) {
    m_mtxEdge(nNode1, nNode2) = tWeight;
    if (this->m_eType == UNDIR_NETWORK || this->m_eType == UNDIR_GRAPH) {
      // 无向图或有向图，需要对称
      m_mtxEdge(nNode2, nNode1) = tWeight;
    }
    ++(this->m_nEdgeCount);  // 边数加1
  }
}

template <class ElemType, class WeightType>
void AdjMatrixGraph<ElemType, WeightType>::DeleteEdge(int nNode1, int nNode2) {
  // 检查节点索引是否在合法范围内
  if (nNode1 < 0 || nNode1 >= this->m_nNodeCount || nNode2 < 0 ||
      nNode2 >= this->m_nNodeCount)
    return;  // 如果不合法，直接返回

  // 删除边，设置为无边权重
  m_mtxEdge(nNode1, nNode2) = m_tNoEdgeWeight;
  // 如果是无向图或无向网，删除对称边
  if (this->m_eType == UNDIR_NETWORK || this->m_eType == UNDIR_GRAPH)
    m_mtxEdge(nNode2, nNode1) = m_tNoEdgeWeight;

  --(this->m_nEdgeCount);  // 更新边的数量
}

template <class ElemType, class WeightType>
int AdjMatrixGraph<ElemType, WeightType>::FirstAdjNode(
    int nNode, WeightType& tWeight) const {
  // 检查节点索引是否在合法范围内
  if (nNode < 0 || nNode >= this->m_nNodeCount)
    return -1;  // 如果不合法，返回-1

  // 遍历节点的邻接节点
  for (int nAdjNode = 0; nAdjNode < this->m_nNodeCount; ++nAdjNode) {
    if (m_mtxEdge(nNode, nAdjNode) != m_tNoEdgeWeight) {
      tWeight = m_mtxEdge(nNode, nAdjNode);  // 获取边的权重
      return nAdjNode;  // 返回第一个邻接节点的索引
    }
  }

  return -1;  // 如果没有邻接节点，返回-1
}

template <class ElemType, class WeightType>
int AdjMatrixGraph<ElemType, WeightType>::NextAdjNode(
    int nNode1, int nNode2, WeightType& tWeight) const {
  if (nNode1 < 0 || nNode1 >= this->m_nNodeCount || nNode2 < 0 ||
      nNode2 >= this->m_nNodeCount || nNode1 == nNode2) {
    return -1;  // 如果不合法，直接返回
  }

  for (int j = nNode2 + 1; j < this->m_nNodeCount; ++j) {
    if (m_mtxEdge(nNode1, j) != m_tNoEdgeWeight) {
      tWeight = m_mtxEdge(nNode1, j);
      return j;
    }
  }

  return -1;
}

template <class ElemType, class WeightType>
bool AdjMatrixGraph<ElemType, WeightType>::Floyd(
    Matrix<WeightType>& mtxPathLen, Matrix<int>& mtxPreNode) const {
  // 检查图的类型是否为网格图（有向或无向）
  if (this->m_eType != UNDIR_NETWORK && this->m_eType != DIR_NETWORK)
    return false;

  int nNodeCount = this->m_nNodeCount;

  // 调整路径长度矩阵的大小
  if (mtxPathLen.GetCols() != nNodeCount || mtxPathLen.GetRows() != nNodeCount)
    mtxPathLen.Resize(nNodeCount, nNodeCount);

  // 初始化路径长度矩阵的大小
  for (int i = 0; i < nNodeCount; ++i) {
    for (int j = 0; j < nNodeCount; ++j) {
      mtxPathLen(i, j) = (i == j) ? 0 : m_mtxEdge(i, j);
      mtxPreNode(i, j) = (m_mtxEdge(i, j) == m_tNoEdgeWeight ? -1 : i);
    }
  }

  // Floyd 算法核心部分
  // 以 k 为中间节点，更新所有节点对之间的最短路径
  for (int k = 0; k < nNodeCount; ++k) {
    for (int i = 0; i < nNodeCount; ++i) {
      for (int j = 0; j < nNodeCount; ++j) {
        // 如果经过 k 点的路径存在且比原路径短
        if (mtxPathLen(i, k) != m_tNoEdgeWeight &&
            mtxPathLen(k, j) != m_tNoEdgeWeight &&
            mtxPathLen(i, k) + mtxPathLen(k, j) < mtxPathLen(i, j)) {
          // 更新最短路径长度
          mtxPathLen(i, j) = mtxPathLen(i, k) + mtxPathLen(k, j);
          // 更新前驱节点
          mtxPreNode(i, j) = mtxPreNode(k, j);
        }
      }
    }
  }

  return true;
}

template <class ElemType, class WeightType>
bool AdjMatrixGraph<ElemType, WeightType>::PrintFloyd(
    Matrix<WeightType>& mtxPathLen, Matrix<int>& mtxPreNode) const {
  // 检查图类型
  if (this->m_eType != UNDIR_NETWORK && this->m_eType != DIR_NETWORK)
    return false;

  int nNodeCount = this->m_nNodeCount;

  // 遍历所有顶点对
  for (int i = 0; i < nNodeCount; ++i) {
    for (int j = 0; j < nNodeCount; ++j) {
      if (i != j && mtxPathLen(i, j) != m_tNoEdgeWeight) {
        // 获取并打印起点
        ElemType tStartNode;
        this->GetElem(i, tStartNode);
        std::cout << "Path from " << tStartNode << std::endl;

        // 获取并打印终点
        ElemType tEndNode;
        this->GetElem(j, tEndNode);
        std::cout << tEndNode << ": ";

        // 打印路径长度
        std::cout << "Length=" << mtxPathLen(i, j) << ", Path: ";

        // 使用栈存储路径
        LkStack<int> lsPath;
        int nNode = j;  // 从终点开始

        // 重建路径（从终点往回找）
        while (nNode != j) {
          lsPath.Push(nNode);            // 将当前节点压栈
          nNode = mtxPreNode(i, nNode);  // 查找前一个节点
          if (nNode == -1)
            break;
        }
        lsPath.Push(i);  // 最后将起点压栈

        // 打印路径（通过出栈获得正向路径）
        while (!lsPath.IsEmpty()) {
          lsPath.Pop(nNode);
          ElemType tElem;
          this->GetElem(nNode, tElem);
          std::cout << tElem;
          if (lsPath.Length() > 0) {  // 如果不是最后一个节点
            std::cout << "->";
          }
        }
        std::cout << std::endl;
      }
    }
  }
  return true;
}
#endif  // INC_ADJ_MATRIX_GRAPH_H_