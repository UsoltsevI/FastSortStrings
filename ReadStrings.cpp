#include "ReadStrings.h"
#include "StructStrQsort.h"

int ReadStrFromFileToBuf(StructPtr *struc_p) {
    printf("The file input process has started...\n");

    if (struc_p->name_file_input == NULL) {
        printf("name_file_input == NULL\n");
        return -1;
    }

    FILE *ReadableFile = fopen(struc_p->name_file_input, "r");

    fseek(ReadableFile, EOF, SEEK_END);

    struc_p->num_elem = ftell(ReadableFile);   

    struc_p->buf = (char *) calloc(struc_p->num_elem + 2, sizeof(char));  

    if (struc_p->buf == NULL)
        return -1;

    fseek(ReadableFile, 0, SEEK_SET);

    fread(struc_p->buf, sizeof(char), struc_p->num_elem, ReadableFile);

    struc_p->buf[struc_p->num_elem] = 0;
    struc_p->buf[struc_p->num_elem] = '\n';

    fclose(ReadableFile);

    printf("The file has successfully read!\n");

    return 0;
}

int CountNumberStringsInBuf(StructPtr *const struc_p) {
    int result = 0;

    for (int i = 0; i < struc_p->num_elem; i++) {
        if (struc_p->buf[i] == '\n')
            result++;
    }

    struc_p->num_str = result;

    return result;
}

int ConvertBufToPtrArray(StructPtr *struc_p) {
    CountNumberStringsInBuf(struc_p);

    struc_p->ptr_str = (char **) calloc(struc_p->num_str + 1, sizeof(char *));  

    if (struc_p->ptr_str == NULL)
        return -1;

    struc_p->ptr_str[0] = (char *) struc_p->buf;

    size_t elem_num = 1, str_num = 1;

    while (elem_num < struc_p->num_elem) {
        if (struc_p->buf[elem_num] == '\n') { 
            struc_p->ptr_str[str_num] = (char *) (struc_p->buf + elem_num + 1);
            str_num++;
        }

        elem_num++;
    }

    return 0;
}

int WriteStrFile(const StructPtr * const struc_p) {
    printf("The file output process has started...\n");

    if (struc_p->name_file_output == NULL) {
        printf("name_file_output == NULL\n");
        return -1;
    }

    FILE *OutputFile;
    OutputFile = fopen(struc_p->name_file_output, "w");

    for (size_t i = 0; i < struc_p->num_str; i++) 
        WriteOneStrFile(struc_p->ptr_str[i], OutputFile);
    
    fclose(OutputFile);

    printf("The data the data was successfully output to the file named %s\n", struc_p->name_file_output);

    return 0;
}

int WriteStrucStrFile(const struct string * const struc_ptr, const size_t num_elem, const char *filename) {
    if (filename == NULL){
        printf("filename == NULL\n");
        return -1;
    }

    FILE *fout = fopen(filename, "w");
    size_t i = 0;
    
    if (fout == NULL) {
        printf("fout == NULL at WriteStrucStrFile\n");
        return -1;
    }
    
    while (i < num_elem + 1) {
        WriteOneStrFile(struc_ptr[i].str, fout);
        i++;
    }

    fclose(fout);

    return 0;
}

void WriteOneStrFile(const char *str, FILE *stream) {
    char check = 0;
    size_t i = 0;

    while (check != '\n'){
        check = *(str + i);
        fputc(check, stream);
        i++;
    }
}

void CleanStructPtr(StructPtr *struc_p) {
    free(struc_p->ptr_str);
    free(struc_p->buf);

    struc_p->ptr_str          = NULL;
    struc_p->buf              = NULL;
    struc_p->name_file_input  = NULL;
    struc_p->name_file_output = NULL;

    struc_p->num_elem = 0;
    struc_p->num_str  = 0;
}

