#include "datatypes.h"
void hienThiMenu();

void hienThiDanhSach(DanhMuc *danhSach, int soLuong);

void themDanhMuc(DanhMuc *danhSach, int *soLuong);

void suaDanhMuc(DanhMuc *danhSach, int soLuong);

void sapXepDanhMuc(DanhMuc *danhSach, int soLuong);

void clear();

void xoaDanhMuc(DanhMuc danhSach[], int *soLuong, int maXoa);

int compareByMaTangDan(const void *a, const void *b);

int compareByMaGiamDan(const void *a, const void *b);

int compareByTenTangDan(const void *a, const void *b);

int compareByTenGiamDan(const void *a, const void *b);

int nhapDanhMuc(DanhMuc *dm, DanhMuc *danhSach, int soLuong);

void timKiemDanhMuc(DanhMuc *danhSach, int soLuong);

void luuDanhSachVaoFileDAT(DanhMuc *danhSach, int soLuong);

void docDanhSachTuFileDAT(DanhMuc *danhSach, int *soLuong);


