#include <iostream>
#include <vector>

using namespace std;

bool findCore(vector<vector<int>> matrix, int value, int row1, int col1,
              int row2, int col2) {
  int rows = matrix.size();
  int cols = matrix[0].size();
  if (value < matrix[row1][col1] || value > matrix[row2][col2]) {
    return false;
  }

  if (value == matrix[row1][col1] || value == matrix[row2][col2]) {
    return true;
  }

  int copyRow1 = row1, copyRow2 = row2;
  int copyCol1 = col1, copyCol2 = col2;

  int midRow = (row1 + row2) / 2;
  int midCol = (col1 + col2) / 2;

  // find the last element less than value on diagonal
  while ((midRow != row1 || midCol != col1) &&
         (midRow != row2 || midCol != col2)) {
    if (value == matrix[midRow][midCol]) {
      return true;
    }
    if (value < matrix[midRow][midCol]) {
      row2 = midRow;
      col2 = midCol;
    } else {
      row1 = midRow;
      col1 = midCol;
    }
    midRow = (row1 + row2) / 2;
    midCol = (col1 + col2) / 2;
  }

  // find value in two sub-matrices
  bool found = false;
  if (midRow < rows - 1) {
    found = findCore(matrix, value, midRow + 1, copyCol1, copyRow2, midCol);
  }
  if (!found && midCol < cols - 1) {
    found = findCore(matrix, value, copyRow1, midCol + 1, midRow, copyCol2);
  }
  return found;
}

bool find_solution1(vector<vector<int>> matrix, int value) {
  int rows = matrix.size();
  int cols = matrix[0].size();
  return findCore(matrix, value, 0, 0, rows - 1, cols - 1);
}

bool find_solution2(vector<vector<int>> matrix, int value) {
  int rows = matrix.size();
  int cols = matrix[0].size();
  int row = 0;
  int col = cols - 1;
  bool found = false;

  while (row < rows && col >= 0) {
    if (matrix[row][col] == value) {
      found = true;
      break;
    }

    if (matrix[row][col] > value) {
      --col;
    } else {
      ++row;
    }
  }

  return found;
}

void test(const string &testName, vector<vector<int>> matrix, int value,
          bool expected) {
  cout << testName << " begins: ";

  if (find_solution1(matrix, value) == expected) {
    cout << "Solution1 passed; ";
  } else {
    cout << "Solution1 FAILED; ";
  }
  if (find_solution2(matrix, value) == expected) {
    cout << "Solution2 passed.\n";
  } else {
    cout << "Solution2 FAILED.\n";
  }
}

//  1   2   8   9
//  2   4   9   12
//  4   7   10  13
//  6   8   11  15
// The value to be found, 7, is in the matrix;
void test1() {
  vector<vector<int>> matrix{
      {1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};
  test("Test1", matrix, 7, true);
}

//  1   2   8   9
//  2   4   9   12
//  4   7   10  13
//  6   8   11  15
// The value to be found, 5, is not in the matrix;
void test2() {
  vector<vector<int>> matrix{
      {1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};
  test("Test2", matrix, 5, false);
}

//  1   2   8   9
//  2   4   9   12
//  4   7   10  13
//  6   8   11  15
// The value to be found, 1, is the minimum in the matrix
void test3() {
  vector<vector<int>> matrix{
      {1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};
  test("Test3", matrix, 1, true);
}

//  1   2   8   9
//  2   4   9   12
//  4   7   10  13
//  6   8   11  15
// The value to be found, 15, is the maximum in the matrix
void test4() {
  vector<vector<int>> matrix{
      {1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};
  test("Test4", matrix, 15, true);
}

//  1   2   8   9
//  2   4   9   12
//  4   7   10  13
//  6   8   11  15
// The value to be found, 0, is less than the minimum in the matrix
void test5() {
  vector<vector<int>> matrix{
      {1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};
  test("Test5", matrix, 0, false);
}

//  1   2   8   9
//  2   4   9   12
//  4   7   10  13
//  6   8   11  15
// The value to be found, 16, is greater than the maximum in the matrix
void test6() {
  vector<vector<int>> matrix{
      {1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};
  test("Test6", matrix, 16, false);
}

//  1   2   8   9   14  15
//  2   4   9   12  16  23
//  4   7   10  13  21  25
//  6   8   11  15  23  27
// The value to be found, 21, is in the matrix
void test7() {
  vector<vector<int>> matrix{{1, 2, 8, 9, 14, 15},
                             {2, 4, 9, 12, 16, 23},
                             {4, 7, 10, 13, 21, 25},
                             {6, 8, 11, 15, 23, 27}};
  test("Test7", matrix, 21, true);
}

//  1   2   8   9
//  2   4   9   12
//  4   7   10  13
//  6   8   11  15
//  8   10  13  20
//  12  13  17  25
//  19  22  25  30
// The value to be found, 18, is not in the matrix
void test8() {
  vector<vector<int>> matrix{{1, 2, 8, 9},    {2, 4, 9, 12},   {4, 7, 10, 13},
                             {6, 8, 11, 15},  {8, 10, 13, 20}, {12, 13, 17, 25},
                             {19, 22, 25, 30}};
  test("Test8", matrix, 18, false);
}

int main() {
  test1();
  test2();
  test3();
  test4();
  test5();
  test6();
  test7();
  test8();

  return 0;
}
