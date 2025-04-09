#include "Person.h"

class Employee : public Person {
    private: 
        float salary;
        string role;
    public:
        Employee(string name, int age, float salary, string role):Person(name,age),salary(salary),role(role) {}

        void display() {
            cout << " Name: " << name << ", Age: " << age << ", Salary: " << salary << " Bath " << endl;
        }
};