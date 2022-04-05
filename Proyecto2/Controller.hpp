// Copyright 2021 Mariana Murillo, Jarod Venegas, Luis Alberto Bolanos
#ifndef CONTROLLER
#define CONTROLLER
#include <string>
class Controller {
 public:
  void run(int argc, char *argv[]);

 private:
  int get_number_of_threads(int argc, char *argv[]);
  std::string get_path(int argc, char *argv[]);
  std::string get_file_name(int argc, char *argv[]);
};
#endif
