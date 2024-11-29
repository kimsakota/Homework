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
#define TVALUE2 vector<pair<int, int>>
#define MAX_SIZE 100

// Tạo dữ liệu sản phẩm của cửa hàng 
struct Product {
    int ID;
    string name;
    int price;
    int quanitity_sold = 0;
};

struct node {
    TVALUE value;
    node* left;
    node* right;
    int doanhthu;
};
typedef node root;

root* create(TVALUE value) {
    root* T = new root;
    T->left = T->right = NULL;
    T->value = value;
    T->doanhthu = 0;
    return T;
}

void insert(root* &T, TVALUE value) {
    if ((T) == NULL)
        (T) = create(value);
    else {
        if (T->value.ID > value.ID)
            insert((T)->left, value);
        else 
            insert(T->right, value);
    }
}

int find_price(root* T, pair<int, int> v) {
    if (T == NULL)
        cout << "San pham khong co du lieu\n";
    else {
        if (T->value.ID == v.first){
            T->value.quanitity_sold += v.second;
            return T->value.price;
        }   
        if (T->value.ID > v.first)
            find_price(T->left, v);
        else 
            find_price(T->right, v);
    }
}

void print_tree(root* root) {
    //Phần này em có dùng chat GPT :))
    if (!root) return;

    print_tree(root->left);
    static bool headerPrinted = false;
    if (!headerPrinted) {
        cout << left << setw(10) << "ID"
            << setw(20) << "Name"
            << setw(15) << "Price (VND)"
            << setw(15) << "Sold Quantity" << endl;
        cout << string(60, '-') << endl;
        headerPrinted = true;
    }
    cout << left << setw(10) << root->value.ID
        << setw(20) << root->value.name
        << setw(15) << root->value.price
        << setw(15) << root->value.quanitity_sold << endl;
    print_tree(root->right);
}

// Tạo hàng khách đang đợi thanh toán 
struct Queue {
    TVALUE2 data[MAX_SIZE];
    int front;
    int rear;
};

Queue* create_queue() {
    Queue* q = new Queue;
    q->front = q->rear = -1;
    return q;
}

int is_queue_empty(Queue* q);
int is_queue_full(Queue* q);
void enqueue(Queue* q, TVALUE2 value) {
    if (is_queue_empty(q))
        q->front = 0;
    ++q->rear;
    q->data[q->rear] = value;
}

TVALUE2 dequeue(Queue* q) {
    TVALUE2 v = q->data[q->front];
    ++q->front;
    return v;
}

int is_queue_empty(Queue* q) {
    return q->front == -1;
}
int is_queue_full(Queue* q) {
    return q->rear == MAX_SIZE - 1;
}

void check(root* T, Queue* &q, TVALUE2 info) {
    int tongtien = 0; 
    for (auto x : info) {
        tongtien += (x.second * find_price(T, x));
    }
}
void ThanhToan(root*T, Queue* &q) {
    int tongtien = 0;
    for (int i = 0; i <= q->rear; i++) {
        for (auto x : q->data[i]) 
            tongtien += (x.second * find_price(T, x));
        q->data[i].clear();
    }
    T->doanhthu = tongtien;
}
int main() {
    root* T = NULL;
    Product products[] = {
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
    int size_products = sizeof(products) / sizeof(products[0]);

    for (int i = 0; i < size_products; i++)
        insert(T, products[i]);
    
    vector<TVALUE2> v = {
        { {1, 2}, {3, 4}, {5, 6} },
        { {7, 8}, {9, 10} },
        { {11, 1}, {12, 2}, {13, 3} },
        { {14, 4}, {15, 5} },
        { { 16, 6 }, {17, 7}, {18, 8} },
        { { 19, 9 }, {20, 10}, {1, 3} },
        { { 2, 4 }, {3, 5}, {4, 6} },
        { { 5, 7 }, {6, 8}, {7, 9} },
        { { 8, 10 }, {9, 11}, {10, 12} },
        { { 11, 13 }, {12, 14}, {13, 15} }
    };
    Queue* Q = create_queue();
    for (auto x : v)
        enqueue(Q, x);
    ThanhToan(T, Q);
    print_tree(T);
    cout << "\nDoanh thu: " << T->doanhthu; 

}
