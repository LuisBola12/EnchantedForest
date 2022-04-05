# Design_Analysis

## Descripción del mapeo por MPI/OpenMp
Nos encargamos de utilizar MPI de forma que los procesos fueran independientes entre ellos mismos pero que a su vez respetaran sus áreas de trabajo, por lo que decidimos mapear los mapas que contiene el *job* del mago. 
Para este caso optamos por un mapeo cíclico, de forma que el proceso itera en el for desde su rango, mientras sea menor que la cantidad de mapas dentro del *job* y va brincando dependiendo de la cantidad de procesos (*+= process_count*) 

```
int rank = -1;
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
int process_count = -1;
MPI_Comm_size(MPI_COMM_WORLD, &process_count);

for(int index = rank; index < number_of_maps; index+=process_count){
// Procesar mapa
}
```
### Ventaja y desventaja de MPI
Una ventaja de esta herramienta es poder disminuir las grandes cargas de trabajo entre procesos con la ventaja de poder seguir usando hilos. Por ejemplo, para este avance dividimos los mapas entre procesos y cada proceso utiliza OpenMp para dividir su mapa.
Una desvantaja de MPI es que la comunicacion de punto a punto es bastante costosa en cuanto a rendimiento y velocidad de ejecución.

## Descripción del mapeo por OpenMp
Nos encargamos de utilizar la herramienta OpenMp de forma que nos permitiera repartir la carga de trabajo de las filas de la matriz del mapa, utilizando el mapeo dinamico, debido a que fue el dio mejores resultados.
Para este tipo de mapeo los hilos compiten por repartirse las filas de la matriz de forma que nunca ociosos.
```
#pragma omp parallel for num_threads(number_of_threads) shared(next_matrix) \
    firstprivate(actual_matrix) schedule(dynamic)
  for (int row = 0; row < rows; ++row) {
    for (int column = 0; column < columns; ++column) {
      next_matrix[row][column] =
          process_cell(actual_matrix, row, column, rows, columns);
    }
  }
```
### Ventaja y desventaja de OpenMp
La principal ventaja de OpenMp es la facilidad para crear  los hilos.
Una desventaja es que los hilos pierden ratreabilidad muy fácil (se pierde la habilidad de manipular los hilos de manera más específica), así como sus falsos positivos en los *sanitazers* que se utilizan para revisar las condiciones de carrera.

## Manejo de la entrada y salida estándar
En este programa no hay problemas de entrada o salida estándar, debido a que los procesos no reciben nada ni imprimen nada en la terminal, además, de que su trabajo es independiente entre ellos.
