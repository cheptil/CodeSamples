//
//  global.h
//  c03
//
//  Created by Cheptil Maisse on 18.12.13.
//  Copyright (c) 2013 Cheptil Maisse. All rights reserved.
//

#ifndef c03_global_h
#define c03_global_h

struct Res
{
    char *name;
    char *value;
};

struct Param
{
    int memory_size;
    int memory_read_time;
    int memory_write_time;
    int memory_width;
    
    int cache_size;
    int block_size;
    int cache_read_time;
    int cache_write_time;
    int seed;
    
    char *associativity;
    char *replacement_strategy;
    char *write_strategy;
};

struct MyCache
{
    int flag;
    int nom;
};

struct Elem
{
    char byte;
    char flag;
};

struct Statis
{
    int clock;
    int reads;
    int writes;
    int hits;
    int cbw;
};


int mycompare(const void *a, const void *b);

void freeall(struct Res *res, int res_count);

int ceilor(int n, int div);

#endif
