#include <stdio.h>
#define SIZE 255
int main() {
    int l, c;//line, column
    scanf("%d%d", &c, &l);
    int a[SIZE][SIZE], p = 0, max, same = 0;
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            max = a[i][j];
            for (int k = i; k < l; k++) {
                for (int m = ((j - p) < 0 ? 0 : j - p); m <= ((j + p) < c ? j + p : c); m++) {
                    max = ((max > a[k][m]) ? max : a[k][m]);
                }
                p++;
            }
            p = 0;
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