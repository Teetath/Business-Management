#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include "Person.h"

class Employee : public Person {
    private:
        float salary;
        string role;
    
    public:
    Employee(string name, int age, float salary, string role)
        : Person(name, age), salary(salary), role(role) {}

    string getRole() const { return role; }
    float getSalary() const { return salary; }

    void display() const {
        cout << "Name: " << name
                << ", Age: " << age
                << ", Role: " << role
                << ", Salary: " << fixed << setprecision(2) << salary << " Bath" << endl;
    }

    string to_file_string() const {
        stringstream ss;
        ss << fixed << setprecision(2) << salary;
        return name + "," + to_string(age) + "," + ss.str() + "," + role;
    }

    // Static function to create from file line
    static Employee from_file_string(const string& line) {
        string name, role;
        int age;
        float salary;

        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);

        name = line.substr(0, pos1);
        age = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
        salary = stof(line.substr(pos2 + 1, pos3 - pos2 - 1));
        role = line.substr(pos3 + 1);

        return Employee(name, age, salary, role);
    }
};

class EmployeeManager {
private:
    vector<Employee> employees;
    const string filename = "employees.txt";

    void save_to_file() {
        ofstream file(filename);
        for (const auto& emp : employees) {
            file << emp.to_file_string() << endl;
        }
        file.close();
    }

    void load_from_file() {
        employees.clear();
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            if (!line.empty()) {
                employees.push_back(Employee::from_file_string(line));
            }
        }
        file.close();
    }

public:
    EmployeeManager() {
        load_from_file();
    }

    void add_employee() {
        string name, role;
        int age;
        float salary;

        cout << "Enter name: ";
        cin >> name;
        cout << "Enter age: ";
        cin >> age;
        cout << "Enter salary: ";
        cin >> salary;
        cout << "Enter role: ";
        cin >> role;

        employees.emplace_back(name, age, salary, role);
        save_to_file();
        cout << "Employee added and saved to file.\n";
    }

    void search_employee() {
        string name;
        cout << "Enter name to search: ";
        cin >> name;

        bool found = false;
        for (const auto& emp : employees) {
            if (emp.getName() == name) {
                emp.display();
                found = true;
            }
        }

        if (!found) {
            cout << "Employee not found.\n";
        }
    }

    void remove_employee() {
        string name;
        cout << "Enter name to remove: ";
        cin >> name;

        for (auto it = employees.begin(); it != employees.end(); ++it) {
            if (it->getName() == name) {
                employees.erase(it);
                save_to_file();
                cout << "Employee removed and file updated.\n";
                return;
            }
        }

        cout << "Employee not found.\n";
    }

    void display_all() {
        if (employees.empty()) {
            cout << "No employees to display.\n";
            return;
        }

        for (const auto& emp : employees) {
            emp.display();
        }
    }
};

#endif