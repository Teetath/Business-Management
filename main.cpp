#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Person {
    protected:      //เดะเอาไปใช้ใน Employee (inheri)
        string name;
        int age;
    public:
        Person (string name, int age) : name(name), age(age) {}
        virtual void display(){
            cout << "Name: " << name << "Age " << age <<endl;
        }
};

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

class Product {
    private:
        string name;
        float price;
        int stock;
    public:
        Product(string name,float price,int stock):name(name),price(price),stock(stock) {}
        void displayProduct() {
            cout << "Product: " << name << ", Price: $" << price
             << ", Stock: " << stock << endl;
        }
    string getName() {return name; }
    float getPrice() { return price; }
    int getStock() { return stock; }

    string getLine() {
        return name + "," + to_string(price) + "," + to_string(stock);
    }
};




