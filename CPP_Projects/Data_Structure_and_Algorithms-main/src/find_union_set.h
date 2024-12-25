#ifndef FIND_UNION_SET_H_
#define FIND_UNION_SET_H_
#include <algorithm>
#include <cstddef>

// 并查集类，用于管理不相交集合的数据结构
class FindUnionSet {
 public:
  FindUnionSet(int nSize);                  // 构造函数，初始化并查集
  ~FindUnionSet();                          // 析构函数，释放资源
  int Find(int nNode);                      // 查找节点的根节点
  bool IsSameTree(int nNode1, int nNode2);  // 判断两个节点是否在同一集合
  bool Union(int nNode1, int nNode2);  // 合并两个节点所在的集合

 private:
  int* m_arrParent;  // 存储每个节点的父节点
  int m_nSize;       // 并查集的大小
};

inline FindUnionSet::FindUnionSet(int nSize)
    : m_arrParent(new int[nSize]), m_nSize(nSize) {
  // 初始化时每个节点的父节点为自身，即每个节点自成一个集合
  for (int i = 0; i < nSize; ++i)
    m_arrParent[i] = i;
}

inline FindUnionSet::~FindUnionSet() {
  // 释放动态分配的内存，防止内存泄漏
  if (m_arrParent) {
    delete[] m_arrParent;
    m_arrParent = NULL;
  }
}

inline int FindUnionSet::Find(int nNode) {
  // 查找节点所属的根节点，使用路径压缩优化
  while (nNode >= 0 && nNode < m_nSize && m_arrParent[nNode] != nNode) {
    nNode = m_arrParent[nNode];
  }
  // 返回根节点，若无效则返回-1
  return (nNode < 0 || nNode >= m_nSize) ? -1 : nNode;
}

inline bool FindUnionSet::Union(int nNode1, int nNode2) {
  // 检查节点参数的有效性
  if (nNode1 < 0 || nNode1 >= m_nSize || nNode2 < 0 || nNode2 >= m_nSize) {
    return false;
  } else if (nNode1 == nNode2) {
    return true;  // 相同节点必然在同一集合
  }

  // 获取两个节点的根节点
  int nRoot1 = Find(nNode1);
  int nRoot2 = Find(nNode2);

  // 检查根节点的有效性
  if (nRoot1 < 0 || nRoot1 >= m_nSize || nRoot2 < 0 || nRoot2 >= m_nSize) {
    return false;
  } else if (nRoot1 == nRoot2) {
    return true;  // 根节点相同说明已在同一集合
  }

  // 按秩合并优化：总是将较大的根节点连接到较小的根节点
  if (nRoot2 > nRoot1) {
    std::swap(nRoot1, nRoot2);
  }
  m_arrParent[nRoot1] = nRoot2;
  return true;
}

inline bool FindUnionSet::IsSameTree(int nNode1, int nNode2) {
  // 检查节点参数的有效性
  if (nNode1 < 0 || nNode1 >= m_nSize || nNode2 < 0 || nNode2 >= m_nSize) {
    return false;
  } else if (nNode1 == nNode2) {
    return true;  // 相同节点必然在同一集合
  }

  // 获取两个节点的根节点
  int nRoot1 = Find(nNode1);
  int nRoot2 = Find(nNode2);

  // 检查根节点的有效性
  if (nRoot1 < 0 || nRoot1 >= m_nSize || nRoot2 < 0 || nRoot2 >= m_nSize) {
    return false;
  } else if (nRoot1 == nRoot2) {
    return true;  // 根节点相同说明在同一集合
  }

  return false;
}
#endif  // FIND_UNION_SET_H_