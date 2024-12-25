#ifndef GRAPH_BASE_H_
#define GRAPH_BASE_H_
#include <cstddef>
#include <iostream>

#include "find_union_set.h"
#include "lk_queue.h"
#include "lk_stack.h"
#include "min_priority_heap_queue.h"
#include "sq_list.h"

template <class WeightType>
struct GraphEdge {
  int m_nNode1;          // 边的起点
  int m_nNode2;          // 边的终点
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
  GraphBase(int nNodeCount, GRAPH_TYPE eType);
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
  bool GetTag(int nNode) const;                         // 获取顶点标志
  void SetTag(int nNode, bool bTag);                    // 设置顶点标志
  int NodeCount() const;                                // 获取顶点个数
  int EdgeCount() const;                                // 获取边数
  void DfsTraverse(
      void (*pVisit)(const ElemType& tElem)) const;  // 深度优先遍历
  void BfsTraverse(void (*pVisit)(const ElemType&)) const;  // 广度优先遍历
  bool GetElem(int nNode, ElemType& tElem) const;  // 获取节点元素
  bool SetElem(int nNode, const ElemType& tElem);  // 设置节点元素
  bool Prim();     // 普里姆算法求最小生成树
  bool Kruskal();  // 克鲁斯卡尔算法求最小生成树
  GraphEdge<WeightType>* GetMstEdge(
      int& nMstEdgeCount) const;  // 获取最小生成树的边集
  bool TopoSort(SqList<int>& slSortedNode) const;  // 拓扑排序
  // 求网的关键路径
  bool CriticalPath(SqList<GraphEdge<WeightType>>& slCriticalPathEdge) const;
  // 迪杰斯特拉算法求最短路径
  bool Dijkstra(int nStartNode, WeightType* arrPathLen, int* arrPreNode,
                int nBufferLen);
  GraphBase<ElemType, NodeType, WeightType>& operator=(
      const GraphBase<ElemType, NodeType, WeightType>& gbSrc);
  // 插入多条边
  int InsertEdges(const GraphEdge<WeightType>* arrEdges, int nEdgeCount);

 protected:
  // 深度优先辅助函数
  void DfsAux(int nNode, void (*pVisit)(const ElemType&)) const;
  // 广度优先辅助函数
  void BfsAux(int nNode, void (*pVisit)(const ElemType&)) const;
  // 获取节点元素
  virtual void GetNodeElem(const NodeType& tNode, ElemType& tElem) const = 0;
  // 设置节点元素
  virtual void SetNodeElem(NodeType& tNode, const ElemType& tElem) = 0;
  void ClearTag();              // 清除访问标志
  void Reserve(int nNodeSize);  // 重新分配节点表和访问标志表的大小
  void StatInDegree(int* arrInDegree) const;  // 统计入度
  NodeType* m_arrNode;                        // 节点表
  bool* m_arrVistedTag;                       // 节点访问标志表
  GraphEdge<WeightType>* m_arrMstEdge;        // 最小生成树的边集
  int m_nNodeCount;                           // 顶点数量
  int m_nEdgeCount;                           // 边数量
  int m_nMstEdgeCount;                        // 最小生成树的边数量
  GRAPH_TYPE m_eType;                         // 图的类型
};

// 构造函数
template <class ElemType, class NodeType, class WeightType>
GraphBase<ElemType, NodeType, WeightType>::GraphBase(int nNodeCount,
                                                     GRAPH_TYPE eType)
    : m_arrNode(new NodeType[nNodeCount]),
      m_arrVistedTag(new bool[nNodeCount]),
      m_arrMstEdge(NULL),
      m_nNodeCount(nNodeCount),
      m_nEdgeCount(0),
      m_nMstEdgeCount(0),
      m_eType(eType) {
  std::fill_n(m_arrVistedTag, nNodeCount, false);
}

// 析构函数
template <class ElemType, class NodeType, class WeightType>
GraphBase<ElemType, NodeType, WeightType>::~GraphBase() {
  if (m_arrNode) {
    delete[] m_arrNode;
    m_arrNode = NULL;
  }

  if (m_arrVistedTag) {
    delete[] m_arrVistedTag;
    m_arrVistedTag = NULL;
  }

  if (m_arrMstEdge) {
    delete[] m_arrMstEdge;
    m_arrMstEdge = NULL;
  }

  m_nNodeCount = 0;
  m_nEdgeCount = 0;
  m_nMstEdgeCount = 0;
}

// 重新分配图的节点表和访问标志表的大小
template <class ElemType, class NodeType, class WeightType>
void GraphBase<ElemType, NodeType, WeightType>::Reserve(int nNodeCount) {
  if (m_arrNode) {
    delete[] m_arrNode;  // 删除旧的节点表
  }

  if (m_arrVistedTag) {
    delete[] m_arrVistedTag;  // 删除旧的访问标志表
  }

  if (m_arrMstEdge) {
    delete[] m_arrMstEdge;  // 删除旧的最小生成树边集
    m_arrMstEdge = NULL;
  }

  m_arrNode = new NodeType[nNodeCount];   // 分配新的节点表
  m_arrVistedTag = new bool[nNodeCount];  // 分配新的访问标志表
  // 初始化访问标志表为 false
  std::fill_n(m_arrVistedTag, nNodeCount, false);
  m_nNodeCount = nNodeCount;  // 更新节点数量
  m_nEdgeCount = 0;           // 重置边数量
  m_nMstEdgeCount = 0;        // 重置最小生成树边数量
}

// 插入多条边
template <class ElemType, class NodeType, class WeightType>
int GraphBase<ElemType, NodeType, WeightType>::InsertEdges(
    const GraphEdge<WeightType>* arrEdges, int nEdgeCount) {
  for (int i = 0; i < nEdgeCount; ++i)
    InsertEdge(arrEdges[i].m_nNode1, arrEdges[i].m_nNode2,
               arrEdges[i].m_tWeight);  // 插入每一条边
  return m_nEdgeCount;                  // 返回当前边的数量
}

template <class ElemType, class NodeType, class WeightType>
bool GraphBase<ElemType, NodeType, WeightType>::GetElem(int nNode,
                                                        ElemType& tElem) const {
  // 检查节点索引是否越界或节点表是否为空
  if (nNode < 0 || nNode >= m_nNodeCount || !m_arrNode)
    return false;
  // 从节点表中获取指定节点的元素值
  GetNodeElem(m_arrNode[nNode], tElem);
  return true;
}

template <class ElemType, class NodeType, class WeightType>
bool GraphBase<ElemType, NodeType, WeightType>::SetElem(int nNode,
                                                        const ElemType& tElem) {
  // 检查节点索引是否越界或节点表是否为空
  if (nNode < 0 || nNode >= m_nNodeCount || !m_arrNode)
    return false;
  // 设置指定节点的元素值
  SetNodeElem(m_arrNode[nNode], tElem);
  return true;
}

template <class ElemType, class NodeType, class WeightType>
void GraphBase<ElemType, NodeType, WeightType>::ClearTag() {
  // 如果访问标志数组为空,直接返回
  if (!m_arrVistedTag)
    return;
  // 使用 std::fill_n 将访问标志数组中所有元素重置为 false
  std::fill_n(m_arrVistedTag, m_nNodeCount, false);
}

template <class ElemType, class NodeType, class WeightType>
void GraphBase<ElemType, NodeType, WeightType>::DfsAux(
    int nNode, void (*pVisit)(const ElemType&)) const {
  SetTag(nNode, true);  // 标记当前节点为已访问
  ElemType tElem;
  GetElem(nNode, tElem);  // 获取当前节点的元素
  (*pVisit)(tElem);       // 访问当前节点

  WeightType tWeight;
  // 遍历所有邻接点：先获取第一个邻接点，然后通过NextAdjNode获取下一个邻接点
  for (int nAdjNode = FirstAdjNode(nNode, tWeight); nAdjNode >= 0;
       nAdjNode = NextAdjNode(nNode, nAdjNode, tWeight)) {
    if (!GetTag(nAdjNode)) {     // 如果邻接点未被访问
      DfsAux(nAdjNode, pVisit);  // 递归访问邻接点
    }
  }
}

template <class ElemType, class NodeType, class WeightType>
void GraphBase<ElemType, NodeType, WeightType>::DfsTraverse(
    void (*pVisit)(const ElemType& tElem)) const {
  ClearTag();  // 清空访问标志

  for (int nNode = 0; nNode < m_nNodeCount; ++nNode) {
    if (!GetTag(nNode))  // 对未访问的顶点进行深度优先搜索
      DfsAux(nNode, pVisit);
  }
}

template <class ElemType, class NodeType, class WeightType>
void GraphBase<ElemType, NodeType, WeightType>::BfsAux(
    int nNode, void (*pVisit)(const ElemType&)) const {
  SetTag(nNode, true);  // 标记起始节点为已访问
  ElemType tElem;
  GetElem(nNode, tElem);  // 获取起始节点的元素
  (*pVisit)(tElem);       // 访问起始节点
  LkQueue<int> lqNode;    // 创建一个队列用于存储待访问节点
  lqNode.InQueue(nNode);  // 将起始节点入队
  WeightType tWeight;
  while (!lqNode.IsEmpty()) {  // 当队列不为空时，继续遍历
    lqNode.OutQueue(nNode);    // 出队一个节点
    for (int nAdjNode = FirstAdjNode(nNode, tWeight); nAdjNode >= 0;
         nAdjNode =
             NextAdjNode(nNode, nAdjNode, tWeight)) {  // 遍历所有邻接节点
      if (!GetTag(nAdjNode)) {     // 如果邻接节点未被访问
        SetTag(nAdjNode, true);    // 标记邻接节点为已访问
        GetElem(nAdjNode, tElem);  // 获取邻接节点的元素
        (*pVisit)(tElem);          // 访问邻接节点
        lqNode.InQueue(nAdjNode);  // 将邻接节点入队
      }
    }
  }
}

template <class ElemType, class NodeType, class WeightType>
void GraphBase<ElemType, NodeType, WeightType>::BfsTraverse(
    void (*pVisit)(const ElemType&)) const {
  ClearTag();
  for (int nNode = 0; nNode < m_nNodeCount; ++nNode) {
    if (!GetTag(nNode))
      BfsAux(nNode, pVisit);
  }
}

template <class ElemType, class NodeType, class WeightType>
int GraphBase<ElemType, NodeType, WeightType>::NodeCount() const {
  return m_nNodeCount;
}

template <class ElemType, class NodeType, class WeightType>
int GraphBase<ElemType, NodeType, WeightType>::EdgeCount() const {
  return m_nEdgeCount;
}

template <class ElemType, class NodeType, class WeightType>
bool GraphBase<ElemType, NodeType, WeightType>::GetTag(int nNode) const {
  if (nNode < 0 || nNode >= m_nNodeCount) {
    std::cerr << "节点索引超出范围: " << nNode << std::endl;
    throw std::out_of_range("节点索引超出范围");
  }

  return m_arrVistedTag[nNode];
}

template <class ElemType, class NodeType, class WeightType>
void GraphBase<ElemType, NodeType, WeightType>::SetTag(int nNode, bool bTag) {
  if (nNode < 0 || nNode >= m_nNodeCount) {
    std::cerr << "节点索引超出范围: " << nNode << std::endl;
    throw std::out_of_range("节点索引超出范围");
  }

  m_arrVistedTag[nNode] = bTag;
}

// 使用Prim算法计算最小生成树
// 从任意顶点开始，每次选择距离当前生成树最近的顶点加入，直到所有顶点都加入
template <class ElemType, class NodeType, class WeightType>
bool GraphBase<ElemType, NodeType, WeightType>::Prim() {
  // 检查图是否为无向网且数据合法
  if (m_nNodeCount <= 0 || m_nEdgeCount <= 0 || !m_arrNode ||
      m_eType != UNDIR_NETWORK) {
    return false;
  }

  // 清理旧的最小生成树边集
  if (m_arrMstEdge) {
    delete[] m_arrMstEdge;
    m_arrMstEdge = NULL;
  }

  // 为最小生成树边集分配内存，最多需要 n-1 条边
  m_arrMstEdge = new GraphEdge<WeightType>[m_nNodeCount - 1];
  m_nMstEdgeCount = 0;

  // 初始化辅助数组:
  // arrMinWeight[i] 表示顶点i到当前生成树的最小权值
  // arrPreNode[i] 记录顶点i在生成树中的前驱顶点
  WeightType* arrMinWeight = new WeightType[m_nNodeCount];
  int* arrPreNode = new int[m_nNodeCount];

  // 初始化所有顶点到生成树的距离为无穷大，前驱顶点为-1
  std::fill_n(arrMinWeight, m_nNodeCount, InfniteWeight());
  std::fill_n(arrPreNode, m_nNodeCount, -1);

  // 从顶点0开始构造最小生成树，初始距离为0
  arrMinWeight[0] = 0;

  // 循环n次，每次选择一个顶点加入生成树
  for (int i = 0; i < m_nNodeCount; ++i) {
    // 在未访问顶点中寻找距离最小的顶点
    WeightType tMinWeight = InfniteWeight();
    int nMinNode = -1;
    for (int j = 0; j < m_nNodeCount; ++j) {
      if (!GetTag(j) && arrMinWeight[j] < tMinWeight) {
        tMinWeight = arrMinWeight[j];
        nMinNode = j;
      }
    }

    // 如果找不到最小权值顶点，说明图不连通
    if (nMinNode == -1) {
      delete[] arrMinWeight;
      delete[] arrPreNode;
      return false;
    }

    // 标记该顶点已加入生成树
    SetTag(nMinNode, true);

    // 将对应的边加入最小生成树边集（第一个顶点除外）
    if (i > 0) {
      m_arrMstEdge[m_nMstEdgeCount].m_nNode1 = arrPreNode[nMinNode];
      m_arrMstEdge[m_nMstEdgeCount].m_nNode2 = nMinNode;
      m_arrMstEdge[m_nMstEdgeCount].m_tWeight = tMinWeight;
      ++m_nMstEdgeCount;
    }

    // 以新加入的顶点为中介，更新其他顶点到生成树的距离
    WeightType tWeight;
    for (int nAdjNode = FirstAdjNode(nMinNode, tWeight); nAdjNode >= 0;
         nAdjNode = NextAdjNode(nMinNode, nAdjNode, tWeight)) {
      // 如果邻接顶点未访问且权值更小，则更新最小权值和前驱顶点
      if (!GetTag(nAdjNode) && tWeight < arrMinWeight[nAdjNode]) {
        arrMinWeight[nAdjNode] = tWeight;
        arrPreNode[nAdjNode] = nMinNode;
      }
    }
  }

  // 释放辅助数组并清除访问标记
  delete[] arrMinWeight;
  delete[] arrPreNode;
  ClearTag();
  return true;
}

template <class ElemType, class NodeType, class WeightType>
bool GraphBase<ElemType, NodeType, WeightType>::Kruskal() {
  // 检查图是否为无向网且数据合法
  if (m_nNodeCount <= 0 || m_nEdgeCount <= 0 || !m_arrNode ||
      m_eType != UNDIR_NETWORK) {
    return false;
  }

  // 清理并重新分配最小生成树边集内存
  if (m_arrMstEdge) {
    delete[] m_arrMstEdge;
    m_arrMstEdge = NULL;
  }
  m_arrMstEdge = new GraphEdge<WeightType>[m_nNodeCount - 1];

  // 创建最小优先级队列存储所有边
  MinPriorityHeapQueue<GraphEdge<WeightType>> mphqEdge;
  GraphEdge<WeightType> geEdge;
  WeightType tWeight;
  int nEdgeCount = 0;

  // 初始化并查集
  FindUnionSet fuSet(m_nNodeCount);

  // 收集所有边并加入优先级队列
  for (int nNode = 0; nNode < m_nNodeCount; ++nNode) {
    for (int nAdjNode = FirstAdjNode(nNode, tWeight); nAdjNode >= 0;
         nAdjNode = NextAdjNode(nNode, nAdjNode, tWeight)) {
      // 只处理一半的边以避免重复（因为是无向图）
      if (nNode < nAdjNode) {
        geEdge.m_nNode1 = nNode;
        geEdge.m_nNode2 = nAdjNode;
        geEdge.m_tWeight = tWeight;
        mphqEdge.InQueue(geEdge);
      }
    }
  }

  // 构建最小生成树
  while (nEdgeCount < m_nNodeCount - 1) {
    // 如果无法取出更多边，说明图不连通
    if (!mphqEdge.OutQueue(geEdge)) {
      break;
    }

    // 如果两个顶点不在同一个集合中，则添加这条边
    if (!fuSet.IsSameTree(geEdge.m_nNode1, geEdge.m_nNode2)) {
      fuSet.Union(geEdge.m_nNode1, geEdge.m_nNode2);
      m_arrMstEdge[nEdgeCount++] = geEdge;
    }
  }

  m_nMstEdgeCount = nEdgeCount;

  // 如果边数小于n-1，说明图不连通
  return nEdgeCount == m_nNodeCount - 1;
}

template <class ElemType, class NodeType, class WeightType>
GraphEdge<WeightType>* GraphBase<ElemType, NodeType, WeightType>::GetMstEdge(
    int& nMstEdgeCount) const {
  nMstEdgeCount = m_nMstEdgeCount;
  return m_arrMstEdge;
}

template <class ElemType, class NodeType, class WeightType>
void GraphBase<ElemType, NodeType, WeightType>::StatInDegree(
    int* arrInDegree) const {
  ElemType tWeight;
  // 初始化入度数组为 0
  std::fill_n(arrInDegree, m_nNodeCount, 0);
  // 遍历所有节点
  for (int nNode = 0; nNode < m_nNodeCount; ++nNode) {
    // 遍历当前节点的所有邻接节点
    for (int nAdjNode = FirstAdjNode(nNode, tWeight); nAdjNode >= 0;
         nAdjNode = NextAdjNode(nNode, nAdjNode, tWeight)) {
      // 增加邻接节点的入度
      ++arrInDegree[nAdjNode];
    }
  }
}

template <class ElemType, class NodeType, class WeightType>
bool GraphBase<ElemType, NodeType, WeightType>::TopoSort(
    SqList<int>& slSortedNode) const {
  // 检查图的基本条件是否满足拓扑排序的要求
  if (m_nNodeCount <= 0 || m_nEdgeCount <= 0 || !m_arrNode ||
      m_eType == UNDIR_GRAPH || m_eType == UNDIR_NETWORK) {
    return false;
  }

  slSortedNode.Clear();  // 清空排序结果列表

  int nNode = -1;            // 当前处理的节点
  int nNodeCount = 0;        // 已排序的节点计数
  LkStack<int> lsTopoStack;  // 用于存储入度为0的节点的栈
  WeightType tWeight;        // 辅助变量，用于存储权重
  int* arrInDegree = new int[m_nNodeCount];  // 入度数组
  StatInDegree(arrInDegree);                 // 计算每个节点的入度

  // 将所有入度为0的节点入栈
  for (int i = 0; i < m_nNodeCount; ++i) {
    if (arrInDegree[i] == 0) {
      lsTopoStack.Push(i);
    }
  }

  // 处理栈中的节点，进行拓扑排序
  while (!lsTopoStack.IsEmpty()) {
    if (!lsTopoStack.Pop(nNode)) {
      break;
    }
    slSortedNode.AddTail(nNode);  // 将节点添加到排序结果中
    ++nNodeCount;                 // 增加已排序节点计数
    // 更新邻接节点的入度
    for (int nAdjNode = FirstAdjNode(nNode, tWeight); nAdjNode >= 0;
         nAdjNode = NextAdjNode(nNode, nAdjNode, tWeight)) {
      if (--arrInDegree[nAdjNode] == 0) {
        lsTopoStack.Push(nAdjNode);  // 如果入度为0，入栈
      }
    }
  }

  delete[] arrInDegree;  // 释放入度数组内存

  // 如果已排序节点数等于节点总数，说明拓扑排序成功
  return nNodeCount == m_nNodeCount;
}

template <class ElemType, class NodeType, class WeightType>
bool GraphBase<ElemType, NodeType, WeightType>::CriticalPath(
    SqList<GraphEdge<WeightType>>& slCriticalPathEdge) const {
  // 参数检查
  if (m_eType != DIR_NETWORK || m_nNodeCount <= 0 || !m_arrNode ||
      m_nEdgeCount <= 0) {
    return false;  // 必须是有向网络且存在顶点和边
  }

  // 初始化数据结构
  int* arrInDegree = new int[m_nNodeCount];  // 入度数组
  int* arrVE = new int[m_nNodeCount];        // 最早发生时间数组
  int* arrVL = new int[m_nNodeCount];        // 最迟发生时间数组

  // 初始化入度和最早发生时间
  StatInDegree(arrInDegree);
  std::fill_n(arrVE, m_nNodeCount, 0);

  // 拓扑排序并计算最早发生时间
  LkStack<int> lsTopoStack;
  LkStack<int> lsReverseStack;
  int nNodeCount = 0;
  WeightType tWeight;

  // 将入度为0的顶点入栈
  for (int nNode = 0; nNode < m_nNodeCount; ++nNode) {
    if (arrInDegree[nNode] == 0) {
      lsTopoStack.Push(nNode);
    }
  }

  // 拓扑排序主循环
  while (!lsTopoStack.IsEmpty()) {
    int nNode;
    lsTopoStack.Pop(nNode);
    lsReverseStack.Push(nNode);
    ++nNodeCount;

    // 遍历邻接顶点
    for (int nAdjNode = FirstAdjNode(nNode, tWeight); nAdjNode != -1;
         nAdjNode = NextAdjNode(nNode, nAdjNode, tWeight)) {
      // 更新入度
      if (--arrInDegree[nAdjNode] == 0) {
        lsTopoStack.Push(nAdjNode);
      }
      // 更新最早发生时间
      int nEarliestTime = arrVE[nNode] + tWeight;
      if (nEarliestTime > arrVE[nAdjNode]) {
        arrVE[nAdjNode] = nEarliestTime;
      }
    }
  }

  // 检查是否存在环
  if (nNodeCount < m_nNodeCount) {
    delete[] arrInDegree;
    delete[] arrVE;
    delete[] arrVL;
    return false;
  }

  // 计算最迟发生时间
  int nEndNode;
  lsReverseStack.Top(nEndNode);
  int nMaxTime = arrVE[nEndNode];

  // 初始化最迟发生时间
  std::fill_n(arrVL, m_nNodeCount, nMaxTime);

  // 逆拓扑序计算最迟发生时间
  while (!lsReverseStack.IsEmpty()) {
    int nNode;
    lsReverseStack.Pop(nNode);

    for (int nAdjNode = FirstAdjNode(nNode, tWeight); nAdjNode != -1;
         nAdjNode = NextAdjNode(nNode, nAdjNode, tWeight)) {
      int nLatestTime = arrVL[nAdjNode] - tWeight;
      if (nLatestTime < arrVL[nNode]) {
        arrVL[nNode] = nLatestTime;
      }
    }
  }

  // 查找关键活动
  slCriticalPathEdge.Clear();
  GraphEdge<WeightType> geEdge;

  for (int nNode = 0; nNode < m_nNodeCount; nNode++) {
    for (int nAdjNode = FirstAdjNode(nNode, tWeight); nAdjNode != -1;
         nAdjNode = NextAdjNode(nNode, nAdjNode, tWeight)) {
      // 计算活动的最早和最迟开始时间
      int nEarliestStart = arrVE[nNode];
      int nLatestStart = arrVL[nAdjNode] - tWeight;

      // 最早开始时间等于最迟开始时间的活动即为关键活动
      if (nEarliestStart == nLatestStart) {
        geEdge.m_nNode1 = nNode;
        geEdge.m_nNode2 = nAdjNode;
        geEdge.m_tWeight = tWeight;
        slCriticalPathEdge.AddTail(geEdge);
      }
    }
  }

  // 清理资源
  delete[] arrInDegree;
  delete[] arrVE;
  delete[] arrVL;

  return true;
}

template <class ElemType, class NodeType, class WeightType>
bool GraphBase<ElemType, NodeType, WeightType>::Dijkstra(int nStartNode,
                                                         WeightType* arrPathLen,
                                                         int* arrPreNode,
                                                         int nBufferLen) {}

// 重载赋值运算符，用于将一个GraphBase对象的内容复制到另一个GraphBase对象中
template <class ElemType, class NodeType, class WeightType>
GraphBase<ElemType, NodeType, WeightType>&
GraphBase<ElemType, NodeType, WeightType>::operator=(
    const GraphBase<ElemType, NodeType, WeightType>& gbSrc) {
  // 检查自赋值情况，避免不必要的操作
  if (&gbSrc != this) {
    // 如果节点数量不同，则重新分配内存
    if (m_nNodeCount != gbSrc.m_nNodeCount) {
      Reserve(gbSrc.m_nNodeCount);  // 调整节点表和访问标志表的大小
    }
    // 复制节点数量、边数量和最小生成树边数量
    m_nNodeCount = gbSrc.m_nNodeCount;
    m_nEdgeCount = gbSrc.m_nEdgeCount;
    m_nMstEdgeCount = gbSrc.m_nMstEdgeCount;

    // 如果源对象的最小生成树边集不为空，则复制该边集
    if (gbSrc.m_arrMstEdge) {
      // 为最小生成树边集分配新内存
      m_arrMstEdge = new GraphEdge<WeightType>[gbSrc.m_nMstEdgeCount];
      // 复制最小生成树边集
      std::copy(gbSrc.m_arrMstEdge, gbSrc.m_arrMstEdge + gbSrc.m_nMstEdgeCount,
                m_arrMstEdge);
    }
    // 复制节点表
    std::copy(gbSrc.m_arrNode, gbSrc.m_arrNode + gbSrc.m_nNodeCount, m_arrNode);
    // 复制访问标志表
    std::copy(gbSrc.m_arrVistedTag, gbSrc.m_arrVistedTag + gbSrc.m_nNodeCount,
              m_arrVistedTag);
    // 复制图的类型
    m_eType = gbSrc.m_eType;
  }
  // 返回当前对象的引用，以支持链式赋值
  return *this;
}

template <class ElemType, class NodeType, class WeightType>
WeightType GraphBase<ElemType, NodeType, WeightType>::InfniteWeight() {
  if (typeid(WeightType) == typeid(char) ||
      typeid(WeightType) == typeid(unsigned char)) {
    return CHAR_MAX;  // 返回char类型的最大值127
  } else if (typeid(WeightType) == typeid(short) ||
             typeid(WeightType) == typeid(unsigned short)) {
    return SHRT_MAX;  // 返回short类型的最大值32767
  } else if (typeid(WeightType) == typeid(float)) {
    return FLT_MAX;  // 返回float类型的最大值
  } else if (typeid(WeightType) == typeid(double)) {
    return DBL_MAX;  // 返回double类型的最大值
  }
  return INT_MAX;  // 返回int类型的最大值2147483647
}

#endif  // GRAPH_BASE_H_