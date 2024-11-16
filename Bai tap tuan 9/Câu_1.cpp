//Nguyen Kim Linh
//20233495
//Bai  1
#include <iostream>
#include <fstream>
using namespace std;

struct Time { //Time ở đây là khi chèn file vào thư mục
    int hour, minute, second;
};

struct File {
    int fileSize;
    Time time;
};

struct Node {
    File info;
    Node* next;
};

Node* create_node(File info) {
    Node* p = new Node;
    p->info = info;
    p->next = NULL;
    return p;
}

struct List {
    Node* head;
    Node* tail;
    int count;
};

List* create_list() {
    List* L = new List;
    L->head = L->tail = NULL;
    L->count = 0;
    return L;
}

bool is_list_empty(List* L) {
    return L->head == 0;
}

void add_first(List* L, File info) {
    Node* p = create_node(info);
    if (is_list_empty(L)) 
        L->tail = p;
    else p->next = L->head;
    L->head = p;
    L->count++;
}

void remove_first(List* L) {
    Node* p = L->head;
    L->head = p->next;
    delete p;
    if (is_list_empty(L))
        L->tail = NULL;
    L->count--;
}

int size_folder(const List* L) {
    int sum = 0;
    Node* p = L->head;
    while (p) {
        sum += p->info.fileSize;
        p = p->next;
    }
    return sum;
}

List* copy_list(const List* L) {
    List* tmp = create_list();
    Node* p = L->head;
    while (p->next) {
        add_first(tmp, p->info);
        p = p->next;
    }
    return tmp;
}

void swap(Node* x, Node* y) {
    File tmp = x->info;
    x->info = y->info;
    y->info = tmp;
}

List* sort_list(List* L) {
    List* gb = copy_list(L);
    bool swapped = true;
    while (swapped) {
        swapped = false;
        Node* p = gb->head;
        while (p->next) {
            if (p->info.fileSize > p->next->info.fileSize) {
                swap(p, p->next);
                swapped = true;
            }
            p = p->next;
        }
    }
    return gb;
}

void copy_to_USB(List* L) {
    const int size_usb = 32;
    int num = size_folder(L);
    Node* p = L->head;
    while (num > size_usb) {
        num -= p->info.fileSize;
        p = p->next;
        remove_first(L);
    }
}

void prinf(const List* L) {
    Node* p = L->head;
    cout << "-----------------------------------------------------------------" << endl;
    while (p) {
        cout << p->info.fileSize << "GB : " << p->info.time.hour << ':' << p->info.time.minute << ':' << p->info.time.second << endl;
        p = p->next;
    }
}

int main() {
    List* folder = create_list();
    add_first(folder, { 12, { 11, 10, 30 } });
    add_first(folder, { 10, { 12, 25, 30 } });
    add_first(folder, { 20, { 13, 30, 25 } });
    add_first(folder, { 5, { 14, 12, 45 } });
    cout << "Folder | Tong kick thuoc: "<< size_folder(folder) << "GB | Tong so file: "<< folder->count << endl;
    prinf(folder);
    List* gb = sort_list(folder);
    copy_to_USB(gb);
    cout << "So file co the copy qua USB la: " << gb->count << endl;
    prinf(gb);
    cout << endl;
}
