#ifndef STRUCTSTRQSORT_H_INCLUDED
#define STRUCTSTRQSORT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <ctype.h>
//#include "ReadStrings.h"

enum HowSort {
    Beginning = 0,
    Ending = 1
};

struct string {
    char *str;
    size_t len;
};

int ConvertStrPointerToStrStruct(char * const *pointer, struct string * *struc_ptr, const size_t num_str);
int StrSort(struct string *ptr_str, size_t num_str, HowSort how_sort);
int StrQsort(struct string *ptr_str, const size_t n, int (*str_cmp) (struct string, struct string));

static void StrSwap(struct string *x, struct string *y);
static void StrSortTwo(struct string *ptr_str, int (*str_cmp) (struct string, struct string));
static void StrSortThree(struct string *ptr_str, int (*str_cmp) (struct string, struct string));

static int is_alpha(const char a);
static int str_cmp_beginning(const struct string s1, const struct string s2);
static int str_cmp_ending(const struct string s1, const struct string s2);


#endif // STRUCTSTRQSORT_H_INCLUDED