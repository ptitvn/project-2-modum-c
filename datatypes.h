#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DANH_MUC 100 // khai bao size 100 thanh chu 
#define MAX_TEN 100


// Cau truc danh muc
typedef struct {
    int maDanhMuc;
    char tenDanhMuc[50];
    float giaTien;
} DanhMuc;
