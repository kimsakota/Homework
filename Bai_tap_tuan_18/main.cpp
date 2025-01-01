//Nguyen Kim Linh
//20233495
//               ..╱ | 、 ♡
//                (˚ˎ 。7      ⋆
//                | 、˜〵
//                じしˍ, )ノ

#include <iostream>
#include<vector>
#include<string>
using namespace std;

struct MaTranKe {
    vector<vector<int>> maTran;
    int soDinh;

    MaTranKe(int dinh) : soDinh(dinh) {
        maTran.resize(dinh, vector<int>(dinh, 0));
    }

    void themCanh(int u, int v) {
        maTran[u][v] = 1;
        maTran[v][u] = 1;
    }

    void hienThi() {
        cout << "Ma tra ke:\n";
        for (const auto& hang : maTran) {
            for (int giaTri : hang) 
                cout << giaTri << " ";
            cout << endl;
        }
    }

    void duyetBFS(int batDau) {
        vector<bool> daTham(soDinh, false);
        vector<int> hangDoi;

        daTham[batDau] = true;
        hangDoi.push_back(batDau);

        cout << "BFS: ";
        int dau = 0;
        while (dau < hangDoi.size()) {
            int dinh = hangDoi[dau++];
            cout << dinh << " ";

            for (int i = 0; i < soDinh; i++) 
                if (maTran[dinh][i] == 1 && !daTham[i]) {
                    daTham[i] = true;
                    hangDoi.push_back(i);
                }
        }
        cout << endl;
    }

    void duyetDFS(int batDau) {
        vector<bool> daTham(soDinh, false);
        vector<int> nganXep;

        nganXep.push_back(batDau);
        cout << "DFS: ";
        while (!nganXep.empty()) {
            int dinh = nganXep.back();
            nganXep.pop_back();

            if (!daTham[dinh]) {
                daTham[dinh] = true;
                cout << dinh << " ";
            }

            for (int i = soDinh - 1; i >= 0; i--) 
                if (maTran[dinh][i] == 1 && !daTham[i]) 
                    nganXep.push_back(i);
        }
        cout << endl;
    }
};


struct DanhSachKe {
    vector<vector<int>> danhSach;
    int soDinh;

    DanhSachKe(int dinh) : soDinh(dinh) {
        danhSach.resize(dinh);
    }

    void themCanh(int u, int v) {
        danhSach[u].push_back(v);
        danhSach[v].push_back(u); 
    }

    void hienThi() {
        cout << "Danh sách kề:\n";
        for (int i = 0; i < soDinh; i++) {
            cout << i << ": ";
            for (int langGieng : danhSach[i]) 
                cout << langGieng << " ";
            cout << endl;
        }
    }

    void duyetBFS(int batDau) {
        vector<bool> daTham(soDinh, false);
        vector<int> hangDoi;

        daTham[batDau] = true;
        hangDoi.push_back(batDau);

        cout << "BFS: ";
        int dau = 0;
        while (dau < hangDoi.size()) {
            int dinh = hangDoi[dau++];
            cout << dinh << " ";

            for (int langGieng : danhSach[dinh]) 
                if (!daTham[langGieng]) {
                    daTham[langGieng] = true;
                    hangDoi.push_back(langGieng);
                }
        }
        cout << endl;
    }

    void duyetDFS(int batDau) {
        vector<bool> daTham(soDinh, false);
        vector<int> nganXep;

        nganXep.push_back(batDau);
        cout << "DFS: ";
        while (!nganXep.empty()) {
            int dinh = nganXep.back();
            nganXep.pop_back();

            if (!daTham[dinh]) {
                daTham[dinh] = true;
                cout << dinh << " ";
            }

            for (auto it = danhSach[dinh].rbegin(); it != danhSach[dinh].rend(); ++it) 
                if (!daTham[*it]) 
                    nganXep.push_back(*it);
        }
        cout << endl;
    }
};

int main() {
    int soDinh, soCanh;
    cout << "Nhap so dinh: ";
    cin >> soDinh;
    cout << "Nhap so canh: ";
    cin >> soCanh;

    MaTranKe doThiMaTran(soDinh);
    cout << "Nhap cac canh (u v):\n";
    for (int i = 0; i < soCanh; i++) {
        int u, v;
        cin >> u >> v;
        doThiMaTran.themCanh(u, v);
    }

    doThiMaTran.hienThi();
    doThiMaTran.duyetBFS(0);
    doThiMaTran.duyetDFS(0);

    DanhSachKe doThiDanhSach(soDinh);
    cout << "Nhap lai cac canh (u v):\n";
    for (int i = 0; i < soCanh; i++) {
        int u, v;
        cin >> u >> v;
        doThiDanhSach.themCanh(u, v);
    }

    doThiDanhSach.hienThi();
    doThiDanhSach.duyetBFS(0);
    doThiDanhSach.duyetDFS(0);

    return 0;
}
