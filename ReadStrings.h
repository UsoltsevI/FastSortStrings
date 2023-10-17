#ifndef ONEGREAD_H_INCLUDED
#define ONEGREAD_H_INCLUDED

#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct StructPtr {
    size_t num_elem;
    char *buf;
    char * *ptr_str;
    size_t num_str;
    const char *name_file_input;
    const char *name_file_output;
};

int ReadStrFromFileToBuf(StructPtr *struc_p);
int CountNumberStringsInBuf(StructPtr *struc_p) ;
int ConvertBufToPtrArray(StructPtr *struc_p);
int WriteStrFile(StructPtr *struc_p); //const
void CleanStructPtr(StructPtr *struc_p);
void WriteOneStrFile(const char *str, FILE *stream);
int WriteStrucStrFile(struct string *struc_ptr, size_t num_elem, const char *filename);

#endif // ONEGREAD_H_INCLUDED
