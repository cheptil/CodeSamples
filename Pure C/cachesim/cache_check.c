//
//  cache_check.c
//  c03
//
//  Created by Cheptil Maisse on 18.12.13.
//  Copyright (c) 2013 Cheptil Maisse. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "global.h"
#include "cache_check.h"

enum
{
    NUMB_PARAM = 8,
    MAX_LEN_PARAM = 30
};

void cache_check(struct Param *param ,struct Res *res, int res_count)
{
    struct Res *cur_mem = NULL;
    int i = 0;
    
    char mem_str[NUMB_PARAM][MAX_LEN_PARAM] =
    {
        "cache_size",
        "block_size",
        "cache_read_time",
        "cache_write_time",
        "seed",
        
        "associativity",
        "replacement_strategy",
        "write_strategy"
    };

    for (i = 0; i < NUMB_PARAM; i++) {
        if (i == 6 && !strcmp("direct", param->associativity)) {
            continue;
        }
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
                    param->cache_size = strtol(cur_mem->value, NULL, 10);
                    break;
                case 1:
                    param->block_size = strtol(cur_mem->value, NULL, 10);
                    break;
                case 2:
                    param->cache_read_time = strtol(cur_mem->value, NULL, 10);
                    break;
                case 3:
                    param->cache_write_time = strtol(cur_mem->value, NULL, 10);
                    break;
                case 4:
                    param->seed = strtol(cur_mem->value, NULL, 10);
                    break;
                case 5:
                    param->associativity = strdup(cur_mem->value);
                    break;
                case 6:
                    param->replacement_strategy = strdup(cur_mem->value);
                    break;
                case 7:
                    param->write_strategy = strdup(cur_mem->value);
                    break;
                default:
                    break;
            }
        }
    }
    return;
}