#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  vector<vector<int>> vi = {{1, 2, 3}, {4, 5, 6}};
  for (int i = 0; i < vi.size(); ++i) {
    for (int j = 0; j < vi[i].size(); ++j) {
      cout << vi[i][j] << ' ';
    }
    cout << '\n';
  }
  
  cout << "Row: " << vi.size() << ", Col: " << vi[0].size() << '\n';
  
  return 0;
}
