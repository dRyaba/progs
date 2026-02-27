#include <stdio.h>
#include <stdlib.h>

#define SIZE 255

int main() {
    int rows, cols;
    if (scanf("%d%d", &cols, &rows) != 2) {
        fprintf(stderr, "Ошибка ввода размеров\n");
        return 1;
    }

    if (rows < 1 || rows > SIZE || cols < 1 || cols > SIZE) {
        fprintf(stderr, "Размеры должны быть в диапазоне 1..%d\n", SIZE);
        return 1;
    }

    int matrix[SIZE][SIZE];

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                fprintf(stderr, "Ошибка ввода элемента\n");
                return 1;
            }
        }
    }

    int same = cols;

    for (int i = rows - 2; i >= 0; --i) {
        for (int j = cols - 1; j >= 0; --j) {
            int current = matrix[i][j];
            int max_value = current;

            int down = matrix[i + 1][j];
            if (down > max_value) {
                max_value = down;
            }

            if (j > 0) {
                int down_left = matrix[i + 1][j - 1];
                if (down_left > max_value) {
                    max_value = down_left;
                }
            }

            if (j < cols - 1) {
                int down_right = matrix[i + 1][j + 1];
                if (down_right > max_value) {
                    max_value = down_right;
                }
            }

            if (current == max_value) {
                ++same;
            }
            matrix[i][j] = max_value;
        }
    }

    printf("%d\n", same);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
