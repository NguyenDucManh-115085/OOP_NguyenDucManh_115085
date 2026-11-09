#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cctype>

using namespace std;

class Xe {
private:
    int maXe;
    string loaiXe;
    int gioVao;
    int gioGui; 
    double phiGui;
    bool trangThaiGui;

public:
    Xe(): maXe(0), loaiXe(""), gioVao(0), gioGui(0), phiGui(0.0), trangThaiGui(false) {}
    Xe(int ID, string type, int hour, int duration): maXe(ID), loaiXe(type), gioVao(hour), gioGui(duration), phiGui(0.0), trangThaiGui(true) {
        this->loaiXe = chuanHoaXe();
        tinhPhiGuiXe();    
    }

    int nhanMaXe() const { return maXe; }
    string nhanLoaiXe() const { return loaiXe; }
    int nhanGioGui() const { return gioVao; }
    int nhanSoGioGui() const { return gioGui; }
    bool nhanDangGui() const { return trangThaiGui; }    
    double nhanTienGui() const { return phiGui; }    

    void ganMaXe(int ID) { maXe = ID; }    
    void ganLoaiXe(string type) {
        loaiXe = type; 
        loaiXe = chuanHoaXe();
    }    
    void ganGioGui(int hour) { gioVao = hour; }    
    void ganThoiGianGui(int time) { gioGui = time; }    
    void ganTienGui(double fee) { phiGui = fee; } 
    void ganDangGui(bool parked) { trangThaiGui = parked; }

    string chuanHoaXe() {
        string temp = loaiXe;
        transform(temp.begin(), temp.end(), temp.begin(), ::tolower);        
        if (temp == "oto") {
            return "Oto";
        }
        if (temp == "xemay" || temp == "xe may") {
            return "xe may";
        } 
        if (temp == "xedap" || temp == "xe dap") { 
            return "xe dap";
        }      
        return "khong xac dinh";
    }

    static bool laLoaiXeHopLe(const string& type) {        
        string temp = type;        
        transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        return (temp == "oto" || temp == "xemay" || temp == "xe may" || temp == "xedap" || temp == "xe dap");
    }

    double tinhPhiGuiXe() {
        if (!trangThaiGui) {            
            phiGui = 0.0;            
            return 0.0;        
        }
        
        double tiLeTien = 0.0;
        if (loaiXe == "Oto") {
            tiLeTien = 6.0 * 25000;
        }
        else if (loaiXe == "xe may") {
            tiLeTien = 4.0 * 25000;
        }
        else if (loaiXe == "xe dap") {
            tiLeTien = 2.0 * 25000;
        }
        
        bool gioCaoDiem = (gioVao >= 6 && gioVao <= 9) || (gioVao >= 15 && gioVao <= 18);
        double tiLeTien2GioDau = gioCaoDiem ? tiLeTien * 1.30 : tiLeTien * 0.95;
        double tiLeTienSau2GioDau = tiLeTien * 0.90;

        if (gioGui <= 2) {            
            phiGui = gioGui * tiLeTien2GioDau;
        }
        else {            
            phiGui = (2 * tiLeTien2GioDau) + ((gioGui - 2) * tiLeTienSau2GioDau);
        }
        return phiGui;    
    }

    void hienThiThongTinXe() const {
        if (!trangThaiGui) {
            return;
        }

        cout << "Ma xe: " << maXe << endl;
        cout << "Loai xe: " << loaiXe << endl;
        cout << "Gio vao: " << gioVao << endl;
        cout << "Thoi gian do: " << gioGui << endl;
        cout << fixed << setprecision(2) << "Phi do xe: " << phiGui << " VND" << endl; 
        cout << "Dang do xe: " << (trangThaiGui ? "Co" : "Khong") << endl;
    }
};

class baiDoXe {
private:
    int maBai;    
    char kichThuoc;    
    Xe xe1, xe2, xe3;
    bool co1, co2, co3;

public:
    baiDoXe(): maBai(0), kichThuoc(' '), co1(false), co2(false), co3(false) {}
    baiDoXe(int maBai, char kichThuoc): maBai(maBai), kichThuoc(toupper(kichThuoc)), co1(false), co2(false), co3(false) {}

    int ganMaBai() const { 
        return maBai; 
    }
    char ganKichThuoc() const { 
        return kichThuoc; 
    }
    int ganLuongXe() const {        
        if (kichThuoc == 'S') { return 1; }        
        if (kichThuoc == 'M') { return 2; }        
        if (kichThuoc == 'L') { return 3; }        
        return 0;    
    } 
    int ganSoLuongXe() const {        
        int cnt = 0;        
        if (co1) { cnt++; }        
        if (co2) { cnt++; }        
        if (co3) { cnt++; }        
        return cnt;    
    }

    bool themXe(const Xe& xe) {
        int cap = (kichThuoc == 'S') ? 1 : (kichThuoc == 'M') ? 2 : 3;
        if (cap >= 1 && !co1) { xe1 = xe; co1 = true; return true; }
        if (cap >= 2 && !co2) { xe2 = xe; co2 = true; return true; }
        if (cap >= 3 && !co3) { xe3 = xe; co3 = true; return true; }
        return false;
    }

    bool timXe(int maXeInput) const {
        if (co1 && xe1.nhanMaXe() == maXeInput) return true;
        if (co2 && xe2.nhanMaXe() == maXeInput) return true;
        if (co3 && xe3.nhanMaXe() == maXeInput) return true;
        return false;
    }

    bool xoaXe(int maXeInput) {
        if (co1 && xe1.nhanMaXe() == maXeInput) {
            if (co2) {
                xe1 = xe2;
                if (co3) { xe2 = xe3; co3 = false; }
                else co2 = false;
            } else co1 = false;
            return true;
        }
        if (co2 && xe2.nhanMaXe() == maXeInput) {
            if (co3) { xe2 = xe3; co3 = false; }
            else co2 = false;
            return true;
        }
        if (co3 && xe3.nhanMaXe() == maXeInput) {
            co3 = false;
            return true;
        }
        return false;
    }

    void hienThiThongTinBaiDo() const {
        int cap = (kichThuoc == 'S') ? 1 : (kichThuoc == 'M') ? 2 : 3;
        int so_xe = co1 + co2 + co3;
        cout << "Bai " << maBai << " [" << kichThuoc << "] "
             << so_xe << "/" << cap << " xe\n";
        if (co1) xe1.hienThiThongTinXe();
        if (co2) xe2.hienThiThongTinXe();
        if (co3) xe3.hienThiThongTinXe();
    }

    void lietKeTheoLoai(const string& type) const {
        if (co1 && xe1.nhanLoaiXe() == type) {
            cout << " [Bai do xe " << maBai << "]\n";            
            xe1.hienThiThongTinXe();        
        }
        if (co2 && xe2.nhanLoaiXe() == type) {
            cout << " [Bai do xe " << maBai << "]\n";            
            xe2.hienThiThongTinXe();        
        }
        if (co3 && xe3.nhanLoaiXe() == type) {
            cout << " [Bai do xe " << maBai << "]\n";            
            xe3.hienThiThongTinXe();        
        }
    }

    void ganPhiDoTheoLoai(const string& type, double& totalFee, int& count) const {
        if (co1 && xe1.nhanLoaiXe() == type) {
            totalFee += xe1.nhanTienGui();            
            count++;        
        }
        if (co2 && xe2.nhanLoaiXe() == type) {
            totalFee += xe2.nhanTienGui();            
            count++;        
        }
        if (co3 && xe3.nhanLoaiXe() == type) {
            totalFee += xe3.nhanTienGui();            
            count++;        
        }
    }

    bool co_loai(string loai, int& dem, double& tong) const {
        dem = 0; tong = 0;
        if (co1 && xe1.nhanLoaiXe() == loai) { ++dem; tong += xe1.nhanTienGui(); }
        if (co2 && xe2.nhanLoaiXe() == loai) { ++dem; tong += xe2.nhanTienGui(); }
        if (co3 && xe3.nhanLoaiXe() == loai) { ++dem; tong += xe3.nhanTienGui(); }
        return dem > 0;
    }
};

class UI {
private:    
    baiDoXe bai1, bai2, bai3;
    bool coBai1, coBai2, coBai3;
    
    bool xeCoTrongBai(int carID) const {
        if (coBai1 && bai1.timXe(carID)) { return true; }
        if (coBai2 && bai2.timXe(carID)) { return true; }
        if (coBai3 && bai3.timXe(carID)) { return true; }
        return false;
    }

public:
    UI(): coBai1(false), coBai2(false), coBai3(false) {}

    void taoBaiDoXe() {
        if (coBai1 && coBai2 && coBai3) {
            cout << "Toi da 3 bai xe co the tao!\n";            
            return;        
        }

        int id;        
        char size;

        cout << "Nhap ma bai do xe: ";
        cin >> id;
        if ((coBai1 && bai1.ganMaBai() == id) || (coBai2 && bai2.ganMaBai() == id) || (coBai3 && bai3.ganMaBai() == id)) {
             cout << "Ma bai do xe da ton tai!\n";
             return;
        }

        cout << "Nhap kich thuoc bai do xe (S/M/L): ";
        cin >> size;
        size = toupper(size);
        if (size != 'S' && size != 'M' && size != 'L') {
            cout << "Kich thuoc khong hop le!\n";
            return;
        }
        
        if (!coBai1) {
            bai1 = baiDoXe(id, size);            
            coBai1 = true;
        }
        else if (!coBai2) {
            bai2 = baiDoXe(id, size);            
            coBai2 = true;
        }
        else if (!coBai3) {
            bai3 = baiDoXe(id, size);            
            coBai3 = true;
        }

        cout << "Tao bai do xe thanh cong!\n";
    }

    void themXeVaoBai() {
        if (!coBai1 && !coBai2 && !coBai3) {
            cout << "Khong co bai do xe trong he thong!\n";
            return;
        }

        int id, hour, duration;
        string type;

        cout << "Nhap ma xe: ";
        cin >> id;
        if (xeCoTrongBai(id)) {
            cout << "Ma xe da ton tai trong he thong!\n";
            return;
        }

        cout << "Nhap loai xe (Oto / Xe may / Xe dap): ";
        cin.ignore();
        getline(cin, type);
        if (!Xe::laLoaiXeHopLe(type)) {
            cout << "Loai xe khong hop le!\n";
            return;
        }

        cout << "Nhap gio vao (0 - 23): ";
        cin >> hour;
        if (hour < 0 || hour > 23) {
            cout << "Gio vao phai nam trong khoang 0 - 23!\n";
            return;
        }

        cout << "Nhap thoi gian gui (1 - 23): ";
        cin >> duration;
        if (duration < 1 || duration > 23) { 
            cout << "Thoi gian gui phai nam trong khoang 1 - 23!\n";
            return;
        }

        Xe xe(id, type, hour, duration);
        if (coBai1 && bai1.themXe(xe)) {
            cout << "Da them xe vao bai " << bai1.ganMaBai() << endl;
            return;
        }
        if (coBai2 && bai2.themXe(xe)) {
            cout << "Da them xe vao bai " << bai2.ganMaBai() << endl;
            return;
        }
        if (coBai3 && bai3.themXe(xe)) {
            cout << "Da them xe vao bai " << bai3.ganMaBai() << endl;
            return;
        }
        else {
            cout << "Tat ca cac bai do xe da day!\n";    
        }
    }

    void xoaBaiDoXe() {
        int id;
        cout << "Nhap ma bai do xe can xoa: ";
        cin >> id;

        if (coBai1 && bai1.ganMaBai() == id) {
            coBai1 = false;           
            bai1 = baiDoXe();            
            cout << "Da xoa bai do xe " << id << endl;           
            return;        
        }
        if (coBai2 && bai2.ganMaBai() == id) {
            coBai2 = false;           
            bai2 = baiDoXe();            
            cout << "Da xoa bai do xe " << id << endl;           
            return;        
        }
        if (coBai3 && bai3.ganMaBai() == id) {
            coBai3 = false;           
            bai3 = baiDoXe();            
            cout << "Da xoa bai do xe " << id << endl;           
            return;        
        }
        else {
            cout << "Ma bai do xe khong ton tai!\n";
        }
    }

    void xoaXeKhoiBai() {
        int id;
        cout << "Nhap ma xe can lay ra: "; 
        cin >> id;

        if (coBai1 && bai1.xoaXe(id)) {
            cout << "Da lay xe ra khoi bai do xe " << bai1.ganMaBai() << endl;
            return;        
        }
        if (coBai2 && bai2.xoaXe(id)) {
            cout << "Da lay xe ra khoi bai do xe " << bai2.ganMaBai() << endl;
            return;        
        }
        if (coBai3 && bai3.xoaXe(id)) {
            cout << "Da lay xe ra khoi bai do xe " << bai3.ganMaBai() << endl;
            return;        
        }
        else {
            cout << "Ma xe khong ton tai!\n";
        }
    }

    void hienThiBaiDoXe() {
        if (!coBai1 && !coBai2 && !coBai3) {
            cout << "He thong khong co bai do xe!\n";
            return;        
        }

        cout << "\n=== DANH SACH BAI DO XE ===\n";
        if (coBai1) { bai1.hienThiThongTinBaiDo(); }
        if (coBai2) { bai2.hienThiThongTinBaiDo(); }
        if (coBai3) { bai3.hienThiThongTinBaiDo(); }
    }

    void hienThiXeTheoBai() {
        int id;
        cout << "Nhap ma bai do xe can xem: ";
        cin >> id;

        if (coBai1 && bai1.ganMaBai() == id) { 
            bai1.hienThiThongTinBaiDo();
            return;        
        }
        if (coBai2 && bai2.ganMaBai() == id) { 
            bai2.hienThiThongTinBaiDo();
            return;        
        }
        if (coBai3 && bai3.ganMaBai() == id) { 
            bai3.hienThiThongTinBaiDo();
            return;        
        }
        else {
            cout << "Ma bai do xe khong ton tai!\n";
        }
    }

    void lietKeXeTheoLoai() {
        string type;
        cout << "Nhap loai xe (Oto / Xe may / Xe dap): ";
        cin.ignore();
        getline(cin, type);

        if (!Xe::laLoaiXeHopLe(type)) {
            cout << "Loai xe khong hop le!\n";
            return;
        }

        Xe temp(0, type, 0, 0);
        string normalizedType = temp.nhanLoaiXe();
        cout << "\n=== DANH SACH XE (LOAI XE : " << normalizedType << ") ===\n";

        if (coBai1) { bai1.lietKeTheoLoai(normalizedType); }
        if (coBai2) { bai2.lietKeTheoLoai(normalizedType); }
        if (coBai3) { bai3.lietKeTheoLoai(normalizedType); }
    }

    void hienThiPhiDoTrungBinh() { 
        string types[3] = {"Oto", "xe may", "xe dap"};
        cout << "\n=== BAO CAO PHI DO XE TRUNG BINH ===\n";
        for (int i = 0; i < 3; ++i) {
            double totalFee = 0.0;
            int count = 0;

            if (coBai1) { bai1.ganPhiDoTheoLoai(types[i], totalFee, count); }
            if (coBai2) { bai2.ganPhiDoTheoLoai(types[i], totalFee, count); }
            if (coBai3) { bai3.ganPhiDoTheoLoai(types[i], totalFee, count); }

            cout << "Loai xe: " << types[i] << " | So luong: " << count;
            if (count > 0) {
                cout << " | Phi do trung binh: " << fixed << setprecision(2) << (totalFee / count) << " VND" << endl;
            }
            else {
                cout << " | Phi do trung binh: 0.00 VND" << endl;
            }
        }
    }

    void runMenu() {
        int choice = 0;
        do {
            cout << "\n================ HE THONG QUAN LY BAI DO XE ================\n";
            cout << "1. Tao bai do xe moi\n";            
            cout << "2. Them xe vao bai\n";            
            cout << "3. Xoa bai do xe\n";            
            cout << "4. Xoa xe khoi bai\n";            
            cout << "5. Hien thi cac bai do xe\n";            
            cout << "6. Hien thi xe trong bai cu the\n";
            cout << "7. Liet ke danh sach phuong tien theo tung loai xe\n";            
            cout << "8. Hien thi phi do xe trung binh cua cac loai xe\n";
            cout << "9. Thoat\n";            
            cout << "Nhap so (1-9): ";
            cin >> choice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Chi nhap so tu 1 den 9!\n";
                continue;
            }

            switch (choice) {
                case 1: taoBaiDoXe();
                    break;
                case 2: themXeVaoBai();
                    break;
                case 3: xoaBaiDoXe();
                    break;
                case 4: xoaXeKhoiBai();
                    break;
                case 5: hienThiBaiDoXe();
                    break;
                case 6: hienThiXeTheoBai();
                    break;
                case 7: lietKeXeTheoLoai();
                    break;
                case 8: hienThiPhiDoTrungBinh();
                    break;
                case 9: 
                    cout << "Da thoat khoi he thong\n";
                    break;
                default: 
                    cout << "Lua chon khong hop le! Hay thu lai!\n";
                    break;
            }
        } while (choice != 9);
    }
};

int main() {
    UI ui;
    ui.runMenu();
    return 0;
}
