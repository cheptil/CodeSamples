//
//  global.c
//  c03
//
//  Created by Cheptil Maisse on 18.12.13.
//  Copyright (c) 2013 Cheptil Maisse. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "global.h"

int mycompare(const void *a, const void *b)
{
    return strcmp(*(char**)a, *(char**)b);
}

void freeall(struct Res *res, int res_count)
{
    int i;
    for (i = 0; i < res_count; i++) {
        free(res[i].name);
        free(res[i].value);
    }
    free(res);
    return;
}

int ceilor(int n, int div)
{
    if (n % div == 0) {
        return n / div;
    } else {
        return n / div + 1;
    }
}
