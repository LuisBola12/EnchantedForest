// Copyright 2021 Mariana Murillo, Jarod Venegas, Luis Alberto Bolanos
#include "Magician.hpp"
Magician::Magician() {}
Magician::~Magician() {}
/**
 * @brief if the value of the column and row is valid to check
 *
 * @param row The row to check
 * @param column The column to check
 * @param rows The row of the cell
 * @param columns The column of the cell
 * @return true
 * @return false
 */
bool Magician::is_valid(const int row, const int column, int rows,
                        int columns) {
  return (row < rows && row >= 0 && column < columns && column >= 0);
}
/**
 * @brief Controls the rules of the program. Check the cell and apply the rules.
 *
 * @param actual_matrix The matrix to check
 * @param a_row the row of the cell
 * @param a_column the column of the cell
 * @param rows the number of rows of the matrix
 * @param columns the number of columns of the matrix
 * @return char
 */
char Magician::process_cell(char** actual_matrix, int a_row, int a_column,
                            int rows, int columns) {
  // Case when the cell is a tree
  if (actual_matrix[a_row][a_column] == 'a') {
    // Find the number of neighbors that are lakes
    const int enchanted_lakes =
        find_neighbors('l', actual_matrix, a_row, a_column, rows, columns);
    // Find the number of neighbors that are magic trees
    const int magic_trees =
        find_neighbors('a', actual_matrix, a_row, a_column, rows, columns) - 1;
    if (enchanted_lakes >= 4) {
      return 'l';
    }
    if (magic_trees > 4) {
      return '-';
    }
  }
  // Case when the cell is a lake
  if (actual_matrix[a_row][a_column] == 'l') {
    // Find the number of neighbors that are magic trees
    const int enchanted_lakes =
        find_neighbors('l', actual_matrix, a_row, a_column, rows, columns) - 1;
    if (enchanted_lakes < 3) {
      return '-';
    }
  }
  // Case when the cell is a plane
  if (actual_matrix[a_row][a_column] == '-') {
    // Find the number of neighbors that are magic trees
    const int magic_trees =
        find_neighbors('a', actual_matrix, a_row, a_column, rows, columns);
    if (magic_trees >= 3) {
      return 'a';
    }
  }
  return actual_matrix[a_row][a_column];
}
/**
 * @brief This method check each immediate neigbohr of the cell. Search for the
 * value in each neighbor and keep a counter of how many neighbors are the same
 * as the value.
 *
 * @param search_value the searched value
 * @param actual_matrix the matrix to check
 * @param a_row the row of the cell
 * @param a_column the column of the cell
 * @param rows the number of rows of the matrix
 * @param columns the number of columns of the matrix
 * @return int
 */
int Magician::find_neighbors(const char search_value, char** actual_matrix,
                             int a_row, int a_column, int rows, int columns) {
  int value_count = 0;
  for (int row = a_row - 1; row < a_row + 2; ++row) {
    for (int column = a_column - 1; column < a_column + 2; ++column) {
      if (is_valid(row, column, rows, columns)) {
        if (actual_matrix[row][column] == search_value) ++value_count;
      }
    }
  }
  return value_count;
}
