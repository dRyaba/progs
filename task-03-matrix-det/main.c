#include <stdio.h>
#include <stdlib.h>

#define SIZE 64
typedef struct matrix {
    double matrix[SIZE][SIZE];
    double det;
    int size;
} Matrix;

double determinent(double matrix[][SIZE], int size, int row, int column[], int cur_rank) {
    double det = 0, s = 1;
    for (int c = 0; c < size; c++) {
        if (!column[c]) {
            if (cur_rank == 1)
                return matrix[row][c];
            if (cur_rank == 2) {
                int i = c+1;
                while (column[i] && i<size)
                    i++;
                return matrix[row][c] * matrix[row + 1][i] - matrix[row][i] * matrix[row + 1][c];
            }
            column[c]++;
            det += s * (matrix[0][c] * determinent(matrix, size, row + 1, column, cur_rank - 1));
            s = -1 * s;
            column[c]--;
        }
    }
    return det;
}

void qs(Matrix *arr, int first, int last) {
    if (first < last) {
        int left = first, right = last;
        Matrix middle = arr[(rand() % (last - first) + first)];
        do {
            while (arr[left].det < middle.det) left++;
            while (arr[right].det > middle.det) right--;
            if (left <= right) {
                Matrix tmp = arr[left];
                arr[left] = arr[right];
                arr[right] = tmp;
                left++;
                right--;
            }
        } while (left <= right);
        qs(arr, first, right);
        qs(arr, left, last);
    }
}

int main() {
    int n;
    FILE *input, *output;
    input = fopen("input.txt", "r"), output = fopen("output.txt", "w");
    if ((input == NULL) || (output == NULL))
        return 63;
    fscanf(input, "%d", &n);
    Matrix arr[n];
    int column[SIZE] = {0};
    for (int i = 0; i < n; i++) {
        fscanf(input, "%d", &arr[i].size);
        for (int j = 0; j < arr[i].size; j++) {
            for (int t = 0; t < arr[i].size; t++)
                fscanf(input, "%lf", &arr[i].matrix[j][t]);
        }
        arr[i].det = determinent(arr[i].matrix, arr[i].size, 0, column, arr[i].size);
    }
    fclose(input);
    qs(arr, 0, n - 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < arr[i].size; j++) {
            for (int t = 0; t < arr[i].size; t++) {
                fprintf(output, "%d ", (int) arr[i].matrix[j][t]);
            }
            fprintf(output, "\n");
        }
    }
    fclose(output);
    return 0;
}
