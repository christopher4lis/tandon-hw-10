#include <iostream>
#include <fstream>
#include <string>
using namespace std;

template<typename GenericType> class LinkedList;

// ------------------------
// LinkedListNode
// ------------------------
template<typename GenericType> class LinkedListNode {
    GenericType data;
    LinkedListNode<GenericType>* next;

    LinkedListNode(GenericType newData = GenericType(), LinkedListNode<GenericType>* newNext = nullptr) {
        data = newData;
        next = newNext;
    }

    friend class LinkedList<GenericType>;
};

// ------------------------
// LinkedList
// ------------------------
template <typename GenericType> class LinkedList {
    LinkedListNode<GenericType>* head = nullptr;

public:
    LinkedList(LinkedListNode<GenericType>* newData = nullptr) {
        head = newData;
    }

    ~LinkedList() {
        clear();
    }

    // class methods
    void insertAtHead(GenericType newData);
    void clear();
    bool isEmpty() const;
    int size() const;
    void insertAtEnd(GenericType newData);
    GenericType* findEmployeeById(int id);
    void sortList();
    void printPayrollInfo() const;
};

template <typename GenericType> void LinkedList<GenericType>::insertAtHead(GenericType newData) {
    head = new LinkedListNode<GenericType>(newData, head);
}

template <typename GenericType> void LinkedList<GenericType>::clear() {
    LinkedListNode<GenericType>* temp;
    while (head != nullptr) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

template <typename GenericType> bool LinkedList<GenericType>::isEmpty() const {
    return head == nullptr;
}

template <typename GenericType> int LinkedList<GenericType>::size() const {
    int count = 0;
    LinkedListNode<GenericType>* temp = head;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}

template <typename GenericType> void LinkedList<GenericType>::insertAtEnd(GenericType newData) {
    if (isEmpty()) {
        insertAtHead(newData);
        return;
    }
    LinkedListNode<GenericType>* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = new LinkedListNode<GenericType>(newData);
}

template <typename GenericType> GenericType* LinkedList<GenericType>::findEmployeeById(int id) {
    LinkedListNode<GenericType>* temp = head;
    while (temp != nullptr) {
        if (temp->data.getId() == id) {
            return &(temp->data);
        }
        temp = temp->next;
    }
    return nullptr;
}

template <typename GenericType> void LinkedList<GenericType>::sortList() {
    if (isEmpty()) {
        return;
    }
    LinkedListNode<GenericType>* i = head;
    LinkedListNode<GenericType>* j;
    for (; i != nullptr; i = i->next) {
        for (j = i->next; j != nullptr; j = j->next) {
            if (j->data < i->data) {
                swap(i->data, j->data);
            }
        }
    }
}

template <typename GenericType> void LinkedList<GenericType>::printPayrollInfo() const {
    cout << "*********Payroll Information********\n";
    LinkedListNode<GenericType>* temp = head;
    while (temp != nullptr) {
        cout << temp->data.getName() << ", $" << temp->data.getPay() << "\n";
        temp = temp->next;
    }
    cout << "*********End payroll**************\n";
}




// ------------------------
// Employee
// ------------------------
class Employee {
    int id;
    float payRate;
    string name;
    int hoursWorked;

public:
    Employee(int newId = 0, float newPayRate = 0.0, string newName = "", int newHoursWorked = 0)
            : id(newId), payRate(newPayRate), name(newName), hoursWorked(newHoursWorked) {}

    // class methods
    void addHours(int hours);
    float getPay() const;
    string getName() const;
    int getId() const;

    bool operator<(const Employee& other) const {
        return getPay() > other.getPay();
    }
};

void Employee::addHours(int hours) {
    hoursWorked += hours;
}

float Employee::getPay() const {
    return payRate * hoursWorked;
}

string Employee::getName() const {
    return name;
}

int Employee::getId() const {
    return id;
}


// ------------------------
// main
// ------------------------
int main() {
    ifstream employeesFile("emps.txt");
    ifstream hoursFile("hours.txt");
    LinkedList<Employee> employeeList;

    int id;
    float payRate;
    string name;
    while (employeesFile >> id >> payRate) {
        employeesFile.ignore(9999, ' ');
        getline(employeesFile, name, '\r');
        employeeList.insertAtEnd(Employee(id, payRate, name));
    }
    employeesFile.close();

    int hours;
    while (hoursFile >> id >> hours) {
        Employee* employee = employeeList.findEmployeeById(id);
        if (employee) {
            employee->addHours(hours);
        }
    }
    hoursFile.close();

    employeeList.sortList();
    employeeList.printPayrollInfo();

    return 0;
}


