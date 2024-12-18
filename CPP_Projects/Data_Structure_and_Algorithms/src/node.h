#include <cstddef>

#ifndef NODE_H_
#define NODE_H_

template <class ElemType>
struct Node {
  ElemType m_tElem;         // 元素数据
  Node<ElemType>* m_pNext;  // 指向下一个节点的指针

  Node() : m_pNext(NULL) {}  // 默认构造函数
  // 带参数的构造函数
  Node(const ElemType& tElem, Node<ElemType>* pNext = NULL)
      : m_tElem(tElem), m_pNext(pNext) {}

  void ClearLink() { m_pNext = NULL; }  // 清除链接
};
#endif  // _NODE_H_

#ifndef DB_NODE_H_
#define DB_NODE_H_
template <class ElemType>
struct DbNode {
  ElemType m_tElem;           // 元素数据
  DbNode<ElemType>* m_pPre;   // 指向前驱节点的指针
  DbNode<ElemType>* m_pNext;  // 指向后继节点的指针

  DbNode() : m_pPre(NULL), m_pNext(NULL) {}  // 默认构造函数

  DbNode(const ElemType& tElem, DbNode<ElemType>* pPre = NULL,
         DbNode<ElemType>* pNext = NULL)  // 带参数的构造函数
      : m_tElem(tElem), m_pPre(pPre), m_pNext(pNext) {}

  void ClearLink() {  // 清除链接
    m_pPre = NULL;
    m_pNext = NULL;
  }
};
#endif  // DB_NODE_H_

#ifndef REF_GEN_NODE_H_
#define REF_GEN_NODE_H_
#ifndef REF_GEN_LIST_NODE_TYPE_
#define REF_GEN_LIST_NODE_TYPE_
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

#ifndef SQ_BIN_TREE_NODE_H_
#define SQ_BIN_TREE_NODE_H_
#ifndef SQ_BIN_TREE_NODE_TYPE_
#define SQ_BIN_TREE_NODE_TYPE_
// 顺序二叉树节点类型
enum SqBinTreeNodeType { EMPTY_NODE, USED_NODE };
#endif  // SQ_BIN_TREE_NODE_TYPE_

template <class ElemType>
struct SqBinTreeNode {
  ElemType m_tElem;          // 元素数据
  SqBinTreeNodeType m_eTag;  // 节点状态标签

  // 默认构造函数，初始化为空节点
  SqBinTreeNode() : m_eTag(EMPTY_NODE) {}

  SqBinTreeNode(const ElemType& tElem, SqBinTreeNodeType eTag)
      : m_tElem(tElem), m_eTag(eTag) {}  // 带参数的构造函数
};
#endif  // SQ_BIN_TREE_NODE_H_

#ifndef BIN_TREE_NODE_H_
#define BIN_TREE_NODE_H_
template <class ElemType>
struct BinTreeNode {
  ElemType m_tElem;                      // 元素数据
  BinTreeNode<ElemType>* m_pLeftChild;   // 指向左孩子的指针
  BinTreeNode<ElemType>* m_pRightChild;  // 指向右孩子的指针

  BinTreeNode() : m_pLeftChild(NULL), m_pRightChild(NULL) {}  // 默认构造函数

  BinTreeNode(const ElemType& tElem, BinTreeNode<ElemType>* pLeftChild,
              BinTreeNode<ElemType>* pRightChild)  // 带参数的构造函数
      : m_tElem(tElem), m_pLeftChild(pLeftChild), m_pRightChild(pRightChild) {}
};
#endif  // BIN_TREE_NODE_H_

#ifndef THREAD_BIN_TREE_NODE_H_
#define THREAD_BIN_TREE_NODE_H_

#ifndef PTR_TAG_TYPE_
#define PTR_TAG_TYPE_
// 指针类型标志：CHILD_PTR(0) 表示指向孩子节点的指针，THREAD_PTR(1)
// 表示指向线索节点的指针
enum PtrTagType { CHILD_PTR, THREAD_PTR };
#endif  // PTR_TAG_TYPE_

template <class ElemType>
struct ThreadBinTreeNode {
  ElemType m_tElem;                        // 元素数据
  ThreadBinTreeNode<ElemType>* m_pLeft;    // 左子节点指针
  ThreadBinTreeNode<ElemType>* m_pRight;   // 右子节点指针
  ThreadBinTreeNode<ElemType>* m_pParent;  // 父节点指针
  PtrTagType m_eLeftTag;                   // 左指针标志
  PtrTagType m_eRightTag;                  // 右指针标志

  ThreadBinTreeNode()
      : m_tElem(ElemType()),
        m_pLeft(NULL),
        m_pRight(NULL),
        m_pParent(NULL),
        m_eLeftTag(CHILD_PTR),
        m_eRightTag(CHILD_PTR) {}  // 默认构造函数，初始化为叶子节点

  ThreadBinTreeNode(const ElemType& tElem,
                    ThreadBinTreeNode<ElemType>* pLeft = NULL,
                    ThreadBinTreeNode<ElemType>* pRight = NULL,
                    PtrTagType eLeftTag = CHILD_PTR,
                    PtrTagType eRightTag = CHILD_PTR)
      : m_tElem(tElem),
        m_pLeft(pLeft),
        m_pRight(pRight),
        m_pParent(NULL),
        m_eLeftTag(eLeftTag),
        m_eRightTag(eRightTag) {}  // 带参数构造函数，初始化节点
};
#endif  // __THREAD_BIN_TREE_NODE_H__

#ifndef PARENT_TREE_NODE_H_
#define PARENT_TREE_NODE_H_
template <class ElemType>
struct ParentTreeNode {
  ElemType m_tElem;  // 节点元素数据
  int m_nParent;     // 父节点索引

  // 默认构造函数，将父节点索引初始化为 -1
  ParentTreeNode() : m_nParent(-1) {}

  // 带参数的构造函数，初始化节点元素和父节点索引
  ParentTreeNode(const ElemType& tElem, int nParent)
      : m_tElem(tElem), m_nParent(nParent) {}
};
#endif  // PARENT_TREE_NODE_H_

#ifndef CHILD_SIBLING_FOREST_NODE_H_
#define CHILD_SIBLING_FOREST_NODE_H_
template <class ElemType>
struct ChildSiblingTreeNode {
  ElemType m_tElem;
  ChildSiblingTreeNode<ElemType>* m_pFirstChild;
  ChildSiblingTreeNode<ElemType>* m_pRightSibling;

  ChildSiblingTreeNode() : m_pFirstChild(NULL), m_pRightSibling(NULL) {}
  ChildSiblingTreeNode(const ElemType& tElem,
                       ChildSiblingTreeNode<ElemType>* pFirstChild = NULL,
                       ChildSiblingTreeNode<ElemType>* pRightSibling = NULL)
      : m_tElem(tElem),
        m_pFirstChild(pFirstChild),
        m_pRightSibling(pRightSibling) {}
};
#endif  // CHILD_SIBLING_FOREST_NODE_H_
