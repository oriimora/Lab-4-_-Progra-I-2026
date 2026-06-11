#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Función que encuentra la secuencia de 1s más larga tratando la matriz como arreglo lineal
void findLargestLine(int **matrix, int size, int *result) {
    int *ptr = *(matrix + 0);   // puntero al primer elemento de la matriz
    int actual = 0;             // contador de 1s consecutivos
    int mayor = 0;              // mayor secuencia encontrada

    for (int i = 0; i < size * size; i++) {   
        if (*(ptr + i) == 1) {
            actual++;             // aumentamos el contador si encontramos un 1
            if (actual > mayor) { // actualizamos el mayor si es necesario
                mayor = actual;
            }
        } else {
            actual = 0;           // si encontramos un 0, reiniciamos contador
        }
    }

    *result = mayor;  // guardamos el resultado en la variable pasada
}

// Función para reservar memoria dinámica de la matriz
void allocateMatrix(int ***matrix, int size) {
    *matrix = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        *(*matrix + i) = (int *)malloc(size * sizeof(int));
    }
}

// Función para llenar la matriz con valores aleatorios 0 o 1
void fillMatrix(int **matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            *(*(matrix + i) + j) = rand() % 2;  // asignamos 0 o 1
        }
    }
}

// Función para imprimir la matriz
void printMatrix(int **matrix, int size) {
    printf("Matriz (%dx%d):\n", size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", *(*(matrix + i) + j));
        }
        printf("\n");
    }
}

// Función para liberar la memoria de la matriz
void freeMatrix(int **matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(*(matrix + i));
    }
    free(matrix);
}

int main(void) {
    int size;
    int largestLine = 0;      // inicializamos en 0 para evitar basura
    int **matrix = NULL;

    srand(time(NULL));        

    printf("Ingrese el tamaño de la matriz: ");
    scanf("%d", &size);

    allocateMatrix(&matrix, size);  
    fillMatrix(matrix, size);       
    printMatrix(matrix, size);     

    findLargestLine(matrix, size, &largestLine);  // encontramos la secuencia más larga

    printf("\nLa secuencia más larga de 1s es: %d\n", largestLine);

    freeMatrix(matrix, size);       // liberamos memoria

    return 0;
}