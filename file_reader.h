#ifndef PORTFOLIO_ALLOCATOR_FILE_READER_H
#define PORTFOLIO_ALLOCATOR_FILE_READER_H
#include "config.h"


int string_to_double(
    char in[NAME_LEN],
    double *out
    );


int word_till_sign(
    const char in[3 * NAME_LEN],
    char sign,
    char *word_out,
    char *rest_out
    );


int check_file_len(
    int *file_len_out,
    char path[NAME_LEN]
    );


int read_from_file(
    asset *v_out,
    double *contribution_out,
    char path[NAME_LEN]
    );


#endif