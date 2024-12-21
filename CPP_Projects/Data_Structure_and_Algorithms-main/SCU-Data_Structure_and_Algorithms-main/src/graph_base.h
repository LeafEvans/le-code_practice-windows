#ifndef GRAPH_BASE_H_
#define GRAPH_BASE_H_
#include "find_union_set.h"
#include "lk_queue.h"
#include "lk_stack.h"
#include "min_priority_heap_queue.h"
#include "sq_list.h"
#include "triple.h"

template <class WeightType>
struct GraphEdge {
  int nNode1;            // 边的起点
  int nNode2;            // 边的终点
  WeightType m_tWeight;  // 边的权重

  // 重载小于运算符，用于比较边的权重
  bool operator<(const GraphEdge<WeightType>& geSrc) const {
    return m_tWeight < geSrc.m_tWeight;
  }

  // 重载小于等于运算符，用于比较边的权重
  bool operator<=(const GraphEdge<WeightType>& geSrc) const {
    return m_tWeight <= geSrc.m_tWeight;
  }

  // 重载大于运算符，用于比较边的权重
  bool operator>(const GraphEdge<WeightType>& geSrc) const {
    return m_tWeight > geSrc.m_tWeight;
  }

  // 重载大于等于运算符，用于比较边的权重
  bool operator>=(const GraphEdge<WeightType>& geSrc) const {
    return m_tWeight >= geSrc.m_tWeight;
  }
};

enum GRAPH_TYPE {
  UNDIR_GRAPH,    // 无向图
  DIR_GRAPH,      // 有向图
  UNDIR_NETWORK,  // 无向网
  DIR_NETWORK     // 有向网
};

template <class ElemType, class NodeType, class WeightType>
class GraphBase {
 public:
  GraphBase(ElemType* arrElems, int nNodeCount, GRAPH_TYPE eType);
  ~GraphBase();
  // 返回顶点 nNode 的第一个邻接点，并获得该边的权重
  virtual int FirstAdjNode(int nNode, WeightType& tWeight) const = 0;
  // 返回顶点 nNode1 的相对于 nNode2 的下一个邻接点，并获得该边权重
  virtual int NextAdjNode(int nNode1, int nNode2,
                          WeightType& tWeight) const = 0;
  // 插入顶点为v1和v2,权为weight的边
  virtual void InsertEdge(int nNode1, int nNode2,
                          const WeightType& tWeight) = 0;
  virtual void DeleteEdge(int nNode1, int nNode2) = 0;  // 删除边
  virtual WeightType InfniteWeight();                   // 边的无穷大权值
  bool GetTag(int nNode) const;                         // 得到点标志
  void SetTag(int nNode, bool bTag);                    // 设置点标志
  int NodeCount() const;                                // 返回顶点个数
  int EdgeCount() const;                                // 返回边数个数
  void DfsTraverse(void (*pVisit)(const ElemType& tElem)) const;  // 深度优先
  void BfsTraverse(void (*pVisit)(const ElemType&)) const;  // 广度优先
  bool GetElem(int nNode, ElemType& tElem) const;           // 得到节点
  bool SetElem(int nNode, const ElemType& tElem);           // 设置节点
  bool Prim();     // 用普里姆算法求最小生成树
  bool Kruskal();  // 用克鲁斯卡尔算法求最小生成树
  GraphEdge<WeightType>* GetMstEdge(int& nMstEdgeSize) const;  // 输出最小生成树
  bool TopSort(SqList<int>& slSortedNode) const;               // 拓扑排序
  // 求网的关键路径
  bool CriticalPath(SqList<GraphEdge<WeightType>>& sqCritalPathEdge) const;
  // 用迪杰斯拉特算法求最短路径
  bool Dijkstra(int start, WeightType D[], int Pre[], int nBufSize);
  GraphBase<ElemType, NodeType, WeightType>& operator=(
      const GraphBase<ElemType, NodeType, WeightType>& gbSrc);
  // 依照边序列插入多条边
  int InsertEdges(const GraphEdge<WeightType>* arrEdges, int nEdgeCount);

 protected:
  //  深度优先
  void DfsAux(int nNode, void (*pVisit)(const ElemType&)) const;
  // 广度优先
  void BfsAux(int nNode, void (*pVisit)(const ElemType&)) const;
  //根据节点类型获取原子数据
  virtual void GetNodeElem(const NodeType& tNode, ElemType& tElem) const = 0;
  //把原子数据存入到节点类型数据中
  virtual void SetNodeElem(NodeType& tNode, const ElemType& tElem) = 0;
  void ClearTag();
  void Reserve(int nNodeSize);
  void StatInDegree(int* arrInDegree) const;
  NodeType* m_arrNodes;                  // 节点表
  bool* m_arrVistedTags;                 // 节点访问标志表
  GraphEdge<WeightType>* m_arrMstEdges;  // 最小生成树的边集
  int m_nNodeCount;                      // 顶点数量
  int m_nEdgeCount;                      // 边集
  int m_nMstEdgeCount;                   // 最小生成树的边数
  GRAPH_TYPE m_eType;                    // 类型
};

// 构造函数
template <class ElemType, class NodeType, class WeightType>
GraphBase<ElemType, NodeType, WeightType>::GraphBase(ElemType* arrElems,
                                                     int nNodeCount,
                                                     GRAPH_TYPE eType)
    : m_arrNodes(new NodeType[nNodeCount]),
      m_arrVistedTags(new bool[nNodeCount]),
      m_arrMstEdges(NULL),
      m_nNodeCount(nNodeCount),
      m_nEdgeCount(0),
      m_nMstEdgeCount(0),
      m_eType(eType) {
  // 初始化节点表和访问标志表
  for (int i = 0; i < nNodeCount; ++i) {
    SetElem(i, arrElems[i]);
    m_arrVistedTags[i] = false;
  }
}

// 析构函数
template <class ElemType, class NodeType, class WeightType>
GraphBase<ElemType, NodeType, WeightType>::~GraphBase() {
  if (m_arrNodes) {
    delete[] m_arrNodes;
    m_arrNodes = NULL;
  }

  if (m_arrVistedTags) {
    delete[] m_arrVistedTags;
    m_arrVistedTags = NULL;
  }

  if (m_arrMstEdges) {
    delete[] m_arrMstEdges;
    m_arrMstEdges = NULL;
  }

  m_nNodeCount = 0;
  m_nEdgeCount = 0;
  m_nMstEdgeCount = 0;
}

// 重新分配图的节点表和访问标志表的大小
template <class ElemType, class NodeType, class WeightType>
void GraphBase<ElemType, NodeType, WeightType>::Reserve(int nNodeCount) {
  if (m_arrNodes) {
    delete[] m_arrNodes;  // 删除旧的节点表
  }

  if (m_arrVistedTags) {
    delete[] m_arrVistedTags;  // 删除旧的访问标志表
  }

  if (m_arrMstEdges) {
    delete[] m_arrMstEdges;  // 删除旧的最小生成树边集
    m_arrMstEdges = NULL;
  }

  m_arrNodes = new NodeType[nNodeCount];   // 分配新的节点表
  m_arrVistedTags = new bool[nNodeCount];  // 分配新的访问标志表
  // 初始化访问标志表为 false
  std::fill_n(m_arrVistedTags, nNodeCount, false);
  m_nNodeCount = nNodeCount;  // 更新节点数量
  m_nEdgeCount = 0;           // 重置边数量
  m_nMstEdgeCount = 0;        // 重置最小生成树边数量
}

// 插入多条边
template <class ElemType, class NodeType, class WeightType>
int GraphBase<ElemType, NodeType, WeightType>::InsertEdges(
    const GraphEdge<WeightType>* arrEdges, int nEdgeCount) {
  for (int i = 0; i < nEdgeCount; ++i)
    InsertEdge(arrEdges[i].nNode1, arrEdges[i].nNode2,
               arrEdges[i].m_tWeight);  // 插入每一条边
  return m_nEdgeCount;                  // 返回当前边的数量
}

template <class ElemType, class NodeType, class WeightType>
bool GraphBase<ElemType, NodeType, WeightType>::GetElem(int nNode,
                                                        ElemType& tElem) const {
  // 检查节点索引是否越界或节点表是否为空
  if (nNode < 0 || nNode >= m_nNodeCount || !m_arrNodes)
    return false;
  // 从节点表中获取指定节点的元素值
  GetNodeElem(m_arrNodes[nNode], tElem);
  return true;
}

template <class ElemType, class NodeType, class WeightType>
bool GraphBase<ElemType, NodeType, WeightType>::SetElem(int nNode,
                                                        const ElemType& tElem) {
  // 检查节点索引是否越界或节点表是否为空
  if (nNode < 0 || nNode >= m_nNodeCount || !m_arrNodes)
    return false;
  // 设置指定节点的元素值
  SetNodeElem(m_arrNodes[nNode], tElem);
  return true;
}

template <class ElemType, class NodeType, class WeightType>
void GraphBase<ElemType, NodeType, WeightType>::ClearTag() {
  // 如果访问标志数组为空,直接返回
  if (!m_arrVistedTags)
    return;
  // 使用 std::fill_n 将访问标志数组中所有元素重置为 false
  std::fill_n(m_arrVistedTags, m_nNodeCount, false);
}

template <class ElemType, class NodeType, class WeightType>
void GraphBase<ElemType, NodeType, WeightType>::DfsAux(
    int nNode, void (*pVisit)(const ElemType&)) const {
  SetTag(nNode, true);    // 设置访问标志
  ElemType tElem;         // 临时变量
  GetElem(nNode, tElem);  // 取顶点 nNode 的元素
  (*pVisit)(tElem);       // 访问顶点
}

#endif  // GRAPH_BASE_H_