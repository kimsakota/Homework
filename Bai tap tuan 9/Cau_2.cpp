//Nguyen Kim Linh
//20233495
//Bai 2
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct phrase {
	string word;
	phrase* next;
};

phrase* make_phrase(string word) {
	phrase* p = new phrase;
	p->word = word;
	p->next = NULL;
	return p;
}

struct list {
	phrase* head;
	phrase* tail;
	int count;
};

list* make_list() {
	list* L = new list;
	L->head = L->tail = NULL;
	L->count = 0;
	return L;
}

bool is_list_empty(list* L) {
	return L->head == 0;
}

void add_last(list* L, string info) {
	phrase* p = make_phrase(info);
	if (is_list_empty(L))
		L->head = p;
	else L->tail->next = p;
	L->tail = p;
	L->count++;
}

void create_list(list* L, char* text) {
	const char space = ' ';
	string s;
	char* tmp = new char[10];
	for (int i = 0; char c = text[i]; i++) {
		if (text[i] == space) {
			add_last(L, s);
			s.clear();
		}
		else s += text[i];
	}
}

void exam_2(list* L) {
	phrase* p = L->head;
	int num = 0;
	string s;
	for (p; p != NULL; p = p->next) {
		int count = 0; 
		string temp = p->word;
		for (phrase* q = p->next; q != NULL; q = q->next) {
			if (temp == q->word)
				count++;
		}
		if (count > num) {
			num = count;
			s = temp;
		}
	}
	cout << "Tu ' " << s << " ' xuat hien nhieu nhat\n";
	cout << "So luong: " << num << " lan\n";
}

void exam_3(list* L) {
	phrase* p = L->head;
	while (p != NULL && p->next != NULL) {
		if (p->word == p->next->word) {
			phrase* temp = p->next;
			p->next = temp->next;
			delete temp;
			L->count--;
		}
		p = p->next;
	}
}

void prinf(const list* L) {
	phrase* p = L->head;
	while (p) {
		cout << p->word << endl;
		p = p->next;
	}
	cout << "Co " << L->count << " tu" << endl;
}

int main() {
	char text[] = "the gioi lao dong giai phong con con nguoi khoi the the gioi dong vat";
	list* phrase = make_list();
	create_list(phrase, text);
	exam_2(phrase); //Ý 2
	cout << "------------------------------------------------\n";
	//exam_3(phrase); //Ý 3
	// Ý 4 đã có sẵn trong hàm prinf;
	prinf(phrase);

}
