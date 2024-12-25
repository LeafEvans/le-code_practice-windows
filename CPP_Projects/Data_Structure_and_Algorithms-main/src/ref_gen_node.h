#ifndef REF_GEN_NODE_H_
#define REF_GEN_NODE_H_
#ifndef REF_GEN_LIST_NODE_TYPE_
#define REF_GEN_LIST_NODE_TYPE_
#include <cstddef>
// 引用生成列表节点类型
enum RefGenNodeType { _HEAD, _ATOM, _LIST };
#endif  // REF_GEN_LIST_NODE_TYPE_

template <class ElemType>
struct RefGenNode {
  RefGenNodeType m_eTag;          // 节点类型标签
  RefGenNode<ElemType>* m_pNext;  // 指向后继节点的指针

  union {
    int m_nRef;                    // 引用计数
    ElemType m_tElem;              // 元素数据
    RefGenNode<ElemType>* m_pSub;  // 指向子节点的指针
  };

  RefGenNode(RefGenNodeType eTag = _HEAD, RefGenNode<ElemType>* pNext = NULL)
      : m_eTag(eTag), m_pNext(pNext) {}  // 默认构造函数

  void ClearLink() {
    m_pNext = NULL;  // 清除链接
    m_nRef = 1;      // 重置引用计数为 1
  }
};
#endif  // REF_GEN_NODE_H_