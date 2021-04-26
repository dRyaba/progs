#include <stdio.h>
#include <stdlib.h>

#define SIZE 64
typedef struct matrix {
    float matrix[SIZE][SIZE];
    float det;
    int size;
} Matrix;

float determinent(float matrix[][SIZE], int size, float minor[][SIZE]) {
    if (size == 1) {
        return (matrix[0][0]);
    } else if (size == 2)
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    else {
        float det = 0, s = 1;
        for (int c = 0; c < size; c++) {
            if (matrix[0][c] == 0) {
                c++;
            }
            for (int i = 0; i < size - 1; i++) {
                for (int j = 0, t = 0; j < size; j++, t++) {
                    if (j == c) {
                        j++;
                    }
                    minor[i][t] = matrix[i + 1][j];
                }
            }
            det += s * (matrix[0][c] * determinent(minor, size - 1, minor));
            s = -1 * s;
        }
        return det;
    }
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
    float minor[SIZE][SIZE] = {0};
    for (int i = 0; i < n; i++) {
        fscanf(input, "%d", &arr[i].size);
        for (int j = 0; j < arr[i].size; j++) {
            for (int t = 0; t < arr[i].size; t++)
                fscanf(input, "%f", &arr[i].matrix[j][t]);
        }
        arr[i].det = determinent(arr[i].matrix, arr[i].size, minor);
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
}
