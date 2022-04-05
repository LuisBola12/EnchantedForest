// Copyright 2021 Mariana Murillo, Jarod Venegas, Luis Alberto Bolanos
/**
 * @file main.cpp
 * @author Mariana Murillo Quintana(mariana.murilloquintana@ucr.ac.cr)
 * @author Jarod Venegas Alpizar(jarod.venegas@ucr.ac.cr)
 * @author Luis Alberto Bolanos Valverde(luis.bolanosvalverde@ucr.ac.cr)
 * @brief  The program is a map generator for a suposed magician who gants to
 * know how a map is going to change depending on the number of midnights he
 * wants the map to pass.
 * @version 0.1
 * @date 2021-07-05
 * @copyright Copyright (c) 2021
 *
 */
#include <mpi.h>
#include "Controller.hpp"

int main(int argc, char* argv[]) {
  Controller controller;
  controller.run(argc, argv);
  return 0;
}
