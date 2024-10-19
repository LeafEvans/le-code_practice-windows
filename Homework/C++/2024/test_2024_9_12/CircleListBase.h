#ifndef _CIRCLELISTBASE_H_
#define _CIRCLELISTBASE_H_
#include "LinkListBase.h"

template <class T, class NodeType>
class CircleListBase : public LinkListBase<T, NodeType> {
 public:
  CircleListBase();                             // 默认构造函数
  ~CircleListBase();                            // 析构函数
  CircleListBase(const CircleListBase &src);    // 拷贝构造函数
  virtual bool delElem(int pos, T &elem);       // 删除指定元素
  virtual bool insert(int pos, const T &elem);  // 插入指定元素
  virtual int append(const T &elem);            // 在末尾接一个元素
  virtual bool isEmpty() const;                 // 判断是否为空
  // 重载等于号
  virtual CircleListBase &operator=(const CircleListBase<T, NodeType> &src);
  void clear();                  // 清空链表
  virtual bool toNext(T &elem);  // 下一个元素

 protected:
  virtual NodeType *first() const;  // 第一个有效元素
  virtual void linkTailToHead();    // 将尾节点连接到头节点
};

template <class T, class NodeType>
CircleListBase<T, NodeType>::CircleListBase() {}  // 默认构造函数

template <class T, class NodeType>
CircleListBase<T, NodeType>::~CircleListBase() {}  // 析构函数

template <class T, class NodeType>
CircleListBase<T, NodeType>::CircleListBase(
    const CircleListBase<T, NodeType> &src) {
  *this = src;  // 拷贝函数
}

template <class T, class NodeType>
CircleListBase<T, NodeType> &CircleListBase<T, NodeType>::operator=(
    const CircleListBase<T, NodeType> &src) {
  LinkListBase<T, NodeType>::operator=(src);  // 先调用基类的拷贝函数
  linkTailToHead();                           // 将尾节点连接到头节点
  return *this;
}

template <class T, class NodeType>
void CircleListBase<T, NodeType>::linkTailToHead() {
  this->link(this->tail_, this->head_);
}

template <class T, class NodeType>
void CircleListBase<T, NodeType>::clear() {
  LinkListBase<T, NodeType>::clear();
  linkTailToHead();  // 将尾节点连接到头节点
}

template <class T, class NodeType>
bool CircleListBase<T, NodeType>::insert(int pos, const T &elem) {
  bool flag = LinkListBase<T, NodeType>::insert(pos, elem);
  linkTailToHead();
  return flag;
}

template <class T, class NodeType>
bool CircleListBase<T, NodeType>::toNext(T &elem) {
  if (isEmpty()) {
    return false;  // 判断是否为空
  }

  // 当前或下一个为空
  if (!this->curr_ || !this->curr_->next) {
    return false;
  }

  // 指向下一个
  this->curr_ = this->curr_->next;

  // 如果现在重新指向了头节点
  if (this->curr_ == this->head_) {
    // 再往后一个，指向第一个有效元素
    this->curr_ = this->curr_->next;
  }

  // 将元素赋值回来
  elem = this->curr_->data;

  return true;
}

template <class T, class NodeType>
bool CircleListBase<T, NodeType>::delElem(int pos, T &elem) {
  bool flag = LinkListBase<T, NodeType>::delElem(pos, elem);
  linkTailToHead();
  return flag;
}

template <class T, class NodeType>
int CircleListBase<T, NodeType>::append(const T &elem) {
  int index = LinkListBase<T, NodeType>::append(elem);
  linkTailToHead();
  return index;
}

template <class T, class NodeType>
bool CircleListBase<T, NodeType>::isEmpty() const {
  if (this->head_->next == this->head_) {
    return true;  // 头指针又指向头指针
  }
  return false;
}

template <class T, class NodeType>
NodeType *CircleListBase<T, NodeType>::first() const {
  if (isEmpty()) {   // 链表为空
    return nullptr;  // 返回空指针
  }
  return this->head_->next;  // 否则正常返回
}

#endif  // _CIRCLELISTBASE_H_
