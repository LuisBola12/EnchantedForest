// Copyright 2021 Mariana Murillo, Jarod Venegas, Luis Alberto Bolanos
#ifndef FILE_MANAGER
#define FILE_MANAGER
#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
class FileManager {
 public:
  FileManager();
  ~FileManager();
  std::vector<std::string> read_file(std::string file_name);
  char **create_matrix(int rows);
  std::string rm_name(std::string file_name);
  char **read_sub_files(std::vector<std::string> input_matrix, int &rows,
                        int &columns);
  char **read_job_case_subfiles(std::string input, std::string path,
                                int &midninght_count, int &rows, int &columns);
  void output_file(std::string file_name, std::string map_done,
                   int midnight_count);

 private:
  int get_where_txt_ends(std::string input);
  char *convert_to_char_pointer(std::string row_of_input, int columns);
  void get_rows_columns(std::string, int &row, int &column);
};
#endif
