#ifndef _PERSON_H_
#define _PERSON_H_

#include <iostream>
#include <string>

using namespace std;

template <class T>
class Person {
 public:
  Person(const T& name, const T& id);
  void show();

  template <class U>
  friend ostream& operator<<(ostream& os, const Person<U>& person);

  template <class U>
  friend void printPerson(Person<U>& person);

 private:
  T _name;
  T _id;
};

template <class T>
Person<T>::Person(const T& name, const T& id) : _name(name), _id(id) {}

template <class T>
void Person<T>::show() {
  cout << "Name: " << _name << " ID: " << _id << endl;
}

template <class T>
ostream& operator<<(ostream& os, const Person<T>& person) {
  os << "Name: " << person._name << " ID: " << person._id << endl;
  return os;
}

template <class T>
void printPerson(Person<T>& person) {
  cout << "Name: " << person._name << " ID: " << person._id << endl;
}

#endif  // _PERSON_H_
