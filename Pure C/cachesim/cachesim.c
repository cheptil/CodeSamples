//
//  main.c
//  c03
//
//  Created by Cheptil Maisse on 18.12.13.
//  Copyright (c) 2013 Cheptil Maisse. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "global.h"
#include "parse_config.h"
#include "parse_arguments.h"
#include "check_opts_params.h"
#include "disable_cache.h"
#include "direct_through.h"
#include "for_stdout.h"

enum
{
    SIZE = 1001,
};

void require_config(
                  struct Param *param,
                  int cur_opts,
                  struct Res *res,
                  int res_count,
                  struct Elem *(*require_func)(struct Param *param,
                                               struct Res *res,
                                               int res_count,
                                               struct Statis *statis))
{
    struct Statis *statis = NULL;
    struct Elem *arr = NULL;
    
    if (cur_opts % 4 != 0) {
        statis = calloc(1, sizeof(*statis));
        arr = require_func(param, res, res_count, statis);
    } else {
        char s[SIZE];
        while (fgets(s, sizeof(s), stdin));
    }
    
    print_results_and_win(param, cur_opts, res, res_count, arr, statis);
    return;
}

int main(int argc, const char * argv[])
{
    int res_count = 0;
    struct Res *res = parse_config(argc, argv, &res_count);
    int cur_opts = parse_arguments(argc, argv, res, res_count);

    struct Param *param = check_opts_params(cur_opts, res, res_count);
    
    struct Elem *(*func_arr[2])(struct Param *param,
                                struct Res *res,
                                int res_count,
                                struct Statis *statis)
    = {disable_cache, direct_through};

    int nom_require_func = 0;
    
    if ((cur_opts & 4) == 4 || cur_opts == 0) {
        nom_require_func = 0;
    } else {
        nom_require_func = 1;
    }
    
    require_config(param, cur_opts, res, res_count, func_arr[nom_require_func]);
    return 0;
}