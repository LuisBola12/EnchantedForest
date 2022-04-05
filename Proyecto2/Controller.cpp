// Copyright 2021 Mariana Murillo, Jarod Venegas, Luis Alberto Bolanos
#include "Controller.hpp"

#include <mpi.h>
#include "EnchantedForest.hpp"
#include "FileManager.hpp"

/**
 * @brief run of the program
 *
 * @param argc
 * @param argv
 */

void Controller::run(int argc, char* argv[]) {
  if (MPI_Init(&argc, &argv) == MPI_SUCCESS) {
    int rank = -1;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int process_count = -1;
    MPI_Comm_size(MPI_COMM_WORLD, &process_count);
    std::string file_name = argv[1];
    std::string path = get_path(argc, argv);
    // In case the user didnt set a path
    if (path == "") {
      std::cerr << "Dont entered the path of the job" << std::endl;
      // return EXIT_FAILURE;
    }
    int rows = 0, columns = 0, midnigth_count = 0, number_of_threads = 0;
    number_of_threads = get_number_of_threads(argc, argv);
    char** matrix;
    FileManager* manager = new FileManager();
    EnchantedForest* forest = new EnchantedForest(number_of_threads);
    // Adding path to file name
    std::string dir_file = path;
    dir_file += file_name;
    // Vector with all the lines of the job, in theory each line is a map send
    // by the user
    std::vector<std::string> files = manager->read_file(dir_file);
    int number_of_files = (int)files.size();
    // For that executes all the maps in order to get the response to the job of
    // the magician
    for (int index = rank; index < number_of_files; index += process_count) {
      matrix = manager->read_job_case_subfiles(files[index], path,
                                               midnigth_count, rows, columns);
      std::string map_done =
          forest->enchanted_forest(matrix, rows, columns, midnigth_count);
      std::string map_name = manager->rm_name(files[index]);
      manager->output_file(map_name, map_done, midnigth_count);
    }
    delete manager;
    delete forest;
    MPI_Finalize();
  }
}

/**
 * @brief Gets the file name of the program sent by parameter when executed
 * @param argc number of parameters
 * @param argv values of the parameter
 * @return std::string
 */
int Controller::get_number_of_threads(int argc, char* argv[]) {
  int threads = sysconf(_SC_NPROCESSORS_ONLN);
  if (argc == 4) {
    if (sscanf(argv[3], "%d", &threads) < 1 || threads == 0) {
      fprintf(stderr, "error: invalid thread count\n");
    }
  }
  return threads;
}
/**
 * @brief Gets the path that is the second parameter that the the program
 * recieve when executed.
 * @param argc number of parameters
 * @param argv values of the parameter
 * @return std::string
 */
std::string Controller::get_path(int argc, char* argv[]) {
  std::string path = "";
  if (argc <= 4) {
    path = argv[2];
  }
  return path;
}
/**
 * @brief Gets the file name of the program sent by parameter when executed
 * @param argc number of parameters
 * @param argv values of the parameter
 * @return std::string
 */
std::string Controller::get_file_name(int argc, char* argv[]) {
  std::string file_name;
  if (argc <= 4) {
    // if (sscanf(argv[1], "%s", &file_name)){
    //  fprintf(stderr, "error: not entered a file name\n");
    //}
    file_name = argv[1];
  }
  return file_name;
}
