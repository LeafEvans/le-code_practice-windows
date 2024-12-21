#ifndef FIND_UNION_SET_H_
#define FIND_UNION_SET_H_
#include <algorithm>
#include <cstddef>

class FindUnionSet {
 public:
  FindUnionSet(int nSize);
  ~FindUnionSet();
  int Find(int nNode);
  bool IsSameTree(int x, int y);
  bool Union(int nNode1, int nNode2);

 private:
  int* m_arrParents;
  int m_nSize;
};

inline FindUnionSet::FindUnionSet(int nSize)
    : m_arrParents(new int[nSize]), m_nSize(nSize) {
  for (int i = 0; i < nSize; ++i)
    m_arrParents[i] = i;
}

inline FindUnionSet::~FindUnionSet() {
  if (m_arrParents) {
    delete[] m_arrParents;
    m_arrParents = NULL;
  }
}

inline int FindUnionSet::Find(int nNode) {
  while (nNode >= 0 && nNode < m_nSize && m_arrParents[nNode] != nNode) {
    nNode = m_arrParents[nNode];
  }

  return (nNode < 0 || nNode >= m_nSize) ? -1 : nNode;
}

inline bool FindUnionSet::Union(int nNode1, int nNode2) {
  // 检查节点索引是否有效
  if (nNode1 < 0 || nNode1 >= m_nSize || nNode2 < 0 || nNode2 >= m_nSize) {
    return false;
  } else if (nNode1 == nNode2) {
    // 如果两个节点相同，已经在同一集合中
    return true;
  }

  // 查找两个节点的根节点
  int nRoot1 = Find(nNode1);
  int nRoot2 = Find(nNode2);

  // 检查根节点索引是否有效
  if (nRoot1 < 0 || nRoot1 >= m_nSize || nRoot2 < 0 || nRoot2 >= m_nSize) {
    return false;
  } else if (nRoot1 == nRoot2) {
    // 如果两个根节点相同，节点已在同一集合中
    return true;
  }

  if (nRoot2 > nRoot1) {
    std::swap(nRoot1, nRoot2);
  }
  // 合并两个节点
  m_arrParents[nRoot1] = nRoot2;
  return true;
}

inline bool FindUnionSet::IsSameTree(int nNode1, int nNode2) {
  // 检查节点索引是否有效
  if (nNode1 < 0 || nNode1 >= m_nSize || nNode2 < 0 || nNode2 >= m_nSize) {
    return false;
  } else if (nNode1 == nNode2) {
    // 如果两个节点相同，已经在同一集合中
    return true;
  }

  // 查找两个节点的根节点
  int nRoot1 = Find(nNode1);
  int nRoot2 = Find(nNode2);

  // 检查根节点索引是否有效
  if (nRoot1 < 0 || nRoot1 >= m_nSize || nRoot2 < 0 || nRoot2 >= m_nSize) {
    return false;
  } else if (nRoot1 == nRoot2) {
    // 如果两个根节点相同，节点已在同一集合中
    return true;
  }

  return false;
}
#endif  // FIND_UNION_SET_H_