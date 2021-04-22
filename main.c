#include <stdio.h>

typedef struct matrix {
    float matrix[64][64];
    float det;
    int size;
} Matrix;

float determinent(float matrix[64][64], int size) {
    int m, n;
    if (size == 1) {
        return (matrix[0][0]);
    } else if (size == 2)
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    else {
        float det = 0, s = 1, b[64][64];
        for (int c = 0; c < size; c++) {
            m = n = 0;
            for (register int i = 0; i < size; i++) {
                for (register int j = 0; j < size; j++) {
                    b[i][j] = 0;
                    if (i != 0 && j != c) {
                        b[m][n] = matrix[i][j];
                        if (n < (size - 2)) {
                            n++;
                        } else {
                            n = 0;
                            m++;
                        }
                    }
                }
            }
            det += s * (matrix[0][c] * determinent(b, size - 1));
            s = -1 * s;
        }
    return (det);
    }
}

void qs(Matrix *arr, int first, int last) {
    if (first < last) {
        int left = first, right = last;
        Matrix middle = arr[(left + right) / 2];
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
    int n, k;
    FILE *input, *output;
    input = fopen("input.txt", "r"), output = fopen("output.txt", "w");
    if ((input == NULL) || (output == NULL))
        return 72;
    fscanf(input, "%d", &n);
    Matrix arr[n];
    for (int i = 0; i < n; i++) {
        fscanf(input, "%d", &k);
        for (int j = 0; j < k; j++) {
            for (int t = 0; t < k; t++)
                fscanf(input, "%f", &arr[i].matrix[j][t]);
        }
        arr[i].det = determinent(arr[i].matrix, k);
        arr[i].size = k;
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
