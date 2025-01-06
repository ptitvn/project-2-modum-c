#include "functions.h"
#include <string.h>

void hienThiMenu() {
    printf("\n======================================\n");
    printf("\n         Product Portfolio Management\n        ");
    printf("\n======================================\n");
    printf("\t1. Show Catalog List\n"); //Hien thi danh sï¿½ch danh muc
    printf("\t2. Add a new category\n"); //them danh muc moi 
    printf("\t3. Catalog Search\n");//Tim kiem danh muc
    printf("\t4. Save the list to file\n");//Luu danh sach vao tep
    printf("\t5. Edit the list\n");//Chinh sua danh sach
    printf("\t6. Delete a category\n");//Xï¿½a danh muc
    printf("\t7. Arrangement\n"); //sap xep
    printf("\t0. Exits\n");
    printf("\nSelect: ");
}
int nhapDanhMuc(DanhMuc *dm, DanhMuc *danhSach, int soLuong) {
    int i;
    do {
        int flag = 0; // Flag to check for duplicate ID
        printf("Enter the catalog code: ");
        scanf("%d", &dm->maDanhMuc);
        getchar(); // Loai bo ki tu '\n' thua

        // Check for duplicate ID
        for (i = 0; i < soLuong; i++) {
            if (dm->maDanhMuc == danhSach[i].maDanhMuc) {
                printf("Catalog code already exists. Please enter again!\n");
                flag = 1;
                break;
            }
        }

        if (dm->maDanhMuc == 0) {
            printf("Catalog code cannot be 0. Please enter again!\n");
            flag = 1;
        }

        if (flag) {
            continue; // If ID is duplicate or 0, continue to re-enter
        }

        printf("Enter a catalog name: ");
        fgets(dm->tenDanhMuc, MAX_TEN, stdin);
        dm->tenDanhMuc[strcspn(dm->tenDanhMuc, "\n")] = '\0';

        printf("Enter the price: ");
        scanf("%f", &dm->giaTien);
        getchar();

        // Kiem tra xem co bi trung lap ko
        for (i = 0; i < soLuong; i++) {
            if (strcmp(dm->tenDanhMuc, danhSach[i].tenDanhMuc) == 0) {
                printf("Catalog name already exists. Please enter again!\n");
                break;
            }
        }
    } while (i < soLuong);

    return i == soLuong; // Tra ve 1 neu khong trung, 0 neu trï¿½ng
}

void hienThiDanhSach(DanhMuc *danhSach, int soLuong) {
    printf("\nCatalog List:\n");
    int i;
    printf("+-----------------+-----------------------+------------+\n");
    printf("|       Catalog id|      Catalog name     |    Price   |\n");
    printf("+-----------------+-----------------------+------------+\n");
    for (i = 0; i < soLuong; i++) {
        printf("| %15d | %-20s | %2.f         |\n", danhSach[i].maDanhMuc, danhSach[i].tenDanhMuc, danhSach[i].giaTien);
    }
    printf("+-----------------+-----------------------+------------+\n");
}

int kiemTraDuLieuHopLe(DanhMuc dm) {
    // Ki?m tra m? danh m?c (vï¿½ du: phai lï¿½ s? nguyï¿½n d??ng)
    if (dm.maDanhMuc <= 0) {
        printf("And the catalog must be a whole number!\n");//Ma danh muc phai la so nguyen duong!
        return 0;
    }

    // Ki?m tra tï¿½n danh m?c (vï¿½ d?: khï¿½ng ï¿½ï¿½?c ï¿½? tr?ng)
    if (strlen(dm.tenDanhMuc) == 0) {
        printf("Category names are not left in the!\n");//Ten danh muc khong duoc de trong
        return 0;
    }

    // Kiem tra gia tien  
    if (dm.giaTien <= 0) {
        printf("Price must be greater than 0.\n");
        return 0;
    }

    return 1;
}

void themDanhMuc(DanhMuc *danhSach, int *soLuong) {
    DanhMuc dm;
    char tieptuc;
    int daThem = 0;
    do {
        if (nhapDanhMuc(&dm, danhSach, *soLuong) && kiemTraDuLieuHopLe(dm)) {
            danhSach[*soLuong] = dm;
            (*soLuong)++;
            printf("Add a successful category!\n");
        } else {
            printf("Add a failed category!\n");
        }
        printf("Do you want to add more categories?\n ");
        printf("(a)Continue\t (b)Exits\n ");
        scanf(" %c", &tieptuc);
    } while (tieptuc == 'a' || tieptuc == 'B');

    if (daThem) {
        printf("Add a successful category!\n");
        // Lï¿½u danh sï¿½ch sau khi thï¿½m
        luuDanhSachVaoFileDAT(danhSach, *soLuong);
    }
}

void luuDanhSachVaoFileDAT(DanhMuc *danhSach, int soLuong) {
    FILE *fp = fopen("danh_sach.dat", "wb");
    if (fp == NULL) {
        printf("Loi mo file!\n");
        return;
    }

    fwrite(danhSach, sizeof(DanhMuc), soLuong, fp);

    fclose(fp);
    printf("Luu danh sach vao file thanh cong!\n");
}

void docDanhSachTuFileDAT(DanhMuc *danhSach, int *soLuong) {
    FILE *fp = fopen("danh_sach.dat", "rb");
    if (fp == NULL) {
        printf("Loi mo file!\n");
        *soLuong = 0; // Reset soLuong if file not found
        return;
    }

    *soLuong = fread(danhSach, sizeof(DanhMuc), MAX_DANH_MUC, fp);
    fclose(fp);
}
void timDanhMuc(DanhMuc *danhSach, int soLuong) {
    char ten[50];
    printf("Enter the name of the category to look for: ");
    scanf("%s", ten);

    int i;
    for (i = 0; i < soLuong; i++) {
        if (strcmp(danhSach[i].tenDanhMuc, ten) == 0) {
            printf("Find the catalog:\n");
            printf("Ma: %d\tTen: %s\tGia: %.2f\n", danhSach[i].maDanhMuc, danhSach[i].tenDanhMuc, danhSach[i].giaTien);
            return;
        }
    }

    printf("No catalog found!\n");
}



void suaDanhMuc(DanhMuc *danhSach, int soLuong) {
    int idCanSua, i;
    printf("Enter the category ID you want to edit: ");
    scanf("%d", &idCanSua);

    // Tim danh sach danh muc can sua  
    for (i = 0; i < soLuong; i++) {
        if (danhSach[i].maDanhMuc == idCanSua) {
            break;
        }
    }

    // Neu khong tim thay danh muc
    if (i == soLuong) {
        printf("Catalog with ID not found %d!\n", idCanSua);
        return;
    }

    // Hien thi thong tin hien tai cua danh muc
    printf("Current information of the catalog:\n");
    printf("Ma: %d\tTen: %s\n", danhSach[i].maDanhMuc, danhSach[i].tenDanhMuc);

     //Nhap thong tin moi
    printf("Enter a new name for the catalog: ");
    scanf(" %s", danhSach[i].tenDanhMuc);


    printf("Editing a successful category!\n");
}

// Helper function to find category index by ID
int findCategoryIndexById(DanhMuc *danhSach, int soLuong, int id) {
    for (int i = 0; i < soLuong; i++) {
        if (danhSach[i].maDanhMuc == id) {
            return i;
        }
    }
    return -1; // Not found
}

void xoaDanhMuc(DanhMuc danhSach[], int *soLuong, int maXoa) {
    int i;
    for (i = 0; i < *soLuong; i++) {
        if (danhSach[i].maDanhMuc == maXoa) {
            // Tim thay danh muc can xoa hoi xac nhan
            char xacNhan;
            printf("Do you want to delete this category? (y/n): ", maXoa);
            scanf(" %c", &xacNhan); 

            if (xacNhan == 'y' || xacNhan == 'Y') {
                // Di chuyen cï¿½c phan tu phï¿½a sau lï¿½n
                for (int j = i; j < *soLuong - 1; j++) {
                    danhSach[j] = danhSach[j + 1];
                }
                (*soLuong)--;
                printf("Catalog deletion successful!\n");
                return;
            } else {
                printf("Undelete a catalogue.\n");
                return;
            }
        }
    }

    // Neu khï¿½ng tim thay danh muc
    printf("No catalog found %d.\n", maXoa);
}


int compareByMaTangDan(const void *a, const void *b) {
    DanhMuc *da = (DanhMuc *)a;
    DanhMuc *db = (DanhMuc *)b;
    return da->maDanhMuc - db->maDanhMuc;
}

// Hï¿½m so sï¿½nh de sap xep theo ma danh muc giam dan
int compareByMaGiamDan(const void *a, const void *b) {
    DanhMuc *da = (DanhMuc *)a;
    DanhMuc *db = (DanhMuc *)b;
    return db->maDanhMuc - da->maDanhMuc;
}

// Hï¿½m so sï¿½nh de sap xep theo tï¿½n danh muc tï¿½ng dan
int compareByTenTangDan(const void *a, const void *b) {
    DanhMuc *da = (DanhMuc *)a;
    DanhMuc *db = (DanhMuc *)b;
    return strcmp(da->tenDanhMuc, db->tenDanhMuc);
}

// Hï¿½m so sï¿½nh de sap xep theo tï¿½n danh muc giam dan
int compareByTenGiamDan(const void *a, const void *b) {
    DanhMuc *da = (DanhMuc *)a;
    DanhMuc *db = (DanhMuc *)b;
    return strcmp(db->tenDanhMuc, da->tenDanhMuc);
}
int compareByGiaTangDan(const void *a, const void *b) {
    DanhMuc *da = (DanhMuc *)a;
    DanhMuc *db = (DanhMuc *)b;
    return da->giaTien - db->giaTien;
}

// Hàm so sánh ð? s?p x?p theo giá gi?m d?n
int compareByGiaGiamDan(const void *a, const void *b) {
    DanhMuc *da = (DanhMuc *)a;
    DanhMuc *db = (DanhMuc *)b;
    return db->giaTien - da->giaTien;
}
void sapXepDanhMuc(DanhMuc *danhSach, int soLuong) {
    int luaChon;
//	int  compareByMaTangDan, compareByMaGiamDan, compareByTenTangDan, compareByTenGiamDan ;
	int compareByMaTangDan(const void *a, const void *b);
	int compareByMaGiamDan(const void *a, const void *b);
	int compareByTenTangDan(const void *a, const void *b);
	int compareByTenGiamDan(const void *a, const void *b);
	int compareByGiaTangDan(const void *a, const void *b);
	int compareByGiaGiamDan(const void *a, const void *b);
    do {
        printf("\nChon cach sap xep:\n");
        printf("\t1. Sort by incremental category code\n");//Sap xep theo ma danh muc tang dan
        printf("\t2. Sort by decreasing category code\n");//Sap xep theo ma danh muc giam dan
        printf("\t3. Sort by incremental category name\n");//Sap xep theo ten danh muc tang dan
        printf("\t4. Sort by decreasing category name\n");//Sap xep theo ten danh muc giam dan
        printf("\t5. Sort by increasing price\n"); // S?p x?p theo giá tãng d?n
        printf("\t6. Sort by decreasing price\n"); // S?p x?p theo giá gi?m d?n
        printf("\t0. Return to main menu\n");//Quay lai menu chinh
        printf("Your Choices: ");//Lua chon cua ban
        scanf("%d", &luaChon);

        switch (luaChon) {
            case 1:
                qsort(danhSach, soLuong, sizeof(DanhMuc), compareByMaTangDan);
                break;
            case 2:
                qsort(danhSach, soLuong, sizeof(DanhMuc), compareByMaGiamDan);
                break;
            case 3:
                qsort(danhSach, soLuong, sizeof(DanhMuc), compareByTenTangDan);
                break;
            case 4:
                qsort(danhSach, soLuong, sizeof(DanhMuc), compareByTenGiamDan);
                break;
            case 5:
                qsort(danhSach, soLuong, sizeof(DanhMuc), compareByGiaTangDan);
                break;
            case 6:
                qsort(danhSach, soLuong, sizeof(DanhMuc), compareByGiaGiamDan);
                break;
            case 0:
                return; // Quay lai menu chinh
            default:
                printf("Lua chon khong hop le!\n");
        }

        // Hien thi danh sach sau khi sap xap
        if (luaChon >= 1 && luaChon <= 6) {
            hienThiDanhSach(danhSach, soLuong);
        }
    } while (luaChon != 0);
}


void timKiemDanhMuc(DanhMuc *danhSach, int soLuong) {
    char tenCanTim[MAX_TEN];
    int i, found = 0;
	getchar();
    printf("Nhap ten danh muc can tim: ");
    fgets(tenCanTim, MAX_TEN, stdin);
    tenCanTim[strcspn(tenCanTim, "\n")] = '\0';

    printf("\nKet qua tim kiem:\n");
    printf("+-----------------+-----------------------+\n");
    printf("|   Catalog id    |     Catalog name      |\n");
    printf("+-----------------+-----------------------+\n");

    for (i = 0; i < soLuong; i++) {
        if (strstr(danhSach[i].tenDanhMuc, tenCanTim) != NULL) {
            printf("| %15d | %-20s |\n", danhSach[i].maDanhMuc, danhSach[i].tenDanhMuc);
            found = 1;
        }
    }

    printf("+-----------------+-----------------------+\n");

    if (!found) {
        printf("Khong tim thay danh muc nao!\n");
    }
}

void clear(){
	#ifdef _WIN32 //ham xoa va chi hien thi giao dien sau no
	system("cls");
	#endif
}
