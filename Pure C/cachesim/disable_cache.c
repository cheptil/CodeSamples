//
//  disable-cache.c
//  c03
//
//  Created by Cheptil Maisse on 18.12.13.
//  Copyright (c) 2013 Cheptil Maisse. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "global.h"

enum
{
    SIZE = 1001,
};

struct Elem *disable_cache(
                           struct Param *param,
                           struct Res *res,
                           int res_count,
                           struct Statis *statis)
{
    char s[SIZE];
    char op1, op2;
    int i, scanf_cnt;
    int addr, size, value;
    
    struct Elem *arr = calloc(param->memory_size, sizeof(*arr));
    memset(arr, 0, param->memory_size * sizeof(*arr));
    
    while (fgets(s, sizeof(s), stdin)) {
        
        scanf_cnt = sscanf(s, "%c%c %X %d %d", &op1, &op2, &addr, &size, &value);
        
        if (op1 == 'R') {
            statis->clock += param->memory_read_time * ceilor(size, param->memory_width);
            statis->reads = statis->reads + 1;
        } else if (op1 == 'W') {
            statis->clock += param->memory_write_time * ceilor(size, param->memory_width);
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
