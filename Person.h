#ifndef PERSON_H
#define PERSON_H

#include <iostream>
using namespace std;

class Person {
protected:
    string name;
    int age;

public:
    Person(string name, int age) : name(name), age(age) {}

    string getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    virtual void display() const {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
    
    virtual float calculateBonus() {
        return 0.0f; // Default ไม่มีโบนัส
    }

    virtual string getSummary() const {
        return name + " (Age: " + to_string(age) + ")";
    }
};

#endif