#if !defined(_LIST_BASH_H_)
#define _LIST_BASH_H
#include <memory.h>

template <class T>
class ListBase {
 public:
  virtual int length() const = 0;
  virtual bool isEmpty() const = 0;
  virtual void clear() = 0;
  virtual bool getElem(int pos, T& elem) const = 0;
  virtual bool setElem(int pos, const T& elem) = 0;
  virtual bool del(int pos, T& elem) = 0;
  virtual bool insert(int pos, const T& elem) = 0;
  virtual bool traverse(bool (*visit)(const T&)) = 0;
  virtual int append(cosnt T& elem) = 0;
};
#endif  // _LIST_BASH_H