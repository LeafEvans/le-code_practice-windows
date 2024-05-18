/* #include <cstdlib>
#include <ctime>
#include <iostream>
#include <queue>
#include <vector>

template <class T>
class CMP {
 public:
  bool operator()(const T& a, const T& b) { return a > b; }
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
  bool operator()(const T &a, const T &b) { return a > b; }
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
  Complex a(1, 2);
  Complex b;
  cout << a << endl;
  cin >> b;
  cout << a + b << endl;
  cout << a * b << endl;

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
#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<int> vi = {1, 2, 3, 4, 5};
  cout << vi.at(3) << endl;
  return 0;
}
