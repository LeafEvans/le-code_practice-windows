#ifndef _NODE_H_
#define _NODE_H_

template<class T>
class Node {
 public:
  Node();  // 无参构造函数
  // 有参构造函数
  Node(const T &elem, Node<T> *link = nullptr);
  ~Node();  // 析构函数
  virtual void clearLink();  // 清空链接状态

  T data;  // 数据成分
  Node<T> *next;  // 指针成分
};

template<class T>
Node<T>::Node() {}

template<class T>
Node<T>::~Node() {}

template<class T>
Node<T>::Node(const T &elem, Node<T> *link) {
  data = elem;
  next = link;
}

template<class T>
void Node<T>::clearLink() {
  next = nullptr;
}

template<class T>
class DblNode : public Node<T> {
 public:
  DblNode();
  DblNode(const T &elem,
          DblNode<T> *prev_link = nullptr,
          DblNode<T> *next_link = nullptr);
  ~DblNode();
  DblNode<T> *prev;
  DblNode<T> *next;
  T data;
  virtual void clearLink();
};

template<class T>
DblNode<T>::DblNode() {
  prev = nullptr;
  next = nullptr;
}

template<class T>
DblNode<T>::DblNode(const T &elem,
                    DblNode<T> *prev_link,
                    DblNode<T> *next_link) {
  this->data = elem;  // 赋值指定元素
  prev = prev_link;   // 指向前驱
  next = next_link;   // 指向后继
}

template<class T>
DblNode<T>::~DblNode() {}

template<class T>
void DblNode<T>::clearLink() {
  prev = nullptr;
  next = nullptr;
}

#endif // _NODE_H_
