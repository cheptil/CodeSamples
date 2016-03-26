//
//  File.c
//  c03
//
//  Created by Cheptil Maisse on 18.12.13.
//  Copyright (c) 2013 Cheptil Maisse. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "global.h"

enum
{
    NUMB_OPT = 4,
    MAX_LEN_OPT = 20
};

int parse_arguments(int argc, const char *argv[], struct Res *res, int res_count)
{
    int i, j;
    int flag = 0;
    
    
    char opts[NUMB_OPT][MAX_LEN_OPT] =
    {
        "--dump-memory",
        "--statistics",
        "--disable-cache",
        "--print-config"
    };
    
    int cur_opts = 0;

    for (i = 1; i < argc - 1; i++) {
        for (j = 0; j < NUMB_OPT; j++) {
            if (!strcmp(argv[i], opts[j])) {
                cur_opts += 1 << j;
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            freeall(res, res_count);
            fprintf(stderr, "Invalid arguments\n");
            exit(EXIT_FAILURE);
        }
    }
    
    return cur_opts;
}
