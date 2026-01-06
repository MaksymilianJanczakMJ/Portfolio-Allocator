#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "config.h"
#include "file_reader.h"

#include "allocator.h"

int string_to_double(char in[NAME_LEN], double *out) {
    char *signs;
    double value;

    errno = 0;
    value = strtod(in, &signs);

    if (errno == ERANGE) {
        fprintf(stderr, "Error in string_to_double() function: out of double range.\n");
        return 1;
    }

    if (signs == in) {
        fprintf(stderr, "Error in string_to_double() function: input is not a number \"%s\".\n", signs);
        return 1;
    }

    if (*signs != '\0' && *signs != '\n') {
        fprintf(stderr, "Error in string_to_double() function: invalid characters in input \"%s\"\n", signs);
        return 1;
    }

    *out = value;
    return 0;
}


int word_till_sign(const char in[3 * NAME_LEN], const char sign, char *word_out, char *rest_out) {
    int word_len = 0, rest_len = 0;
    int i;
    char word[NAME_LEN], rest[2 * NAME_LEN];

    while (in[word_len] != sign && in[word_len] != '\0') {
        word_len++;
    }

    if (word_len >= NAME_LEN) {
        fprintf(stderr, "Error in word_till_sign() function: word length out of range.\n");
        return 1;
    }

    for (i = 0; i < word_len; i++) {
        word[i] = in[i];
    }

    word[word_len] = '\0';

    if (in[word_len] == '\0') {
        strncpy(word_out, word, (word_len + 1) * sizeof (char));
        strncpy(rest_out, "\0", sizeof (char));

        return 0;
    }

    while (in[word_len + rest_len] != '\0') {
        rest_len++;
    }

    if (rest_len >= 2 * NAME_LEN) {
        fprintf(stderr, "Error in word_till_sign() function: rest length out of range.\n");
        return 1;
    }

    for (i = 0; i < rest_len; i++) {
        rest[i] = in[word_len + 1 + i];
    }

    rest[rest_len] = '\0';

    strncpy(word_out, word, (word_len + 1) * sizeof (char));
    strncpy(rest_out, rest, (rest_len + 1) * sizeof (char));

    return 0;
}


int check_file_len(int *file_len_out, char path[NAME_LEN]) {
    int file_len = 0;
    char line[3 * NAME_LEN];
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        fprintf(stderr, "Error in check_file_len() function: could not open \"%s\" file.\n", path);
        return 1;
    }

    while (fgets(line, sizeof line, file) != NULL) {
        file_len++;
    }

    fclose(file);

    *file_len_out = file_len;

    return 0;
}


int read_from_file(asset *v_out, char path[NAME_LEN]) {
    int row = 0, i;
    int file_len;
    char line[3 * NAME_LEN];
    char rest[2 * NAME_LEN];
    char name[NAME_LEN];
    char str_value[NAME_LEN];
    char str_target_percentage[NAME_LEN];
    double value;
    double target_percentage;
    asset *v;
    FILE *file = fopen(path, "r");

    check_file_len(&file_len, path);

    v = malloc(file_len * sizeof *v);

    file = fopen(path, "r");
    if (file == NULL) {
        fprintf(stderr, "Error in read_from_file() function: could not open \"%s\" file.\n", path);
        free(v);
        return 1;
    }

    while (fgets(line, sizeof line, file) != NULL) {
        if (word_till_sign(line, ';', name, rest)) {
            fprintf(stderr, "Error in read_from_file() function: in name in the [%d] row of \"%s\" file.\n", row + 1, path);
            free(v);
            return 1;
        }

        if (word_till_sign(rest, ';', str_value, rest)) {
            fprintf(stderr, "Error in read_from_file() function: in value in the [%d] row of \"%s\" file.\n", row + 1, path);
            free(v);
            return 1;
        }
        if (string_to_double(str_value, &value)) {
            fprintf(stderr, "Error in read_from_file() function: in value in the [%d] row of \"%s\" file.\n", row + 1, path);
            free(v);
            return 1;
        }

        if (word_till_sign(rest, ';', str_target_percentage, rest)) {
            fprintf(stderr, "Error in read_from_file() function: in target percentage in the [%d] row of \"%s\" file.\n", row + 1, path);
            free(v);
            return 1;
        }
        if (string_to_double(str_target_percentage, &target_percentage)) {
            fprintf(stderr, "Error in read_from_file() function: in target percentage in the [%d] row of \"%s\" file.\n", row + 1, path);
            free(v);
            return 1;
        }

        v[row] = make_asset(name, value, target_percentage);
        row++;
    }

    memcpy(v_out, v, file_len * sizeof *v);

    free(v);
    return 0;
}