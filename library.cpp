#include <__nullptr>
#include <fstream>
#include <iostream>

struct Company {
    int age;
    char gender;
    int id;
    Company *next;
};

class LinkedList {
private:
    Company *head;
    Company *tail;
    int count = 0;

public:
    LinkedList() : head(nullptr), tail(nullptr) {}
    void add(int age, char gender, int id);
    void insertAtBeginning(int age, char gender, int id);
    void insertAtEnd(int age, char gender, int id);
    void insertAfter(int id, int age, char gender, int newId);

    bool remove(int id);

    bool isEmpty();
    bool isEmptyFromFile(const std::string &fileName);
    void print();
    void readFromFile(const std::string &fileName);


    bool replace(int id, int newAge, char newGender);

    void removeFromBeginning();
    void writeToFile(const std::string &fileName);

    int getCount();
    void clearList();
    void find(int id);

    void sort();
};


void LinkedList::add(int age, char gender, int id) {
    Company *newCompany = new Company{age, gender, id, nullptr};
    if (tail != nullptr) {
        tail->next = newCompany;
        tail = newCompany;
    } else {
        head = newCompany;
        tail = newCompany;
    }

    count++;
}

void LinkedList::insertAtBeginning(int age, char gender, int id) {
    Company *newCompany = new Company{age, gender, id, head};
    head = newCompany;

    if (tail == nullptr) {
        tail = newCompany;
    }

    count++;
}

void LinkedList::insertAtEnd(int age, char gender, int id) {
    Company *newCompany = new Company{age, gender, id, nullptr};
    if(tail != nullptr) {
        tail->next = newCompany;
    }
    tail = newCompany;
    if(head == nullptr) {
        head = newCompany;
    }
    tail = newCompany;
    count++;
}

void LinkedList::insertAfter(int id, int age, char gender, int newId) {
    Company *current = head;
    while(current != nullptr) {
        if(current->id == id) {
            Company *newCompany = new Company{age, gender, newId, current->next};
            current->next = newCompany;
            if(current == tail) {
                tail = newCompany;
            }
            break;
        }
        current = current->next;
    }
    count++;
}

bool LinkedList::remove(int id) {
    bool result = false;
    Company *current = head;
    Company *previous = nullptr;
    while (current != nullptr) {
        if (current->id == id) {
            result = true;
            if (previous != nullptr) {
                previous->next = current->next;
            } else {
                head = current->next;
            }
            delete current;
            count--;
            break;
        }
        previous = current;
        current = current->next;
    }
    return result;
}


bool LinkedList::isEmpty() {
    return count;
}

bool LinkedList::isEmptyFromFile(const std::string &fileName) {
    std::ifstream file(fileName);
    return file.peek() == std::ifstream::traits_type::eof();
}

void LinkedList::print() {
    Company *current = head;
    while (current != nullptr) {
        printf("Age: %d Gender: %c ID: %d\n", current->age, current->gender, current->id);
        current = current->next;
    }
}

void LinkedList::readFromFile(const std::string &fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cout << "bad open file" << std::endl;
        return;
    }
    int age, id;
    char gender;
    while (file >> age >> gender >> id) {
        add(age, gender, id);
    }
    file.close();
}


bool LinkedList::replace(int id, int newAge, char newGender) {
    Company *current = head;
    bool result = false;
    while (current != nullptr) {
        if (current->id == id) {
            result = true;
            current->age = newAge;
            current->gender = newGender;
            break;
        }
        current = current->next;
    }
    return result;
}

void LinkedList::removeFromBeginning() {
    if (head != nullptr) {
        Company *temp = head;
        head = head->next;
        delete temp;
        count--;
        if(head == nullptr) {
            tail = nullptr;
        }
    }
}

void LinkedList::writeToFile(const std::string &fileName) {
    std::ofstream file(fileName);
    if (!file.is_open()) {
        std::cout << "Failed to open file" << std::endl;
        return;
    }

    Company *current = head;
    while (current != nullptr) {
        file << current->age << " " << current->gender << " " << current->id << "\n";
        current = current->next;
    }
    file.close();
}

void LinkedList::clearList() {
    Company *current = head;
    while (current != nullptr) {
        Company *temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
    tail = nullptr;
    count = 0;
}

void LinkedList::find(int id) {
    Company *current = head;
    while (current != nullptr) {
        if (current->id == id) {
            printf("Age: %d Gender: %c ID: %d\n", current->age, current->gender, current->id);
            break;
        }
        current = current->next;
    }
    if (current == nullptr) {
        std::cout << "Item not found" << std::endl;
    }
}

int LinkedList::getCount() {
    return count;
}
void LinkedList::sort() {
    if (head == nullptr || head->next == nullptr) {
        return;
    }
    bool swapped = false;
    Company *ptr1 = nullptr;
    Company *lptr = nullptr;

    do {
        swapped = false;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->id > ptr1->next->id) {
                std::swap(ptr1->id, ptr1->next->id);
                std::swap(ptr1->age, ptr1->next->age);
                std::swap(ptr1->gender, ptr1->next->gender);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

int main() {
    LinkedList list;
    list.add(30, 'M', 1);
    list.add(25, 'F', 2);
    list.add(32, 'M', 3);
    list.insertAtBeginning(35, 'F', 4);
    list.insertAtEnd(28, 'M', 5);
    list.insertAfter(3, 31, 'F', 6);
    list.remove(5);
    std::cout << "пуст ли текстовый документ? - " << list.isEmptyFromFile("data.txt");
    list.add(18, 'F', 5);
    list.add(82, 'M', 7);
    list.replace(1, 29, 'M');
    list.removeFromBeginning();
    list.writeToFile("new_data.txt");
    list.clearList();
    list.readFromFile("data.txt");
    list.print();
    list.sort();
    list.print();
    std::cout << "Number of items in list: " << list.getCount() << std::endl;

    list.clearList();
    std::cout << "Number of items in list: " << list.getCount() << std::endl;
    return 0;
}
