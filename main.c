#include <stdio.h>
#define SIZE 255

int main() {
    int l, c;//line, column
    scanf("%d%d", &c, &l);
    int a[SIZE][SIZE], max, same = c;
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    for (int i = l - 2; i >= 0; i--) {
        for (int j = c - 1; j >= 0; j--) {
            max = a[i][j];
            for (int m = ((j - 1) < 0 ? 0 : j - 1); m <= ((j + 1) < c ? j + 1 : c); m++) {
                max = ((max > a[i + 1][m]) ? max : a[i + 1][m]);
            }
            same += (a[i][j] == max);
            a[i][j] = max;
        }
    }
    printf("%d\n", same);
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }
}