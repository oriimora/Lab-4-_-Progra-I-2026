#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void allocateMatrix(int ***matrix, int size) {

    *matrix = (int **)malloc(size * sizeof(int *));

    for (int i = 0; i < size; i++) {
        *(*matrix + i) = (int *)malloc(size * sizeof(int));
    }
}

void fillMatrix(int **matrix, int size) {

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            *(*(matrix + i) + j) = rand() % 2;
        }
    }
}

void printMatrix(int **matrix, int size) {

    printf("\nMatriz (%dx%d):\n", size, size);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", *(*(matrix + i) + j));
        }
        printf("\n");
    }
}

void findLargestLine(int **matrix, int size, int *result) {

    int actual = 0;
    int mayor = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {

            if (*(*(matrix + i) + j) == 1) {
                actual++;
                if (actual > mayor) {
                    mayor = actual;
                }
            } else {
                actual = 0;
            }
        }
    }

    *result = mayor;
}

void freeMatrix(int **matrix, int size) {

    for (int i = 0; i < size; i++) {
        free(*(matrix + i));
    }
    free(matrix);
}

int main() {

    int size;
    int largestLine = 0;
    int **matrix = NULL;

    srand(time(NULL));

    printf("Ingrese el tamaño de la matriz: ");
    scanf("%d", &size);

    allocateMatrix(&matrix, size);
    fillMatrix(matrix, size);
    printMatrix(matrix, size);

    findLargestLine(matrix, size, &largestLine);

    printf("\nLa secuencia mas larga de 1s es: %d\n", largestLine);

    freeMatrix(matrix, size);

    return 0;
}