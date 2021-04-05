#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define sign "+-/*"
#define elif else if
#define or ||
#define and &&
#define not !
#define char_to_int(char_id, start, n) ((char *) memchr(char_id, start, n) - char_id)

void int_to_char (char *result, int *cur_el, int *int_id, char *char_id, int n, char *start) {
    int x = char_to_int(char_id, *start, n);
    itoa(int_id[x], &result[*cur_el], 10);
    *cur_el += (int) log10(int_id[x]) + 1;
}

void ordinary (char **start, char *result, int *j, char *char_id, int *int_id, int n, int *flag, int *sign_cnt, int *recur_cnt) {
    while (**start != ')') {
        if (not (**start != '(' or *(*start + 1) == 0 or memchr(sign, *(*start + 1), sizeof(int)))) {
            result[(*j)++] = *((*start)++); ++(*recur_cnt);
            ordinary(start, result, j, char_id, int_id, n, flag, sign_cnt, recur_cnt);
        } elif (memchr(sign, **start, sizeof(int)) and *(*start + 1) != 0 and *(*start + 1) != ')') {
            result[(*j)++] = *((*start)++);(*sign_cnt)++;
        } elif (memchr(char_id, **start, n) and ((memchr(sign, *(*start + 1), sizeof(int)) and *(*start - 1) == '(') or (memchr(sign, *(*start - 1), sizeof(int)) and *(*start + 1) == ')')))
            int_to_char(result, j, int_id, char_id, n, (*start)++);
        elif (not isdigit(**start) and not memchr(sign, **start, sizeof(int)) and not memchr(sign, *(*start + 1), sizeof(int)) and *(*start + 1) != ')' and **start != '(' or isdigit(**start) and *(*start + 1) != 0)
            while (not memchr(sign, **start, sizeof(int)) and **start != ')' and **start != '(')
                result[(*j)++] = *((*start)++);
        else {
            (*flag)++;
            return;
        }
    }
    result[(*j)++] = *((*start)++);
}

int main() {
    int n;
    scanf("%d\n", &n);
    char *char_id = (char*)malloc(n+1);
    int *int_id = (int*)malloc(sizeof(int)*n+4);
    for (int i = 0; i < n; i++) scanf("%c %d\n", &char_id[i], &int_id[i]);
    char_id[n] = 0;
    char *str = (char*)malloc(256), *final_str = (char*)malloc(256);
    scanf("%s", str);
    int cur_el = 0, flag=0, sign_cnt = 0, recur_cnt = 0;
    char *end = str;
    if (*end == '(' and *(++end) and not memchr(sign, *(end), sizeof(int))) {
        final_str[cur_el++] = *(end-1);
        recur_cnt++;
        ordinary(&end, final_str, &cur_el, char_id, int_id, n, &flag, &sign_cnt, &recur_cnt);
    } elif (memchr(char_id, *end, n))
        int_to_char(final_str, &cur_el, int_id, char_id, n, end++);
    elif (isdigit(*end))
        while (*end) {
            flag += (*end == '(' or *end == ')' or not isdigit(*end) or memchr(sign, *end, sizeof(int)));
            final_str[cur_el++] = *(end)++;
        }
    else
        flag++;
    if (not flag and sign_cnt == recur_cnt) {
        final_str[cur_el] = 0;
        printf("%s", final_str);
    } else
        printf("INCORRECT");
}