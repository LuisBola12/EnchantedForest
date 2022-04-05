// Copyright 2021 Mariana Murillo, Jarod Venegas, Luis Alberto Bolanos
#ifndef _FOREST
#define _FOREST
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Magician.hpp"
#include <iostream>

class EnchantedForest {
 public:
  EnchantedForest(int number_of_threads);
  ~EnchantedForest();
  std::string enchanted_forest(char** actual_matrix, int rows, int columns,
                               int midnigth_count);
  char** create_char_matrix(int rows, int columns);
  Magician * magician;
 private:
  int number_of_threads;
  std::string get_string_of_matrix(char** matrix, int rows, int columns);
  void destroy_matrix(char** matrix, int rows);
  void test_rules(char** actual_matrix, char** next_matrix, int rows,
                  int columns);
};
#endif
