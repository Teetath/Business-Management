#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "Person.h"

class Employee : public Person {
    private:
        float salary;
        string id,role;

    public:
        Employee(string id, string name, int age, float salary, string role)
            : Person(name, age), id(id), salary(salary), role(role) {}

        string getId() const { return id; }
        string getRole() const { return role; }
        float getSalary() const { return salary; }

        void display() const {
            cout << fixed << setprecision(2);
            cout << left
                 << setw(12) << id
                 << "| " << setw(20) << name
                 << "| " << setw(5)  << age
                 << "| " << setw(12) << role
                 << "| " << setw(10) << salary
                 << "| " << setw(10) << calculateBonus() << endl;
        }
        float calculateBonus() const {
            return salary * 0.1f; // พนักงานได้โบนัส 10%
        }

        string getSummary() const override {
            stringstream ss;
            ss << fixed << setprecision(2);
            ss << name << " - " << role
               << " (Total: " << (salary + calculateBonus()) << " Bath)";
            return ss.str();
        }

        string to_file_string() const {
            stringstream ss;
            ss << fixed << setprecision(2) << salary;
            return id + "," + name + "," + to_string(age) + "," + ss.str() + "," + role;
        }

        static Employee from_file_string(const string& line) {
            string id, name, role;
            int age;
            float salary;

            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            size_t pos3 = line.find(',', pos2 + 1);
            size_t pos4 = line.find(',', pos3 + 1);

            id = line.substr(0, pos1);
            name = line.substr(pos1 + 1, pos2 - pos1 - 1);
            age = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
            salary = stof(line.substr(pos3 + 1, pos4 - pos3 - 1));
            role = line.substr(pos4 + 1);

            return Employee(id, name, age, salary, role);
        }
};

// ------------------- Linked List Version ----------------------

struct Node {
    Employee data;
    Node* next;
    Node(Employee emp) : data(emp), next(nullptr) {}
};

class EmployeeManager {
    private:
        Node* head = nullptr;
        const string filename = "employees.txt";

        void save_to_file() {
            ofstream file(filename);
            Node* current = head;
            while (current) {
                file << current->data.to_file_string() << endl;
                current = current->next;
            }
            file.close();
        }

        void load_from_file() {
            clear_list();
            ifstream file(filename);
            string line;
            while (getline(file, line)) {
                if (!line.empty()) {
                    Employee emp = Employee::from_file_string(line);
                    add_to_list(emp);
                }
            }
            file.close();
        }

        void add_to_list(const Employee& emp) {
            Node* newNode = new Node(emp);
            if (!head) {
                head = newNode;
            } else {
                Node* current = head;
                while (current->next)
                    current = current->next;
                current->next = newNode;
            }
        }

        void clear_list() {
            Node* current = head;
            while (current) {
                Node* toDelete = current;
                current = current->next;
                delete toDelete;
            }
            head = nullptr;
        }

    public:
        EmployeeManager() {
            load_from_file();
        }

        ~EmployeeManager() {
            clear_list();
        }

        void add_employee() {
            int age;
            float salary;
            string id, name, role;

            system("clear");
            cout << "\033[1;36m+------------------------------------+\n";
            cout << "|        🆕 Add New Employee         |\n";
            cout << "+------------------------------------+\033[0m\n";
            while (true) {
                cout << "\033[1;34mEnter ID: \033[0m ";
                cin >> id;
            
                if (!isValidID(id)) {
                    cout << "\033[1;31mError: ID must contain only English letters or digits.\033[0m\n";
                    continue;
                }
                if (isDuplicateID(id)) {
                    cout << "\033[1;31mError: ID '" << id << "' already exists. Please enter a new one.\033[0m\n";
                    continue;
                }
                break;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            while(true){
                cout << "\033[1;34mEnter name: \033[0m";
                getline(cin, name);
                if (!isValidName(name)) {
                    cout << "\033[1;31mError: Name must contain only English letters.\033[0m\n";
                    continue;
                }
                break;
            }

            while(true){
                cout << "\033[1;34mEnter age: \033[0m";
                cin >> age;
                if(check() && age > 0)break;
                else cout << "\033[1;31mError!?! Please try again.\033[0m\n";
            }
            
            while(true){
                cout << "\033[1;34mEnter salary: \033[0m";
                cin >> salary;
                if(check() && salary >= 0)break;
                else cout << "\033[1;31mError!?! Please try again.\033[0m\n";
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            while(true){
                cout << "\033[1;34mEnter role: \033[0m";
                getline(cin, role);
                if (!isValidName(role)) {
                    cout << "\033[1;31mError: Role must contain only English letters.\033[0m\n";
                    continue;
                }
                break;
            }

            Employee emp(id, name, age, salary, role);
            add_to_list(emp);
            save_to_file();
            cout << "Employee added and saved to file.\n";
        }

        bool isDuplicateID(const string& id) const {
            Node* current = head;
            while (current) {
                if (current->data.getId() == id) {
                    return true; // พบไอดีซ้ำ
                }
                current = current->next;
            }
            return false; // ไม่ซ้ำ
        }

        void search_employee() {
            string input;
            system("clear");
            cout << "\033[1;34mEnter ID or name to search: \033[0m";
            cin >> input;
            system("clear");

            Node* current = head;
            bool found = false;

            while (current) {
                if (current->data.getId() == input || current->data.getName() == input) {
                    current->data.display();
                    found = true;
                }
                current = current->next;
            }

            if (!found) {
                cout << "Employee not found.\n";
            }
        }

        void remove_employee() {
            string id;
            system("clear");
            cout << "\033[1;34mEnter ID to remove: \033[0m";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("clear");
            Node* current = head;
            Node* prev = nullptr;

            while (current) {
                if (current->data.getId() == id) {
                    if (prev)
                        prev->next = current->next;
                    else
                        head = current->next;

                    delete current;
                    save_to_file();
                    cout << "Employee removed and file updated.\n";
                    return;
                }

                prev = current;
                current = current->next;
            }

            cout << "Employee not found.\n";
        }

        void getSummary() {
            system("clear");
            if (!head) {
                cout << "No employees to summarize.\n";
                return;
            }
        
            Node* current = head;
            while (current) {
                cout << current->data.getSummary() << endl;
                current = current->next;
            }
        }
        void split(Node* source, Node** frontRef, Node** backRef) {
            Node* slow = source;
            Node* fast = source->next;
        
            while (fast) {
                fast = fast->next;
                if (fast) {
                    slow = slow->next;
                    fast = fast->next;
                }
            }
        
            *frontRef = source;
            *backRef = slow->next;
            slow->next = nullptr;
        }
        Node* sortedMerge(Node* a, Node* b, int mode, bool ascending) {
            if (!a) return b;
            if (!b) return a;
        
            bool condition;
            if (mode == 1) { // salary
                condition = ascending ? (a->data.getSalary() < b->data.getSalary())
                                      : (a->data.getSalary() > b->data.getSalary());
            } else if (mode == 2) { // name
                condition = ascending ? (a->data.getName() < b->data.getName())
                                      : (a->data.getName() > b->data.getName());
            } else { // ID
                condition = ascending ? (a->data.getId() < b->data.getId())
                                      : (a->data.getId() > b->data.getId());
            }
        
            Node* result = nullptr;
            if (condition) {
                result = a;
                result->next = sortedMerge(a->next, b, mode, ascending);
            } else {
                result = b;
                result->next = sortedMerge(a, b->next, mode, ascending);
            }
        
            return result;
        }
        void mergeSort(Node** headRef, int mode, bool ascending) {
            Node* head = *headRef;
            if (!head || !head->next) return;
        
            Node* a;
            Node* b;
            split(head, &a, &b);
        
            mergeSort(&a, mode, ascending);
            mergeSort(&b, mode, ascending);
        
            *headRef = sortedMerge(a, b, mode, ascending);
        }
        bool display_sort_menu() {

            if (!head) {
                cout << "No employees to sort.\n";
                return true;
            }
            while(true){
                system("clear");
                char option;
                cout << "\033[1;34m";
                cout << "+=================================================+\n";
                cout << "| 🔽           EMPLOYEE SORT MENU                 |\n";
                cout << "+=================================================+\033[0m\n";
                cout << "| \033[1;32m[1]\033[0m 💵 Salary (Low to High)                     |\n";
                cout << "| \033[1;32m[2]\033[0m 💰 Salary (High to Low)                     |\n";
                cout << "| \033[1;32m[3]\033[0m 🔤 Name (A-Z)                               |\n";
                cout << "| \033[1;32m[4]\033[0m 🔡 Name (Z-A)                               |\n";
                cout << "| \033[1;32m[5]\033[0m 🆔 ID (Ascending)                           |\n";
                cout << "| \033[1;32m[6]\033[0m 🆔 ID (Descending)                          |\n";
                cout << "| \033[1;32m[0]\033[0m 🔙 Return to Employee Menu                  |\n";
                cout << "+-------------------------------------------------+\n";
                option = getch();

                bool ascending = true;
                int mode = 0;
                switch (option-'0') {
                    case 1: mode = 1; ascending = true; break; // Salary ASC
                    case 2: mode = 1; ascending = false; break; // Salary DESC
                    case 3: mode = 2; ascending = true; break; // Name A-Z
                    case 4: mode = 2; ascending = false; break; // Name Z-A
                    case 5: mode = 3; ascending = true; break; // ID ASC
                    case 6: mode = 3; ascending = false; break; // ID DESC
                    case 0: return true;
                    default: continue;
                }
                mergeSort(&head, mode, ascending);
                system("clear");
                displayTableHeader();
                display_all();
                Pause();
            }
            return false;
        }

        void display_all(){
            Node* current = head;
                while (current) {
                    current->data.display();
                    current = current->next;
                }
        }

        void displayTableHeader() {
            cout << left
                << setw(12) << "ID"
                << "| " << setw(20) << "Name"
                << "| " << setw(5)  << "Age"
                << "| " << setw(12) << "Role"
                << "| " << setw(10) << "Salary"
                << "| " << setw(10) << "Bonus" << endl;
            cout << string(80, '-') << endl;
        }

        void edit_employee() {
            string id;
            system("clear");
            displayTableHeader();
            display_all();
            cout << "\033[1;34mEnter ID to edit: \033[0m";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
            Node* current = head;
            while (current) {
                if (current->data.getId() == id) {
                    string empID = current->data.getId();
                    string name = current->data.getName();
                    int age = current->data.getAge();
                    float salary = current->data.getSalary();
                    string role = current->data.getRole();
        
                    char option;
                    do {
                        system("clear");
                        cout << "\033[1;36m";
                        cout << "+---------------------------------------------+\n";
                        cout << "|       ✏️  Edit Employee Information          |\n";
                        cout << "+---------------------------------------------+\033[0m\n";

                        cout << "\033[1;33mCurrent Employee Info:\033[0m\n";
                        cout << left
                            << setw(12) << "ID"
                            << "| " << setw(20) << "Name"
                            << "| " << setw(5)  << "Age"
                            << "| " << setw(12) << "Role"
                            << "| " << setw(10) << "Salary"<< endl;
                        cout << string(80, '-') << endl;
                        cout << fixed << setprecision(2);
                        cout << left
                            << setw(12) << empID
                            << "| " << setw(20) << name
                            << "| " << setw(5)  << age
                            << "| " << setw(12) << role
                            << "| " << setw(10) << salary<< endl;

                        cout << "\n\033[1;34mChoose the field you want to edit:\033[0m\n";
                        cout << "\033[1;36m";
                        cout << "  [1] \033[0mEdit \033[1mID\033[0m\n";
                        cout << "\033[1;36m  [2] \033[0mEdit \033[1mName\033[0m\n";
                        cout << "\033[1;36m  [3] \033[0mEdit \033[1mAge\033[0m\n";
                        cout << "\033[1;36m  [4] \033[0mEdit \033[1mSalary\033[0m\n";
                        cout << "\033[1;36m  [5] \033[0mEdit \033[1mRole\033[0m\n";
                        cout << "\033[1;32m  [S] \033[0m\033[1mSave and Exit\033[0m\n";
                        cout << "\033[1;31m  [C] \033[0m\033[1mCancel\033[0m\n";
                        option = getch();
                        string input;
                        switch (option) {
                            case '1':
                                cout << "Enter new ID (leave blank to keep current): ";
                                getline(cin, input);
                                if (!input.empty()) {
                                    if (!isDuplicateID(input) && isValidID(input)) empID = input;
                                    else cout << "\033[1;31mInvalid or duplicate ID. Keeping current.\033[0m\n";
                                }
                                Pause();
                                break;
                            case '2':
                                cout << "Enter new name (leave blank to keep current): ";
                                getline(cin, input);
                                if (!input.empty()) {
                                    if (isValidName(input)) name = input;
                                    else cout << "\033[1;31mInvalid name. Keeping current.\033[0m\n";
                                }
                                Pause();
                                break;
                            case '3':
                                cout << "Enter new age (or type 'cancel' to skip): ";
                                getline(cin, input);
                                if (input != "cancel") {
                                    try {
                                        int newAge = stoi(input);
                                        if (check() && newAge > 0) age = newAge;
                                        else cout << "\033[1;31mInvalid age. Keeping current.\033[0m\n";
                                    } catch (...) {
                                        cout << "\033[1;31mInvalid input. Keeping current.\033[0m\n";
                                    }
                                }
                                Pause();
                                break;
                            case '4':
                                cout << "Enter new salary (or type 'cancel' to skip): ";
                                getline(cin, input);
                                if (input != "cancel") {
                                    try {
                                        float newSalary = stof(input);
                                        if (check() && newSalary >= 0) salary = newSalary;
                                        else cout << "\033[1;31mInvalid salary. Keeping current.\033[0m\n";
                                    } catch (...) {
                                        cout << "\033[1;31mInvalid input. Keeping current.\033[0m\n";
                                    }
                                }
                                Pause();
                                break;
                            case '5':
                                cout << "Enter new role (leave blank to keep current): ";
                                getline(cin, input);
                                if (!input.empty()) {
                                    if (isValidName(input)) role = input;
                                    else cout << "\033[1;31mInvalid role. Keeping current.\033[0m\n";
                                }
                                Pause();
                                break;
                            case 'S':
                            case 's':
                                current->data = Employee(empID, name, age, salary, role);
                                save_to_file();
                                cout << "\033[1;32m✅ Employee updated successfully!\033[0m\n";
                                return;
                            case 'C':
                            case 'c':
                                cout << "\033[1;33mChanges cancelled..\033[0m\n";
                                return;
                            default:
                                cout << "\033[1;31mInvalid option. Try again.\033[0m\n";
                                Pause();
                                break;
                        }
                    } while (true);
                }
                current = current->next;
            }
        
            cout << "\033[1;31mEmployee with ID '" << id << "' not found.\033[0m\n";
        }
};
#endif
