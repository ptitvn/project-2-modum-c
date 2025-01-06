#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	DanhMuc danhSach [MAX_DANH_MUC];
	
    int soLuong = 0;
    int luaChon;
    int soLuongDanhMuc = 0;
    char tenDanhMuc[MAX_TEN];
    char tenCanTim[MAX_TEN];
    char tieptuc;
    docDanhSachTuFileDAT(danhSach, &soLuongDanhMuc);
    do {
    	
        hienThiMenu();
        scanf("%d", &luaChon);

        switch (luaChon) {
            case 1:       	
				hienThiDanhSach(danhSach, soLuongDanhMuc);
                break;
            case 2:
            	clear();
               themDanhMuc(danhSach, &soLuongDanhMuc);
               clear();

                break;
            case 3:
            	clear();
            	do {
            		timKiemDanhMuc(danhSach, soLuongDanhMuc);
	           		printf("Ban co muon tiep tuc khong?\n ");
        			printf("(a)Continue\t (b)Exits\n "); 
        			scanf(" %c", &tieptuc);
    			} while (tieptuc == 'a' || tieptuc == 'B');
            	clear();
                break;
            case 4:
            	clear();
            	do {
				luuDanhSachVaoFileDAT(danhSach, soLuongDanhMuc);
				
            	printf("Ban co muon tiep tuc khong?\n ");
        		printf("(a)Continue\t (b)Exits\n "); 
        		scanf(" %c", &tieptuc);
    			} while (tieptuc == 'a' || tieptuc == 'B');
            	clear();
                break;
            case 5:
            	clear();
            	do {
            		suaDanhMuc (danhSach, soLuongDanhMuc);
            	
            		printf("Ban co muon tiep tuc khong?\n ");
        			printf("(a)Continue\t (b)Exits\n "); 
        			scanf(" %c", &tieptuc);
    			} while (tieptuc == 'a' || tieptuc == 'B');
    			clear();
				break;    
            case 6:
            	clear();
            	do {
				int maXoa;
				printf("Nhap ID danh muc muon xoa: ");
				scanf("%d", &maXoa);
				xoaDanhMuc(danhSach, &soLuongDanhMuc, maXoa); 
				printf("Ban co muon tiep tuc khong?\n ");
        		printf("(a)Continue\t (b)Exits\n "); 
        		scanf(" %c", &tieptuc);
    			} while (tieptuc == 'a' || tieptuc == 'B');
				clear(); 
                break;
            case 7:
            	clear();
				sapXepDanhMuc(danhSach, soLuongDanhMuc);
				break;
			
			   
            default:
            	
                printf("Lua chon khong hop le!\n");
        }
    } while (luaChon != 0);
	
	return 0;
}
	
