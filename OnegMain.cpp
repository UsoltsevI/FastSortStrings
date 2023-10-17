#include "OnegMain.h"

int main(int argc, const char *argv[]) { 

    struct StructPtr struc_p = {};

    struc_p.name_file_input  = argv[1];
    struc_p.name_file_output = argv[2];

    ReadStrFromFileToBuf(&struc_p);
    ConvertBufToPtrArray(&struc_p);

    HowSort how_sort = (HowSort) 0;

    printf("Enter 0 if you wand to sort by left side, or 1 if you want to sort by right side:\n");

    scanf("%d", &how_sort);

    struct string *struc_ptr = NULL;

    ConvertStrPointerToStrStruct(struc_p.ptr_str, &struc_ptr, struc_p.num_str);

    StrSort(struc_ptr, struc_p.num_str, how_sort);

    WriteStrucStrFile(struc_ptr, struc_p.num_str, struc_p.name_file_output);
    
    CleanStructPtr(&struc_p);

    printf("program comlited\n");

    return 0;
}
