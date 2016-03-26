//
//  for_stdout.c
//  c03
//
//  Created by Cheptil Maisse on 18.12.13.
//  Copyright (c) 2013 Cheptil Maisse. All rights reserved.
//

#include <stdio.h>
#include <string.h>

#include "global.h"

void memory_dump(struct Param *param, struct Elem *arr)
{
    int i;
    int cur = 0;
    
    for (i = 0; i < param->memory_size; i++) {
        if (i % 16 == 0) {
            if (cur != 0) {
                printf("\n");
            }
            printf("%08X ", cur);
            cur += 16;
        }
        if (arr[i].flag == 0) {
            printf("??");
        } else {
            printf("%02X", (unsigned char) arr[i].byte);
        }
        if (i % 16 != 15) {
            printf(" ");
        }
    }
    printf("\n");
    return;
}

void statistics(struct Statis *statis, int statis_counter) {
    printf("clock count: %d\nreads: %d\nwrites: %d\n", statis->clock, statis->reads, statis->writes);
    if (statis_counter >= 4) {
        printf("read hits: %d\n", statis->hits);
    }
    if (statis_counter == 5) {
        printf("cache block writes: %d\n", statis->cbw);
    }
    return;
}

void print_results_and_win(
                            struct Param *param,
                            int cur_opts,
                            struct Res *res,
                            int res_count,
                            struct Elem *arr,
                            struct Statis *statis)
{
    int i = 0, statis_counter = 3;
    
    if ((cur_opts & 8) == 8) {
        for (i = 0; i < res_count; i++) {
            printf("%s = \"%s\"\n", res[i].name, res[i].value);
        }
        return;
    }
    
    if (cur_opts % 4 == 0) {
        return;
    }
    
    if ((cur_opts & 4) == 4) {
        statis_counter = 3;
    } else {
        statis_counter = 4;
        /*
        if (strcmp("write-back", param->write_strategy)) {
            statis_counter = 4;
        } else {
            statis_counter = 5;
        }
        */
    }
        
    switch (cur_opts % 4) {
        case 1:
            memory_dump(param, arr);
            break;
        case 2:
            statistics(statis, statis_counter);
            break;
        case 3:
            memory_dump(param, arr);
            statistics(statis, statis_counter);
            break;
        default:
            break;
    }
    
    return;
}