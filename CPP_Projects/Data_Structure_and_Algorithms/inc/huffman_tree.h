#ifndef _INC_HUFFMAN_TREE_H_
#define _INC_HUFFMAN_TREE_H_
#include "char_string.h"
#include "huffman_tree_node.h"
#include "lk_bin_tree_base.h"
#include "min_priority_heap_queue.h"
#include "sq_list.h"

template <class ElemType, class WeightType>
class HuffmanTree
    : public LkBinTreeBase<ElemType, HuffmanTreeNode<ElemType, WeightType>> {
 public:
  HuffmanTree();
  HuffmanTree(const HuffmanTree<ElemType, WeightType>& htSrc);
  ~HuffmanTree();
  bool CreateHuffmanTree(ElemType* arrElem, WeightType* arrWeight, int nSize);
  bool Ecode(const ElemType tElem, CharString& csCode);
  bool Dcode(SqList<ElemType>& sqCode, const CharString& csCode);
  void Clear();
  virtual HuffmanTreeNode<ElemType, WeightType>* GetParent(
      HuffmanTreeNode<ElemType, WeightType>* pNode) const;

 private:
  virtual void LinkParentChild(HuffmanTreeNode<ElemType, WeightType>* pParent,
                               HuffmanTreeNode<ElemType, WeightType>* pChild,
                               bool bLeft);
  HuffmanTreeNode<ElemType, WeightType>* m_pNode;
  CharString* m_arrCode;
  ElemType* m_arrElem;
  int m_nElemCount;
};

template <class ElemType, class WeightType>
bool HuffmanTree<ElemType, WeightType>::CreateHuffmanTree(ElemType* arrElem,
                                                          WeightType* arrWeight,
                                                          int nSize) {
  if (!arrElem || !arrWeight || nSize <= 0)
    return false;

  Clear();
  
}
#endif  // _INC_HUFFMAN_TREE_H_