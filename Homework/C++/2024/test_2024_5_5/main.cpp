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
/* #include <iostream>

using namespace std;

int main() {
  cout << "Hello World!" << endl;
  return 0;
} */
/* #include <iostream>

using namespace std;

template <class T>
void quickSort(T *arr, int left, int right) {
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

  quickSort(arr, left, j);

  quickSort(arr, j + 1, right);
} */
/* #include <iostream>

using namespace std;

template <class T>
void quickSort(T *arr, int left, int right) {
  if (left > right) {
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

  quickSort(arr, left, j);
  quickSort(arr, j + 1, right);
} */
/* #include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

template <class T>
void quickSort(T *arr, int left, int right) {
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

  quickSort(arr, left, j);
  quickSort(arr, j + 1, right);
}

int main() {
  srand((unsigned int)time(nullptr));
  int arr[10];
  for (int i = 0; i < 10; ++i) {
    arr[i] = rand() % 100 + 1;
    cout << arr[i] << ' ';
  }
  cout << endl;

  quickSort(arr, 0, 10);

  for (int i = 0; i < 10; ++i) {
    cout << arr[i] << ' ';
  }
  cout << endl;
  return 0;
} */
/* #include <iostream>

using namespace std;

template <class T>
void quickSort(T *arr, int left, int right) {
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

  quickSort(arr, left, i - 1);
  quickSort(arr, i, right);
} */
/* #include <iostream>

using namespace std;

template <class T>
void quickSort(T *arr, int left, int right) {
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

  quickSort(arr, left, j);
  quickSort(arr, j + 1, right);
}

template <class T>
void mergeSort(T *arr, int left, int right) {
  if (left >= right) {
    return;
  }

  int mid = left + (right - left) / 2;

  mergeSort(arr, left, mid);
  mergeSort(arr, mid + 1, right);

  int k = 0, i = left, j = mid + 1;

  T *temp = new T[right - left + 1];

  while (i <= mid && j <= right) {
    if (arr[i] <= arr[j]) {
      temp[k++] = arr[i++];
    } else {
      temp[k++] = arr[j++];
    }
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

template <class T>
void mergeSort(T *arr, int left, int right) {
  if (left >= right) {
    return;
  }

  int mid = left + (right - left) / 2;

  mergeSort(arr, left, mid);
  mergeSort(arr, mid + 1, right);

  int k = 0, i = left, j = right;

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
/* #include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

template <class T>
void mergeSort(T *arr, int left, int right) {
  if (left >= right) {
    return;
  }

  int mid = left + (right - left) / 2;

  mergeSort(arr, left, mid);
  mergeSort(arr, mid + 1, right);

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
}

int main() {
  srand((unsigned int)time(nullptr));

  int arr[10];

  for (int i = 0; i < 10; ++i) {
    arr[i] = rand() % 100 + 1;
    cout << arr[i] << ' ';
  }
  cout << endl;

  mergeSort(arr, 0, 10);

  for (int i = 0; i < 10; ++i) {
    cout << arr[i] << ' ';
  }
  cout << endl;

  return 0;
} */
/* #include <iostream>

template <class T>
void quickSort(T *arr, int left, int right) {
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

  quickSort(arr, left, i - 1);
  quickSort(arr, i, right);
}

template <class T>
void mergeSort(T *arr, int left, int right) {
  if (left >= right) {
    return;
  }

  int mid = left + (right - left) / 2;

  mergeSort(arr, left, mid);
  mergeSort(arr, mid + 1, right);

  int i = left, j = mid + 1, k = 0;
  T *temp = new T[right - left + 1];

  while (i <= mid && j <= right) {
    if (arr[i] < arr[j]) {
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

  for (i = left, j = 0; i <= right; ++i) {
    arr[i] = temp[j];
  }

  delete[] temp;
} */
/* template <class T>
void quickSort(T *arr, int left, int right) {
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

  quickSort(arr, left, j);
  quickSort(arr, j + 1, right);
} */
/* template <class T>
void quickSort(T *arr, int left, int right) {
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
} */
/* template <class T>
void quickSort(T *arr, int left, int right) {
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

  quickSort(arr, left, j);
  quickSort(arr, j + 1, right);
}

template <class T>
void mergeSort(T *arr, int left, int right) {
  if (left >= right) {
    return;
  }

  int mid = left + (right - left) / 2;

  mergeSort(arr, left, mid);
  mergeSort(arr, mid + 1, right);

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
} */
/* #include <iostream>

using namespace std;

int main() {
  int arr[10] = {1, 2, 2, 2, 3, 3, 3, 3, 4, 4};

  int l = 0, r = 9, x;

  cin >> x;

  while (l < r) {
    int mid = l + (r - l) / 2;

    if (arr[mid] >= x) {
        r = mid;
    } else {
       l = mid + 1;
    }
  }
  cout << l << ' ';

  l = 0, r = 9;
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
/* #include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> PII;  // 表示整数对

const int N = 300010;  // 常数 N, 用来定义数组的最大大小

int n, m;
int a[N], s[N];  // 数组 a 存储离散化后的位置的值, 数组 s 用于存储前缀和

vector<int> alls;        // 用来存储所有需要离散化的值
vector<PII> add, query;  // 存储需要加的数对和查询区间

int find(int x) {  // 二分查找
  int l = 0, r = alls.size() - 1;
  while (l < r) {
    int mid = l + r >> 1;
    if (alls[mid] >= x) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }

  return r + 1;  // 因为是前缀和数组, 所以要进行加一操作
}

int main() {
  cin >> n >> m;  // 代表需要加的数对的个数和查询的区间的个数

  for (int i = 0; i < n; ++i) {
    int x, c;  // 每个操作由一对数 (x, c) 构成, 表示在 x 处加上 c
    cin >> x >> c;
    add.push_back({x, c});

    alls.push_back(x);  // 将 x 加入 alls 中
  }

  for (int i = 0; i < m; ++i) {  // m 个查询操作
    int l, r;
    cin >> l >> r;
    query.push_back({l, r});  // 代表查询操作

    alls.push_back(l);  // 将两个操作数存入 alls 中
    alls.push_back(r);
  }

  sort(alls.begin(), alls.end());  // 排序所有的数
  alls.erase(unique(alls.begin(), alls.end()), alls.end());  // 去重

  for (auto item : add) {  // 遍历插入操作, 找到位置 x
    int x = find(item.first);
    a[x] += item.second;  // 在位置 x 处加上相应的数
  }

  for (int i = 1; i <= alls.size(); ++i) {
    s[i] = s[i - 1] + a[i];  // 构建前缀和数组
  }

  for (auto item : query) {
    int l = find(item.first), r = find(item.second);
    cout << s[r] - s[l - 1] << endl;  // 进行查询操作
  }

  return 0;
} */
/* #include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> PII;

const int N = 300010;

int n, m;
int a[N], s[N];

vector<int> alls;
vector<PII> add, query;

int find(int x) {
  int l = 0, r = alls.size() - 1;
  while (l < r) {
    int mid = l + (r - l) >> 1;

    if (alls[mid] >= x) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }

  return r + 1;
}

int main() {
  cin >> n >> m;

  for (int i = 0; i < n; ++i) {
    int x, c;
    cin >> x >> c;
    add.push_back({x, c});
    alls.push_back(x);
  }

  for (int i = 0; i < m; ++i) {
    int l, r;
    cin >> l >> r;
    query.push_back({l, r});

    alls.push_back(l);
    alls.push_back(r);
  }

  sort(alls.begin(), alls.end());
  alls.erase(unique(alls.begin(), alls.end()), alls.end());

  for (auto item : add) {
    int x = find(item.first);
    a[x] += item.second;
  }

  for (int i = 1; i <= alls.size(); ++i) {
    s[i] = s[i - 1] + a[i];
  }

  for (auto item : query) {
    int l = find(item.first), r = find(item.second);
    cout << s[r] - s[l - 1] << endl;
  }

  return 0;
} */
/* #include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef pair<int, int> PII;

const int N = 300010;

int n, m;
int a[N], s[N];

vector<int> alls;
vector<PII> add, query;

int find(int x) {
  int l = 0, r = alls.size() - 1;
  while (l < r) {
    int mid = l + (r - l) / 2;
    if (alls[mid] >= x) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  return r + 1;
}

int main() {
  cin >> n >> m;

  for (int i = 0; i < n; ++i) {
    int x, c;
    cin >> x >> c;
    add.push_back({x, c});
    alls.push_back(x);
  }

  for (int i = 0; i < m; ++i) {
    int l, r;
    cin >> l >> r;
    query.push_back({l, r});

    alls.push_back(l);
    alls.push_back(r);
  }

  sort(alls.begin(), alls.end());
  alls.erase(unique(alls.begin(), alls.end()), alls.end());

  for (auto item : add) {
    int x = find(item.first);
    a[x] += item.second;
  }

  for (int i = 1; i <= alls.size(); ++i) {
    s[i] = s[i - 1] + a[i];
  }

  for (auto item : query) {
    int l = find(item.first), r= find(item.second);
    cout << s[r] - s[l - 1] << endl;
  }

  return 0;
} */
/* #include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> PII;

const int N = 300010;

int n, m;
int a[N], s[N];

vector<int> alls;
vector<PII> add, query;

int find(int x) {
  int l = 0, r = alls.size() - 1;
  while (l < r) {
    int mid = l + (r - l) / 2;
    if (alls[mid] >= x) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  return r + 1;
}

int main() {
  cin >> n >> m;

  for (int i = 0; i < n; ++i) {
    int x, c;
    cin >> x >> c;
    add.push_back({x, c});
    alls.push_back(x);
  }

  for (int i = 0; i < m; ++i) {
    int l, r;
    cin >> l >> r;

    query.push_back({l, r});
    alls.push_back(l);
    alls.push_back(r);
  }

  sort(alls.begin(), alls.end());
  alls.erase(unique(alls.begin(), alls.end()), alls.end());

  for (auto item : add) {
    int x = find(item.first);
    a[x] += item.second;
  }

  for (int i = 1; i <= alls.size(); ++i) {
    s[i] = s[i - 1] + a[i];
  }

  for (auto item : query) {
    int l = find(item.first), r = find(item.second);
    cout << s[r] - s[l - 1] << endl;
  }

  return 0;
} */
/* #include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> PII;

const int N = 300010;

int n, m;
int a[N], s[N];

vector<int> alls;
vector<PII> add, query;

int find(int x) {
  int l, r;
  cin >> l >> r;
  while (l < r) {
    int mid = l + (r - l) / 2;
    if (alls[mid] >= x) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  return r + 1;
}

int main() {
  cin >> n >> m;

  for (int i = 0; i < n; ++i) {
    int x, c;
    cin >> x >> c;
    add.push_back({x, c});
    alls.push_back(x);
  }

  for (int i = 0; i < m; ++i) {
    int l, r;
    cin >> l >> r;
    query.push_back({l, r});
    alls.push_back(l);
    alls.push_back(r);
  }

  sort(alls.begin(), alls.end());
  alls.erase(unique(alls.begin(), alls.end()), alls.end());

  for (auto item : add) {
    int x = find(item.first);
    a[x] += item.second;
  }

  for (int i = 1; i <= alls.size(); ++i) {
    s[i] = s[i - 1] + a[i];
  }

  for (auto item : query) {
    int l = find(item.first), r = find(item.second);
    cout << s[r] - s[l - 1] << endl;
  }

  return 0;
} */
/* #include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int N = 300010;

typedef pair<int, int> PII;

int n, m;
int a[N], s[N];

vector<int> alls;
vector<PII> add, query;

int find(int x) {
  int l = 0, r = alls.size() - 1;

  while (l < r) {
    int mid = l + (r - l) >> 1;
    if (alls[mid] >= x) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }

  return r + 1;
}

int main() {
  cin >> n >> m;

  for (int i = 0; i < n; ++i) {
    int x, c;
    cin >> x >> c;
    add.push_back({x, c});
    alls.push_back(x);
  }

  for (int i = 0; i < m; ++i) {
    int l, r;
    cin >> l >> r;
    query.push_back({l, r});
    alls.push_back(l);
    alls.push_back(r);
  }

  sort(alls.begin(), alls.end());
  alls.erase(unique(alls.begin(), alls.end()), alls.end());

  for (auto item : add) {
    int x = find(item.first);
    a[x] += item.second;
  }

  for (int i = 1; i <= alls.size(); ++i) {
    s[i] = s[i - 1] + a[i];
  }

  for (auto item : query) {
    int l = find(item.first), r = find(item.second);
    cout << s[r] - s[l - 1] << endl;
  }

  return 0;
} */
/* #include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> PII;

const int N = 300010;

int n, m;
int a[N], s[N];

vector<int> alls;
vector<PII> add, query;

int find(int x) {
  int l = 0, r = alls.size();
  while (l < r) {
    int mid = l + (r - l) >> 1;
    if (alls[mid] >= x) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  return r + 1;
}

vector<int>::iterator unique(vector<int> &a) {
  int j = 0;
  for (int i = 0; i < a.size(); ++i) {
    if (!i || a[i] != a[i - 1]) {
      a[j++] = a[i];
    }
  }
  return a.begin() + j;
}

int main() {
  cin >> n >> m;

  for (int i = 0; i < n; ++i) {
    int x, c;
    cin >> x >> c;
    add.push_back({x, c});
    alls.push_back(x);
  }

  for (int i = 0; i < m; ++i) {
    int l, r;
    cin >> l >> r;
    query.push_back({l, r});
    alls.push_back(l);
    alls.push_back(r);
  }

  sort(alls.begin(), alls.end());
  alls.erase(unique(alls.begin(), alls.end()), alls.end());

  for (auto item : add) {
    int x = find(item.first);
    a[x] += item.second;
  }

  for (int i = 1; i <= alls.size(); ++i) {
    s[i] = s[i - 1] + a[i];
  }

  for (auto item : query) {
    int l = find(item.first), r = find(item.second);
    cout << s[r] - s[l - 1] << endl;
  }

  return 0;
} */
/* #include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> PII;

const int N = 100010;

int n;
vector<PII> segs;

void merge(vector<PII> &segs) {
  vector<PII> res;

  sort(segs.begin(), segs.end());

  int st = -2e9, ed = -2e9;

  for (auto seg : segs) {
    if (ed < seg.first) {
      if (st != -2e9) {
        res.push_back({st, ed});
      }
      st = seg.first, ed = seg.second;
    } else {
      ed = max(ed, seg.second);
    }
  }

  if (st != -2e9) {
    res.push_back({st, ed});
  }

  segs = res;
}

int main() {
  cin >> n;

  for (int i = 0; i < n; ++i) {
    int l, r;
    cin >> l >> r;
    segs.push_back({l, r});
  }

  merge(segs);

  cout << segs.size() << endl;

  return 0;
} */
/* #include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef pair<int, int> PII;

const int N = 100010;

int n;
vector<PII> segs;

void merge(vector<PII> &segs) {
  vector<PII> res;

  sort(segs.begin(), segs.end());

  int st = -2e9, ed = -2e9;

  for (auto seg : segs) {
    if (ed < seg.first) {
      if (st != -2e9) {
        res.push_back({st, ed});
      }
      st = seg.first, ed = seg.second;
    } else {
      ed = max(ed, seg.second);
    }
  }

  if (st != -2e9) {
    res.push_back({st, ed});
  }

  segs = res;
}

int main() {
  cin >> n;

  for (int i = 0; i < n; ++i) {
    int l, r;
    cin >> l >> r;
    segs.push_back({l, r});
  }

  merge(segs);
} */
/* #include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> PII;

const int N = 100010;

int n;
vector<PII> segs;

void merge(vector<PII> &segs) {
  vector<PII> res;

  sort(segs.begin(), segs.end());

  int st = -2e9, ed = -2e9;

  for (auto seg : segs) {
    if (ed < seg.first) {
      if (st != -2e9) {
        res.push_back({st, ed});
      }
      st = seg.first, ed = seg.second;
    } else {
      ed = max(ed, seg.second);
    }
  }

  if (st != -2e9) {
    res.push_back({st, ed});
  }

  segs = res;
}

int main() {
  cin >> n;

  for (int i = 0; i < n; ++i) {
    int l, r;
    cin >> l >> r;
    segs.push_back({l, r});
  }

  merge(segs);

  cout << segs.size() << endl;

  return 0;
} */
/* #include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> PII;

const int N = 100010;

int n;
vector<PII> segs;

void merge(vector<PII> &segs) {
  vector<PII> res;

  int st = -2e9, ed = -2e9;

  for (auto seg : segs) {
    if (ed < seg.first) {
      if (st != -2e9) {
        res.push_back({st, ed});
      }
      st = seg.first, ed = seg.second;
    } else {
      ed = max(seg.second, ed);
    }
  }

  if (st != -2e9) {
    res.push_back({st, ed});
  }

  segs = res;
}

int main() {
  cin >> n;

  for (int i = 0; i < n; ++i) {
    int l, r;
    cin >> l >> r;
    segs.push_back({l, r});
  }

  merge(segs);

  cout << segs.size() << endl;

  return 0;
} */
/* #include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> PII;

int n;
vector<PII> segs;

const int N = 100010;

void merge(vector<PII> &segs) {
  vector<PII> res;

  sort(segs.begin(), segs.end());

  int st = -2e9, ed = -2e9;

  for (auto seg : segs) {
    if (ed < seg.first) {
      if (st != -2e9) {
        res.push_back({st, ed});
      }
      st = seg.first, ed = seg.second;
    } else {
      ed = max(seg.second, ed);
    }
  }

  if (st != -2e9) {
    res.push_back({st, ed});
  }

  segs = res;
}

int main() {
  cin >> n;

  for (int i = 0; i < n; ++i) {
    int l, r;
    cin >> l >> r;
    segs.push_back({l, r});
  }

  merge(segs);

  cout << segs.size() << endl;

  return 0;
} */
/* #include <iostream>

using namespace std;

template <class T>
void quick_sort(T *arr, int left, int right) {
  if (left > right) {
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
  if (left > right) {
    return;
  }

  int mid = left + (right - left) / 2;

  merge_sort(arr, left, mid);
  merge_sort(arr, mid + 1, right);

  int i = 0, j = mid + 1, k = 0;

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

  for (i = left, j = 0; i <= right; ++i) {
    arr[i] = temp[j];
  }

  delete[] temp;
}

int main() {
  int arr[10] = {1, 1, 2, 2, 2, 2, 3, 3, 3, 4};
  int x;

  cin >> x;

  int l = 0, r = 9;
  while (l < r) {
    int mid = l + (r - l) / 2;

    if (arr[mid] >= x) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  cout << l << ' ';

  l = 0, r = 9;
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

  while (r - l > 1e-9) {
    double mid = l + (r - l) / 2;
    if (mid * mid >= x) {
      r = mid;
    } else {
      l = mid;
    }
  }

  cout << l << endl;

  return 0;
} */
/* #include <algorithm>
#include <vector>

using namespace std;

vector<int> add(const vector<int> &v1, const vector<int> &v2) {
  vector<int> sum;

  int max_size = max(v1.size(), v2.size());
  int carry = 0;

  for (int i = 0; i < max_size || carry; ++i) {
    if (i < v1.size()) {
      carry += v1[i];
    }

    if (i < v2.size()) {
      carry += v2[i];
    }

    sum.push_back(carry % 10);
    carry /= 10;
  }

  return sum;
}

bool cmp(const vector<int> &v1, const vector<int> &v2) {
  if (v1.size() != v2.size()) {
    return v1.size() > v2.size();
  }

  for (int i = 0; i < v1.size(); ++i) {
    if (v1[i] != v2[i]) {
      return v1[i] > v2[i];
    }
  }

  return true;
}

vector<int> sub(const vector<int> &v1, const vector<int> &v2) {
  vector<int> res;

  int carry = 0;

  for (int i = 0; i < v1.size(); ++i) {
    int diff = v1[i] - carry;

    if (i < v2.size()) {
      diff -= v2[i];
    }

    res.push_back((diff + 10) % 10);

    carry = diff < 0 ? 1 : 0;
  }

  while (res.size() > 1 && res.back() == 0) {
    res.pop_back();
  }

  return res;
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

vector<int> div(const vector<int> &n, int m, int &rem) {
  vector<int> quot;

  for (int i = n.size() - 1; i >= 0; --i) {
    rem = rem * 10 + n[i];
    quot.push_back(rem / m);
    rem %= 10;
  }

  reverse(quot.begin(), quot.end());

  while (quot.size() > 1 && quot.back() == 0) {
    quot.pop_back();
  }

  return quot;
} */
/* #include <iostream>
#include <vector>

using namespace std;

const int LEN = 100010;

int main() {
  int n, m;
  int arr[LEN] = {0}, sum[LEN] = {0};

  for (int i = 1; i <= n; ++i) {
    cin >> arr[i];
    sum[i] = sum[i - 1] + arr[i];
  }

  while (m--) {
    int l, r;
    cin >> l >> r;
    cout << sum[r] - sum[l - 1] << endl;
  }

  return 0;
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

int main() {
  int n, m;
  int a[N], s[N];

  cin >> n >> m;

  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    s[i] = s[i - 1] + a[i];
  }

  for (int i = 0; i < m; ++i) {
    int l, r;
    cin >> l >> r;
    cout << s[r] - s[l - 1] << endl;
  }

  return 0;
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

int main() {
  int n, m;
  int a[N], s[N];
  cin >> n >> m;

  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    s[i] = s[i - 1] + a[i];
  }

  for (int i = 0; i < m; ++i) {
    int l, r;
    cin >> l >> r;
    cout << s[r] - s[l - 1] << endl;
  }
} */
/* #include <algorithm>
#include <vector>

using namespace std;

vector<int> div(const vector<int> &n, int d, int &r) {
  vector<int> q;

  int c = 0;
  for (int i = 0; i < n.size(); ++i) {
    r = r * 10 + n[i];
    q.push_back(r / d);
    r %= 10;
  }

  reverse(q.begin(), q.end());

  while (q.size() > 1 && q.back() == 0) {
    q.pop_back();
  }

  return q;
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

int main() {
  int n, m;
  int arr[N] = {0}, sum[N] = {0};

  cin >> n >> m;

  for (int i = 1; i <= n; ++i) {
    cin >> arr[i];
    sum[i] = sum[i - 1] + arr[i];
  }

  for (int i = 0; i < m; ++i) {
    int l, r;
    cin >> l >> r;
    cout << sum[r] - sum[l - 1] << endl;
  }

  return 0;
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

int main() {
  int n, m, q;
  int a[N][N], s[N][N];

  cin >> n >> m;

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cin >> a[i][j];
      s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + a[i][j];
    }
  }

  while (q--) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    cout << s[x2][y2] - s[x2][y1 - 1] - s[x1 - 1][y2] + s[x1][y1] << endl;
  }

  return 0;
} */
/* #include <iostream>

const int N = 100010;

using namespace std;

int main() {
  int n, m, q;
  int a[N][N], s[N][N];

  cin >> n >> m >> q;

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cin >> a[i][j];
      s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + a[i][j];
    }
  }

  for (int i = 0; i < q; ++i) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    cout << s[x2][y2] - s[x2][y1 - 1] - s[x1 - 1][y2] + s[x1 - 1][y1 - 1]
         << endl;
  }

  return 0;
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

int n, m;
int a[N], d[N];

void insert(int l, int r, int x) {
  d[l] += x;
  d[r + 1] -= x;
}

int main() {
  cin >> n >> m;

  for (int i = 1; i <=n; ++i) {
    cin >> a[i];
    insert(i, i, a[i]);
  }

  while (m--) {
    int l, r, x;
    cin >> l >> r >> x;
    insert(l, r, x);
  }

  for (int i = 1; i <= n; ++i) {
    d[i] += d[i - 1];
    cout << d[i] << ' ';
  }

  return 0;
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

int n, m;
int a[N], d[N];

void insert(int l, int r, int x) {
  d[l] += x;
  d[r + 1] -= x;
}

int main() {
  cin >> n >> m;

  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    insert(i, i, a[i]);
  }

  while (m--) {
    int l, r, x;
    cin >> l >> r >> x;
    insert(l, r, x);
  }

  for (int i = 1; i <= n; ++i) {
    d[i] += d[i - 1];
    cout << d[i] << ' ';
  }

  return 0;
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

int n, m;

int a[N], d[N];

void insert(int l, int r, int x) {
  d[l] += x;
  d[r + 1] -= x;
}

int main() {
  cin >> n >> m;

  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    insert(i, i, a[i]);
  }

  while (m--) {
    int l, r, x;
    cin >> l >> r >> x;
    insert(l, r, x);
  }

  for (int i = 1; i <= n; ++i) {
    d[i] += d[i - 1];
    cout << d[i] << ' ';
  }

  return 0;
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

int a[N][N], d[N][N];

void insert(int x1, int y1, int x2, int y2, int v) {
  d[x1][y1] += v;
  d[x2 + 1][y1] -= v;
  d[x1][y2 + 1] -= v;
  d[x2 + 1][y2 + 1] += v;
}

int main() {
  int n, m, q;
  cin >> n >> q;

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cin >> a[i][j];
      insert(i, j, i, j, a[i][j]);
    }
  }

  while (q--) {
    int x1, y1, x2, y2, v;
    cin >> x1 >> y1 >> x2 >> y2 >> v;
    insert(x1, y1, x2, y2, v);
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      d[i][j] += d[i - 1][j] + d[i][j - 1] - d[i - 1][j - 1];
      cout << d[i][j] << ' ';
    }
    cout << endl;
  }

  return 0;
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

int a[N][N], d[N][N];

void insert(int x1, int y1, int x2, int y2, int v) {
  d[x1][y1] += v;
  d[x2 + 1][y1] -= v;
  d[x1][y2 + 1] -= v;
  d[x2 + 1][y2 + 1] += v;
}

int main() {
  int n, m, q;
  cin >> n >> m >> q;

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cin >> a[i][j];
      insert(i, j, i, j, a[i][j]);
    }
  }

  while (q--) {
    int x1, y1, x2, y2, v;
    cin >> x1 >> y1 >> x2 >> y2 >> v;
    insert(x1, y1, x2, y2, v);
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      d[i][j] += d[i - 1][j] + d[i][j - 1] - d[i - 1][j - 1];
      cout << d[i][j] << ' ';
    }
    cout << endl;
  }

  return 0;
} */
/* #include <iostream>

using namespace std;

const int N = 100010;
int a[N][N], d[N][N];

void insert(int x1, int y1, int x2, int y2, int v) {
  d[x1][y1] += v;
  d[x2 + 1][y1] -= v;
  d[x1][y2 + 1] -= v;
  d[x2 + 1][y2 + 1] += v;
}

int main() {
  int n, m, q;
  cin >> n >> m >> q;

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cin >> a[i][j];
      insert(i, j, i, j, a[i][j]);
    }
  }

  while (q--) {
    int x1, y1, x2, y2, v;
    cin >> x1 >> y1 >> x2 >> y2 >> v;
    insert(x1, y1, x2, y2, v);
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      d[i][j] += d[i - 1][j] + d[i][j - 1] - d[i - 1][j - 1];
      cout << d[i][j] << ' ';
    }
    cout << endl;
  }

  return 0;
} */
/* #include <cstring>
#include <iostream>

using namespace std;

int main() {
  char str[1000];
  gets(str);
  int n = strlen(str);

  for (int i = 0; str[i]; ++i) {
    int j = i;
    while (j < n && str[j] != ' ') {
      ++j;
    }
    for (int k = i; k < j; ++k) {
      cout << str[k];
    }
    i = j;
    cout << endl;
  }

  return 0;
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

int n, a[N], s[N] = {0};

int main() {
  cin >> n;

  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  int res = 0;
  for (int i = 0, j = 0; i < n; ++i) {
    ++s[a[i]];

    while (s[a[i]] > 1) {
      --s[a[j]];
      ++j;
    }
    res = max(res, i - j + 1);
  }

  cout << res << endl;

  return 0;
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

int n, a[N], s[N] = {0};

int main() {
  cin >> n;

  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  int res = 0;

  for (int i = 0, j = 0; i < n; ++i) {
    ++s[a[i]];

    while (s[a[i]] > 1) {
      --s[a[j]];
      ++j;
    }

    res = max(res, i - j + 1);
  }
  cout << res << endl;

  return 0;
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

int n, a[N], s[N];

int main() {
  cin >> n;

  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  int res = 0;
  for (int i = 0, j = 0; i < n; ++i) {
   ++s[a[i]];
   while (s[a[i]] > 1) {
    --s[a[j]];
    ++j;
   }
   res = max(res, i - j + 1);
  }
  cout << res << endl;

  return 0;
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

int n, a[N], s[N] = {0};

int main() {
  cin >> n;

  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  int res = 0;
  for (int i = 0, j = 0; i < n; ++i) {
    ++s[a[i]];
    while (s[a[i]] > 1) {
      --s[a[j]];
      ++j;
    }
    res = max(res, i - j + 1);
  }

  cout << res << endl;

  return 0;
} */
/* #include <iostream>

using namespace std;

int main() {
  int n = 10;

  for (int k = 3; k >= 0; --k) {
    cout << (n >> k & 1);
  }

  return 0;
} */
/* #include <iostream>

using namespace std;

int main() {
  int n = 10;

  for (int k = 3; k >= 0; --k) {
    cout << (n >> k & 1);
  }

  return 0;
} */
/* #include <iostream>

using namespace std;

int lowbit(int x) { return x & -x; }

int main() {
  int n;
  cin >> n;

  while (n--) {
    int x;
    cin >> x;

    int res = 0;
    while (x) {
      x -= lowbit(x);
      ++res;
    }
    cout << res << ' ';
  }
  return 0;
} */
/* #include <iostream>

using namespace std;

int lowbit(int x) {
  return x & -x;
}

int main() {
  int n;
  cin >> n;

  while (n--) {
    int x;
    cin >> x;

    int res = 0;
    while (x) {
      x -= lowbit(x);
      ++res;
    }
    cout << res << ' ';
  }
} */
/* #include <iostream>

using namespace std;

int lowbit(int x) {
  return x & -x;
}

int main() {
  int n;
  cin >> n;

  while (n--) {
    int x;
    cin >> x;

    int res = 0;
    while (x) {
      x -= lowbit(x);
      ++res;
    }

    cout << res << endl;
  }

  return 0;
} */
/* #include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> PII;

const int N = 300010;

int n, m;
int a[N], s[N];

vector<int> alls;
vector<PII> add, query;

int find(int x) {
  int l = 0, r = alls.size() - 1;
  while (l < r) {
    int mid = l + r >> 1;
    if (alls[mid] >= x) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  return r + 1;
}

int main(){
  cin >> n >> m;

  for (int i = 0; i < n; ++i) {
    int x, c;
    cin >> x >> c;
    add.push_back({x, c});
    alls.push_back(x);
  }

  for (int i = 0;i < m; ++i) {
    int l,r;
    cin >> l >> r;
    query.push_back({l, r});
    alls.push_back(l);
    alls.push_back(r);
  }

  sort(alls.begin(), alls.end());
  alls.erase(unique(alls.begin(), alls.end()), alls.end());

  for (auto item : add) {
    int x = find(item.first);
    a[x] += item.second;
  }

  for (int i = 1; i <= alls.size(); ++i) {
    s[i] = s[i - 1] + a[i];
  }

  for (auto item : query) {
    int l = find(item.first), r = find(item.second);
    cout << s[r] - s[l - 1] << endl;
  }

  return 0;


} */
/* #include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> PII;

const int N = 300010;

int n, m;
int a[N], s[N];

vector<int> alls;
vector<PII> add, query;

int find(int x) {
  int l = 0, r = alls.size() - 1;
  while (l < r) {
    int mid = l + r >> 1;
    if (alls[mid] >= mid) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  return r + 1;
}

int main() {
  cin >> n >> m;

  for (int i = 0; i < n; ++i) {
    int x, c;
    cin >> x >> c;
    add.push_back({x, c});
    alls.push_back(x);
  }

  for (int i = 0; i < m; ++i) {
    int l, r;
    cin >> l >> r;
    query.push_back({l, r});
    alls.push_back(l);
    alls.push_back(r);
  }

  sort(alls.begin(), alls.end());
  alls.erase(unique(alls.begin(), alls.end()), alls.end());

  for (auto item : add) {
    int x = find(item.first);
    a[x] += item.second;
  }

  for (auto item : query) {
    int l = find(item.first), r = find(item.second);
    cout << s[r] - s[l - 1] << endl;
  }

  return 0;
} */
/* #include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> PII;

const int N = 300010;

int n, m;
int a[N], s[N];

vector<int> alls;
vector<PII> add, query;

int find(int x) {
  int l = 0, r = alls.size() - 1;
  while (l < r) {
    int mid = l + r >> 1;
    if (alls[mid] >= x) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  return r + 1;
}

int main() {
  cin >> n >> m;

  for (int i = 0; i < n; ++i) {
    int x, c;
    cin >> x >> c;
    add.push_back({x, c});

    alls.push_back(x);
  }

  for (int i = 0; i < n; ++i) {
    int l, r;
    cin >> l >> r;
    query.push_back({l, r});
    alls.push_back(l);
    alls.push_back(r);
  }

  sort(alls.begin(), alls.end());
  alls.erase(unique(alls.begin(), alls.end()), alls.end());

  for (auto item : add) {
    int x = find(item.first);
    a[x] += item.second;
  }

  for (int i = 1; i <= alls.size(); ++i) {
    s[i] = s[i - 1] + a[i];
  }

  for (auto item : query) {
    int l = find(item.first), r = find(item.second);
    cout << s[r] - s[l - 1] << endl;
  }

  return 0;
} */
/* #include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> PII;

const int N = 300010;

int n, m;
int a[N], s[N];

vector<int> alls;
vector<PII> add, query;

int find(int x) {
  int l = 0, r = alls.size();

  while (l < r) {
    int mid = l + r >> 1;
    if (alls[mid] >= x) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  return r + 1;
}

int main() {
  cin >> n >> m;

  for (int i = 0; i < n; ++i) {
    int x, c;
    cin >> x >> c;
    add.push_back({x, c});
    alls.push_back(x);
  }

  for (int i = 0; i < m; ++i) {
    int l, r;
    cin >> l >> r;
    query.push_back({l, r});
    alls.push_back(l);
    alls.push_back(r);
  }

  sort(alls.begin(), alls.end());
  alls.erase(alls.unique(alls.begin(), alls.end()), alls.end());

  for (auto item : add) {
    int x = find(item.first);
    a[x] += item.second;
  }

  for (int i = 1; i <= alls.size(); ++i) {
    s[i] = s[i - 1] + a[i];
  }

  for (auto item : query) {
    int l = find(item.first), r = find(item.second);
    cout << s[r] - s[l - 1] << endl;
  }

  return 0;
} */
/* #include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> PII;

const int N = 300010;

int n, m;
int a[N], s[N];

vector<int> alls;
vector<PII> add, query;

int find(int x) {
  int l = 0, r = alls.size();
  while (l < r) {
    int mid = l + r >> 1;
    if (alls[mid] >= x) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }

  return r + 1;
}

int main() {
  cin >> n >> m;

  for (int i = 0; i < n; ++i) {
    int x, c;
    cin >> x >> c;
    add.push_back({x, c});
    alls.push_back(x);
  }

  for (int i = 0; i < n; ++i) {
    int l, r;
    cin >> l >> r;
    query.push_back({l, r});
    alls.push_back(l);
    alls.push_back(r);
  }

  sort(alls.begin(), alls.end());
  alls.erase(unique(alls.begin(), alls.end()), alls.end());

  for (auto item : add) {
    int x = find(item.first);
    a[x] += item.second;
  }

  for (int i = 1; i < alls.size(); ++i) {
    s[i] = s[i - 1] + a[i];
  }

  for (auto item : query) {
    int l = find(item.first), r = find(item.second);
    cout << s[r] - s[l - 1] << endl;
  }

  return 0;
} */
/* #include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef pair<int, int> PII;

const int N = 100010;

int n;
vector<PII> segs;

void merge(vector<PII> &segs) {
  vector<PII> res;

  sort(segs.begin(), segs.end());


  int st = -2e9, ed = -2e9;

  for (auto seg : segs) {
    if (ed < seg.first) {
      if (st != -2e9) {
        res.push_back({st, ed});
      }
      st = seg.first, ed = seg.second;
    } else {
      ed = max(ed, seg.second);
    }
  }

  if (st != -2e9) {
    res.push_back({st, ed});
  }

  segs = res;
}

int main() {
  cin >> n;

  for (int i = 0; i < n; ++i) {
    int l, r;
    cin >> l >> r;
    segs.push_back({l, r});
  }

  merge(segs);

  cout << segs.size() << endl;

  return 0;
} */
/* #include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> PII;

const int N = 100010;

int n;
vector<PII> segs;

void merge(vector<PII> &segs) {
  vector<PII> res;

  sort(segs.begin(), segs.end());

  int st = -2e9, ed = -2e9;

  for (auto seg : segs) {
    if (ed < seg.first) {
      if (st != -2e9) {
        res.push_back({st, ed});
      }
    } else {
      ed = max(ed, seg.second);
    }
  }
  if (st != -2e9) {
    res.push_back({st, ed});
  }

  segs = res;
}

int main() {
  cin >> n;

  for (int i = 0; i < n; ++i) {
    int l, r;
    cin >> l >> r;
    segs.push_back({l, r});
  }
  merge(segs);

  cout << segs.size() << endl;

  return 0;
} */
/* #include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int N = 100010;

typedef pair<int, int> PII;

int n;
vector<PII> segs;

void merge(vector<PII> &segs) {
  vector<PII> res;

  int st = -2e9, ed = -2e9;

  for (auto seg : segs) {
    if (ed < seg.first) {
      if (st != -2e9) {
        res.push_back({st, ed});
      }
      st = seg.first, ed = seg.second;
    } else {
      ed = max(ed, seg.second);
    }
  }

  segs = res;
}

int main() {
  cin >> n;

  for (int i = 0; i < n; ++i) {
    int l, r;
    cin >> l >> r;
    segs.push_back({l, r});
  }

  merge(segs);

  cout << segs.size() << endl;

  return 0;
} */
/* #include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> PII;

const int N = 100010;

int n, m;
int a[N], s[N];

vector<int> alls;
vector<PII> add, query;

int find(int x) {
  int l = 0, r = alls.size() - 1;

  while (l < r) {
    int mid = l + (r - l) / 2;

    if (alls[mid] >= x) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }

  return r + 1;
}

int main() {
  cin >> n >> m;

  for (int i = 0; i < n; ++i) {
    int x, c;
    cin >> x >> c;
    add.push_back({x, c});
    alls.push_back(x);
  }

  for (int i = 0; i < m; ++i) {
    int l, r;
    cin >> l >> r;
    query.push_back({l, r});
    alls.push_back(l);
    alls.push_back(r);
  }

  sort(alls.begin(), alls.end());
  alls.erase(unique(alls.begin(), alls.end()), alls.end());

  for (auto item : add) {
    int x = item.first;
    a[x] += item.second;
  }

  for (int i = 1; i <= alls.size(); ++i) {
    s[i] = s[i - 1] + a[i];
  }

  for (auto item : query) {
    int l = find(item.first), r = find(item.second);
    cout << s[r] - s[l - 1] << endl;
  }

  return 0;
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

// head 表示头结点的下标
// e[i] 表示节点 i 的值
// ne[i] 表示节点 i 的 next 指针
// idx 存储当前已经使用的点, 也表示已经使用的节点数量
int head, e[N], ne[N], idx;

// 初始化
void init() {
  head = -1;  // 表示链表为空
  idx = 0;    // 表示还没有使用任何节点
}

// 将 x 插入到头结点
void add_to_head(int x) {
  e[idx] = x;
  ne[idx] = head;
  head = idx;
  ++idx;
}

// 将 x 插入到下标是 k 的点后面
void add(int k, int x) {
  e[idx] = x;
  ne[idx] = ne[k];
  ne[k] = idx;
  ++idx;
}

// 将下标是 k 的点后面的点删掉
void remove(int k) { ne[k] = ne[ne[k]]; }

int main() {
  int m;
  cin >> m;

  init();

  while (m--) {
    int k, x;
    char op;

    cin >> op;

    if (op == 'H') {
      cin >> x;
      add_to_head(x);
    } else if (op == 'D') {
      cin >> k;
      if (!k) {
        head = ne[head];
      }
      remove(k - 1);
    } else {
      cin >> k >> x;
      add(k - 1, x);
    }
  }

  for (int i = head; i != -1; i = ne[i]) {
    cout << e[i] << ' ';
  }
  cout << endl;

  return 0;
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

int head, e[N], ne[N], idx;

void init() {
  head = -1;
  idx = 0;
}

void add_to_head(int x) {
  e[idx] = x;
  ne[idx] = head;
  head = idx;
  ++idx;
}

void add(int k, int x) {
  e[idx] = x;
  ne[idx] = ne[k];
  ne[k] = idx;
  ++idx;
}

void remove(int k) { ne[k] = ne[ne[k]]; }

int main() {
  int m;
  cin >> m;

  init();

  while (m--) {
    int k, x;
    char op;

    cin >> op;

    if (op == 'H') {
      cin >> x;
      add_to_head(x);
    } else if (op == 'D') {
      cin >> k;
      if (!k) {
        head = ne[head];
      }
      remove(k - 1);
    } else {
      cin >> k >> x;
      add(k - 1, x);
    }

    for (int i = head; i != -1; i = ne[i]) {
      cout << e[i] << ' ';
    }
    cout << endl;

    return 0;
  }
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

int head, e[N], ne[N], idx;

void init() {
  head = -1;
  idx = 0;
}

void add_to_head(int x) {
  e[idx] = x;
  ne[idx] = head;
  head = idx;
  ++idx;
}

void add(int k, int x) {
  e[idx] = x;
  ne[idx] = ne[k];
  ne[k] = idx;
  ++idx;
}

void remove(int k) {
  ne[k] = ne[ne[k]];
}

int main() {
  int m;
  cin >> m;

  init();

  while (m--) {
    int k, x;
    char op;

    cin >> op;

    if (op == 'H') {
      cin >> x;
      add_to_head(x);
    } else if (op == 'D') {
      cin >> k;
      if (!k) {
        head = ne[head];
      }
      remove(k - 1);
    } else {
      cin >> k >> x;
      add(k - 1, x);
    }
  }

  for (int i = head; i != -1; i = ne[i]) {
    cout << e[i] << ' ';
  }
  cout << endl;

  return 0;
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

int head, e[N], ne[N], idx;

void init() {
  head = -1;
  idx = 0;
}

void add_to_head(int x) {
  e[idx] = x;
  ne[idx] = ne[head];
  head = idx;
  ++idx;
}

void add(int k, int x) {
  e[idx] = x;
  ne[idx] = ne[k];
  ne[k] = idx;
  ++idx;
}

int main() {
  int m;
  cin >> m;

  init();

  while (m--) {
    int k, x;
    char op;

    cin >> op;

    if (op = 'H') {
      cin >> x;
      add_to_head(x);
    } else if (op == 'D') {
      cin >> k;
      if (!k) {
        head = ne[head];
      }
      remove(k - 1);
    } else {
      cin >> k >> x;
      add(k - 1, x);
    }
  }

  for (int i = head; i != -1; i = ne[i]) {
    cout << e[i] << ' ';
  }
  cout << endl;

  return 0;
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

int m;
int e[N], l[N], r[N], idx;

void init() {
  r[0] = 1, l[1] = 0;
  idx = 2;
}

void add(int k, int x) {
  e[idx] = x;
  r[idx] = r[k];
  l[idx] = k;
  l[r[k]] = idx;
  r[k] = idx;
}

void remove(int k) {
  r[l[k]] = r[k];
  l[r[k]] = l[k];
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

int m;
int e[N], l[N], r[N], idx;

void init() {
  l[1] = 0;
  r[0] = 1;
  idx = 2;
}

void add(int k, int x) {
  e[idx] = x;
  r[idx] = r[k];
  l[idx] = k;
  l[r[k]] = idx;
  r[k] = idx;
  ++idx;
}

void remove(int k) {
  r[l[k]] = r[k];
  l[r[k]] = l[k];
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

int e[N], l[N], r[N], idx;

void init() {
  l[1] = 0, r[0] = 1;
  idx = 2;
}

void add(int k, int x) {
  e[idx] = x;
  r[idx] = r[k];
  r[k] = idx;
  l[r[k]] = idx;
  r[k] = idx;
  ++idx;
}

void remove(int k) {
  r[l[k]] = r[k];
  l[r[k]] = l[k];
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

int n;
int stk[N], tt = 0;

int main() {
  cin >> n;

  // 遍历序列中的元素
  for (int i = 0; i < n; ++i) {
    int x;
    // 输入相应的元素
    cin >> x;

    // 如果栈非空并且栈顶元素大于等于 x
    // 弹出栈顶
    while (tt && stk[tt] >= x) {
      --tt;
    }

    // 此时栈顶元素不存在或者更小
    if (tt) { // 存在就输出
      cout << stk[tt] << ' ';
    } else { // 不存在就输出 -1
      cout << -1 << ' ';
    }
    // 更新栈顶元素
    stk[++tt] = x;
  }

  return 0;
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

int n;
int stk[N], tt = 0;

int main() {
  cin >> n;

  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;

    while (tt && stk[tt] >= x) {
      --tt;
    }

    if (tt) {
      cout << stk[tt] << ' ';
    } else {
      cout << -1 << ' ';
    }

    stk[++tt] = x;
  }

  return 0;
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

int n;
int stk[N], tt = 0;

int main() {
  cin >> n;

  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;

    while (tt && stk[tt] >= x) {
      --tt;
    }

    if (tt) {
      cout << stk[tt] << ' ';
    } else {

    }

    stk[++tt] = x;
  }
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

int n;
int stk[N], tt;

int main() {
  cin >> n;

  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;

    while (tt && stk[tt] >= x) {
      --tt;
    }

    if (tt) {
      cout << stk[tt] << ' ';
    } else {
      cout << -1 << ' ';
    }

    stk[++tt] = x;
  }

  return 0;
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

int n, stk[N], tt;

int main() {
  cin >> n;

  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;

    while (tt && stk[tt] >= x) {
      --tt;
    }

    if (tt) {
      cout << stk[tt] << ' ';
    } else {
      cout << -1 << ' ';
    }

    cout << endl;
  }

  return 0;
} */
/* #include <iostream>

using namespace std;

const int N = 1000010;

int n, k;        // 数组大小和滑动窗口大小
int a[N], q[N];  // 一个存数组, 一个存队列下标

int main() {
  cin.tie(0);
  cin >> n >> k;

  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  int hh = 0, tt = -1;  // 定义头尾
  for (int i = 0; i < n; ++i) {
    // 如果头小于尾, 且判断头元素是否超出了范围
    if (hh <= tt && i - k + 1 > q[hh]) {
      ++hh;
    }

    // 头小于尾, 且尾的值大于 a[i]
    // 将尾部弹出
    while (hh <= tt && a[q[tt]] >= a[i]) {
      --tt;
    }

    // 将新的插入进尾部
    q[++tt] = i;

    // 必须等到滑动窗口形成后才可以进行输出
    if (i >= k - 1) {
      // 头部便是最小元素
      cout << a[q[hh]] << ' ';
    }
  }

  cout << endl;

  hh = 0, tt = -1;
  for (int i = 0; i < n; ++i) {
    if (hh <= tt && i - k + 1 > q[hh]) {
      ++hh;
    }

    while (hh <= tt && a[q[tt]] <= a[i]) {
      --tt;
    }

    q[++tt] = i;

    if (i >= k - 1) {
      cout << a[q[hh]] << ' ';
    }
  }

  cout << endl;

  return 0;
} */
/* #include <iostream>

using namespace std;

const int N = 1000010;

int n, k;
int a[N], q[N];

int main() {
  cin >> n >> k;

  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  int hh = 0, tt = -1;
  for (int i = 0; i < n; ++i) {
    if (hh <= tt && i - k + 1 > q[hh]) {
      ++hh;
    }

    while (hh <= tt && a[q[tt]] >= a[i]) {
      --tt;
    }

    q[++tt] = i;

    if (i >= k - 1) {
      cout << a[q[hh]] << ' ';
    }
  }
  cout << endl;

  hh = 0, tt = -1;
  for (int i = 0; i < n; ++i) {
    if (hh <= tt && i - k + 1 > q[hh]) {
      ++hh;
    }

    while (hh <= tt && a[q[tt]] <= a[i]) {
      --tt;
    }

    q[++tt] = i;

    if (i >= k - 1) {
      cout << a[q[hh]] << ' ';
    }
  }
  cout << endl;

  return 0;
} */
/* #include <iostream>

using namespace std;

const int N = 1000010;

int n, k;
int a[N], q[N];

int main() {
  cin >> n >> k;

  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  int hh = 0, tt = -1;
  for (int i = 0; i < n; ++i) {
    if (hh <= tt && i - k + 1 > q[hh]) {
      ++hh;
    }

    while (hh <= tt && a[q[tt]] >= a[i]) {
      --tt;
    }

    q[++tt] = i;

    if (i >= k - 1) {
      cout << a[q[hh]] << ' ';
    }
  }
  cout << endl;

  return 0;
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

int n, k, a[N], q[N];

int main() {
  cin >> n >> k;

  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  int hh = 0, tt = -1;
  for (int i = 0; i < n; ++i) {
    if (hh <= tt && i - k + 1 > q[hh]) {
      ++hh;
    }

    if (hh <= tt && a[q[tt]] >= a[i]) {
      --tt;
    }

    q[++tt] = i;

    if (i > k) {
      cout << a[q[hh]] << ' ';
    }
    cout << endl;

    return 0;
  }

  hh = 0, tt = -1;
  for (int i = 0; i < n; ++i) {
    if (hh <= tt && i - k + 1 > q[hh]) {
      ++hh;
    }

    while (hh <= tt && a[q[tt]] >= a[i]) {
      --tt;
    }

    q[++tt] = i;

    if (i >= k - 1) {
      cout << a[q[hh]] << ' ';
    }
  }

  cout << endl;

  return 0;
} */
/* #include <iostream>

using namespace std;

const int N = 1000010;

int n, k, a[N], q[N];

int main() {
  cin >> n >> k;

  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  int hh = 0, tt = -1;
  for (int i = 0; i < n; ++i) {
    if (hh <= tt && i - k + 1 > q[hh]) {
      ++hh;
    }

    while (hh <= tt && a[q[tt]] >= a[i]) {
      --tt;
    }

    q[++tt] = i;

    if (i >= k - 1) {
      cout << a[q[hh]] << ' ';
    }
  }
  cout << endl;

  hh = 0, tt = -1;
  for (int i = 0; i < n; ++i) {
    if (hh <= tt && i - k + 1 > q[hh]) {
      ++hh;
    }

    while (hh <= tt && a[q[tt]] <= a[i]) {
      --tt;
    }

    q[++tt] = i;

    if (i >= k - 1) {
      cout << a[q[hh]] << ' ';
    }
  }
  cout << endl;

  return 0;
} */
/* #include <iostream>

using namespace std;

const int N = 1000010;

int n, k, a[N], q[N];

int main() {
  cin >> n >> k;

  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }


  int hh = 0, tt = -1;
  for (int i = 0; i < n; ++i) {
    if (hh <= tt && i - k + 1 > q[hh]) {
      ++hh;
    }

    while (hh <= tt && a[q[hh]] >= a[i]) {
      --tt;
    }

    q[++tt] = i;

    if (i >= k - 1) {
      cout << a[q[hh]] << ' ';
    }
  }

  hh = 0, tt = -1;
  for (int i = 0; i < n; ++i) {
    if (hh <= tt && i - k + 1 > q[hh]) {
      ++hh;
    }

    while (hh <= tt && a[q[hh]] <= a[i]) {
      --tt;
    }

    q[++tt] = i;

    if (i >= k - 1) {
      cout << a[q[hh]] << ' ';
    }
  }
  cout << endl;

  return 0;
} */
/* template <class T>
void bubbleSort(T *arr, int len) {
  for (int i = 0; i < len; ++i) {
    for (int j = 0; j < len - 1 - i; ++j) {
      if (arr[i] > arr[j]) swap(arr[i], arr[j]);
    }
  }
}

template <class T>
void insertSort(T *arr, int len) {
  int i, j, key;

  for (i = 1; i < len; ++i) {
    key = arr[i];
    for (j = i - 1; j >= 0 && arr[j] > key; --j) {
      arr[j + 1] = arr[j];
    }
    arr[j + 1] = key;
  }
}

template <class T>
void selectionSort(T *arr, int len) {
  int i, j, min_idx;

  for (i = 0; i < len; ++i) {
    min_idx = i;

    for (j = i + 1; j < len; ++j) {
      if (arr[i] < arr[j]) {
        min_idx = j;
      }
    }
    swap(arr[min_idx], arr[i]);
  }
} */
/* #include <cstring>
#include <iostream>

using namespace std;


// str: 主串
// sub: 子串
// 返回值: 返回子串在主串中的下标，不存在返回 -1

int BF(const char *str, const char *sub) {
  if (!str || !sub) {
    return -1;
  }

  int len_str = strlen(str), len_sub = strlen(sub);

  int i = 0, j = 0;

  while (i < len_str && j < len_sub) {
    if (str[i] == sub[j]) {
      ++i, ++j;
    } else {
      i = i - j + 1;
      j = 0;
    }
  }

  if (j >= len_sub) {
    return i - j;
  } else {
    return -1;
  }
}

int main() {
  cout << BF("ababcabcdabcde", "abcd") << endl;
  return 0;
} */
/* #include <iostream>
#include <cstring>

using namespace std;

int BF(const char *str, const char *sub) {
  if (!str || !sub) {
    return -1;
  }

  int len_str = strlen(str), len_sub = strlen(sub), i = 0, j = 0;

  while (i < len_str && j < len_sub) {
    if (str[i] == str[j]) {
      ++i, ++j;
    } else {
      i = i - j + 1;
      j = 0;
    }
  }

  if (j >= len_sub) {
    return i - j;
  } else {
    return -1;
  }
} */
/* #include <iostream>
#include <cstring>

using namespace std;

int BF(const char *str, const char *sub) {
  if (!sub || !sub) {
    return -1;
  }

  int len_str = strlen(str), len_sub = strlen(sub), i = 0, j = 0;

  while (i < len_str && j < len_sub) {
    if (str[i] == sub[j]) {
      ++i, ++j;
    } else {
      i = i - j + 1;
      j = 0;
    }
  }

  if (j >= len_sub) {
    return i - j;
  } else {
    return -1;
  }
} */
/* #include <cstring>
#include <iostream>

using namespace std;

void getNext(const char *sub, int *next) {
  next[0] = -1, next[1] = 0;

  int len_sub = strlen(sub);
  int i = 2;  // 当前 i 下标
  int k = 0;  // 前一项的 k

  while (i < len_sub) {
    if (k == -1 || sub[i - 1] == sub[k]) {
      next[i] = k + 1;
      ++i, ++k;
    } else {
      k = next[k];
    }
  }
}

// str: 代表主串
// sub: 代表子串
// pos: 代表从主串的 pos 位置开始找
int KMP(const char *str, const char *sub, int pos) {
  int len_str = strlen(str), len_sub = strlen(sub);

  if (len_str == 0 || len_sub == 0) {
    return -1;
  }

  if (pos < 0 || pos >= len_str) {
    return -1;
  }

  int *next = new int[len_sub];

  int i = pos;  // 遍历主串
  int j = 0;    // 遍历子串

  getNext(sub, next);

  while (i < len_str && j < len_sub) {
    if (j == -1 || str[i] == sub[j]) {
      ++i, ++j;
    } else {
      j = next[j];
    }
  }

  delete[] next;

  if (j >= len_sub) {
    return i - j;
  }

  return -1;
}

int main() {
  cout << KMP("adadsaca", "sa", 0) << endl;
  return 0;
} */
/* #include <iostream>

using namespace std;

void getNext(const char *sub, int *next) {
  next[0] = -1, next[1] = 0;

  int len_sub = strlen(sub);
  int i = 2, k = 0;

  while (i < len_sub) {
    if (k == -1 || sub[i - 1] == sub[k]) {
      next[i++] = ++k;
    } else {
      k = next[k];
    }
  }
}

int KMP(const char *str, const char *sub) {
  int len_str = strlen(str), len_sub = strlen(sub);

  if (!len_str || !len_sub) {
    return -1;
  }

  int *next = new int[len_sub];

  int i = 0, j = 0;

  getNext(sub, next);

  while (i < len_str && j < len_sub) {
    if (j == -1 || str[i] == sub[j]) {
      ++i, ++j;
    } else {
      j = next[j];
    }
  }

  delete[] next;

  if (j >= len_sub) {
    return i - j;
  }

  return -1;
} */
/* #include <cstring>
#include <iostream>

using namespace std;

void getNext(const char *sub, int *next) {
  int len_sub = strlen(sub), i = 2;
  int k = 0;

  next[0] = -1, next[1] = 0;

  while (i < len_sub) {
    if (k == -1 || sub[i - 1] == sub[k]) {
      next[i++] = ++k;
    } else {
      k = next[k];
    }
  }
}

int KMP(const char *str, const char *sub) {
  if (!str || !sub) {
    return -1;
  }

  int len_str = strlen(str), len_sub = strlen(sub);

  int *next = new int[len_sub];

  int i = 0, j = 0;

  getNext(sub, next);

  while (i < len_str && j < len_sub) {
    if (j == -1 || str[i] == sub[j]) {
      ++i, ++j;
    } else {
      j = next[j];
    }
  }

  if (j >= len_sub) {
    return i - j;
  }

  return -1;
} */
/* #include <cstring>
#include <iostream>

using namespace std;

void getNext(const char *sub, int *next) {
  int len_sub = strlen(sub), i = 2, k = 0;

  next[0] = -1, next[1] = 0;

  while (i < len_sub) {
    if (k == -1 || sub[i - 1] == sub[k]) {
      next[i++] = ++k;
    } else {
      k = next[k];
    }
  }
}

int KMP(const char *str, const char *sub) {
  if (!str || !sub) {
    return -1;
  }

  int len_str = strlen(str), len_sub = strlen(sub), i = 0, j = 0;
  int *next = new int[len_sub];

  getNext(sub, next);

  while (i < len_str && j < len_sub) {
    if (j == -1 || str[i] == sub[j]) {
      ++i, ++j;
    } else {
      j = next[j];
    }
  }

  delete[] next;

  if (j >= len_sub) {
    return i - j;
  }

  return -1;
} */
/* #include <cstring>
#include <iostream>

using namespace std;

void getNext(const char *sub, int *next) {
  int len_sub = strlen(sub), i = 2, k = 0;

  while (i < len_sub) {
    if (k == -1 || sub[i - 1] == sub[k]) {
      next[i++] = ++k;
    } else {
      k = next[k];
    }
  }
}

int KMP(const char *str, const char *sub) {
  if (!(str || sub)) {
    return -1;
  }

  int len_str = strlen(str), len_sub = strlen(sub);
  int i = 0, j = 0;

  int *next = new int[len_sub];

  getNext(sub, next);

  while (i < len_str && j < len_sub) {
    if (j == -1 || str[i] == str[j]) {
      ++i, ++j;
    } else {
      j = next[j];
    }
  }

  if (j >= len_sub) {
    return i - j;
  }

  return -1;
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

int head, e[N], ne[N], idx;

void init() {
  head = -1;
  idx = 0;
}

void addToHead(int x) {
  e[idx] = x;
  ne[idx] = head;
  head = idx;
  ++idx;
}

void add(int k, int x) {
  e[idx] = x;
  ne[idx] = ne[k];
  ne[k] = idx;
  ++idx;
}

void remove(int k) {
  ne[k] = ne[ne[k]];
}

int main() {
  int m;
  cin >> m;

  init();

  while (m--) {
    int k, x;
    char op;

    cin >> op;

    if (op == 'H') {
      cin >> x;
      addToHead(x);
    } else if (op == 'D') {
      cin >> k;
      if (!k) {
        head = ne[head];
      }
      remove(k - 1);
    } else {
      cin >> k >> x;
      add(k - 1, x);
    }
  }

  for (int i = head; i != -1; i = ne[i]) {
    cout << e[i] << ' ';
  }
  cout << endl;

  return 0;
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

int m;
int e[N], l[N], r[N], idx;

void init() {
  r[0] = 0, l[1] = -1;
  idx = 2;
}

void add(int k, int x) {
  e[idx] = x;
  r[idx] = r[k];
  l[idx] = k;
  l[r[k]] = idx;
  r[k] = idx;
  ++idx;
}

void remove(int k) {
  r[l[k]] = r[k];
  l[r[k]] = l[k];
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

int m, e[N], l[N], r[N], idx;

void init() {
  r[0] = 0, l[1] = -1;
  idx = 2;
}

void add(int k, int x) {
  e[idx] = x;
  r[idx] = r[k];
  l[idx] = k;
  l[r[k]] = idx;
  r[k] = idx;
  ++idx;
}

void remove(int k) {
  r[l[k]] = r[k];
  l[r[k]] = l[k];
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

int e[N], l[N], r[N], idx;

void init() {
  r[0] = 0, l[1] = -1;
  idx = 2;
}

void add(int k, int x) {
  e[idx] = x;
  r[idx] = r[k];
  l[r[k]] = idx;
  l[idx] = k;
  r[k] = idx;
  ++idx;
}

void remove(int k) {
  r[l[k]] = r[k];
  l[r[k]] = l[k];
} */
/* #include <cstring>
#include <iostream>

using namespace std;

void getNext(const char *sub, int *next) {
  int len_sub = strlen(sub), i = 2, k = 0;

  while (i < len_sub) {
    if (k == -1 && sub[i - 1] == sub[k]) {
      next[i++] = ++k;
    } else {
      k = next[k];
    }
  }
}

int KMP(const char *str, const char *sub) {
  if (!str || !sub) {
    return -1;
  }

  int len_str = strlen(str), len_sub = strlen(sub), i = 0, j = 0;
  int *next = new int[len_sub];

  getNext(sub, next);

  while (i < len_str && j < len_sub) {
    if (str[i] == sub[j] || j == -1) {
      ++i, ++j;
    } else {
      j = next[j];
    }
  }

  if (j >= len_sub) {
    return i - j;
  }

  return -1;
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

int l[N], r[N], e[N], idx;

void init() {
  l[1] = -1, r[0] = 0;
  idx = 2;
}

void add(int k, int x) {
  e[idx] = x;
  r[idx] = r[k];
  l[idx] = k;
  l[r[k]] = idx;
  r[k] = idx;
  ++idx;
}

void remove(int k) {
  r[l[k]] = r[k];
  l[r[k]] = l[k];
} */
/* #include <iostream>

using namespace std;

const int N = 100010;



int main() {
  int n, stk[N], tt = 0;

  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;

    while (tt && stk[tt] >= x) {
      --tt;
    }

    if (tt) {
      cout << stk[tt] << ' ';
    } else {
      cout << -1 << ' ';
    }

    stk[++tt] = x;
  }

  return 0;
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

int main() {
  int stk[N], tt = 0, n;
  cin >> n;


  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;

    while (tt && stk[tt] >= x) {
      --tt;
    }

    if (tt) {
      cout << stk[tt] << ' ';
    } else {
      cout << -1 << ' ';
    }
  }

  return 0;
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

int main() {
  cin >> n;

  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;

    while (tt && stk[tt] >= x) {
      --tt;
    }

    if (tt) {
      cout << stk[tt] << ' ';
    } else {
      cout << -1 << ' ';
    }

    stk[++tt] = x;
  }
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

int main() {
  int stk[N], n, tt = 0;

  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;

    while (tt && stk[tt] >= x) {
      --tt;
    }

    if (tt) {
      cout << stk[tt] << ' ';
    } else {
      cout << -1 << ' ';
    }

    stk[++tt] = x;
  }

  return 0;
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

int stk[N], n, tt = 0;

int main() {
  cin >> n;

  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;

    while (tt && stk[tt] >= x) {
      --tt;
    }

    if (tt) {
      cout << stk[tt] << ' ';
    } else {
      cout << -1 << ' ';
    }

    stk[++tt] = x;
  }

  return 0;
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

int main() {
  int n, stk[N], tt = 0;

  cin >> n;

  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;

    while (tt && stk[tt] >= x)  {
      --tt;
    }

    if (tt) {
      cout << stk[tt] << ' ';
    } else {
      cout << -1 << ' ';
    }
  }
  cout << endl;

  return 0;
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

int n, k;
int a[N], q[N];

int main() {
  cin >> n >> k;

  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  int hh = 0, tt = -1;
  for (int i = 0; i < n; ++i) {
    if (hh <= tt && i - k + 1 > q[hh]) {
      ++hh;
    }

    while (hh <= tt && a[q[tt]] >= a[i]) {
      --tt;
    }

    q[++tt] = i;

    if (i >= k - 1) {
      cout << a[q[hh]] << ' ';
    }
  }

  cout << endl;
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

int n, k, a[N], q[N];

int main() {
  cin >> n >> k;

  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  int hh = 0, tt = -1;
  for (int i = 0; i < n; ++i) {
    if (hh <= tt && i - k >= q[hh]) {
      ++hh;
    }

    while (hh <= tt && a[q[tt]] >= a[i]) {
      --tt;
    }

    q[++tt] = i;

    if (i >= k - 1) {
      cout << a[q[hh]] << ' ';
    }
  }
  cout << endl;

  hh = 0, tt = -1;
  for (int i = 0; i < n; ++i) {
    if (hh <= tt && i - k + 1 > q[hh]) {
      ++hh;
    }

    while (hh <= tt && a[q[tt]] <= a[i]) {
      --tt;
    }

    q[++tt] = i;

    if (i >= k - 1) {
      cout << a[q[hh]] << ' ';
    }
  }
  cout << endl;

  return 0;
} */
/* #include <iostream>

using namespace std;

const int N = 100010;

int n, k, a[N], q[N];

int main() {
  cin >> n >> k;

  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  int hh = 0, tt = -1;
  for (int i = 0; i < n; ++i) {
    if (hh <= tt && i - k >= q[hh]) {
      ++hh;
    }

    while (hh <= tt && a[q[tt]] >= a[i]) {
      --tt;
    }

    q[++tt] = i;

    if (i >= k - 1) {
      cout << a[q[hh]] << ' ';
    }
  }
  cout << endl;

  return 0;
} */
/* #include <iostream>
#include <cstring>

using namespace std;

void getNext(const char*sub, int *next) {
  next[0] = -1, next[1] = 0;
  int len_sub = strlen(sub), i = 2, k = 0;

  while (i < len_sub) {
    if (k == -1 || sub[i - 1] == sub[k]) {
      next[i++] = ++k;
    } else {
      k = next[k];
    }
  }
}

int KMP(const char *str, const char *sub) {
  if (!str || !sub) {
    return -1;
  }

  int len_str = strlen(str), len_sub = strlen(sub), i = 0, j = 0;
  int *next = new int[len_sub];

  getNext(sub, next);

  while (i < len_str && j < len_sub) {
    if (j == -1 || str[i] == sub[j]) {
      ++i, ++j;
    } else {
      j = next[j];
    }
  }

  if (j >= len_sub) {
    return i - j;
  }

  return -1;
} */
/* #include <iostream>
#include <cstring>

using namespace std;

void getNext(const char *sub, int *next) {
  next[0] = -1, next[1] = 0;

  int len_sub = strlen(sub), i = 2, k = 0;

  while (i < len_sub) {
    if (i == -1 && sub[i - 1] == sub[k]) {
      next[i++] = ++k;
    } else {
      k = next[k];
    }
  }
}

int KMP(const char *str, const char *sub) {
  if (!str || !sub) {
    return -1;
  }

  int len_str = strlen(str), len_sub = strlen(sub), i = 0, j = 0;
  int *next = new int[len_sub];

  while (i < len_str && j < len_sub) {
    if (j == -1 || str[i] == sub[j]) {
      ++i, ++j;
    } else {
      j = next[j];
    }
  }

  if (j >= len_sub) {
    return i - j;
  }

  return -1;
} */
/* #include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> PII;

const int N = 100010;

int n, m, a[N], s[N];

vector<int> alls;
vector<PII> add, query;

int find(int x) {
  int l = 0, r = alls.size() - 1;

  while (l < r) {
    int mid = l + r >> 1;
    if (alls[mid] >= x) {
      r = mid;
    } else {
      l = mid + 1;
    }

    return r + 1;
  }
}

int main() {
  cin >> n >> m;

  for (int i = 0; i < n; ++i) {
    int x, c;

    cin >> x >> c;

    add.push_back({x, c});

    alls.push_back(x);
  }

  for (int i = 0; i < m; ++i) {
    int l, r;
    cin >> l >> r;
    query.push_back({l, r});

    alls.push_back(l);
    alls.push_back(r);
  }

  sort(alls.begin(), alls.end());
  alls.erase(unique(alls.begin(), alls.end()), alls.end());

  for (auto item : add) {
    int x = find(item.first);
    a[x] += item.second;
  }

  for (int i = 1; i <= alls.size(); ++i) {
    s[i] = s[i - 1] + a[i];
  }

  for (auto item : query) {
    int l = find(item.first), r = find(item.second);
    cout << s[r] - s[l - 1] << endl;
  }

  return 0;
} */
/* #include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> PII;

const int N = 100010;

int n, m, a[N], s[N];

vector<int> alls;
vector<PII> add, query;

int find(int x) {
  int l = 0, r = alls.size() - 1;
  while (l < r) {
    int mid = l + r >> 1;
    if (alls[mid] >= x) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  return r + 1;
}

int main() {
  cin >> n >> m;

  for (int i = 0; i < n; ++i) {
    int x, c;
    cin >> x >> c;
    add.push_back({x, c});
    alls.push_back(x);
  }

  for (int i = 0; i < m; ++i) {
    int l, r;
    cin >> l >> r;
    query.push_back({l, r});

    alls.push_back(l);
    alls.push_back(r);
  }

  sort(alls.begin(), alls.end());
  alls.erase(unique(alls.begin(), alls.end()), alls.end());

  for (auto item : add) {
    int x = find(item.first);
    a[x] = item.second;
  }

  for (int i = 1; i <= alls.size(); ++i) {
    s[i] = s[i - 1] + a[i];
  }

  for (auto item : query) {
    int l = find(item.first), r = find(item.second);
    cout << s[r] - s[l - 1] << endl;
  }

  return 0;
} */
/* #include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> PII;

const int N = 100010;

int n;
vector<PII> segs;

void merge(vector<PII> &segs) {
  vector<PII> res;

  sort(segs.begin(), segs.end());

  int st = -2e9, ed = -2e9;

  for (auto seg : segs) {
    if (ed < seg.first) {
      if (st != -2e9) {
        res.push_back({st, ed});
      }
      st = seg.first, ed = seg.second;
    } else {
      ed = max(ed, seg.second);
    }
  }

  if (st != -2e9) {
    res.push_back({st, ed});
  }

  segs = res;
}

int main() {
  cin >> n;

  for (int i = 0; i < n; ++i) {
    int l, r;
    cin >> l >> r;
    segs.push_back({l, r});
  }

  merge(segs);

  cout << segs.size() << endl;

  return 0;
} */
/* #include <iostream>

#include <algorithm>
#include <vector>

using namespace std;

typedef pair<int, int> PII;

void merge(vector<PII> &segs) {
  vector<PII> res;

  sort(segs.begin(), segs.end());

  int st = -2e9, ed = -2e9;

  for (auto seg : segs) {
    if (ed < seg.first) {
      if (st != -2e9) {
        res.push_back({st, ed});
      }
      st = seg.first, ed = seg.second;
    } else {
      ed = max(ed, seg.second);
    }
  }

  if (st != -2e9) {
    res.push_back({st, ed});
  }

  segs = res;
}

int main() {
  cin >> n;

  for (int i = 0; i < n; ++i) {

  }
} */
/* #include <iostream>

using namespace std;

void getNext(const char* sub, int *next) {
  int len_sub = strlen(sub);
} */
/* #define EPS 0.001f
#include <cmath>

float violentRecSqrt(float x) {
  float y;

  for (y = 0; fabs(x - y * y) > EPS; y += EPS);

  return 1.0f / y;
}

float newtonRecSqrt(float a) {
  float x = 0.5f;
  float ax2 = a * x * x;

  while (fabs(ax2 - 1.0f) > EPS) {
    x = x * (1.5f - 0.5f * ax2);
    ax2 = a * x * x;
  }

  return x;
} */
/* #ifndef _DYNAMIC_ARRAY_
#define _DYNAMIC_ARRAY_
#include <cstring>  // 用于memcpy和memmove
#include <vector>

template <class T>
class DynamicArray {
 public:
  DynamicArray();  // 构造函数
#if defined(_INITIALIZER_LIST_)
  DynamicArray(
      std::initializer_list<T> ilist);  // 支持C++11的初始化列表构造函数
#endif
  DynamicArray(const DynamicArray& other);  // 拷贝构造函数
  ~DynamicArray();                          // 析构函数

  int SetCapacity(int newCapacity);           // 设置内部缓冲区大小
  int GetSize() const;                        // 获取当前有效数据数量
  int Append(const T& element);               // 添加数据至末尾
  int Save(const T* data, int dataLength);    // 存入一批数据
  int Insert(int index, const T& element);    // 插入数据
  bool Remove(int index, T& removedElement);  // 删除数据
  const DynamicArray& operator=(const DynamicArray& other);  // 重载“=”运算符
  const DynamicArray& operator+=(const DynamicArray& other);  // 重载“+=”运算符
  T& operator[](int index);  // 重载“[]”运算符

 private:
  T* data_;       // 内部数据缓冲区
  int size_;      // 当前有效数据数量
  int capacity_;  // 缓冲区大小
};

// 动态数组类的实现
template <class T>
DynamicArray<T>::DynamicArray() : data_(new T[4]), size_(0), capacity_(4) {
  // 初始化之后，将相应的数据设置成 0
  std::memset(data_, 0, sizeof(T) * capacity_);
}

#if defined(_INITIALIZER_LIST_)
template <class T>
DynamicArray<T>::DynamicArray(std::initializer_list<T> ilist)
    : size_(ilist.size()), capacity_(ilist.size() + 4) {
  // 初始化现有的数据容量
  data_ = new T[capacity_];  // new 一个对象
  // 将 ilist 中的数据复制到 data_ 中
  std::memcpy(data_, ilist.begin(), sizeof(T) * size_);
  // 将后面那段多的数据设置为 0
  std::memset(data_ + size_, 0, sizeof(T) * (capacity_ - size_));
}
#endif

template <class T>
DynamicArray<T>::~DynamicArray() {
  // 删除数据
  delete[] data_;   // 将堆上面的那块区域设置为 0
  data_ = nullptr;  // 将指针设置为空指针
  size_ = 0;        // 数量改为 0
  capacity_ = 0;    // 容量改为 0
}

template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other)
    : size_(0), capacity_(other.capacity_), data_(new T[other.capacity_]) {
  if (other.size_ > 0) {  // 如果数据数量不为 0
    // 将 other 中的数据保存进去
    Save(other.data_, other.size_);
  }
}

template <class T>
int DynamicArray<T>::SetCapacity(int newCapacity) {
  // 设置容量
  if (newCapacity <= size_) {  // 如果新的容量比数量小
    return capacity_;          // 返回原有容量
  }

  T* newData = new T[newCapacity];  // new 一个新的区域
  if (!newData) {                   // 异常判断
    return capacity_;
  }

  std::memcpy(newData, data_, sizeof(T) * size_);  // 设置数据
  // 将后面那段设置为 0
  std::memset(newData + size_, 0, sizeof(T) * (newCapacity - size_));
  // 删除数据
  delete[] data_;
  // 数据段变成新的数据
  data_ = newData;
  // 容量改变，数量不变
  capacity_ = newCapacity;

  return capacity_;
}

template <class T>
int DynamicArray<T>::GetSize() const {
  // 得到数量大小
  return size_;
}

template <class T>
int DynamicArray<T>::Append(const T& element) {
  // 在尾部接上一个新元素
  if (size_ >= capacity_) {  // 如果大小大于容量
    // 小于 64 则加上 32；如果大于 64，则加上 原有容量的一半
    int newCapacity =
        (capacity_ < 64) ? capacity_ + 32 : capacity_ + (capacity_ >> 1);
    if (!SetCapacity(newCapacity)) {
      return -1;  // 设置失败，返回 -1
    }
  }

  data_[size_++] = element;  // 将末尾更新为新的元素
  return size_ - 1;          // 返回新元素索引位置
}

template <class T>
int DynamicArray<T>::Save(const T* data, int dataLength) {
  // 将一堆数据报存到后面
  if (!data || dataLength <= 0) {
    return -1;  // 排除异常数据
  }

  if (size_ + dataLength >= capacity_) {  // 如果新的数据长度超过了原有的
    int newCapacity = size_ + dataLength;  // 更新长度
    newCapacity = (newCapacity < 64) ? newCapacity + 32
                                     : newCapacity + (newCapacity >> 1);

    if (!SetCapacity(newCapacity)) {
      return -1;
    }
  }

  // 拷贝过去
  std::memcpy(data_ + size_, data, dataLength * sizeof(T));
  // 更新大小
  size_ += dataLength;

  // 返回新的数据的初始位置
  return size_ - dataLength;
}

template <class T>
int DynamicArray<T>::Insert(int index, const T& element) {
  // 插入数据
  if (index < 0 || index >= capacity_) {
    return -1;  // 排除异常
  }

  if (size_ >= capacity_) {
    // 设置新的容量
    int newCapacity =
        (capacity_ < 64) ? capacity_ + 32 : capacity_ + (capacity_ >> 1);
    if (!SetCapacity(newCapacity)) {
      return -1;
    }
  }

  if (index <= size_ - 1) {
    // 索引是之前的
    // 将原本的数据往后拷贝一格
    std::memmove(data_ + index + 1, data_ + index, sizeof(T) * (size_ - index));
  }

  // 将索引更新为当前元素
  data_[index] = element;
  // 进行索引的更新
  size_++;

  // 返回下标
  return index;
}

// 去除元素
template <class T>
bool DynamicArray<T>::Remove(int index, T& removedElement) {
  if (index < 0 || index >= size_) {
    return false;  // 排除异常
  }

  removedElement = data_[index];  // 保存要去除的元素

  if (index < size_ - 1) {  // 如果不是最后一个元素
                            // 将元素往前移动一位
    std::memmove(data_ + index, data_ + index + 1,
                 (size_ - index - 1) * sizeof(T));
  }

  size_--;      // 改变数量
  return true;  // 返回 true
}

// 重载等于号操作符
template <class T>
const DynamicArray<T>& DynamicArray<T>::operator=(
    const DynamicArray<T>& other) {
  // 如果两个地址不一致
  if (this != &other) {
    delete[] data_;               // 删除原有的数据
    capacity_ = other.capacity_;  // 更新容量
    size_ = 0;                    // 熟练设置为 0
    data_ = new T[capacity_];     // new 一个新的
    if (other.size_ > 0) {
      // 保存数据
      Save(other.data_, other.size_);
    }
  }
  // 返回 this 指针
  return *this;
}

// 重载 += 操作符
template <class T>
const DynamicArray<T>& DynamicArray<T>::operator+=(
    const DynamicArray<T>& other) {
  Save(other.data_, other.size_);
  return *this;
}

// 重载 [] 操作符
template <class T>
T& DynamicArray<T>::operator[](int index) {
  // 判断索引
  if (index < 0 || index >= capacity_) {
    int newCapacity =
        (index + 1 < 64) ? index + 33 : index + ((index + 1) >> 1);
    SetCapacity(newCapacity);
  }

  // 如果索引比数量要大
  // 扩大 size_ ，返回
  if (index >= size_) {
    size_ = index + 1;
  }

  return data_[index];
}

#endif  // _DYNAMIC_ARRAY_ */
