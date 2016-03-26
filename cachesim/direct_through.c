//
//  direct_throw.c
//  c03
//
//  Created by Cheptil Maisse on 18.12.13.
//  Copyright (c) 2013 Cheptil Maisse. All rights reserved.
//

#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

#include "global.h"

enum
{
    SIZE = 1001,
};

struct Elem *direct_through(
                            struct Param *param,
                            struct Res *res, 
                            int res_count,
                            struct Statis *statis)
{
    char s[PATH_MAX];
    char op1, op2;
    struct MyCache *cache_check;
    int addr, size, value, i;
    int cache_block_num, memory_block_num, block_count;
    int scanf_cnt = 0;
    
    struct Elem *arr = calloc(param->memory_size, sizeof(*arr));
    memset(arr, 0, param->memory_size * sizeof(*arr));

    
    block_count = param->cache_size / param->block_size;
    cache_check = calloc(block_count, sizeof(*cache_check));
    
    for (i = 0; i < block_count; i++) {
        cache_check[i].flag = 0;
    }
    
    while (fgets(s, sizeof(s), stdin)) {
        sscanf(s, "%c%c %x %d %d", &op1, &op2, &addr, &size, &value);
        memory_block_num = addr / param->block_size;
        cache_block_num = memory_block_num % block_count;
        if (cache_check[cache_block_num].flag == 0) {
            if (op1 == 'R') {
                cache_check[cache_block_num].flag = 1;
                cache_check[cache_block_num].nom = memory_block_num;
                statis->clock += param->memory_read_time * ceilor(size, param->memory_width);
                statis->clock += param->cache_write_time;
            } else if (op1 == 'W') {
                statis->clock += param->memory_write_time * ceilor(size, param->memory_width);
            }
        } else if (cache_check[cache_block_num].nom != memory_block_num) {
            statis->clock += param->cache_read_time;
            if (op1 == 'R') {
                cache_check[cache_block_num].nom = memory_block_num;
                statis->clock += param->memory_read_time * ceilor(size, param->memory_width);
                statis->clock += param->cache_write_time;
            } else if (op1 == 'W') {
                statis->clock += param->memory_write_time * ceilor(size, param->memory_width);
            }
        } else {
            statis->clock += param->cache_read_time;
            statis->hits = statis->hits + 1;
        }
        if (op1 == 'R') {
            statis->reads = statis->reads + 1;
        } else if (op1 == 'W') {
            statis->writes = statis->writes + 1;
        }
        
        if (scanf_cnt == 2) {
            size = 1;
            value = 0;
        }
        for (i = 0; i < size; i++) {
            arr[addr + size - 1 - i].byte = value & 255;
            arr[addr + size - 1 - i].flag = 1;
            value >>= 8;
        }
    }    
    return arr;
}
