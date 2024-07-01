/* #include <cstdlib>
#include <ctime>
#include <iostream>
#include <queue>
#include <vector>

template <class T>
class CMP {
 public:
  bool operator()(const T& arr, const T& b) { return arr > b; }
};

int main() {
  srand(time(nullptr));

  std::priority_queue<int, std::vector<int>,CMP<int>> pd;

  for (int i = 0; i < 10; ++i) {
    pd.push(rand());
  }

  while (!pd.empty()) {
    std::cout << pd.top() << ' ';
    pd.pop();
  }
  std::cout << std::endl;

  return 0;
} */
/* #include <cstdlib>
#include <ctime>
#include <deque>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

template <class T>
class CMP {
 public:
  bool operator()(const T &arr, const T &b) { return arr > b; }
};

int main() {
  srand(time(nullptr));

  queue<int, list<int>> qu;
  stack<int, vector<int>> st;
  priority_queue<int, deque<int>> pq;
  priority_queue<int, vector<int>, CMP<int>> pd;

  for (int i = 0; i < 10; ++i) {
    int num = rand() % 100 + 1;
    qu.push(num);
    st.push(num);
    pq.push(num);
    pd.push(num);
  }

  while (!qu.empty()) {
    cout << qu.front() << ' ';
    qu.pop();
  }
  cout << endl;

  while (!st.empty()) {
    cout << st.top() << ' ';
    st.pop();
  }
  cout << endl;

  while (!pq.empty()) {
    cout << pq.top() << ' ';
    pq.pop();
  }
  cout << endl;

  while (!pd.empty()) {
    cout << pd.top() << ' ';
    pd.pop();
  }
  cout << endl;

  return 0;
} */
/* #include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<vector<int>> vi;

  for (int i = 0; i < 10; ++i) {
    vector<int> tmp;
    vi.push_back(tmp);
    for (int j = 0; j < 10; ++j) {
      vi[i].push_back(i + j);
    }
  }

  for (vector<int> elvi : vi) {
    for (const int elem : elvi) {
      cout << elem << ' ';
    }
    cout << '\n';
  }
  cout << '\n';

  return 0;
} */
/* #include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

template <typename T>
class Array {
 public:
  Array() : m_arr(nullptr), m_len(0) {}                 // 默认构造函数
  Array(size_t len) : m_arr(new T[len]), m_len(len) {}  // 有参构造函数

  ~Array() {
    if (m_arr) {
      delete[] m_arr;
    }
  }


  T sum() {
    T sum = T();  // 零值初始化

    for (int i = 0; i < m_len; ++i) {
      sum += m_arr[i];
    }

    return sum;
  }

  T max() {
    T max = m_arr[0];

    for (int i = 0; i < m_len; ++i) {
      if (m_arr[i] > max) {
        max = m_arr[i];
      }
    }

    return max;
  }

  T &operator[](size_t index) { return m_arr[index]; }

 private:
  T *m_arr;
  size_t m_len;
};

int main() {
  srand(time(nullptr));
  Array<int> arr(10);
  for (int i = 0; i < 10; ++i) {
    arr[i] = rand();
    cout << arr[i] << ' ';
  }
  cout << '\n';

  cout << arr.sum() << '\n';
  cout << arr.max() << '\n';

    return 0;
} */
/* #include <cstring>
#include <iostream>

using namespace std;

class Complex {
 public:
  Complex(double real = 0, double imag = 0) : m_real(real), m_imag(imag) {}

  Complex operator+(const Complex& other) {
    Complex sum(m_real + other.m_real, m_imag + other.m_imag);
    return sum;
  }

  Complex operator-(const Complex& other) {
    Complex diff(m_real - other.m_real, m_imag - other.m_imag);
    return diff;
  }

  Complex operator*(const Complex& other) {
    double newReal = m_real * other.m_real - m_imag * other.m_imag;
    Complex prod(newReal, m_imag * other.m_real + m_real * other.m_imag);
    return prod;
  }

  Complex& operator+=(const Complex& other) {
    m_real += other.m_real;
    m_imag += other.m_imag;
    return *this;
  }

  Complex& operator-=(const Complex& other) {
    m_real -= other.m_real;
    m_imag -= other.m_imag;
    return *this;
  }

  Complex& operator*=(const Complex& other) {
    double newReal = m_real * other.m_real - m_imag * other.m_imag;
    m_imag = m_imag * other.m_real + m_real * other.m_imag;
    m_real = newReal;
    return *this;
  }

  Complex operator+(const double& other) {
    Complex sum(m_real + other, m_imag);
    return sum;
  }

  Complex operator-(const double& other) {
    Complex diff(m_real - other, m_imag);
    return diff;
  }

  Complex operator*(const double& other) {
    Complex prod(m_real * other, m_imag * other);
    return prod;
  }

  Complex& operator+=(const double& other) {
    m_real += other;
    return *this;
  }

  Complex& operator-=(const double& other) {
    m_real -= other;
    return *this;
  }

  Complex& operator*=(const double& other) {
    m_real *= other;
    m_imag *= other;
    return *this;
  }

  operator double() {
    if (!m_imag) {
      throw "The imaginary part is not zero.";
    }

    return m_real;
  }

  operator int() {
    if (!m_imag) {
      throw "The imaginary part is not zero.";
    }

    return int(m_real);
  }

  friend istream& operator>>(istream& is, Complex& that) {
    char buff[50];
    is >> buff;

    sscanf(buff, "%lf+%lfj", &that.m_real, &that.m_imag);

    return is;
  }

  friend ostream& operator<<(ostream& os, const Complex& that) {
    if (that.m_imag == 0 && that.m_real != 0) {
      os << that.m_real;
    } else if (that.m_imag != 0 && that.m_real == 0) {
      os << that.m_imag << 'j';
    } else if (that.m_imag == 0 && that.m_real == 0) {
      os << 0;
    } else {
      os << that.m_real;
      if (that.m_imag < 0) {
        os << that.m_imag;
      } else {
        os << '+' << that.m_imag;
      }
      os << 'j';
    }
    return os;
  }

 private:
  double m_real;
  double m_imag;
};

int main() {
  Complex arr(1, 2);
  Complex b;
  cout << arr << endl;
  cin >> b;
  cout << arr + b << endl;
  cout << arr * b << endl;

  return 0;
} */
/* #include <cstdlib>
#include <ctime>
#include <iostream>

class ArrayAlg {
 public:
  template <class T>
  static T sum(T *arr, size_t len) {
    T sum = T();
    for (int i = 0; i < len; ++i) {
      sum += *(arr + i);
    }
    return sum;
  }

  template <class T>
  static T max(T *arr, size_t len) {
    T max = *arr;
    for (int i = 0; i < len; ++i) {
      if (*(arr + i) > max) {
        max = *(arr + i);
      }
    }

    return max;
  }

  template <class T>
  static void sort(T *arr, size_t len) {
    for (int i = 0; i < len - 1; ++i) {
      for (int j = 0; j < len - i - 1; ++j) {
        if (*(arr + j) > *(arr + j + 1)) {
          std::swap(*(arr + j), *(arr + j + 1));
        }
      }
    }
  }
};

int main() {
  srand(time(nullptr));
  int arr[10] = {0};
  for (int i = 0; i < 10; ++i) {
    arr[i] = rand();
    std::cout << arr[i] << ' ';
  }
  std::cout << '\n';

  std::cout << ArrayAlg::max(arr, 10) << '\n';
  std::cout << ArrayAlg::sum(arr, 10) << '\n';

  ArrayAlg::sort(arr, 10);

  for (int i = 0; i < 10; ++i) {
    std::cout << arr[i] << ' ';
  }
  std::cout << '\n';

  return 0;
} */
/* #include <iostream>

int main() {
  int arr[10] = {1, 2 ,3 ,4 ,5 ,6 ,7 ,8, 9, 10};
  for (const int elem : arr) {
    std::cout << elem << ' ';
  }
  return 0;
} */
/* #include <iostream>
#include <set>

using namespace std;

int main() {
  set<int> s1;

  s1.insert(1);
  s1.insert(5);
  s1.insert(3);
  s1.insert(7);
  s1.insert(6);
  s1.insert(8);
  s1.insert(10);

  pair<set<int>::iterator, set<int>::iterator> p = s1.equal_range(18);
  cout << *(p.first) << ' ' << *(p.second) << '\n';

  return 0;
} */
/* #include <iostream>
#include <map>

using namespace std;

class Student {
 public:
  int id;
  string name;

  Student() {}

  Student(int id, string name) : id(id), name(name) {}
};

int main() {
  map<int, Student> stus;

  Student s1(1, "小李");
  Student s2(2, "小王");
  Student s3(3, "小田");
  stus.insert(pair<int, Student>(s1.id, s1));
  stus.insert(map<int, Student>::value_type(s2.id, s2));
  stus[s3.id] = s3;

  for (map<int, Student>::iterator it = stus.begin(); it != stus.end(); ++it) {
    auto pr = *it;
    auto key = pr.first;
    auto value = pr.second.name;
    cout << key << ": " << value << endl;
  }

  return 0;
} */
/* #include <iostream>
#include <map>

using namespace std;

int main() {
  map<int, string> mapS;

  mapS.insert(pair<int, string>(3, "小张"));
  mapS.insert(pair<int, string>(4, "小王"));
  mapS.insert(pair<int, string>(5, "小赵"));
  mapS.insert(map<int, string>::value_type(6, "小周"));

  cout << mapS.at(3) << endl;

  return 0;
} */
/* #include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<int> vi = {1, 2, 3, 4, 5};
  cout << vi.at(3) << endl;
  return 0;
} */
/* #include <deque>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

using namespace std;

int main() {
  vector<vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  return 0;
} */
/* #include <iostream>
#include <stack>

using namespace std;

int main() {
  stack<int> si;

  si.push(1);
  si.push(2);
  si.push(3);
  si.push(4);
  si.push(5);

  cout << si.size() << endl;

  while (!si.empty()) {
    cout << si.top() << ' ';
    si.pop();
  }

  return 0;
} */
/* #include <deque>
#include <iostream>

using namespace std;

int main() {
  deque<int> di;

  for (int i = 0; i < 10; ++i) {
    di.push_front(i);
  }

  for (int i = 0; i < 10; ++i) {
    di.push_back(10 * i);
  }

  while (!di.empty()) {
    cout << di.back() << ' ';
    di.pop_back();
  }

  return 0;
} */
/* #include <iostream>
#include <queue>

using namespace std;

int main() {
  queue<int> qi;

  for (int i = 0; i < 10; ++i) {
    qi.push(i);
  }

  while (!qi.empty()) {
    cout << qi.front() << ' ';
    qi.pop();
  }

  return 0;
} */
/* #include <algorithm>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

using namespace std;

void test01() {
  vector<vector<int>> arr = {
      {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};

  for (auto it = arr.begin(); it != arr.end(); ++it) {
    for (auto iti = (*it).begin(); iti != (*it).end(); ++iti) {
      cout << (*iti) << ' ';
    }
    cout << '\n';
  }

  auto it = find(arr[0].begin(), arr[0].end(), 2);

  *(it) = 3;

  for (auto it = arr.begin(); it != arr.end(); ++it) {
    for (auto iti = (*it).begin(); iti != (*it).end(); ++iti) {
      cout << (*iti) << ' ';
    }
    cout << '\n';
  }
}

void test02() {
  stack<int> s;

  for (int i = 0; i < 10; ++i) {
    s.push(i);
  }

  while (!s.empty()) {
    cout << s.top() << ' ';
    s.pop();
  }
}

void test03() {
  deque<int> d;

  for (int i = 0; i < 10; ++i) {
    d.push_front(i);
  }

  for (int i = 10; i < 20; ++i) {
    d.push_back(i);
  }

  for (int i = 0; i < 20; ++i) {
    cout << d[i] << ' ';
  }
  cout << '\n';

  less<int> le;
  sort(d.begin(), d.end(), le);
  for (int i = 0; i < 20; ++i) {
    cout << d[i] << ' ';
  }
  cout << '\n';
}

void test04() {
  list<int> ls;

  for (int i = 0; i < 10; ++i) {
    ls.push_front(i);
  }

  for (int i = 0; i < 20; ++i) {
    ls.push_back(i);
  }

  for (auto it = ls.begin(); it != ls.end(); ++it) {
    cout << *it << ' ';
  }
  cout << '\n';

  less<int> le;
  ls.sort(le);

  for (auto it = ls.begin(); it != ls.end(); ++it) {
    cout << *it << ' ';
  }
  cout << '\n';

  ls.unique();

  for (auto it = ls.begin(); it != ls.end(); ++it) {
    cout << *it << ' ';
  }
  cout << '\n';

  list<int> lst;

  lst.splice(lst.begin(), ls, ++ls.begin(), --ls.end());

  for (auto it = lst.begin(); it != lst.end(); ++it) {
    cout << *it << ' ';
  }
}

void test05() {
  queue<int, list<int>> q;

  for (int i = 0; i < 10; ++i) {
    q.push(i);
  }

  while (!q.empty()) {
    cout << q.front() << ' ';
    q.pop();
  }
}

void test06() {
  priority_queue<int, vector<int>, less<int>> pq;

  for (int i = 0; i < 10; ++i) {
    int num = rand() % 50 + 1;
    cout << num << ' ';
    pq.push(num);
  }
  cout << '\n';

  while (!pq.empty()) {
    cout << pq.top() << ' ';
    pq.pop();
  }
}

void test07() {
  set<int, greater<int>> s;
  for (int i = 0; i < 9; ++i) {
    int num = rand() % 30 + 1;
    cout << num << ' ';
    s.insert(num);
  }
  s.insert(40);
  cout << '\n';

  for (auto it = s.begin(); it != s.end(); ++it) {
    cout << *it << ' ';
  }
  cout << '\n';

  auto it = s.find(40);
  cout << *(it) << '\n';
}

void test08() {
  set<int> s1;

  s1.insert(1);
  s1.insert(5);
  s1.insert(3);
  s1.insert(7);
  s1.insert(6);
  s1.insert(8);
  s1.insert(10);

  auto p = s1.equal_range(5);
  cout << *(p.first) << ' ' << *(p.second) << '\n';
}

void test09() {
  map<int, string> mapS;
  mapS.insert(pair<int, string>(3, "小李"));
  mapS.insert(map<int, string>::value_type(1, "小王"));
  mapS[2] = "小田";

  int key = 5;
  string name = "小赵";
  pair<int, string> p(key, name);
  mapS.insert(p);
  map<int, string>::value_type v(6, "小周");
  mapS.insert(v);

  cout << (*(mapS.find(1))).first << '\n';
  cout << mapS.at(1) << '\n';
}

void test10() {
  map<int, string> mapS;
  mapS.insert(pair<int, string>(1, "小李"));
  mapS.insert(map<int, string>::value_type(2, "小王"));
  mapS[3] = "小田";
  int key = 4;
  string name = "小赵";
  pair<int, string> p(key, name);
  mapS.insert(p);
  map<int, string>::value_type v(5, "小周");
  mapS.insert(v);
  cout << (*mapS.find(3)).second << endl;
  cout << mapS.at(3) << endl;
}

int main() {
  srand(time(nullptr));
  test10();
  return 0;
} */
/* #include <iostream>

template <typename T>
void bubble_sort(T *arr, int len) {
  for (int i = 0; i < len - 1; ++i) {
    for (int j = 0; j < len - i - 1; ++j) {
      if (arr[j + 1] > arr[j]) {
        swap(arr[j + 1], arr[j]);
      }
    }
  }
}

template <typename T>
void insertion_sort(T *arr, int len) {
  int i, j;
  T key = T();
  for (int i = 1; i < len; ++i) {
    key = arr[i];
    for (int j = i - 1; j > 0 && arr[j] > key; --j) {
      arr[j + 1] = arr[j];
    }
    arr[j + 1] = key;
  }
}

template <typename T>
void selection_sort(T *arr, int len) {
  int min_index;
  for (int i = 0; i < len - 1; ++i) {
    min_index = i;
    for (int j = i + 1; j < len; ++j) {
      if (arr[j] < arr[min_index]) {
        min_index = j;
      }
    }
    swap(arr[i], arr[min_index]);
  }
} */
/* #include <iostream>

using namespace std;

void selection_sort(int *arr, int len) {
  for (int i = 0; i < len - 1; ++i) {
    int min_index = i;
    for (int j = i + 1; j < len; ++j) {
      if (arr[j] < arr[min_index]) {
        min_index = j;
      }
    }
    swap(arr[min_index], arr[i]);
  }
}

void insertion_sort(int *arr, int len) {
  int i, j, key;
  for (i = 1; i < len; ++i) {
    key = arr[i];
    for (j = i - 1; j >= 0 && arr[j] > key; --j) {
      arr[j + 1] = arr[j];
    }
    arr[j + 1] = key;
  }
} */
/* #include <iostream>

using namespace std;

void bubble_sort(int *arr, int len) {
  for (int i = 0; i < len - 1; ++i) {
    for (int j = 0; j < len - 1 - i; ++j) {
      if (arr[j] > arr[j + 1]) {
        swap(arr[j], arr[j + 1]);
      }
    }
  }
}

void insertion_sort(int *arr, int len) {
  int i, j, key;
  for (i = 1; i < len; ++i) {
    key = arr[i];
    for (j = i - 1; j >= 0 && arr[j] > key; --j) {
      arr[j + 1] = arr[j];
    }
    arr[j + 1] = key;
  }
}

void selection_sort(int *arr, int len) {
  for (int i = 0; i < len - 1; ++i) {
    int min_index = i;
    for (int j = i + 1; j < len; ++j) {
      if (arr[j] < arr[min_index]) {
        min_index = j;
      }
    }
    swap(arr[i], arr[min_index]);
  }
} */
/* #include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

template <class T>
void quick_sort(T *arr, int left, int right) {
  if (left >= right) {
    return;
  }

  T x = arr[right];
  int i = left - 1, j = right + 1;
  while (i < j) {
    do {
      ++i;
    } while (arr[i] < x);

    do {
      --j;
    } while (arr[j] > x);

    if (i < j) {
      swap(arr[i], arr[j]);
    }
  }

  quick_sort(arr, left, i - 1);

  quick_sort(arr, i, right);
}

int main() {
  srand(time(nullptr));
  int arr[10] = {0};

  for (int i = 0; i < 10; ++i) {
    arr[i] = rand() % 30 + 1;
    printf("%d ", arr[i]);
  }
  putchar('\n');

  quick_sort(arr, 0, 9);

  for (int i = 0; i < 10; ++i) {
    printf("%d ", arr[i]);
  }
  putchar('\n');

  return 0;
} */
/* #include <iostream>
using namespace std;

template <typename T>
class DList {
 protected:
  class Node {
   public:
    T data;
    Node *prev;
    Node *next;
    Node(T value) : data(value), prev(nullptr), next(nullptr) {}
  };

  Node *head;
  Node *tail;

 public:
  DList() : head(nullptr), tail(nullptr) {}
  ~DList() { clear(); }

  void clear() {
    Node *current = head;
    while (current) {
      Node *next = current->next;
      delete current;
      current = next;
    }
    head = tail = nullptr;
  }

  virtual void insert(const T &value) {
    Node *new_node = new Node(value);

    if (!head) {
      head = tail = new_node;
    } else {
      tail->next = new_node;
      new_node->prev = tail;
      tail = new_node;
    }
  }

  Node *find(const T &value) const {
    Node *current = head;

    while (current) {
      if (current->data == value) {
        return current;
      }
      current = current->next;
    }

    return nullptr;
  }

  void erase(const T &value) {
    Node *current = find(value);

    if (!current) {
      return;
    }

    if (current == head) {
      head = current->next;
      if (head) {
        head->prev = nullptr;
      } else {
        tail = nullptr;
      }
    } else {
      current->prev->next = current->next;
      if (current->next) {
        current->next->prev = current->prev;
      } else {
        tail = current->prev;
      }
    }

    delete current;
  }

  virtual void print_front() const {
    if (!head) {
      cout << "List is empty" << endl;
      return;
    }

    Node *current = head;

    while (current) {
      cout << current->data << ' ';
      current = current->next;
    }

    cout << '\n';
  }

  bool modify(const T &old_value, const T &new_value) {
    Node *node_to_modify = find(old_value);

    if (!node_to_modify) {
      return false;
    }

    node_to_modify->data = new_value;
    return true;
  }
};

template <typename T>
class OrderedList : public DList<T> {
 public:
  void insert(const T &value) override {
    typename DList<T>::Node *new_node = new typename DList<T>::Node(value);

    if (!this->head) {
      this->head = this->tail = new_node;
    } else {
      typename DList<T>::Node *current = this->head;

      while (current && current->data < value) {
        current = current->next;
      }

      if (!current) {
        this->tail->next = new_node;
        new_node->prev = this->tail;
        this->tail = new_node;
      } else if (current = this->head) {
        new_node->next = this->head;
        this->head->prev = new_node;
        this->head = new_node;
      } else {
        current->prev->next = new_node;
        new_node->prev = currenr->prev;
        new_node->next = current;
        current->prev = new_node;
      }
    }
  }
};

class Student {
 public:
  int id;
  string name;
  double score;
  Student(int id, string name, double score)
      : id(id), name(name), score(score) {}

  bool operator==(const Student &other) { return id == other.id; }
  bool operator<(const Student &other) { return id < other.id; }
  bool operator<=(const Student &other) { return id <= other.id; }
  bool operator>(const Student &other) { return id > other.id; }
  bool operator>=(const Student &other) { return id >= other.id; }

  friend ostream &operator<<(ostream &os, const Student &self) {
    return os << "ID: " << self.id << " Name: " << self.name
              << "Score: " << self.score << '\n';
  }
};

int main() {
  OrderedList<Student> students;
  Student student1 = Student(1, "小王", 34);
  Student student2 = Student(2, "小陈", 56);
  Student student3 = Student(3, "小田", 45);
  Student student4 = Student(4, "小李", 21);

  students.insert(student1);
  students.insert(student2);
  students.insert(student3);
  students.insert(student4);

  students.print_front();

  Student new_student1 = Student(1, "小王", 40);
  students.modify(student1, new_student1);

  students.print_front();

  students.erase(new_student1);

  students.print_front();

  return 0;
} */
/* #include <cstdlib>
#include <ctime>
#include <iostream>

template <class T>
void quick_sort(T* arr, int left, int right) {
  if (left >= right) {
    return;
  }

  int i = left - 1, j = right + 1;

  T x = arr[left];

  while (i < j) {
    do {
      ++i;
    } while (arr[i] < x);

    do {
      --j;
    } while (arr[j] > x);

    if (i < j) {
      std::swap(arr[i], arr[j]);
    }
  }

  quick_sort(arr, left, j);
  quick_sort(arr, j + 1, right);
}

int main() {
  srand(time(nullptr));
  int arr[10] = {0};

  for (int i = 0; i < 10; ++i) {
    arr[i] = rand() % 10 + 1;
    printf("%d ", arr[i]);
  }
  putchar('\n');

  quick_sort(arr, 0, 9);

  for (int i = 0; i < 10; ++i) {
    printf("%d ", arr[i]);
  }
  putchar('\n');

  return 0;
} */
/* #include <iostream>

using namespace std;

template <class T>
void quick_sort(T *arr, int left, int right) {
  if (left >= right) {
    return;
  }

  int i = left - 1, j = right + 1;

  T x = arr[left];

  while (i < j) {
    do {
      ++i;
    } while (arr[i] < x);

    do {
      --j;
    } while (arr[j] > x);

    if (i < j) {
      swap(arr[i], arr[j]);
    }
  }

  quick_sort(arr, left, j);
  quick_sort(arr, j + 1, right);
}

template <class T>
void merge_sort(T *arr, int left, int right) {
  if (left >= right) {
    return;
  }

  int mid = left + (right - left) / 2;

  merge_sort(arr, left, mid);
  merge_sort(arr, mid + 1, right);

  int k = 0, i = left, j = mid + 1;

  T *temp = new T[right - left + 1];

  while (i <= mid && j <= right) {
    if (arr[i] <= arr[j]) {
      temp[k++] = arr[i++];
    } else {
      temp[k++] = arr[j++];
    }
  }

  while (i <= mid) {
    temp[k++] = arr[i++];
  }

  while (j <= right) {
    temp[k++] = arr[j++];
  }

  for (int i = left, j = 0; i <= right; ++i, ++j) {
    arr[i] = temp[j];
  }

  delete[] temp;
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

template <class T>
void quick_sort(T *arr, int left, int right) {
  if (left >= right) {
    return;
  }

  int i = left - 1, j = right + 1;

  T x = arr[left];

  while (i < j) {
    do {
      ++i;
    } while (arr[i] < x);

    do {
      --j;
    } while (arr[j] > x);

    if (i < j) {
      swap(arr[i], arr[j]);
    }
  }

  quick_sort(arr, left, j);
  quick_sort(arr, j + 1, right);
}

template <class T>
void merge_sort(T *arr, int left, int right) {
  if (left >= right) {
    return;
  }

  int mid = left + (right - left) / 2;

  merge_sort(arr, left, mid);
  merge_sort(arr, mid + 1, right);

  int k = 0, i = left, j = mid + 1;

  T *temp = new T[right - left + 1];

  while (i <= mid && j <= right) {
    if (arr[i] <= arr[j]) {
      temp[k++] = arr[i++];
    } else {
      temp[k++] = arr[j++];
    }
  }

  while (i <= mid) {
    temp[k++] = arr[i++];
  }

  while (j <= right) {
    temp[k++] = arr[j++];
  }

  for (int i = left, j = 0; i < right; ++i, ++j) {
    arr[i] = temp[j];
  }

  delete[] temp;
}

int n, m;
int q[N];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &q[i]);
  }

  while (m--) {
    int x;
    scanf("%d", &x);

    int l = 0, r = n - 1;

    while (l < r) {
      int mid = l + (r - l) / 2;
      if (q[mid] >= x) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }

    if (q[l] != x) {
      printf("%d %d\n", -1, -1);
    } else {
      printf("%d ", l);

      int l = 0, r = n - 1;

      while (l < r) {
        int mid = l + (r - l + 1) / 2;
        if (q[mid] <= x) {
          l = mid;
        } else {
          r = mid - 1;
        }
      }
      printf("%d\n", l);
    }
  }

  return 0;
} */
/* #include <iostream>
#include <vector>

using namespace std;

bool check(int num) {}

int binary_search(int left, int right) {
  while (left < right) {
    int mid = left + (right - left + 1);
    if (check(mid)) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }

  return left;
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

int n, m;
int q[N];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &q[i]);
  }

  while (m--) {
    int x;
    scanf("%d", &x);

    int l = 0, r = n - 1;

    while (l < r) {
      int mid = l + (r - l) / 2;
      if (q[mid] >= x) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }

    if (q[l] != x) {
      printf("%d %d\n", -1, -1);
    } else {
      printf("%d ", l);

      int l = 0, r = n - 1;
      while (l < r) {
        int mid = l + (r - l + 1) / 2;

        if (q[mid] <= x) {
          l = mid;
        } else {
          r = mid - 1;
        }
      }

      printf("%d\n", l);
    }
  }

  return 0;
} */
/* #include <iostream>

using namespace std;

template <class T>
void bubble_sort(T *arr, int len) {
  for (int i = 0; i < len - 1; ++i) {
    for (int j = 0; j < len - 1 - i; ++j) {
      if (arr[j] > arr[j + 1]) {
        swap(arr[j], arr[j + 1]);
      }
    }
  }
}

template <class T>
void selection_sort(T *arr, int len) {
  int min_index;
  for (int i = 0; i < len - 1; ++i) {
    min_index = i;
    for (int j = i + 1; j < len; ++j) {
      if (arr[min_index] > arr[j]) {
        min_index = j;
      }
    }
    swap(arr[min_index, i]);
  }
}

template <class T>
void insertion_sort(T *arr, int len) {
  int i, j;
  T key;
  for (i = 1; i < len; ++i) {
    key = arr[i];
    for (j = i - 1; j >= 0 && key > arr[j]; --j) {
      arr[j + 1] = arr[j];
    }
    arr[j + 1] = key;
  }
}

template <class T>
void quick_sort(T *arr, int left, int right) {
  if (left >= right) {
    return;
  }

  int i = left - 1, j = right + 1;

  T x = arr[left];

  while (i < j) {
    do {
      ++i;
    } while (arr[i] < x);

    do {
      --j;
    } while (arr[j] > x);

    if (i < j) {
      swap(arr[i], arr[j]);
    }
  }

  quick_sort(arr, left, j);
  quick_sort(arr, j + 1, right);
}

template <class T>
void merge_sort(T *arr, int left, int right) {
  if (left >= right) {
    return;
  }

  int mid = left + (right - left) / 2;

  merge_sort(arr, left, mid);
  merge_sort(arr, mid + 1, right);

  int i = left, j = mid + 1, k = 0;

  T *temp = new T[right - left + 1];

  while (i <= mid && j <= right) {
    if (arr[i] <= arr[j]) {
      temp[k++] = arr[i++];
    } else {
      temp[k++] = arr[j++];
    }
  }

  while (i <= mid) {
    temp[k++] = arr[i++];
  }

  while (j <= right) {
    temp[k++] = arr[j++];
  }

  for (i = left, j = 0; i <= right; ++i, ++j) {
    arr[i] = temp[j];
  }

  delete[] temp;
}

int main() {
  int x = 5;
  int arr[10] = {1, 8, 9, 5, 5, 5, 2, 2, 5, 10};

  int l = 0, r = 9;

  merge_sort<int>(arr, l, r);

  for (int i = 0; i < 10; ++i) {
    cout << arr[i] << ' ';
  }
  cout << endl;

  while (l < r) {
    int mid = l + (r - l + 1) / 2;

    if (arr[mid] <= x) {
      l = mid;
    } else {
      r = mid - 1;
    }
  }

  cout << r << endl;

  return 0;
} */
/* #include <iostream>

using namespace std;

int main() {
  double x;
  cin >> x;

  double l = 0, r = x;

  for (int i = 0; i < 100; ++i){
    double mid = (l + r) / 2;
    if (mid * mid >= x) {
      r = mid;
    } else {
      l = mid;
    }
  }

  cout << l << endl;

  return 0;
} */
/* #include <iostream>

using namespace std;

int main() {
  double x;
  cin >> x;

  double l = 0, r = x;

  while (r - l > 1e-8) {
    double mid = (r + l) / 2;
    if (mid * mid >= x) {
      r = mid;
    } else {
      l = mid;
    }
  }

  cout << l << endl;
  return 0;
} */
/* #include <iostream>

using namespace std;

template <class T>
void quick_sort(T* arr, int left, int right) {
  if (left >= right) {
    return;
  }

  int i = left - 1, j = right + 1;

  T x = arr[left];

  while (i < j) {
    do {
      ++i
    } while (arr[i] < x);

    do {
      --j
    } while (arr[j] > x);

    if (i < j) {
      swap(arr[i], arr[j]);
    }

    quick_sort(arr, left, j);
    quick_sort(arr, j + 1, right);
  }
}

template<class T>
void merge_sort(T*arr, int left, int right) {
  if (left >= right) {
    return;
  }

  int mid = l + (r - l) / 2;

  merge_sort(arr, left, mid);
  merge_sort(arr, mid + 1, right);


} */
/* #include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

template <class T>
void bubble_sort(T* arr, int len) {
  for (int i = 0; i < len - 1; ++i) {
    for (int j = 0; j < len - 1 - i; ++j) {
      if (arr[j] > arr[j + 1]) {
        swap(arr[j], arr[j + 1]);
      }
    }
  }
}

template <class T>
void quick_sort(T* arr, int left, int right) {
  if (left >= right) {
    return;
  }

  int i = left - 1, j = right + 1;

  T x = arr[left];

  while (i < j) {
    do {
      ++i;
    } while (arr[i] < x);

    do {
      --j;
    } while (arr[j] > x);

    if (i < j) {
      swap(arr[i], arr[j]);
    }
  }

  quick_sort(arr, left, j);
  quick_sort(arr, j + 1, right);
}

template <class T>
void merge_sort(T* arr, int left, int right) {
  if (left >= right) {
    return;
  }

  int mid = left + (right - left) / 2;

  merge_sort(arr, left, mid);
  merge_sort(arr, mid + 1, right);

  int i = left, j = mid + 1, k = 0;
  T* temp = new T[right - left + 1];

  while (i <= mid && j <= right) {
    if (arr[i] <= arr[j]) {
      temp[k++] = arr[i++];
    } else {
      temp[k++] = arr[j++];
    }
  }

  while (i <= mid) {
    temp[k++] = arr[i++];
  }

  while (j <= right) {
    temp[k++] = arr[j++];
  }

  for (i = left, j = 0; i <= right; ++i, ++j) {
    arr[i] = temp[j];
  }

  delete[] temp;
}

int main() {
  int x = 5;

  int arr[10] = {1, 2, 3, 4, 5, 5, 5, 5, 10, 12};

  int l = 0, r = 9;
  while (l < r) {
    int mid = l + (r - l + 1) / 2;
    if (arr[mid] <= x) {
      l = mid;
    } else {
      r = mid - 1;
    }
  }
  cout << r << '\n';

  return 0;
} */
/* #include <array>
#include <iostream>
#include <vector>

using namespace std;

template <class T>
void quick_sort(T* arr, int left, int right) {
  if (left >= right) {
    return;
  }

  T x = arr[left];
  int i = left - 1, j = right + 1;

  while (i < j) {
    do {
      ++i;
    } while (arr[i] < x);

    do {
      --j;
    } while (arr[j] > x);

    if (i < j) {
      swap(arr[i], arr[j]);
    }
  }

  quick_sort(arr, left, j);
  quick_sort(arr, j + 1, right);
}

template <class T>
void merge_sort(T* arr, int left, int right) {
  if (left >= right) {
    return;
  }

  int mid = left + (right - left) / 2;

  merge_sort(arr, left, mid);
  merge_sort(arr, mid + 1, right);

  int i = left, j = mid, k = 0;

  vector<T> temp;

  while (i <= mid && j <= right) {
    if (arr[i] <= arr[j]) {
      temp[k++] = arr[i++];
    } else {
      temp[k++] = arr[j++];
    }
  }

  while (i <= mid) {
    temp[k++] = arr[i++];
  }

  while (j <= right) {
    temp[k++] = arr[j++];
  }

  for (int i = left, j = 0; i <= right; ++i, ++j) {
    arr[i] = temp[k];
  }
}

int main() {
  array<int, 5> myArray = {1, 2, 3, 4, 5};
  for (const int element : myArray) {
    cout << element << ' ';
  }
  cout << endl;
  return 0;
}
 */
/* #include <iostream>

using namespace std;

const int N = 100010;

int n, m;
int q[N];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &q[i]);
  }

  while (m--) {
    int x;
    scanf("%d", &x);

    int l = 0, r = n - 1;

    while (l < r) {
      int mid
    }
  }
} */
/* #include <iostream>

using namespace std;

int main() {
  double x;
  cin >> x;

  double l  = 0, r = x;

  while (r - l > 1e-8) {
    double mid = l + (r - l) /2;

    if (mid * mid >= x) {
      r = mid;
    } else {
      l = mid;
    }
  }

  cout << l << endl;

  return 0;
} */
/* #include <iostream>

using namespace std;

int main() {
  double x;
  cin >> x;

  double l = 0, r = x;

  while (r - l > 1e-8) {
    double mid = (l + r) / 2;
    if (mid * mid >= x) {
      r = mid;
    } else {
      l = mid;
    }
  }

  cout << l << endl;

  return 0;
} */
/* #include <iostream>
#include <vector>

using namespace std;

vector<int> add(const vector<int>& v1, const vector<int>& v2) {
  vector<int> result;

  int t = 0;
  size_t maxSize = max(v1.size(), v2.size());

  for (size_t i = 0; i < maxSize; ++i) {
    if (i < v1.size()) {
      t += v1[i];
    }

    if (i < v2.size()) {
      t += v2[i];
    }

    result.push_back(t % 10);

    t /= 10;
  }

  if (t) {
    result.push_back(t);
  }
}

int main() {
  string n1, n2;
  vector<int> digits1, digits2;

  cin >> n1 >> n2;

  for (int i = n1.size() - 1; i >= 0; --i) {
    digits1.push_back(n1[i] - '0');
  }

  for (int i = n2.size() - 1; i >= 0; --i) {
    digits2.push_back(n2[i] - '0');
  }

  vector<int> resultDigits = add(digits1, digits2);

  for (int i = resultDigits.size() - 1; i >= 0; --i) {
    printf("%d", resultDigits[i]);
  }

  return 0;
} */
/* #include <iostream>
#include <vector>

using namespace std;

vector<int> add(const vector<int> &v1, const vector<int> &v2) {
  vector<int> result;

  int carry = 0;

  size_t maxSize = max(v1.size(), v2.size());

  for (size_t i = 0; i < maxSize; ++i) {
    if (i < v1.size()) {
      carry += v1[i];
    }

    if (i < v2.size()) {
      carry += v2[i];
    }

    result.push_back(carry % 10);

    carry /= 10;
  }

  if (carry) {
    result.push_back(carry);
  }

  return result;
}

bool cmp(const vector<int> &v1, const vector<int> &v2) {
  if (v1.size() != v2.size()) {
    return v1.size() > v2.size();
  }

  for (int i = v1.size() - 1; i >= 0; --i) {
    if (v1[i] != v2[i]) {
      return v1[i] > v2[i];
    }

    return true;
  }
}

vector<int> sub(const vector<int> &v1, const vector<int> &v2) {
  vector<int> result;

  int carry = 0;

  for (size_t i = 0; i < v1.size(); ++i) {
    int diff = v1[i] - carry;
    if (i < v2.size()) {
      diff -= v2[i];
    }

    result.push_back((diff + 10) % 10);

    carry = (diff < 0) ? 1 : 0;
  }

  while (result.size() > 1 && result.back() == 0) {
    result.pop_back();
  }

  return result;
}

int main() {} */
/* #include <iostream>
#include <vector>

using namespace std;

template <class T>
void quick_sort(vector<T> arr, int left, int right) {
  if (left >= right) {
    return;
  }

  T x = arr[left];
  int i = left - 1, j = right + 1;

  while (i < j) {
    do {
      ++i;
    } while (arr[i] < x);

    do {
      --j;
    } while (arr[j] > x);

    if (i < j) {
      swap(arr[i], arr[j]);
    }
  }

  quick_sort(arr, left, j);
  quick_sort(arr, j + 1, right);
}

template <class T>
void merge_sort(vector<int> arr, int left, int right) {
  if (left >= right) {
    return;
  }

  int mid = left + (right - left) / 2;

  merge_sort(arr, left, mid);
  merge_sort(arr, mid + 1, right);

  int i = left, j = mid + 1, k = 0;

  vector<T> temp;

  while (i <= mid && j <= right) {
    if (arr[i] <= arr[j]) {
      temp[k++] = arr[i++];
    } else {
      temp[k++] = arr[j++];
    }
  }

  while (i <= mid) {
    temp[k++] = arr[i++];
  }

  while (j <= right) {
    temp[k++] = arr[j++];
  }

  for (int i = left, j = 0; i <= right; ++i, ++j) {
    arr[i] = temp[j];
  }
}

vector<int> add(vector<int> &v1, vector<int> &v2) {
  vector<int> result;

  int carry = 0;
  size_t maxSize = max(v1.size(), v2.size());
  for (size_t i = 0; i < maxSize; ++i) {
    if (i < v1.size()) {
      carry += v1[i];
    }

    if (i < v2.size()) {
      carry += v2[i];
    }

    result.push_back(carry % 10);

    carry /= 10;
  }

  if (carry) {
    result.push_back(carry);
  }

  return result;
}

bool cmp(vector<int> &v1, vector<int> &v2) {
  if (v1.size() != v2.size()) {
    return v1.size() > v2.size();
  }

  for (int i = v1.size() - 1; i >= 0; --i) {
    if (v1[i] != v2[i]) {
      return v1[i] > v2[i];
    }
  }

  return true;
}

vector<int> sub(vector<int> &v1, vector<int> &v2) {
  vector<int> result;

  int carry = 0;

  for (size_t i = 0; i < v1.size(); --i) {
    int diff = v1[i] - carry;

    if (i < v2.size()) {
      diff -= v2[i];
    }

    result.push_back((diff + 10) % 10);

    carry = (diff < 0) ? 1 : 0;
  }

  while (result.size() > 1 && !result.back()) {
    result.pop_back();
  }
} */
/* #include <iostream>
#include <vector>

using namespace std;

template <class T>
void bubble_sort(T *arr, int len) {
  for (int i = 0; i < len - 1; ++i) {
    for (int j = 0; j < len - 1 - i; ++j) {
      if (arr[j] > arr[j + 1]) {
        swap(arr[j], arr[j + 1]);
      }
    }
  }
}

template <class T>
void insertion_sort(T *arr, int len) {
  int i = 0, j = 0;

  T key = T();

  for (int i = 1; i < len; ++i) {
    key = arr[i];
    for (int j = i - 1; j >= 0 && key > arr[j]; --j) {
      arr[j + 1] = arr[j];
    }
    arr[j + 1] = key;
  }
}

template <class T>
void selection_sort(T *arr, int len) {
  int min_index = 0;

  for (int i = 0; i < len - 1; ++i) {
    min_index = i;

    for (int j = i + 1; j < len; ++j) {
      if (arr[j] < arr[min_index]) {
        min_index = j;
      }
    }

    swap(arr[min_index], arr[i]);
  }
}

template <class T>
void quick_sort(T *arr, int left, int right) {
  if (left >= right) {
    return;
  }

  T x = arr[left];
  int i = left - 1, j = right + 1;

  while (i < j) {
    do {
      ++i;
    } while (arr[i] < x);

    do {
      --j;
    } while (arr[j] > x);

    if (i < j) {
      swap(arr[i], arr[j]);
    }
  }

  quick_sort(arr, left, j);
  quick_sort(arr, j + 1, right);
}

template <class T>
void merge_sort(T *arr, int left, int right) {
  if (left >= right) {
    return;
  }

  int mid = left + (right - left) / 2;

  merge_sort(arr, left, mid);
  merge_sort(arr, mid + 1, right);

  int i = left, j = mid + 1, k = 0;

  T *temp = new T[right - left + 1];

  while (i <= mid && j <= right) {
    if (arr[i] <= arr[j]) {
      temp[k++] = arr[i++];
    } else {
      temp[k++] = arr[j++];
    }
  }

  while (i <= mid) {
    temp[k++] = arr[i++];
  }

  while (j <= right) {
    temp[k++] = arr[j++];
  }

  for (i = left, j = 0; i <= right; ++i, ++j) {
    arr[i] = temp[j];
  }

  delete[] temp;
}

vector<int> add(const vector<int> &v1, const vector<int> &v2) {
  vector<int> result;

  int carry = 0;
  size_t maxSize = max(v1.size(), v2.size());
  for (size_t i = 0; i < maxSize; ++i) {
    if (i < v1.size()) {
      carry += v1[i];
    }

    if (i < v2.size()) {
      carry += v2[i];
    }

    result.push_back(carry % 10);

    carry /= 10;
  }

  if (carry) {
    result.push_back(carry);
  }

  return result;
}

bool cmp(const vector<int> &v1, const vector<int> &v2) {
  if (v1.size() != v2.size()) {
    return v1.size() > v2.size();
  }

  for (int i = v1.size(); i >= 0; --i) {
    if (v1[i] != v2[i]) {
      return v1[i] > v2[i];
    }
  }

  return true;
}

vector<int> sub(const vector<int> &v1, const vector<int> &v2) {
  vector<int> result;

  int carry = 0;
  for (int i = 0; i < v1.size(); ++i) {
    int diff = v1[i] - carry;

    if (i < v2.size()) {
      diff -= v2[i];
    }

    result.push_back((diff + 10) % 10);

    carry = (diff < 0) ? 1 : 0;
  }

  while (result.size() > 1 && result.back() == 0) {
    result.pop_back();
  }

  return result;
}

int main() { return 0; } */
/* #include <iostream>
#include <vector>

using namespace std;

vector<int> mul(const vector<int> n, int m) {
  vector<int> prod;

  int carry = 0;

  for (int i = 0; i < n.size()|| carry; ++i) {
    if (i < n.size()) {
      carry += n[i] * m;
    }

    prod.push_back(carry % 10);

    carry /= 10;
  }

  return prod;
}

int main() {
  string arr;
  int b;

  cin >> arr >> b;

  vector<int> c;

  for (int i = arr.size() - 1; i >= 0; --i) {
    c.push_back(arr[i] - '0');
  }

  c = mul(c, b);

  for (int i = c.size() - 1; i >= 0; --i) {
    printf("%d", c[i]);
  }

  cout << '\n';

  return 0;
} */
/* #include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> div(const vector<int> &num, int d, int &rem) {
  vector<int> quot;

  rem = 0;
  for (int i = num.size() - 1; i >= 0; --i) {
    rem = rem * 10 + num[i];
    quot.push_back(rem / d);
    rem %= d;
  }

  reverse(quot.begin(), quot.end());

  while (quot.size() > 1 && !quot.back()) {
    quot.pop_back();
  }

  return quot;
}

vector<int> div(const vector<int> &num, int d, int &rem) {
  vector<int> quot;

  rem = 0;
  for (int i = num.size() - 1; i >= 0; --i) {
    rem = rem * 10 + num[i];
    quot.push_back(rem / d);
    rem %= d;
  }

  reverse(quot.begin(), quot.end());

  while (quot.size() > 1 && !quot.back()) {
    quot.pop_back();
  }

  return quot;
}

int main() {
  string arr;
  int b;

  cin >> arr >> b;

  vector<int> A;
  for (int i = arr.size() - 1; i >= 0; --i) {  // 只能使用 int
    A.push_back(arr[i] - '0');
  }

  int r;
  auto C = div(A, b, r);

  for (int i = C.size() - 1; i >= 0; --i) {
    printf("%d", C[i]);
  }
  cout << endl << r << endl;
  return 0;
} */
/* #include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> div(const vector<int> &num, int d, int &rem) {
  vector<int> quot;

  int carry = 0;

  for (int i = num.size() - 1; i >= 0; --i) {
    rem = rem * 10 + num[i];
    quot.push_back(rem / d);
    rem %= d;
  }

  while (quot.size() > 1 && quot.back() == 0) {
    quot.pop_back();
  }

  return quot;
} */
/* #include <iostream>

using namespace std;

const int LEN = 100010;

int main() {
  int n, m;
  int arr[LEN], sum[LEN];

  scanf("%d%d", &n, &m);

  for (int i = 1; i <= n; ++i) {
    scanf("%d", &arr[i]);
  }

  for (int i = 1; i <= n; ++i) {
    sum[i] = sum[i - 1] + arr[i];
  }

  while (m--) {
    int left, right;
    scanf("%d%d", &left, &right);
    printf("%d\n", sum[right] - sum[left - 1]);
  }

  return 0;
} */
/* #include <iostream>

using namespace std;

const int LEN = 1000010;

int main() {
  int n, m;
  int arr[LEN] = {0}, sum[LEN] = {0};

  scanf("%d%d", &n, &m);

  for (int i = 1; i <= n; ++i) {
    scanf("%d", &arr[i]);
  }

  for (int i = 1; i <= n; ++i) {
    sum[i] = sum[i - 1] + arr[i];
  }

  while (m--) {
    int left, right;
    scanf("%d%d", &left, &right);
    printf("%d\n", sum[right] - sum[left - 1]);
  }

  return 0;
} */
/* #include <iostream>

using namespace std;

const int LEN = 100010;

int main() {
  int n, m;
  int arr[LEN], sum[LEN];

  scanf("%d%d", &n, &m);

  for (int i = 1; i <= n; ++i) {
    scanf("%d", &arr[i]);
  }

  for (int i = 1; i <= n; ++i) {
    sum[i] = sum[i - 1] + arr[i];
  }

  while (m--) {
    int left, right;
    scanf("%d%d", &left, &right);
    printf("%d\n", sum[right] - sum[left - 1]);
  }

  return 0;
} */
/* #include <iostream>

using namespace std;

const int SIZE = 110;

int main() {
  int n, m, q;

  scanf("%d%d%d", &n, &m, &q);

  int arr[SIZE][SIZE] = {0}, sum[SIZE][SIZE] = {0};

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &arr[i][j]);
      sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + arr[i][j];
    }
  }

  while (q--) {
    int x1, y1, x2, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    printf("%d\n", sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] +
                       sum[x1 - 1][x2 - 1]);
  }

  return 0;
} */
/* #include <iostream>
#include <vector>

using namespace std;

const int LEN = 100010;

int main() {
  int n, m;
  vector<int> arr(LEN), sum(LEN);

  scanf("%d%d", &n, &m);

  for (int i = 1; i <= n; ++i) {
    scanf("%d", &arr[i]);
  }

  for (int i = 1; i <= n; ++i) {
    sum[i] = sum[i - 1] + arr[i];
  }

  while (m--) {
    int left, right;
    scanf("%d%d", &left, &right);
    printf("%d\n", sum[right] - sum[left - 1]);
  }

  return 0;
} */
/* #include <iostream>
#include <vector>

using namespace std;

const int SIZE = 1010;

int main() {
  int n, m, q;

  scanf("%d%d%d", &n, &m, &q);

  vector<vector<int>> arr(SIZE, vector<int>(SIZE)),
      sum(SIZE, vector<int>(SIZE));

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &arr[i][j]);
      sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + arr[i][j];
    }
  }

  while (q--) {
    int x1, y1, x2, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    printf("%d\n", sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] +
                       sum[x1 - 1][y1 - 1]);
  }

  return 0;
} */
/* #include <iostream>
#include <vector>

using namespace std;

const int SIZE = 10001;

int main() {
  vector<vector<int>> arr(SIZE, vector<int>(SIZE)),
      sum(SIZE, vector<int>(SIZE));

  int n, m, q;

  scanf("%d%d%d", &n, &m, &q);

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &arr[i][j]);
      sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + arr[i][j];
    }
  }

  while (q--) {
    int x1, y1, x2, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    printf("%d\n", sum[x2][y2] - sum[x2][y1 - 1] - sum[x1 - 1][y2] +
                       sum[x1 - 1][y1 - 1]);
  }

  return 0;
} */
/* #include <iostream>
#include <vector>

using namespace std;

const int SIZE = 10010;

int main() {
  vector<vector<int>> arr(SIZE, vector<int>(SIZE)),
      sum(SIZE, vector<int>(SIZE));

  int n, m, q;

  scanf("%d%d%d", &n, &m, &q);

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &arr[i][j]);
      sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + arr[i][j];
    }
  }

  while (q--) {
    int x1, y1, x2, y2;

    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);

    printf("%d\n", sum[x2][y2] - sum[x2][y1 - 1] - sum[x1 - 1][y2] +
                       sum[x1 - 1][y1 - 1]);
  }

  return 0;
} */
/* #include <iostream>
#include <vector>

using namespace std;

const int SIZE = 10001;

int main() {
  vector<vector<int>> arr(SIZE, vector<int>(SIZE)),
      sum(SIZE, vector<int>(SIZE));

  int n, m, q;

  scanf("%d%d%d", &n, &m, &q);

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &arr[i][j]);
      sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + arr[i][j];
    }
  }

  while (q--) {
    int x1, y1, x2, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    printf("%d\n", sum[x2][y2] - sum[x2][y1 - 1] - sum[x1 - 1][y2] +
                       sum[x1 - 1][y1 - 1]);
  }

  return 0;
} */
/* #include <iostream>
#include <vector>

using namespace std;

const int SIZE = 1000;

int main() {
  vector<vector<int>> arr(SIZE, vector<int>(SIZE)),
      sum(SIZE, vector<int>(SIZE));

  int n, m, q;

  scanf("%d%d%d", &n, &m, &q);

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &arr[i][j]);
      sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + arr[i][j];
    }
  }

  while (q--) {
    int x1, y1, x2, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    printf("%d\n", sum[x2][y2] - sum[x2][y1 - 1] - sum[x1 - 1][y2] +
                       sum[x1 - 1][y1 - 1]);
  }

  return 0;
} */
/* #include <iostream>
#include <vector>

using namespace std;

const int LEN = 1000;

int main() {
  int n, m;
  vector<int> arr(LEN), sum(LEN);

  scanf("%d%d", &n, &m);

  for (int i = 1; i <= n; ++i) {
    scanf("%d", &arr[i]);
    sum[i] = sum[i - 1] + arr[i];
  }

  while (m--) {
    int left, right;
    scanf("%d%d", &left, &right);
    printf("%d\n", sum[right] - sum[left - 1]);
  }

  return 0;
} */
/* #include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> mul(const vector<int> &n, int m) {
  vector<int> prod;

  int carry = 0;

  for (int i = 0; i < n.size() || carry; ++i) {
    if (i < n.size()) {
      carry += n[i] * m;
    }

    carry /= 10;
  }

  return prod;
}

vector<int> div(const vector<int> &num, int d, int &rem) {
  vector<int> quot;

  rem = 0;

  for (int i = num.size() - 1; i >= 0; --i) {
    rem = rem * 10 + num[i];
    quot.push_back(rem / d);
    rem %= d;
  }

  reverse(quot.begin(), quot.end());

  while (quot.size() > 1 && quot.back() == 0) {
    quot.pop_back();
  }

  return quot;
}

int main() { return 0; } */
/* #include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int SIZE = 1010;

vector<int> div(const vector<int> &num, int d, int &rem) {
  vector<int> quot;

  rem = 0;

  for (int i = 0; i < num.size(); ++i) {
    rem = rem * 10 + num[i];
    quot.push_back(rem / d);
    rem %= d;
  }

  return quot;
}

vector<int> mul(const vector<int> &n, int m) {
  vector<int> prod;

  int carry = 0;

  for (int i = 0; i < n.size() || carry; ++i) {
    if (i < n.size()) {
      carry += n[i] * m;
    }

    prod.push_back(carry % 10);
    carry /= 10;
  }

  return prod;
}

int main() {
  vector<vector<int>> arr(SIZE, vector<int>(SIZE, 0)),
      sum(SIZE, vector<int>(SIZE, 0));

  int n, m, q;

  scanf("%d%d%d", &n, &m, &q);

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &arr[i][j]);
      sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + arr[i][j];
    }
  }

  while (q--) {
    int x1, y1, x2, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    printf("%d\n", sum[x2][y2] - sum[x2][y1 - 1] - sum[x1 - 1][y2] +
                       sum[x1 - 1][y1 - 1]);
  }

  return 0;
} */
/* #include <iostream>

using namespace std;

const int SIZE = 100010;  // 定义数组的最大长度

int n, m;  // n: 数组大小，m: 操作次数
int arr[SIZE],
    diff[SIZE];  // arr: 初始数组，diff: 差分数组

// 插入函数，在区间 [left, right] 上加上值 value
void insert(int left, int right, int value) {
  diff[left] += value;
  diff[right + 1] -= value;
}

int main() {
  // 读取数组大小和操作次数
  scanf("%d%d", &n, &m);

  // 读取初始数组并更新差分数组
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &arr[i]);
    insert(i, i, arr[i]);
  }

  // 读取每次操作并更新差分数组
  while (m--) {
    int left, right, value;
    scanf("%d%d%d", &left, &right, &value);
    insert(left, right, value);
  }

  // 计算前缀和并输出结果数组
  for (int i = 1; i <= n; ++i) {
    diff[i] += diff[i - 1];
    printf("%d ", diff[i]);
  }

  return 0;
} */
/* #include <iostream>

using namespace std;

const int SIZE = 100010;

int n, m;
int arr[SIZE], diff[SIZE];

void insert(int left, int right, int value) {
  diff[left] += value;
  diff[right + 1] -= value;
}

int main() {
  scanf("%d%d", &n, &m);

  for (int i = 1; i <= n; ++i) {
    scanf("%d", &arr[i]);
    insert(i, i, arr[i]);
  }

  while (m--) {
    int left, right, value;
    scanf("%d%d%d", &left, &right, &value);
    insert(left, right, value);
  }

  for (int i = 1; i <= n; ++i) {
    diff[i] += diff[i - 1];
    printf("%d\n", diff[i]);
  }

  return 0;
} */
/* #include <iostream>

using namespace std;

const int SIZE = 1010;

int n, m, q;
int arr[SIZE][SIZE], diff[SIZE][SIZE];

void insert(int x1, int y1, int x2, int y2, int value) {
  diff[x1][y1] += value;
  diff[x2 + 1][y1] -= value;
  diff[x1][y2 + 1] -= value;
  diff[x2 + 1][y2 + 1] += value;
}

int main() {
  scanf("%d%d%d", &n, &m, &q);

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &arr[i][j]);
      insert(i, j, i, j, arr[i][j]);
    }
  }

  while (q--) {
    int x1, y1, x2, y2, value;
    scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &value);
    insert(x1, y1, x2, y2, value);
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];
      printf("%d ", diff[i][j]);
    }
    putchar('\n');
  }

  return 0;
} */
/* #include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

int main(void) {
  ifstream f1;  // 文件输入流
  ofstream f2;  // 文件输出流
  int i = 0, n;

  double arr[21][5];                             // 计算金额的 Table
  string str;                                    // 字符串
  f1.open("..\\data\\salary.txt");               // 打开
  f2.open("..\\data\\newsalary.txt", ios::out);  // 打开，输出模式
  f2 << "2023116204陈靖盈" << endl;              // 输出个人信息

  getline(f1, str);  // 读取第一行的信息放进字符串 str 中
  for (i = 0; !f1.eof(); ++i) {
    // 当文件没有到达末尾时，外层循环继续，计算应发工资
    for (int j = 0; j < 4; j++) {
      f1 >> arr[i][j];  // 金额 Table
    }
    arr[i][4] = arr[i][1] + arr[i][2] - arr[i][3];  // 计算应发金额
  }

  n = i;       // 此时结束循环，文件末尾的行数
  f1.close();  // 关闭读取文件

  for (int j = 1; j < 5; j++) {  // 列数
    for (i = 0; i < n; i++) {    // 行数
      arr[n][j] += arr[i][j];    // 最后一行算合计
    }
  }

  str = str + "    应发工资";  // 加入字符串
  f2 << str << endl;         // 将字符串输出在 newsalary

  for (i = 0; i < n; i++) {  // 将 Table 中的内容输出
    for (int j = 0; j < 5; j++) {
      f2 << left << setw(10) << arr[i][j];  // 设置 6 的位宽
    }
    f2 << endl;
  }

  f2 << endl << "合计    " ;
  for (int j = 1; j < 5; j++) {
    f2 << left << setw(10) << arr[n][j];  // 将最后一段的内容输出
  }
  f2.close();  // 关闭文件

  return 0;
} */
/* #include <algorithm>
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

template <class T>
void quick_sort(T* arr, int left, int right) {
  if (left >= right) {
    return;
  }

  T x = arr[left];

  int i = left - 1, j = right + 1;
  while (i < j) {
    do {
      ++i;
    } while (arr[i] < x);

    do {
      --j;
    } while (arr[j] > x);

    if (i < j) {
      swap(arr[i], arr[j]);
    }
  }

  quick_sort(arr, left, j);
  quick_sort(arr, j + 1, right);
}

template <class T>
void merge_sort(T* arr, int left, int right) {
  if (left >= right) {
    return;
  }

  int mid = left + right >> 1;

  merge_sort(arr, left, mid);
  merge_sort(arr, mid + 1, right);

  int i = left, j = mid + 1, k = 0;
  T* temp = new T[right - left + 1];

  while (i <= mid && j <= right) {
    if (arr[i] <= arr[j]) {
      temp[k++] = arr[i++];
    } else {
      temp[k++] = arr[j++];
    }
  }

  while (i <= mid) {
    temp[k++] = arr[i++];
  }

  while (j <= right) {
    temp[k++] = arr[j++];
  }

  for (i = left, j = 0; i <= mid; ++i, ++j) {
    arr[i] = temp[j];
  }

  delete[] temp;
}

void test01() {
  int m, x;

  scanf("%d", &m);

  int* arr = new int[m];

  for (int i = 0; i < m; ++i) {
    scanf("%d", &arr[i]);
  }

  scanf("%d", &x);

  int left = 0, right = 9;
  while (left < right) {
    int mid = left + right + 1 >> 1;
    if (arr[mid] >= x) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }
  printf("%d ", left);

  left = 0, right = 9;
  while (left < right) {
    int mid = left + right + 1 >> 1;
    if (arr[mid] <= x) {
      left = mid;
    } else {
      right = mid - 1;
    }
  }
  printf("%d\n", left);

  delete[] arr;
}

void test02() {
  double x = 0;

  cin >> x;

  double left = 0, right = x;

  while (right - left > 1e-8) {
    double mid = (right + left) / 2;
    if (mid * mid >= x) {
      right = mid;
    } else {
      left = mid;
    }
  }
  cout << left << endl;
}

vector<int> add(const vector<int>& n1, const vector<int>& n2) {
  vector<int> sum;

  int carry = 0;
  int max_size = max(n1.size(), n2.size());
  for (int i = 0; i < max_size || carry; ++i) {
    if (i < n1.size()) {
      carry += n1[i];
    }

    if (i < n2.size()) {
      carry += n2[i];
    }

    sum.push_back(carry % 10);

    carry /= 10;
  }

  return sum;
}

bool cmp(const vector<int>& n1, const vector<int>& n2) {
  if (n1.size() != n2.size()) {
    return n1.size() - n2.size();
  }

  for (int i = n1.size() - 1; i >= 0; --i) {
    if (n1[i] != n2[i]) {
      return n1[i] > n2[i];
    }
  }

  return true;
}

vector<int> sub(const vector<int>& n1, const vector<int>& n2) {
  vector<int> result;

  int carry = 0;

  for (int i = n1.size() - 1; i >= 0; --i) {
    int diff = n1[i] - carry;

    if (diff < n2.size()) {
      diff -= n2[i];
    }

    result.push_back((diff + 10) % 10);

    carry = diff < 0 ? 1 : 0;
  }

  while (result.size() > 1 && result.back() == 0) {
    result.pop_back();
  }

  return result;
}

vector<int> mul(const vector<int>& n, int m) {
  vector<int> result;

  int carry = 0;

  for (int i = 0; i < n.size() || carry; ++i) {
    if (i < n.size()) {
      carry += n[i] * m;
    }

    result.push_back(carry % 10);

    carry /= 10;
  }

  return result;
}

vector<int> div(const vector<int>& n, int d, int& r) {
  vector<int> result;

  for (int i = n.size() - 1; i >= 0; --i) {
    r = r * 10 + n[i];
    result.push_back(r / d);
    r %= d;
  }

  reverse(result.begin(), result.end());

  while (result.size() > 1 && result.back() == 0) {
    result.pop_back();
  }

  return result;
}

void test03() {
  const int LEN = 10010;
  vector<int> arr(LEN), sum(LEN);

  int n, m;
  scanf("%d%d", &n, &m);

  for (int i = 1; i <= n; ++i) {
    scanf("%d", &arr[i]);
    sum[i] = sum[i - 1] + arr[i];
  }

  while (m--) {
    int left, right;
    scanf("%d%d", &left, &right);
    printf("%d\n", sum[right] - sum[left - 1]);
  }
}

void test04() {
  const int SIZE = 1010;

  vector<vector<int>> arr(SIZE, vector<int>(SIZE)),
      sum(SIZE, vector<int>(SIZE));

  int n, m, q;

  scanf("%d%d%d", &n, &m, &q);

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &arr[i][j]);
      sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + arr[i][j];
    }
  }

  while (q--) {
    int x1, y1, x2, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    printf("%d\n", sum[x2][y2] - sum[x2][y1 - 1] - sum[x1 - 1][y2] +
                       sum[x1 - 1][y1 - 1]);
  }
}

void insert(vector<int>& diff, int left, int right, int value) {
  diff[left] += value;
  diff[right + 1] -= value;
}

void test05() {
  const int SIZE = 10010;

  vector<int> arr(SIZE), diff(SIZE);

  int n, m;

  scanf("%d%d", &n, &m);

  for (int i = 1; i <= n; ++i) {
    scanf("%d", &arr[i]);
    insert(diff, i, i, arr[i]);
  }

  while (m--) {
    int left, right, value;
    scanf("%d%d%d", &left, &right, &value);
    insert(diff, left, right, value);
  }

  for (int i = 1; i <= n; ++i) {
    diff[i] += diff[i - 1];
    printf("%d ", diff[i]);
  }
  putchar('\n');
}

void insert(vector<vector<int>>& diff, int x1, int y1, int x2, int y2,
            int value) {
  diff[x1][y1] += value;
  diff[x2 + 1][y1] -= value;
  diff[x1][y2 + 1] -= value;
  diff[x2 + 1][y2 + 1] += value;
}

void test06() {
  const int SIZE = 1010;

  vector<vector<int>> arr(SIZE, vector<int>(SIZE, 0)),
      diff(SIZE, vector<int>(SIZE, 0));

  int n, m, q;
  scanf("%d%d%d", &n, &m, &q);

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &arr[i][j]);
      insert(diff, i, j, i, j, arr[i][j]);
    }
  }

  while (q--) {
    int x1, y1, x2, y2, value;
    scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &value);
    insert(diff, x1, y1, x2, y2, value);
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];
      printf("%d ", diff[i][j]);
    }
    putchar('\n');
  }
}

void test07() {
  unique_ptr<int> ptr(new int(42));
  cout << *ptr << endl;

  unique_ptr<int> ptr2 = move(ptr);
  cout << *ptr2 << endl;
}

int main() {
  test07();
  return 0;
} */
/* #include <iostream>

using namespace std;

namespace name_a {
int x;
void func(void) { cout << "name_a" << endl; }
}  // namespace name_a

namespace name_b {
int x;
void func(void) { cout << "name_b" << endl; }
}  // namespace name_b

int main() {
  name_a::x = 100;
  name_b::x = 1000;
  cout << name_a::x << endl;
  cout << name_b::x << endl;
  name_a::func();
  name_b::func();
  return 0;
} */
/* #include <iostream>

using namespace std;

namespace A {
int a = 10;
namespace B {
int a = 20;
}  // namespace B
}  // namespace A

void test(void) {
  cout << "A::a = " << A::a << endl;
  cout << "A::B::a = " << A::B::a << endl;
}

int main(void) {
  test();
  return 0;
}
 */
/* #include "test.hpp"

int main() {
  MySpace::func1();
  MySpace::func2(10);
  return 0;
} */
/* #include <iostream>

using namespace std;

namespace student_info_handle {
int a = 10;
void func() { cout << "student_info_handle" << endl; }
}  // namespace student_info_handle

int main() {
  namespace stuInfoH = student_info_handle;
  stuInfoH::func();
  return 0;
} */
/* #include <iostream>

using namespace std;

int main(int argc, char** argv) {
  int a = 10;
  cout << &a << endl;
  return 0;
} */
/* #include <iostream>

using namespace std;

int main() {
  int a = 10;
  int& aRef = a;
  aRef = 20;
  cout << "a: " << a << endl;
  return 0;
} */
/* #include <iostream>

using namespace std;

struct test {
  int &a;
  int &b;
};

int main() {
  cout << sizeof(struct test) << endl;
  return 0;
} */
/* #include <iostream>

using namespace std;

inline int func(int a) { return ++a; }

int main() { return 0; } */
/* #include <iostream>

using namespace std;

void testFunc(int a = 10, int b = 20) { cout << "a + b = " << a + b << endl; }

int main() {
  testFunc();
  testFunc(100);
  testFunc(100, 200);
  return EXIT_SUCCESS;
} */
/* #include <iostream>

using namespace std;

class CAnimal {
 public:
 char name[32];
 int age;
 void cry(const char *voice) {
  cout << name << voice << endl;
 }
};

int main() {
  CAnimal cat;
  cat.age = 1;
  cout << cat.age << endl;
  cat.cry("miao miao");
  return 0;
} */
/* #include <cstdio>
#include <iostream>

using namespace std;

class Box {
 public:
  bool set_length(int length);
  bool set_width(int width);
  bool set_height(int height);

  int get_length(void);
  int get_width(void);
  int get_height(void);

  int get_area(void);
  int get_volumn(void);

 private:
  int _length;
  int _width;
  int _height;
  int _area;
  int _volume;
};


bool Box::set_length(int length) {
  if (length <= 0 || length > 100) {
    cout << "length error" << endl;
    return false;
  }

  _length = length;

  return true;
} */
/* #include <iostream>

using namespace std;

class Box {
 public:
  Box() {
    _length = 10;
    _width = 10;
    _height = 10;
  }

  int get_length() { return _length; }
  int get_width() { return _width; }
  int get_height() { return _height; }

 private:
  int _length;
  int _width;
  int _height;
};

int main() {
  Box box;
  cout << box.get_height() << endl;
  cout << box.get_length() << endl;
  cout << box.get_width() << endl;
  return 0;
} */
/* #include <iostream>

using namespace std;

class Box {
 public:
  Box(int length, int width, int height)
      : _length(length), _width(width), _height(height) {}

  int get_lenght() { return _length; }

 private:
  int _length;
  int _width;
  int _height;
};

int main() {
  Box b(10, 10, 10);
  cout << b.get_lenght() << endl;
  return 0;
} */
/* #include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

class Animal {
 public:
  char *name;
  int age;

  Animal() {
    name = (char *)malloc(32);
    cout << "Animal()" << endl;
  }

  Animal(const char *name1) {
    int len = strlen(name1);
    name1 = (char *)malloc(len + 1);
    strcpy(name, name1);
  }

  ~Animal() {
    if (name) {
      free(name);
    }
    cout << "~Animal()" << endl;
  }
};

int main() {
  Animal animal;
  return 0;
} */
/* #include <iostream>

using namespace std;

class Box {
 public:
  int length;
  int width;
  int height;

  Box() { cout << "Box()" << endl; }

  Box(int x, int y, int z) : length(x), width(y), height(z) {
    std::cout << "Box(int x, int y, int z) : length(x), width(y), height(z)"
              << std::endl;
  }
};

int main() {
  int *p1 = new int(10);
  delete p1;

  int *p2 = new int[4];
  delete[] p2;

  Box *p3 = new Box;
  delete p3;

  Box *p4 = new Box[4];

  Box *p5 = new Box(10, 10, 10);
  delete p5;

  return 0;
} */
/* #include <iostream>

using namespace std;

class Test {
 public:
  int *sum;
  int x;
  int y;

  Test(void) {
    cout << "Test(void);" << endl;
    x = 0;
    y = 0;
    sum = new int[4];
  }

  Test(int a, int b) : x(a), y(b) {
    cout << "Test(int a, int b);" << endl;
    sum = new int[4];
  }

  Test(const Test &t) {
    x = t.x;
    y = t.y;
    sum = new int[4];

    for (int i = 0; i < 4; ++i) {
      sum[i] = t.sum[i];
    }
  }

  ~Test() {
    cout << "~Test();" << endl;
    delete[] sum;
  }
};

int main(void) {
  Test *t1 = new Test(1, 2);
  t1->sum[1] = 10;
  cout << t1->sum[1] << endl;
  return 0;
} */
/* #include <iostream>

using namespace std;

class ABC {
 public:
  int x, y, z;
  ABC(int x, int y, int z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }
};

int main() {
  ABC a(1, 2, 3);
  ABC b(1, 2, 3);
  return 0;
} */
/* #include <iostream>

using namespace std;

class Sheep {
 public:
  char name[32];
  int age;
  Sheep() {
    cout << "Sheep();" << endl;
    ++count;
  }

  ~Sheep() { --count; }
  static int sheep_num() { return count; }

 private:
  static int count;
};

int Sheep::count = 0;

int main() {
  Sheep s1;
  cout << Sheep::sheep_num() << endl;
  cout << s1.sheep_num() << endl;
  return 0;
} */
/* #include <iostream>
#include <string>

using namespace std;

int main() {
  string s1("12345", 2, 4);
  string s2(3, 'O');
  cout << s1 << s2 << endl;
  cout << s1 + s2 << endl;

  return 0;
} */
/* #include <iostream>
#include <string>

using namespace std;

int main() {
  string s;
  s = "Hello World";
  s = 'A';
  cout << s << endl;
  return 0;
} */
/* #include <string>

using namespace std;

int main() {
  string s("abc", 3);

} */
/* #include <iostream>
#include <string>
#include <vector>

using namespace std;

class MyClass {
 public:
  MyClass() { cout << "Default constructor" << endl; }

  MyClass(const MyClass& other) { cout << "Copy constructor" << endl; }

  MyClass(MyClass&& other) noexcept { cout << "Move constructor" << endl; }
};

int main() {
  MyClass a;
  MyClass b = std::move(a);  // 将调用移动构造函数
  return 0;
} */
/* #include <cstring>  // std::strlen, std::strcpy
#include <iostream>
#include <utility>  // std::move

class MyString {
 public:
  // 默认构造函数
  MyString() : data_(nullptr), size_(0) {
    std::cout << "Default constructor" << std::endl;
  }

  // 带参数的构造函数
  MyString(const char* str) {
    std::cout << "Parameterized constructor" << std::endl;
    size_ = std::strlen(str);
    data_ = new char[size_ + 1];
    std::strcpy(data_, str);
  }

  // 拷贝构造函数
  MyString(const MyString& other) {
    std::cout << "Copy constructor" << std::endl;
    size_ = other.size_;
    data_ = new char[size_ + 1];
    std::strcpy(data_, other.data_);
  }

  // 移动构造函数
  MyString(MyString&& other) noexcept : data_(other.data_), size_(other.size_) {
    std::cout << "Move constructor" << std::endl;
    other.data_ = nullptr;
    other.size_ = 0;
  }

  // 拷贝赋值运算符
  MyString& operator=(const MyString& other) {
    std::cout << "Copy assignment operator" << std::endl;
    if (this == &other) {
      return *this;
    }
    delete[] data_;
    size_ = other.size_;
    data_ = new char[size_ + 1];
    std::strcpy(data_, other.data_);
    return *this;
  }

  // 移动赋值运算符
  MyString& operator=(MyString&& other) noexcept {
    std::cout << "Move assignment operator" << std::endl;
    if (this == &other) {
      return *this;
    }
    delete[] data_;
    data_ = other.data_;
    size_ = other.size_;
    other.data_ = nullptr;
    other.size_ = 0;
    return *this;
  }

  // 析构函数
  ~MyString() {
    std::cout << "Destructor" << std::endl;
    delete[] data_;
  }

  // 打印字符串
  void print() const {
    if (data_) {
      std::cout << data_ << std::endl;
    } else {
      std::cout << "Empty" << std::endl;
    }
  }

 private:
  char* data_;
  std::size_t size_;
}; */

