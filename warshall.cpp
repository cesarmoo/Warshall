#include <iostream>
#include <string>
#include <cassert>
using namespace std;

void print_header() {
  cout << "This calculator uses the Warshall algorithm to compute the transitive closure of a relation R, with zero-one matrix representation, in O(n^3) time, where n is the dimension of the nxn matrix. The matrix maps from left to right.\n";
}

int prompt_for_size() {
  cout << "\nChoose the size of the matrix: ";
  int n;
  cin >> n;
  assert(n > 0);
  return n;
}

int* prompt_for_matrix(int n) {
  cout << "Enter the values of each row, using 0 or 1, without spaces.\n";
  int size = n * n;
  int *matrix = new int[size];
  for (int row = 0; row < n; ++row) {
    cout << "Enter values for row " << (row+1) << ": ";
    string row_input;
    cin >> row_input;
    assert(row_input.length() == n);
    for (int col = 0; col < n; ++col) {
      int value;
      if (row_input[col] == '0') {
        value = 0;
      }
      else {
        value = 1;
      }
      matrix[row*n + col] = value;
    }
  }
  return matrix;
}

void print_matrix(int matrix[], int n) {
  for (int row = 0; row < n; ++row) {
    cout << "[";
    for (int col = 0; col < n; ++col) {
      cout << matrix[row*n + col];
      if (col != n-1) {
        cout << " ";
      }
    }
    cout << "]\n";
  }
}

void solve(int matrix[], int n) {
  cout << "\nW0:\n";
  print_matrix(matrix, n);

  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        matrix[i*n + j] = matrix[i*n + j] || 
                            (matrix[i*n + k] && matrix[k*n + j]);
      }
    }
    cout << "\nW" << k+1 << ":\n";
    print_matrix(matrix, n);
  }
}

int main() {
  print_header();
  int n = prompt_for_size();
  int *matrix = prompt_for_matrix(n);
  cout << "Your matrix:\n";
  print_matrix(matrix, n);
  solve(matrix, n);
  delete[] matrix;

  return 0;
}