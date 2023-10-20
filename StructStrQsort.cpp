#include "StructStrQsort.h"

int ConvertStrPointerToStrStruct(char * const * pointer, struct string * *struc_ptr, const size_t num_str) {
    *struc_ptr = (string *) calloc(num_str + 1, sizeof(string));

    if (*struc_ptr == nullptr) {
        printf("Failed reallocation in ConvertStrPointerToStrStruct\n");
        return -1;
    }

    for (size_t i = 0; i < num_str; i++) {
        (*struc_ptr + i)->str = pointer[i];
        (*struc_ptr + i)->len = pointer[i + 1] - pointer[i];
    }

    size_t end_num = 0;

    while (*(pointer[num_str] + end_num) != 0) 
        end_num++;

    (*struc_ptr + num_str)->str = pointer[num_str];
    (*struc_ptr + num_str)->len = end_num;
    
    return 0;
}

int StrSort(struct string *ptr_str, size_t num_str, HowSort how_sort) {
    printf("StrSort started...\n");

    num_str++;

    int (*str_cmp) (struct string, struct string);

    if (how_sort == Beginning) {
        str_cmp = str_cmp_beginning;

    } else if (how_sort == Ending) {
        str_cmp = str_cmp_ending;

    } else {
        printf("Incorrect how_sort\n");
        printf("StrSort go to the bed\n");
        return -1;
    }

    StrQsort(ptr_str, num_str, str_cmp);

    printf("StrSort finished!\n");

    return 0;
}

int StrQsort(struct string *ptr_str, const size_t n, int (*str_cmp) (struct string, struct string)) {
    if (ptr_str == NULL) {
        printf("ptr_str == NULL at StrQsort\n");
        return -1;
    }

    size_t left = 0, right = n - 1;

    if (n <= 1) {

    } else if (n == 2) {
        StrSortTwo(ptr_str, str_cmp);

    } else if (n == 3) {
        StrSortThree(ptr_str, str_cmp);

    } else {
        size_t mid = n / 2;

        while (left < right) {
            while ((str_cmp(ptr_str[left], ptr_str[mid]) <= 0) && (left < mid)) 
                left++;

            while ((str_cmp(ptr_str[mid], ptr_str[right]) <= 0) && (mid < right)) 
                right--;

            if (left < right) {
                StrSwap(&ptr_str[left], &ptr_str[right]);

                if (mid == left) {
                    mid = right;

                } else if (mid == right) {
                    mid = left;
                }
            }
        }

        StrQsort(ptr_str, mid + 1, str_cmp);
    
        StrQsort(&ptr_str[mid + 1], n - mid - 1, str_cmp);
    }

    return 0;
}

static void StrSortTwo(struct string *ptr_str, int (*str_cmp) (struct string, struct string)) {
    if (str_cmp(ptr_str[0], ptr_str[1]) > 0)
        StrSwap(&ptr_str[0], &ptr_str[1]);
}

static void StrSortThree(struct string *ptr_str, int (*str_cmp) (struct string, struct string)) {
    int c01 = (str_cmp(ptr_str[0], ptr_str[1]) >= 0);
    int c12 = (str_cmp(ptr_str[1], ptr_str[2]) >= 0);
    int c20 = (str_cmp(ptr_str[2], ptr_str[0]) >= 0);

    if ((!c01) && c12 && c20) {
        StrSwap(&ptr_str[1], &ptr_str[2]);

    } else if  (  c01  && (!c12) &&   c20 ) {
        StrSwap(&ptr_str[0], &ptr_str[1]);

    } else if  ((!c01) &&   c12  && (!c20)) {
        StrSwap(&ptr_str[0], &ptr_str[2]);
        StrSwap(&ptr_str[1], &ptr_str[2]);

    } else if  (  c01  && (!c12) && (!c20)) {
        StrSwap(&ptr_str[0], &ptr_str[1]);
        StrSwap(&ptr_str[1], &ptr_str[2]);

    } else if  (  c01  && c12) {
        StrSwap(&ptr_str[0], &ptr_str[2]);
    }
}

static void StrSwap(struct string *x, struct string *y) {
    assert(x != NULL);
    assert(x != NULL);

    struct string c = *x; 
    *x = *y;
    *y = c;
}

static int str_cmp_beginning(const struct string s1, const struct string s2) {
    assert(s1.str != NULL);
    assert(s2.str != NULL);

    size_t i = 0, j = 0;

    while ((i < s1.len) && (j < s2.len)) {
        while (is_alpha(s1.str[i]) && (i < s1.len)) {
            i++;
        }

        while (is_alpha(s2.str[j]) && (j < s2.len)) {
            j++;
        }

        if (s1.str[i] != s2.str[j]) 
            return (s1.str[i] - s2.str[j]);

        i++;
        j++;
    }
    
    return s1.str[i] - s2.str[j];
}

static int str_cmp_ending(const struct string s1, const struct string s2) {
    assert(s1.str != NULL);
    assert(s2.str != NULL);

    int i = s1.len - 1, j = s2.len - 1;

    while ((i > 0) && (j > 0)) {
        while (is_alpha(s1.str[i]) && (i > 0)) 
            i--;

        while (is_alpha(s2.str[j]) && (j > 0))
            j--;

        if (s1.str[i] != s2.str[j])
            return (s1.str[i] - s2.str[j]);

        i--;
        j--;
    }

    return s1.str[0] - s2.str[0];
}

static int is_alpha(const char a) {
    if (('A' <= a) && (a <= 'Z')) 
        return 0;

    if (('a' <= a) && (a <= 'z'))
        return 0;
    
    return -1;
}