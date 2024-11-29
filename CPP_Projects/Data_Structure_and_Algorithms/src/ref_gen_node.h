#ifndef __REF_GEN_NODE_H__
#define __REF_GEN_NODE_H__

#include <cstddef>

#ifndef __REF_GEN_LIST_NODE_TYPE__
#define __REF_GEN_LIST_NODE_TYPE__
typedef enum { _HEAD, _ATOM, _LIST } RefGenNodeType;
#endif  // __REF_GEN_LIST_NODE_TYPE__

template <class ElemType>
struct RefGenNode {
  RefGenNodeType m_eTag;
  RefGenNode<ElemType>* m_pNext;

  union {
    int m_nRef;
    ElemType m_tData;
    RefGenNode<ElemType>* m_pSub;
  };

  RefGenNode(RefGenNodeType eTag = _HEAD, RefGenNode<ElemType>* pNext = NULL)
      : m_eTag(eTag), m_pNext(pNext) {}

    void ClearLink() {
      m_pNext = NULL;
      m_nRef = 1;
    }
};
#endif  //__REF_GEN_NODE_H__