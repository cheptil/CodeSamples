//
//  check_opt_param.c
//  c03
//
//  Created by Cheptil Maisse on 18.12.13.
//  Copyright (c) 2013 Cheptil Maisse. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "global.h"
#include "trace_check.h"
#include "cache_check.h"

struct Param *check_opts_params(int cur_opts, struct Res *res, int res_count)
{
    struct Param *param = calloc(1, sizeof(*param));
    memset(param, '\0', sizeof(*param));
    
    if ((cur_opts & 1) == 1 || (cur_opts & 2) == 2) {
        trace_check(param, res, res_count);
    }
    if ((cur_opts & 4) == 0 && cur_opts != 0) {
        cache_check(param, res, res_count);
    }
    
    return param;
}
