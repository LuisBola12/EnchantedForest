// Copyright 2021 Mariana Murillo, Jarod Venegas, Luis Alberto Bolanos
#ifndef MAGICIAN
#define MAGICIAN
class Magician {
 public:
  Magician();
  ~Magician();
  bool is_valid(const int row, const int column, int rows, int columns);
  char process_cell(char** actual_matrix, int a_row, int a_column, int rows,
                    int columns);
  int find_neighbors(const char search_value, char** actual_matrix, int a_row,
                     int a_column, int rows, int columns);
};
#endif
