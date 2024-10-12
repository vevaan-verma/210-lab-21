// COMSC-210 | Lab 21 | Vevaan Verma
using namespace std;
#include <iostream>
#include <string>

/* CONSTANTS */
const int MIN_LS = 5, MAX_LS = 20;

class Goat {

private:
	int age;
	string name;
	string color;
	string* names = new string[15]{ "Billy", "Bob", "Joe", "Tom", "Jerry", "Tim", "Sam", "Max", "Alex", "John", "Mike", "Jake", "Jack", "Nick", "Rick" };
	string* colors = new string[15]{ "White", "Black", "Brown", "Gray", "Spotted", "Tan", "Cream", "Beige", "Red", "Blue", "Green", "Yellow", "Orange", "Purple", "Pink" };

public:
	Goat() {

		age = rand() % 20 + 1; // random age between 1 and 20
		name = names[rand() % 15]; // random name from names array
		color = colors[rand() % 15]; // random color from colors array

	}

	Goat(int age, string name, string color) {

		this->age = age; // this->age refers to the private member age
		this->name = name; // this->name refers to the private member name
		this->color = color; // this->color refers to the private member color

	}

	// print() prints the goat's name, age, and color
	// arguments: none
	// returns: void
	void print() { cout << "   " << name << " (" << color << ", " << age << ")" << endl; }

};

class DoublyLinkedList {

private:
	struct Node {

		Goat data;
		Node* prev;
		Node* next;

		Node(Goat goat, Node* p = nullptr, Node* n = nullptr) {

			data = goat;
			prev = p;
			next = n;

		}
	};
	Node* head;
	Node* tail;

public:
	// constructor
	DoublyLinkedList() { head = nullptr; tail = nullptr; }

	void push_back(Goat goat) {

		Node* newNode = new Node(goat);

		if (!tail) { // if there's no tail, the list is empty

			head = tail = newNode;

		} else {

			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;

		}
	}

	void push_front(Goat goat) {

		Node* newNode = new Node(goat);

		if (!head) { // if there's no head, the list is empty

			head = tail = newNode;

		} else {

			newNode->next = head;
			head->prev = newNode;
			head = newNode;

		}
	}

	void insert_after(Goat goat, int position) {

		if (position < 0) {

			cout << "Position must be >= 0." << endl;
			return;

		}

		Node* newNode = new Node(goat);

		if (!head) {

			head = tail = newNode;
			return;

		}

		Node* temp = head;

		for (int i = 0; i < position && temp; ++i)
			temp = temp->next;

		if (!temp) {

			cout << "Position exceeds list size. Node not inserted.\n";
			delete newNode;
			return;

		}

		newNode->next = temp->next;
		newNode->prev = temp;

		if (temp->next)
			temp->next->prev = newNode;
		else
			tail = newNode; // insert at the end

		temp->next = newNode;

	}

	void delete_node(int position) {

		if (!head) return; // empty list

		Node* temp = head;

		for (int i = 0; i < position && temp; i++)
			temp = temp->next;

		if (!temp) return; // value not found

		if (temp->prev)
			temp->prev->next = temp->next;
		else
			head = temp->next; // delete head

		if (temp->next)
			temp->next->prev = temp->prev;
		else
			tail = temp->prev; // delete tail

		delete temp; // free memory

	}

	void print() {

		Node* current = head;

		if (!current) { // check if list is empty

			cout << "List is empty." << endl;
			return;

		}

		while (current) {

			current->data.print(); // print goat data
			current = current->next;

		}

		cout << endl;

	}

	void print_reverse() {

		Node* current = tail;

		if (!current) { // check if list is empty

			cout << "List is empty." << endl;
			return;

		}

		while (current) {

			current->data.print(); // print goat data
			current = current->prev;

		}

		cout << endl;

	}

	~DoublyLinkedList() {

		while (head) {

			Node* temp = head;
			head = head->next;
			delete temp;

		}
	}
};

// main() is the entry point and driver of the program
// arguments: none
// returns: int - the exit code of the program
int main() {

	srand(time(0)); // seed random number generator

	DoublyLinkedList list;
	int size = rand() % (MAX_LS - MIN_LS + 1) + MIN_LS; // random size between 5 and 20

	// add size number of goats to the list
	for (int i = 0; i < size; i++)
		list.push_back(Goat());

	cout << "Forward:" << endl;
	list.print();
	cout << "Backward:" << endl;
	list.print_reverse();

	return 0;

}