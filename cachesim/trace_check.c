//
//  dump-memory.c
//  c03
//
//  Created by Cheptil Maisse on 18.12.13.
//  Copyright (c) 2013 Cheptil Maisse. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "trace_check.h"

enum
{
    NUMB_PARAM = 4,
    MAX_LEN_PARAM = 30
};

void trace_check(struct Param *param ,struct Res *res, int res_count)
{
    struct Res *cur_mem = NULL;
    int i = 0;
    
    char mem_str[NUMB_PARAM][MAX_LEN_PARAM] =
    {
        "memory_size",
        "memory_read_time",
        "memory_write_time",
        "memory_width"
    };
    
    for (i = 0; i < NUMB_PARAM; i++) {
        char *cur_elem = mem_str[i];
        cur_mem = bsearch(&cur_elem, res, res_count, sizeof(*res), mycompare);
        if (!cur_mem) {
            fprintf(stderr, "Configuration parameter %s is undefined\n", mem_str[i]);
            for (i = 0; i < res_count; i++) {
                free(res[i].name);
                free(res[i].value);
            }
            free(res);
            exit(EXIT_FAILURE);
        } else {
            switch (i) {
                case 0:
                    param->memory_size = strtol(cur_mem->value, NULL, 10);
                    break;
                case 1:
                    param->memory_read_time = strtol(cur_mem->value, NULL, 10);
                    break;
                case 2:
                    param->memory_write_time = strtol(cur_mem->value, NULL, 10);
                    break;
                case 3:
                    param->memory_width = strtol(cur_mem->value, NULL, 10);
                    break;
                default:
                    break;
            }
        }
    }
    return;
}