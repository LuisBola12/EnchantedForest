// Copyright 2021 Mariana Murillo, Jarod Venegas, Luis Alberto Bolanos
#include "FileManager.hpp"
FileManager::FileManager() {}
FileManager::~FileManager() {}
/**
 * @brief Reads the file send by the user.
 * @details Using ifstream the method reads the file and saves each line in a
 * vector
 * @param file_name name of the file to be read
 * @return std::vector<std::string>
 */
std::vector<std::string> FileManager::read_file(std::string file_name) {
  std::ifstream input_file(file_name, std::ios::in);
  std::vector<std::string> input_files;
  std::string store;
  if (input_file) {
    while (std::getline(input_file, store)) {
      // std::cout<<store;
      input_files.push_back(store);
    }

  } else {
    std::cerr << "ERROR READING FILE NAME " << file_name << std::endl;
    exit(0);
  }
  input_file.close();
  return input_files;
}
/**
 * @brief Creates a matrtix only initializing its rows
 * @param rows Rows of the matrix
 * @return char**
 */
char** FileManager::create_matrix(int rows) {
  // Size of the rows
  char** matrix = (char**)calloc(rows, sizeof(char*));
  if (!matrix) {
    // In case the matrix couldnt be created
    return NULL;
  }
  return matrix;
}
/**
 * @brief Reads sub files, so it can create a matrix with the input file.
 * @details Receive the vector with all the lines of the map, so it can get
 * the value of rows an columns, and with that creates a matrix with the values
 * @param input_matrix vector with the inner file
 * @param rows reference to the variable rows
 * @param columns reference to the variable columns
 * @return char**
 */
char** FileManager::read_sub_files(std::vector<std::string> input_matrix,
                                   int& rows, int& columns) {
  std::string values = input_matrix[0];
  get_rows_columns(values, rows, columns);
  char** matrix = create_matrix(rows);
  int counter_matrix = 0;
  for (int i = 1; i <= rows; i++) {
    matrix[counter_matrix] = convert_to_char_pointer(input_matrix[i], columns);
    counter_matrix++;
  }
  return matrix;
}
/**
 * @brief gets the values of the rows and columns for each matrix
 * @details Receive a string wich is the first line of the input, wich
 * contains the values for rowa and columns
 * @param input string with the first line of the map
 * @param rows reference to the variable rows
 * @param columns reference to the variable columns
 * @return void
 */
void FileManager::get_rows_columns(std::string input, int& row, int& column) {
  std::string str_row;
  std::string str_column;
  int counter = 0;
  int size_of_string = input.length();
  while (input[counter] != ' ' && counter < size_of_string) {
    str_row += input[counter];
    counter++;
  }
  row = stoi(str_row);
  counter++;
  while (input[counter] != ' ' && counter < size_of_string) {
    str_column += input[counter];
    counter++;
  }
  column = stoi(str_column);
}
/**
 * @brief Converts a string to a char pointer, so it can be stored in the matrix
 * @param row_of_input row of the string to be input
 * @param columns reference to the variable columns
 * @return char*
 */
char* FileManager::convert_to_char_pointer(std::string row_of_input,
                                           int columns) {
  char* row_of_matrix = (char*)calloc(columns, sizeof(char));
  for (int i = 0; i < columns; i++) {
    row_of_matrix[i] = row_of_input[i];
  }
  return row_of_matrix;
}
/**
 * @brief Returns the counter where .txt ends in a stringg.
 * @param input string to be analized
 * @return int
 */
int FileManager::get_where_txt_ends(std::string input) {
  int counter = 0;
  int size_of_string = input.length();
  while (input[counter] != ' ' && counter < size_of_string) {
    counter++;
  }
  counter++;
  return counter;
}
/**
 * @brief Reads job case sub files, so it can create a matrix with the input
 * file.
 * @details Receive the vector with all the lines of the map, so it can get
 * the value of rows an columns, and with that creates a matrix with the values
 * @param input string with input of the map
 * @param path strign with path of the files
 * @param rows reference to the variable rows
 * @param columns reference to the variable columns
 * @param midnight_count reference
 * @return char**
 */
char** FileManager::read_job_case_subfiles(std::string input, std::string path,
                                           int& midninght_count, int& rows,
                                           int& columns) {
  std::string number = "";
  int counter = get_where_txt_ends(input);
  int size_of_string = input.length();
  while (input[counter] != ' ' && counter < size_of_string) {
    number += input[counter];
    counter++;
  }
  midninght_count = stoi(number);
  int final1 = input.length() - 10;
  input.erase(10, final1);
  std::string dir_file = path;
  dir_file += input;
  std::vector<std::string> vector = read_file(dir_file);
  std::string str = vector[0];
  get_rows_columns(str, rows, columns);
  char** matrix = read_sub_files(vector, rows, columns);
  return matrix;
}
/**
 * @brief Removes the name of the input so it can only have the name of the map
 * @param file_name string with the name of the file
 * @return std::string
 */
std::string FileManager::rm_name(std::string file_name) {
  std::string name = file_name;
  int end = name.length();
  name.erase(10, end);
  return name;
}
/**
 * @brief Creates the output file for each map
 * @param file_name string with name of the file
 * @param map_done string with all the map
 * @param midnight_count number of nights done
 * @return void
 */
void FileManager::output_file(std::string file_name, std::string map_done,
                              int midnight_count) {
  std::ofstream answer_file;
  int in_cout = abs(midnight_count);
  std::string str_midnight_count = "-" + std::to_string(in_cout);
  file_name.insert(6, str_midnight_count);
  answer_file.open(file_name);
  answer_file << map_done;
  answer_file.close();
}
