// Copyright 2021 Mariana Murillo, Jarod Venegas, Luis Alberto Bolanos
#include "EnchantedForest.hpp"
EnchantedForest::EnchantedForest(int number_of_threads) {
  this->number_of_threads = number_of_threads;
  this->magician =  new Magician();
}
EnchantedForest::~EnchantedForest() {}
/**
 * @brief Create the forest and make the calculations to each night.
 *
 * @param actual_matrix The matrix to be done
 * @param rows Rows of the matrix
 * @param columns Columns of the matrix
 * @param midnigth_count The number of nights
 * @return std::string
 */
std::string EnchantedForest::enchanted_forest(char** actual_matrix, int rows,
                                              int columns, int midnigth_count) {
  // The matrix that is going to be used for the calculations of the days
  std::string output;
  char** next_day_matrix = create_char_matrix(rows, columns);
  int midnigth_positive = 0;
  if (actual_matrix && next_day_matrix) {
    midnigth_positive = abs(midnigth_count);
  }
  output += "0:\n";
  output += get_string_of_matrix(actual_matrix, rows, columns);
  for (int nigth_index = 0; nigth_index < midnigth_positive; ++nigth_index) {
    // Check for the number of nights entered by user
    test_rules(actual_matrix, next_day_matrix, rows, columns);
    if (midnigth_count > 0 || nigth_index + 1 == abs(midnigth_count)) {
      // Print the resulting map
      output += "\n";
      output += std::to_string(nigth_index + 1);
      output += ":\n";
      output += get_string_of_matrix(next_day_matrix, rows, columns);
    }
    // Keep always the matrix, by making the actual matrix equal to the matrix
    // of the next day onces the night is done.
    char** tmp = actual_matrix;
    actual_matrix = next_day_matrix;
    next_day_matrix = tmp;
  }
  destroy_matrix(actual_matrix, rows);
  destroy_matrix(next_day_matrix, rows);
  return output;
}
/**
 * @brief Covert a matrix to a string.
 *
 * @param matrix The matrix to convert
 * @param rows The rows of the matrix
 * @param columns The columns of the matrix
 * @return std::string
 */
std::string EnchantedForest::get_string_of_matrix(char** matrix, int rows,
                                                  int columns) {
  std::string output;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      output += matrix[i][j];
    }
    output += '\n';
  }
  return output;
}
/**
 * @brief Create a matrix of the size of the rows and columns indicated
 *
 * @param rows Rows of the matrix
 * @param columns Columns of the columns
 * @return char**
 */
char** EnchantedForest::create_char_matrix(int rows, int columns) {
  char** matrix = (char**)calloc(rows, sizeof(char*));
  if (!matrix) {
    return NULL;
  }
  for (int row = 0; row < rows; ++row) {
    if ((matrix[row] = (char*)calloc(columns, sizeof(char))) == NULL) {
      destroy_matrix(matrix, rows);
      return NULL;
    }
  }
  return matrix;
}
/**
 * @brief Process each cell of the matrix and apply the rules.
 *
 * @param actual_matrix the matrix tho be analyze
 * @param next_matrix the matrix in result
 * @param rows the rows of the matrix
 * @param columns the columns of the matrix
 */
void EnchantedForest::test_rules(char** actual_matrix, char** next_matrix,
                                 int rows, int columns) {
#pragma omp parallel for num_threads(number_of_threads) shared(next_matrix) \
    firstprivate(actual_matrix) schedule(dynamic)
  for (int row = 0; row < rows; ++row) {
    for (int column = 0; column < columns; ++column) {
      // printf(" %d \n",omp_get_thread_num());
      next_matrix[row][column] =
          this->magician->process_cell(actual_matrix, row,
          column, rows, columns);
    }
  }
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

/**
 * @brief This method free the memory created of a matrix
 *
 * @param matrix the matrix to free
 * @param rows the rows of the matrix
 */
void EnchantedForest::destroy_matrix(char** matrix, int rows) {
  for (int row = 0; row < rows; ++row) {
    free(matrix[row]);
  }
  free(matrix);
}
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
