#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct matrix {
    double **matrix;
    double det;
    int size;
} Matrix;


double determinant(double **a, int n) {
    if (n == 1)
        return a[0][0];
    else if (n == 2)
        return a[0][0] * a[1][1] - a[0][1] * a[1][0];
    else {
        double d = 0;
        for (int k = 0; k < n; k++) {
            double **m = (double **) malloc(sizeof(double *) * n);
            if (*m) {
                for (int i = 0; i < n - 1; i++)
                    m[i] = (double *) malloc(sizeof(double) * n);

                for (int i = 1; i < n; i++) {
                    if (m[i - 1]) {
                        int t = 0;
                        for (int j = 0; j < n; j++) {
                            if (j == k)
                                continue;
                            m[i - 1][t] = a[i][j];
                            t++;
                        }
                    }
                }
                d += pow(-1, k + 2) * a[0][k] * determinant(m, n - 1);
                for (int i = 0; i < n - 1; i++)
                    free(m[i]);
                free(*m);
            }
        }
        return d;
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

void print_matrix(double **arr, int k) {
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            printf("%d ", (int) arr[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n, k;
//    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    Matrix *arr = (Matrix *) malloc(sizeof(Matrix) * n);
    if (arr) {
        for (int i = 0; i < n; i++) {
            scanf("%d", &k);
            arr[i].matrix = (double **) malloc(sizeof(double *) * k);
            if (arr[i].matrix) {
                for (int j = 0; j < k; j++) {
                    arr[i].matrix[j] = (double *) malloc(sizeof(double) * k);
                    if (arr[i].matrix[j]) {
                        for (int t = 0; t < k; t++)
                            scanf("%lf", &arr[i].matrix[j][t]);
                    }
                }
                arr[i].det = determinant(arr[i].matrix, k);
                arr[i].size = k;
            }
        }
        qs(arr, 0, n - 1);
        for (int i = 0; i < n; i++)
            print_matrix(arr[i].matrix, arr[i].size);
    }

    free(arr);
}