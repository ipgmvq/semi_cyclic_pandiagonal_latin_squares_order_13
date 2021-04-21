#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>

#define MATRIX_NUMBER 1000000
#define ORDER_LIMIT 19
#define mod(x, p) (x < 0 ? x % p + p : x % p)

int order = 5;
int * vector;
FILE * output;
int count = 0;
char * matrices;
char * matrix_status;
int matrix_size;


static void printSquare(int position) {
    for (int row = 0; row < order; ++row) {
        for (int column = 0; column < order; ++column) {
            if (column + 1 != order)
                fprintf(output, "%2d ", matrices[position * matrix_size + row * order + column]);
            else
                fprintf(output, "%2d\n", matrices[position * matrix_size + row * order + column]);
        }
    }
    fprintf(output, "\n");
}


static int compareHash(const void * x, const void * y) {
    for (int i = 0; i < matrix_size; ++i) {
        if( ( (char *) x)[i] < ( (char *) y)[i] ) return -1;
        else if( ( (char *) x)[i] > ( (char *) y)[i] ) return 1;
    }
    return 0;
}


static void markEqual(int position) {
    for (int i = 0; i < matrix_size; ++i) {
        if ( ( (char) (matrices[(position - 1) * matrix_size + i]) ) < ( (char) matrices[position * matrix_size + i] ) ) return;
        else if( ( (char) (matrices[(position - 1) * matrix_size + i]) ) > ( (char) matrices[position * matrix_size + i]) ) return;
    }
    matrix_status[position] = 0;
}


static void normalize(int position) {
    char alphabet[order];
    for (int i = 0; i < order; ++i)
        alphabet[matrices[position * matrix_size + i]] = i;
    for (int i = 0; i < matrix_size; ++i)
        matrices[position * matrix_size + i] = alphabet[matrices[position * matrix_size + i]];
}


static void hashSquareSraight(int _count) {
    for (int row = 0; row < order; ++row)
        for (int column = 0; column < order; ++column)
            matrices[_count * matrix_size + row * order + column] = (char) mod(column - vector[row], order);
}


static void hashSquareTranspose(int _count) {
    for (int column = 0; column < order; ++column)
        for (int row = 0; row < order; ++row)
            matrices[_count * matrix_size + column * order + row] = (char) mod(column - vector[row], order);
}


static void step(int row) {
    int to_proceed;
    for (int column = 1; column < order; ++column) {
        to_proceed = 1;
        for (int row_history = 0; row_history < row; ++row_history)
            if (column == vector[row_history] || mod(column - vector[row_history], order) == row - row_history || mod(vector[row_history] - column, order) == row - row_history)
                to_proceed = 0;
        if (to_proceed) {
            vector[row] = column;
            if (row + 1 < order)
                step(row + 1);
            else {
                if (order <= ORDER_LIMIT) {
                    hashSquareSraight(count++);
                    hashSquareTranspose(count++);
                } else count += 2;
            }
        }
    }
}


int main(int argc, char * argv[]) {
    time_t t0 = time(0);
    char file_name[51] = "semi_cyclic_pandiagonal_latin_squares_order_5.txt";
    if (argc > 1) {
        order = strtoll(argv[1], NULL, 10);
        if (order > 99 || order < 3) order = 5;
        else snprintf(file_name, 51, "semi_cyclic_pandiagonal_latin_squares_order_%d.txt", order);
    }
    matrix_size = order * order;
    vector = malloc(order * sizeof(int));
    vector[0] = 0;
    errno = 0;
    output = fopen(file_name, "w");
    if(output == NULL) {
        printf("I couldn't open the file %s\n%s\n", file_name, strerror(errno));
        exit(1);
    }
    matrices = malloc(matrix_size * MATRIX_NUMBER);
    matrix_status = malloc(MATRIX_NUMBER);
    for (int i = 0; i < MATRIX_NUMBER; ++i)
        matrix_status[i] = 1;
    for (int i = 2; i < order - 1; ++i) {
        vector[1] = i;
        step(2);
    }
    int countNonEqual = 0;
    if (order <= ORDER_LIMIT) {
        for (int i = 0; i < count; ++i) normalize(i);
        qsort(matrices, count, matrix_size, compareHash);
        for (int i = 1; i < count; ++i) markEqual(i);
        for (int i = 0; i < count; ++i)
            if (matrix_status[i]) {
                printSquare(i);
                ++countNonEqual;
            }
    }
    fclose(output);
    free(vector);
    free(matrices);
    free(matrix_status);
    printf("The total number of horizontally and vertically semi-cyclic (including full-cyclic) pandiagonal Latin squares: %d\n", count);
    if (order <= ORDER_LIMIT)
        printf("The total number of non-equal horizontally and vertically semi-cyclic (including full-cyclic) pandiagonal Latin squares: %d\n", countNonEqual);
    else
        puts("Some of them are equal");

    time_t t1 = time(0);
    int diff = t1 - t0;
    printf("\nIt took: %02d:%02d\n\n", diff / 60, diff % 60);
    
	return 0;
}
