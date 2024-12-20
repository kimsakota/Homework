//Nguyen Kim Linh
//20233495
//               ..╱ | 、 ♡
//               (˚ˎ 。7      ⋆
//                | 、˜〵
//                じしˍ, )ノ
               
#include <iostream> 
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

#define TVALUE Product
#define MAX_SIZE 100

// Tạo dữ liệu sản phẩm của cửa hàng 
struct Product {
    int ID = 0;
    string name;
    int price = 0;
    int quanitity = 0;
};

vector<Product> products= {
        {1, "Apple", 15000},
        {2, "Banana", 10000},
        {3, "Milk", 25000},
        {4, "Bread", 20000},
        {5, "Cheese", 50000},
        {6, "Orange", 12000},
        {7, "Tomato", 8000},
        {8, "Potato", 7000},
        {9, "Egg", 3000},
        {10, "Chicken", 120000},
        {11, "Fish", 150000},
        {12, "Rice", 18000},
        {13, "Oil", 50000},
        {14, "Salt", 6000},
        {15, "Sugar", 10000},
        {16, "Coffee", 70000},
        {17, "Tea", 40000},
        {18, "Chocolate", 30000},
        {19, "Soap", 15000},
        {20, "Shampoo", 80000}
};
int size_products = products.size();
int doanhthu = 0;

Product find_price(int id, int quanitity) {
    int first = 0, last = size_products - 1;
    while (first <= last) {
        int mid = (first + last) / 2;
        if (products[mid].ID == id) {
            products[mid].quanitity += quanitity;
            return products[mid];
        }
        else if (products[mid].ID > id) 
            last = mid - 1;
        else
            first = mid + 1;
    }
    return { -1, "False", 0, 0 };
}

// Thanh toán giỏ hàng

struct Shopping_Cart {
    TVALUE data[MAX_SIZE];
    int front;
    int rear;
    int tongtien;
};
typedef Shopping_Cart SC;

SC* create_queue() {
    SC* q = new SC;
    q->front = q->rear = -1;
    q->tongtien = 0;
    return q;
}

int is_queue_empty(SC* q) {
    return q->front == -1;
}
int is_queue_full(SC* q) {
    return q->rear == MAX_SIZE - 1;
}
void enqueue(SC* q, TVALUE v) {
    if (is_queue_empty(q))
        q->front = 0;
    ++q->rear;
    q->data[q->rear] = v;
    q->tongtien += (v.price * v.quanitity);
}

// Thanh toán sản phẩm 
void Chon_SP(SC*& sc) {
    
    while (true) {
        int ID, quanitity;
        cout << "Nhap ID: "; cin >> ID;
        if (ID == 0) break;
        cout << "\Nhap so luong: "; cin >> quanitity;
        TVALUE v = find_price(ID, quanitity);
        if (v.ID == -1) {
            cout << "San pham khong ton tai!\n";
            continue;
        }
        doanhthu += (v.price * quanitity);
        v.quanitity = quanitity;
        enqueue(sc, v);
    }
}

void InHoaDon(SC* sc) {
    cout << left << setw(10) << "ID"
        << setw(20) << "Name"
        << setw(15) << "Price (VND)"
        << setw(15) << "Quantity" << endl;
    cout << string(60, '-') << endl;
    for (int i = 0; i <= sc->rear; i++) {
        cout << left << setw(10) << sc->data[i].ID
            << setw(20) << sc->data[i].name
            << setw(15) << sc->data[i].price
            << setw(15) << sc->data[i].quanitity << endl;
    }
    cout << string(34, ' ') << "Tong tien: " << sc->tongtien << endl;
    cout << string(60, '-') << endl;
    free(sc);
}

void ThongKe() {
    cout << left << setw(10) << "ID"
        << setw(20) << "Name"
        << setw(15) << "Price (VND)"
        << setw(15) << "Sold Quantity" << endl;
    cout << string(60, '-') << endl;
    for (int i = 0; i < size_products; i++) {
        cout << left << setw(10) << products[i].ID
            << setw(20) << products[i].name
            << setw(15) << products[i].price
            << setw(15) << products[i].quanitity << endl;
    }
    cout << string(34, ' ') << "Doanh thu: " << doanhthu << endl;
}

void ThemSPMoi() {
    TVALUE v;
    cout << "Nhap ten san pham: "; cin.ignore(); getline(cin, v.name);
    cout << "Nhap gia san pham: "; cin >> v.price;
    v.ID = (products.back().ID + 1);
    products.push_back(v);
    ++size_products;
}
int Menu() {
    int a;
    cout << "1. Chon hang(Nhap 0 de ket thuc)\n"
        << "2. Thanh Toan\n"
        << "3. Thong ke\n"
        << "4. Them san pham moi\n"
        << "5. Thoat\n>>";
    cin >> a;
    if (a < 1 || a > 5)
        return Menu();
    return a;
}

int main() {
    Shopping_Cart* sc = create_queue();
    while (1) {
        switch (Menu()) 
        {
        case 1: 
            sc = create_queue();
            Chon_SP(sc); continue;
        case 2: InHoaDon(sc); continue;
        case 3: ThongKe(); continue;
        case 4: ThemSPMoi(); continue;
        case 5: return 0;
        default:
            break;
        }
    }
}
