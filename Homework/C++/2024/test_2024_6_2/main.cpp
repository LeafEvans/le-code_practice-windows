/* #include <iostream>
#include <vector>

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

template <class T>
void bubble_sort(T* arr, int len) {
  for (int i = 0; i < len - 1; ++i) {
    for (int j = 0; j < len - 1 - i; ++j) {
      if (arr[j] >= arr[j + 1]) {
        std::swap(arr[j], arr[j + 1]);
      }
    }
  }
}

template <class T>
void insertion_sort(T* arr, int len) {
  int i, j;
  T key = T();

  for (i = 1; i < len; ++i) {
    key = arr[i];
    for (j = i - 1; j >= 0 && key > arr[j]; --j) {
      arr[j + 1] = arr[j];
    }
    arr[j + 1] = key;
  }
}

template <class T>
void selection_sort(T* arr, int len) {
  int min_index;
  for (int i = 0; i < len - 1; ++i) {
    min_index = i;
    for (int j = i + 1; j < len; ++j) {
      if (arr[j] < arr[min_index]) {
        min_index = j;
      }
    }
    std::swap(arr[i], arr[min_index]);
  }
}

std::vector<int> add(const std::vector<int>& v1, const std::vector<int>& v2) {
  std::vector<int> result;

  int carry = 0;

  size_t max_size = std::max(v1.size(), v2.size());

  for (size_t i = 0; i < max_size; ++i) {
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

std::vector<int> sub(const std::vector<int>& v1, const std::vector<int>& v2) {
  std::vector<int> result;

  int carry = 0;

  for (int i = 0; i < v1.size(); ++i) {
    int diff = v1[i] - carry;
    if (i < v2.size()) {
      diff -= v2[i];
    }

    result.push_back((diff + 10) % 10);

    carry = (diff < 0) ? 1 : 0;
  }

  return result;
}

int main() {
  std::cout << "Hello World!\n";
  return 0;
} */
/* #include <fstream>
#include <iostream>
using namespace std;
int main(void) {
  ifstream f1;  // 文件输入流
  ofstream f2;  // 文件输出流
  int a[10], sum;
  f1.open("..\\source.txt");                 // 读取数据
  f2.open("..\\destination.txt", ios::out);  // 写入模式
  f2 << "2023116204陈靖盈" << endl;                // 输出个人信息
  for (int i = 0; i < 10; i++) {
    f1 >> a[i];  // 将数字放入数组
  }
  for (int i = 0; i < 10; i++) {
    sum = 0;                          // 初始化真因子的和为 1
    for (int j = 1; j < a[i]; j++) {  // 真因子小于本身
      if (a[i] % j == 0) {
        sum += j;  // 如果为真因子，则加上去
      }
    }
    // 所有的真因子加起来后判断
    if (sum == a[i]) {
      f2 << a[i] << ' ';  // 成立就输出
    }
  }

  f1.close();  // 关闭文件
  f2.close();

  return 0;
} */
/* #ifndef _DYNAMIC_ARRAY_
#define _DYNAMIC_ARRAY_
#include <cstring>
#include <vector>

template <class T>
class DynamicArray {
 public:
  DynamicArray();
#if defined(_INITIALIZER_LIST_)
  DynamicArray(std::initializer_list<T> ilist);
#endif
  DynamicArray(const DynamicArray& other);
  ~DynamicArray();

  int setCapacity(int newCapacity);
  int getSize() const;
  int append(const T& element);
  int save(const T* data, int dataLength);
  int insert(int index, const T& element);
  bool remove(int index, T& removedElement);
  const DynamicArray& operator=(const DynamicArray& other);
  const DynamicArray& operator+=(const DynamicArray& other);
  T& operator[](int index);

 private:
  T* data_;
  int size_;
  int capacity_;
};

template <class T>
DynamicArray<T>::DynamicArray() : data_(new T[4]), size_(0), capacity_(4) {
  std::memset(data_, 0, sizeof(T) * capacity_);
}

template <class T>
DynamicArray<T>::DynamicArray(std::initializer_list<T> ilist)
    : size_(ilist.size()), capacity_(ilist.size() + 4) {
  data_ = new T[capacity_];
  std::memcpy(data_, ilist.begin(), sizeof(T) * size_);
  std::memset(data_ + size_, 0, sizeof(T) * (capacity_ - size_));
}

template <class T>
DynamicArray<T>::~DynamicArray() {
  delete[] data_;
  data_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}

template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other)
    : size_(0), capacity_(other.capacity_), data_(new T[other.capacity_]) {
  if (other.size_ > 0) {
    save(other.data_, other.size_);
  }
}

template <class T>
int DynamicArray<T>::setCapacity(int newCapacity) {
  if (newCapacity <= size_) {
    return capacity_;
  }

  T* newData = new T[newCapacity];

  std::memcpy(newData, data_, sizeof(T) * size_);
  std::memset(newData + size_, 0, sizeof(T) * (newCapacity - size_));

  delete[] data_;
  data_ = newData;
  capacity_ = newCapacity;

  return capacity_;
}

template <class T>
int DynamicArray<T>::append(const T& element) {
  if (size_ >= capacity_) {
    int newCapacity =
        (capacity_ < 64) ? capacity_ + 32 : capacity_ + (capacity_ >> 1);
    if (!setCapacity(capacity_)) {
      return -1;
    }
  }

  data_[size_++] = element;
  return size_ - 1;
}

template <class T>
int DynamicArray<T>::save(const T* data, int dataLength) {
  if (!data || dataLength <= 0) {
    return -1;
  }

  if (size_ + dataLength >= capacity_) {
    int newCapacity = size_ + dataLength;
    newCapacity = (newCapacity < 64) ? newCapacity + 32
                                     : newCapacity + (newCapacity >> 1);

    if (!setCapacity(newCapacity)) {
      return -1;
    }
  }

  std::memcpy(data_ + size_, data, dataLength * sizeof(T));

  size_ += dataLength;

  return size_ - dataLength;
}

template <class T>
int DynamicArray<T>::insert(int index, const T& element) {
  if (index < 0 || index >= capacity_) {
    return -1;
  }

  if (size_ >= capacity_) {
    int newCapacity =
        (capacity_ < 64) ? capacity_ + 32 : capacity_ + (capacity_ >> 1);

    if (!setCapacity(newCapacity)) {
      return -1;
    }
  }

  if (index <= size_ - 1) {
    std::memmove(data_ + index + 1, data_ + index, sizeof(T) * (size_ - index));
  }

  data[index] = element;
  size_++;

  return index;
}

template <class T>
bool DynamicArray<T>::remove(int index, T& removedElement) {
  if (index < 0 || index >= size_) {
    return false;
  }

  removedElement = data_[index];

  if (index < size_ - 1) {
    std::memmove(data_ + index + 1, data_ + index,
                 sizeof(T) * (size_ - index + 1));
  }

  --size_;
  return true;
}

template <class T>
const DynamicArray<T>& DynamicArray<T>::operator=(
    const DynamicArray<T>& other) {
  if (this != &other) {
    delete[] data_;
    size_ = 0;
    capacity_ = other.capacity_;
    data_ = new T[capacity_];

    if (other.size_ > 0) {
      save(other.data_, other.capacity_);
    }
  }

  return *this;
}

template <class T>
const DynamicArray<T>& DynamicArray<T>::operator+=(
    const DynamicArray<T>& other) {
  save(other.data_, other.size_);
  return *this;
}

template <class T>
T& DynamicArray<T>::operator[](int index) {
  if (index < 0 || index >= capacity_) {
    int newCapacity =
        (index + 1 < 64) ? index + 33 : index + ((index + 1) >> 1);
    setCapacity(newCapacity);
  }

  if (index >= size_) {
    size_ = index + 1;
  }

  return data_[index];
}
#endif  // _DYNAMIC_ARRAY_ */
/* #ifndef _DYNAMIC_ARRAY_
#define _DYNAMIC_ARRAY_
#include <cstring>
#include <vector>

template <class T>
class DynamicArray {
 public:
  DynamicArray();

#if defined(_INITIALIZER_LIST_)
  DynamicArray(std::initializer_list<T> ilist);
#endif
  DynamicArray(const DynamicArray& other);
  ~DynamicArray();

  int setCapacity(int new_capacity);
  int getSize() const;
  int append(const T& element);
  int save(const T* data, int len);
  int insert(int index, const T& element);
  bool remove(int index, T& removed_element);
  const DynamicArray& operator=(const DynamicArray& other);
  const DynamicArray& operator+=(const DynamicArray& other);
  T& operator[](int index);

 private:
  T* data_;
  int size_;
  int capacity_;
};

template <class T>
DynamicArray<T>::DynamicArray() : data_(new T[4]), size_(0), capacity_(4) {
  std::memset(data_, 0, sizeof(T) * capacity_);
}

#if defined(_INITIALIZER_LIST_)
template <class T>
DynamicArray<T>::DynamicArray(std::initializer_list<T> ilist)
    : size_(ilist.size()), capacity_(ilist.size() + 4) {
  data_ = new T[capacity_];
  std::memcpy(data_, ilist.begin(), sizeof(T) * capacity_);
  std::memset(data_ + size_, 0, sizeof(T) * (capacity_ - size_));
}
#endif

template <class T>
DynamicArray<T>::~DynamicArray() {
  delete[] data_;
  data_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}

template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other)
    : size_(0), capacity_(other.capacity_), data_(new T[other.capacity_]) {
  if (other.size() > 0) {
    save(other.data_, other.size_);
  }
}

template <class T>
int DynamicArray<T>::setCapacity(int new_capacity) {
  if (new_capacity <= size_) {
    return capacity_;
  }

  T* new_data = new T[new_capacity];
  if (!new_data) {
    return capacity_;
  }

  std::memcpy(new_data, data_, sizeof(T) * new_capacity);
  std::memset(new_data + size_, 0, sizeof(T) * (new_capacity - size_));

  delete[] data_;
  data_ = new_data;
  capacity_ = new_capacity;

  return capacity_;
}

template <class T>
int DynamicArray<T>::getSize() const {
  return size_;
}

template <class T>
int DynamicArray<T>::append(const T& element) {
  if (size_ >= capacity_) {
    int new_capacity =
        (capacity_ < 64) ? capacity_ + 32 : capacity_ + (capacity_ + 1 >> 1);
    if (!setCapacity(new_capacity)) {
      return -1;
    }
  }

  data_[size_++] = element;
  return size_ - 1;
}

template <class T>
int DynamicArray<T>::save(const T* data, int len) {
  if (!data || len <= 0) {
    return -1;
  }

  if (size_ + len >= capacity_) {
    int new_capacity = size_ + len;
    new_capacity = (new_capacity < 64) ? new_capacity + 32
                                       : new_capacity + (new_capacity + 1 >> 1);
    if (!setCapacity(new_capacity)) {
      return -1;
    }
  }

  std::memcpy(data_ + size_, data, sizeof(T) * len);

  size_ += len;

  return size_ - len;
}

template <class T>
int DynamicArray<T>::insert(int index, const T& element) {
  if (index < 0 || index >= capacity_) {
    return -1;
  }

  if (size_ >= capacity_) {
    int new_capacity =
        capacity_ + 64 ? (capacity_ + 32) : capacity_ + (capacity_ + 1 >> 1);
    if (!setCapacity(new_capacity)) {
      return -1;
    }
  }
  if (index <= size_ - 1) {
    std::memmove(data_ + index + 1, data_ + index, sizeof(T) * (size_ - index));
  }

  data_[index] = element;

  return index;
}

template <class T>
bool DynamicArray<T>::remove(int index, T& removed_element) {
  if (index < 0 || index >= size_) {
    return false;
  }

  removed_element = data_[index];

  if (index < size_ - 1) {
    std::memmove(data_ + index, data_ + index + 1,
                 sizeof(T) * (size_ - index - 1));
  }

  --size_;
  return true;
}

template <class T>
const DynamicArray<T>& DynamicArray<T>::operator=(
    const DynamicArray<T>& other) {
  if (this != &other) {
    delete[] data_;
    capcity_ = other.capacity_;
    size_ = 0;
    data_ = new T[capacity_];
    if (other.size() > 0) {
      save(other.data_, other.size());
    }
  }

  return *this;
}

template <class T>
const DynamicArray<T> &DynamicArray<T>::operator+=(
  const DynamicArray<T>& other
) {
  save(other.data_, other.size_);
  return *this;
}

template <class T>
T &DynamicArray<T>::operator[](int index) {
  if (index < 0 || index >= capacity_) {
    int new_capacity =
    index + 1 < 64 ? index +33: index + ((index + 1) >> 1);
    setCapacity(new_capacity);
  }

  if (index >= size_) {
    size_ = index + 1;
  }

  return data_[index];
}
#endif  // _DYNAMIC_ARRAY_ */
/* #include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 1010;

int main() {
  int n, m;
  int v[N], w[N];
  int f[N] = {0};
  cin >> n >> m;

  for (int i = 1; i <= n; ++i) {
    cin >> v[i] >> w[i];
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = m; j >= v[i]; --j) {
      f[j] = max(f[j], f[j - v[i]] + w[i]);
    }
  }
  cout << f[m] << endl;
  return 0;
} */
#include <math.h>
#include <stdio.h>

void hanoiTower(int n, char x, char y, char z) {
  if (n > 1) {
    hanoiTower(n - 1, x, z, y);
    printf("%c -> %c\n", x, z);
    hanoiTower(n - 1, y, x, z);
  } else {
    printf("%c -> %c\n", x, z);
  }
}

int main(void) {
  int n = 0;
  char a = 'A', b = 'B', c = 'C';

  scanf("%d", &n);

  hanoiTower(n, a, b, c);
  printf("%d\n", (int)(pow(2, n) - 1));

  return 0;
}