#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 256
#define OPERATORS "+-/*"
#define OPERATOR_COUNT ((int)(sizeof(OPERATORS) - 1))

static int find_char_index(const char *str, char ch, int len) {
    const char *p = memchr(str, (unsigned char)ch, (size_t)len);
    return p ? (int)(p - str) : -1;
}

static int is_operator(char ch) {
    return memchr(OPERATORS, (unsigned char)ch, OPERATOR_COUNT) != NULL;
}

static void append_int(char *result, int *pos, int value) {
    int written;
    if (value == 0) {
        result[(*pos)++] = '0';
        return;
    }
    written = sprintf(result + *pos, "%d", value);
    if (written > 0) {
        *pos += written;
    }
}

static void substitute_variable(char *result, int *pos, int value) {
    append_int(result, pos, value);
}

static void parse_expression(const char **input, char *result, int *result_pos,
                             const char *var_names, const int *var_values,
                             int var_count, int *error_flag, int *op_count,
                             int *paren_count) {
    while (**input != ')') {
        const char *curr = *input;
        char next = *(curr + 1);
        char prev = *(curr - 1);

        if (*curr == '(' && next != '\0' && !is_operator(next)) {
            result[(*result_pos)++] = *((*input)++);
            (*paren_count)++;
            parse_expression(input, result, result_pos, var_names, var_values,
                            var_count, error_flag, op_count, paren_count);
        }
        else if (is_operator(*curr) && next != '\0' && next != ')') {
            result[(*result_pos)++] = *((*input)++);
            (*op_count)++;
        }
        else if (find_char_index(var_names, *curr, var_count) >= 0 &&
                 ((is_operator(next) && prev == '(') ||
                  (is_operator(prev) && next == ')'))) {
            int idx = find_char_index(var_names, *curr, var_count);
            substitute_variable(result, result_pos, var_values[idx]);
            (*input)++;
        }
        else if ((!isdigit((unsigned char)*curr) && !is_operator(*curr) &&
                  !is_operator(next) && next != ')' && *curr != '(') ||
                 (isdigit((unsigned char)*curr) && next != '\0')) {
            while (!is_operator(**input) && **input != ')' && **input != '(') {
                result[(*result_pos)++] = *((*input)++);
            }
        }
        else {
            (*error_flag)++;
            return;
        }
    }
    result[(*result_pos)++] = *((*input)++);
}

int main(void) {
    int var_count;
    if (scanf("%d\n", &var_count) != 1 || var_count <= 0) {
        printf("INCORRECT");
        return 1;
    }

    char *var_names = malloc((size_t)var_count + 1);
    int *var_values = malloc((size_t)var_count * sizeof(int));
    if (!var_names || !var_values) {
        free(var_names);
        free(var_values);
        printf("INCORRECT");
        return 1;
    }

    for (int i = 0; i < var_count; i++) {
        if (scanf(" %c %d\n", &var_names[i], &var_values[i]) != 2) {
            free(var_names);
            free(var_values);
            printf("INCORRECT");
            return 1;
        }
    }
    var_names[var_count] = '\0';

    char *input_str = malloc(MAX_BUFFER_SIZE);
    char *output_str = malloc(MAX_BUFFER_SIZE);
    if (!input_str || !output_str) {
        free(var_names);
        free(var_values);
        free(input_str);
        free(output_str);
        printf("INCORRECT");
        return 1;
    }

    if (scanf("%255s", input_str) != 1) {
        free(var_names);
        free(var_values);
        free(input_str);
        free(output_str);
        printf("INCORRECT");
        return 1;
    }

    int result_pos = 0;
    int error_flag = 0;
    int op_count = 0;
    int paren_count = 0;
    const char *cursor = input_str;

    if (*cursor == '(' && *(cursor + 1) != '\0' && !is_operator(*(cursor + 1))) {
        output_str[result_pos++] = *cursor++;
        paren_count++;
        parse_expression(&cursor, output_str, &result_pos, var_names,
                         var_values, var_count, &error_flag, &op_count,
                         &paren_count);
    }
    else if (find_char_index(var_names, *cursor, var_count) >= 0) {
        int idx = find_char_index(var_names, *cursor, var_count);
        substitute_variable(output_str, &result_pos, var_values[idx]);
        cursor++;
    }
    else if (isdigit((unsigned char)*cursor)) {
        while (*cursor != '\0') {
            if (*cursor == '(' || *cursor == ')' || !isdigit((unsigned char)*cursor) ||
                is_operator(*cursor)) {
                error_flag++;
            }
            output_str[result_pos++] = *cursor++;
        }
    }
    else {
        error_flag++;
    }

    if (error_flag == 0 && op_count == paren_count) {
        output_str[result_pos] = '\0';
        printf("%s", output_str);
    }
    else {
        printf("INCORRECT");
    }

    free(var_names);
    free(var_values);
    free(input_str);
    free(output_str);
    return 0;
}
