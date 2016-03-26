
//
//  main.c
//  c02
//
//  Created by Cheptil Maisse on 17.12.13.
//  Copyright (c) 2013 Cheptil Maisse. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdlib.h>

#include "global.h"
#include "parse_config.h"

enum
{
    NUMB_PARAM = 12,
    MAX_LEN_PARAM = 30
};

char * getline2(FILE *f)
{
    char *text = NULL;
    int a = 0, n = 0, c;
    while ((c = getc(f)) != EOF && c != '\n') {
        if (n == a) {
            if (!a) {
                a = 128;
            }
            text = realloc(text, (a*=2)*sizeof(*text));
        }
        text[n++] = c;
    }
    if (c == EOF && n == 0) {
        return text;
    }
    if ((n + 1) >= a) {
        if (!a) {
            a = 128;
        }
        text = realloc(text, (a*=2)*sizeof(*text));
    }
    if (c == '\n') {
        text[n++] = '\n';
    }
    text[n] = '\0';
    return text;
}

void del_final_spaces(char *ch, int len)
{
    char *cur = ch + len - 1;
    while (isspace(*cur) && cur >= ch) {
        cur--;
    }
    cur++;
    *cur = '\0';
    return;
}

struct Res *parse_config(int argc, const char * argv[], int *res_count)
{
    struct Res *res = NULL;
    
    char *cur_string, *sep, *name, *value, *string_addr;
    int i;
    int line_cnt = 1, n = 0;

    if (argc == 1) {
        fprintf(stderr, "Invalid arguments\n");
        exit(EXIT_FAILURE);
    }
    
    FILE *f = fopen(argv[argc - 1], "r");
    if (!f) {
        fprintf(stderr, "Failed to open %s for reading\n", argv[argc - 1]);
        exit(EXIT_FAILURE);
    }
    
    while ((cur_string = getline2(f)) != NULL) {
        if (strlen(cur_string) > 1000) {
            fprintf(stderr, "Syntax error in line %d of %s\n", line_cnt, argv[argc - 1]);
            free(cur_string);
            freeall(res, *res_count);
            exit(EXIT_FAILURE);
        }
        for (i = 0; i < strlen(cur_string); i++) {
            if (cur_string[i] < ' ' && cur_string[i] != '\n' &&
                cur_string[i] != '\r' && cur_string[i] != '\t') {
                fprintf(stderr, "Syntax error in line %d of %s\n", line_cnt, argv[argc - 1]);
                free(cur_string);
                freeall(res, *res_count);
                exit(EXIT_FAILURE);
            }
        }
        string_addr = cur_string;
        
        sep = strchr(cur_string, '#');
        if (sep) {
            *sep = '\0';
        }
        
        while (isspace(*cur_string)) {
            cur_string++;
        }
        if (*cur_string == '\0') {
            free(string_addr);
            line_cnt++;
            continue;
        }
        
        sep = strchr(cur_string, '=');
        if (sep) {
            *sep = '\0';
        } else {
            fprintf(stderr, "Syntax error in line %d of %s\n", line_cnt, argv[argc - 1]);
            free(cur_string);
            freeall(res, *res_count);
            exit(EXIT_FAILURE);
        }
        
        name = strdup(cur_string);
        del_final_spaces(name, strlen(name));
        
        if (!isalpha(name[0]) && name[0] != '_') {
            fprintf(stderr, "Syntax error in line %d of %s\n", line_cnt, argv[argc - 1]);
            free(name);
            free(cur_string);
            freeall(res, *res_count);
            exit(EXIT_FAILURE);
        }
        for (i = 1; i < strlen(name); i++) {
            if (name[i] != '_' && name[i] != '-' && !isalnum(name[i])) {
                fprintf(stderr, "Syntax error in line %d of %s\n", line_cnt, argv[2]);
                free(name);
                free(cur_string);
                freeall(res, *res_count);
                exit(EXIT_FAILURE);
            }
        }
        
        for (i = 0; i < *res_count; i++) {
            if(!strcmp(name, res[i].name)) {
                fprintf(stderr, "Duplicate parameter %s in %s\n", name, argv[argc - 1]);
                free(name);
                free(cur_string);
                freeall(res, *res_count);
                exit(EXIT_FAILURE);
            }
        }
        
        sep++;
        while (isspace(*sep)) {
            sep++;
        }
        
        value = strdup(sep);
        del_final_spaces(value, strlen(value));
        
        char param_names[NUMB_PARAM][MAX_LEN_PARAM] =
        {
            "memory_size",
            "memory_read_time",
            "memory_write_time",
            "memory_width",
            "cache_size",
            "block_size",
            "cache_read_time",
            "cache_write_time",
            "seed",
            "associativity",
            "replacement_strategy",
            "write_strategy"
        };
        
        char *end_of_number;
        int num = 0, baf_flag = 0;
        
        for (i = 0; i < NUMB_PARAM; i++) {
            if (!strcmp(name, param_names[i])) {
                num = strtol(value, &end_of_number, 10);
                if ((num == 0 || *end_of_number != '\0') && i < 9) {
                    baf_flag = 1;
                }
                switch (i) {
                    case 0:
                        if(num > 1024 * 1024 * 1024) {
                            baf_flag = 1;
                        }
                        break;
                    case 5:
                        if (num != 16 && num != 32 && num != 64) {
                            baf_flag = 1;
                        }
                        break;
                    case 9:
                        if (strcmp(value, "full") && strcmp(value, "direct")) {
                            baf_flag = 1;
                        }
                        break;
                    case 10:
                        if(strcmp(value, "random")) {
                            baf_flag = 1;
                        }
                        break;
                    case 11:
                        if (strcmp(value, "write-through") && strcmp(value, "write-back")) {
                            baf_flag = 1;
                        }
                        break;
                    default:
                        break;
                }
                if (baf_flag == 1) {
                    fprintf(stderr, "Configuration parameter %s value is invalid\n", name);
                    free(value);
                    free(name);
                    free(cur_string);
                    freeall(res, *res_count);
                    exit(EXIT_FAILURE);
                }
            }
        }
        
        if (*res_count == n) {
            if (!n) {
                n = 8;
            }
            res = realloc(res, (n *= 2) * sizeof(*res));
        }
        res[*res_count].name = name;
        res[*res_count].value = value;
        *res_count = *res_count + 1;
        line_cnt++;
        free(string_addr);
    }
    
    qsort(res, *res_count, sizeof(*res), mycompare);

    return res;
}

