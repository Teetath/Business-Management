#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <vector>
#include <termios.h>
#include <unistd.h>
using namespace std;

#include "Employee.h"
#include "Finance.h"

char getch() {
    char buf = 0;
    termios old = {};
    if (tcgetattr(STDIN_FILENO, &old) < 0) perror("tcgetattr()");
    termios newt = old;
    newt.c_lflag &= ~ICANON; // ปิด canonical mode
    newt.c_lflag &= ~ECHO;   // ไม่ echo ตัวอักษรออกจอ
    if (tcsetattr(STDIN_FILENO, TCSANOW, &newt) < 0) perror("tcsetattr ICANON");
    if (read(STDIN_FILENO, &buf, 1) < 0) perror("read()");
    if (tcsetattr(STDIN_FILENO, TCSADRAIN, &old) < 0) perror("tcsetattr ~ICANON");
    return buf;
}

//ฟังก์ชันหยุดหน้าจอ
void Pause() {
    cout << "\033[1;32mPress any key to continue...\033[0m\n";
    getch();
}

void SortproductMenu(ProductList& list) {
    char choice;
    while (true) {
        system("clear");
        cout << "\033[1;34m";
        cout << "+=============================================+\n";
        cout << "| 🔽        SORT PRODUCT DISPLAY MENU        |\n";
        cout << "+=============================================+\033[0m\n";
        cout << "| [1] 🆕 Newest to Oldest                    |\n";
        cout << "| [2] 📜 Oldest to Newest                    |\n";
        cout << "| [3] 🔤 Sort by Name A-Z                    |\n";
        cout << "| [4] 💰 Price High to Low                   |\n";
        cout << "| [5] 📦 Stock Low to High                   |\n";
        cout << "| [0] 🔙 Back to Product Menu                |\n";
        cout << "+---------------------------------------------+\n";
        cout << "Select option (press key): " << flush;

        choice = getch(); // รับค่าทันทีที่กด ไม่ต้อง Enter
        system("clear");

        switch (choice) {
            case '1':
                system("clear");
                list.sortByNewest();
                list.displayAll();
                break;
            case '2':
                system("clear");
                list.loadFromFile("products.txt");
                list.displayAll();
                break;
            case '3':
                system("clear");
                list.sortByNameAZ();
                list.displayAll();
                break;
            case '4':
                system("clear");
                list.sortByHighPrice();
                list.displayAll();
                break;
            case '5':
                system("clear");
                list.sortByLowStock();
                list.displayAll();
                break;
            case '0':
                return;
            default:
                continue;
        }
        Pause();
    }
}

void EmployeeMenu() {
    EmployeeManager manager;
    char choice;

    while (true) {
        system("clear");
        cout << "\033[1;32m";
        cout << "+=============================================+\n";
        cout << "| 👨‍💼       EMPLOYEE MANAGEMENT         👨‍💼 | \n";
        cout << "+=============================================+\033[0m\n";
        cout << "| ➕ [1] Add Employee                         | \n";
        cout << "| 🔍 [2] Search Employee                      | \n";
        cout << "| ❌ [3] Remove Employee                      | \n";
        cout << "| 📋 [4] Display All Employees                | \n";
        cout << "| 🔙 [5] Summary of All Employees             | \n";
        cout << "| 🔙 [6] Return to Main Menu                  | \n";
        cout << "+---------------------------------------------+\n";
        
        choice = getch();
        
        system("clear");

        switch(choice) {
            case '1': {
                manager.add_employee(); break;
            }
            case '2': {
                manager.search_employee(); break;
            }
            case '3': {
                manager.remove_employee(); break;
            }
            case '4': {
                while(true){
                    system("clear");
                    char option;
                    cout << "\033[1;34m************** Employee Sort Menu **************\033[0m\n";
                    cout << "\033[1;32m[1]\033[0m Sort by Salary (Ascending)\n";
                    cout << "\033[1;32m[2]\033[0m Sort by Salary (Descending)\n";
                    cout << "\033[1;32m[3]\033[0m Sort by Name (A-Z)\n";
                    cout << "\033[1;32m[4]\033[0m Sort by Name (Z-A)\n";
                    cout << "\033[1;32m[5]\033[0m Sort by ID (Ascending)\n";
                    cout << "\033[1;32m[6]\033[0m Sort by ID (Descending)\n";
                    cout << "\033[1;32m[7]\033[0m Return to Employee Menu\n";
                    cout << "\033[1;36m************************************************\033[0m\n";
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
                        case 7: break;
                        default: continue;
                    }
                    if(option-'0' == 7)break;
                    manager.display_all(mode,ascending);Pause(); //เป็น polymorphism แล้วเพราะ inherit มาจาก Person
                }break;
            }
            case '5': {
                manager.getSummary(); break; //เป็น polymorphism
            }
            case '6': return;
            default : continue;
        }
        Pause();
    }
}

void FinanceMenu() {
    char choice;
    while(true) {
        system("clear");
        cout << "\033[1;32m";
        cout << "+=======================================+\n";
        cout << "| 💰       FINANCE MANAGEMENT        💰 | \n";
        cout << "+=======================================+\033[0m\n";
        cout << "| 💸 [1] Sell Product                   | \n";
        cout << "| 📊 [2] Show Income/Expense/Profit     | \n";
        cout << "| 🔙 [3] Return to Main Menu            | \n";
        cout << "+---------------------------------------+\n";
        
        choice = getch();  // รับตัวอักษรแบบไม่ต้องกด Enter
        
        system("clear");

        switch(choice) {
            case '1': {
                // Add functionality for selling products
                ProductList list;
                list.loadFromFile("products.txt");
                list.sell();
                cout << "\033[1;36m💰 Selling Product...\033[0m\n";
                break;
            }
            case '2': {
                // Add functionality for showing income/expense/profit
                cout << "\033[1;36m📈 Showing Income/Expense/Profit...\033[0m\n";
                break;
            }
            case '3': return;
            default : continue;
        }
        Pause();
    }
}

void ProductMenu() {
    ProductList list;
    char choice;
    list.loadFromFile("products.txt");

    while(true) {
        system("clear");
        cout << "\033[1;34m";
        cout << "+=======================================+\n";
        cout << "| 📦       PRODUCT MANAGEMENT        📦 | \n";
        cout << "+=======================================+\033[0m\n";
        cout << "| 🆕 [1] Add Product                    | \n";
        cout << "| 👀 [2] Display Products               | \n";
        cout << "| 🗑  [3] Remove Product                 | \n";
        cout << "| 🔙 [4] Return to Main Menu            | \n";
        cout << "+---------------------------------------+\n";
        
        choice = getch();  // รับตัวอักษรแบบไม่ต้องกด Enter
        
        system("clear");

        switch(choice) {
            case '1': {
                string name;
                float price, cost;
                int stock;
                cout << "\033[1;36m+------------------------------------+\n";
                cout << "|        🆕 Add New Product          |\n";
                cout << "+------------------------------------+\033[0m\n";
                cout << "📦 Product Name   : ";
                getline(cin, name);

                if (list.isDuplicateName(name)) {
                    cout << "\033[1;31m❌ Product name already exists! Cannot add duplicate.\033[0m\n";
                    break;
                }

                cout << "💲 Product Price  : ";
                cin >> price;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "💲 Product Cost   : ";
                cin >> cost;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
                cout << "📦 Product Stock  : ";
                cin >> stock;
                cin.ignore();
                list.addProduct(new Product(name, price, cost, stock));
                list.saveToFile("products.txt");
                
                cout << "\n\033[1;32m✅ Product \"" << name << "\" added successfully! 🎉\033[0m\n";
                break;
            }
            case '2': {
                SortproductMenu(list);
                continue;
                break;
            }   
            case '3': {
                string target;
                list.displayAll();
                cout << "Enter the name of the product you want to remove: ";
                getline(cin, target);
                if(target == "cancel") continue;
                list.removeProduct(target);
                list.saveToFile("products.txt");
                break;
            }
            case '4': return;
            default : continue;
        }
        Pause();
    }
}

int main() {
    while (true) {
        system("clear");
        cout << "\033[1;35m";
        cout << "+===========================================+\n";
        cout << "|        BUSINESS MANAGEMENT SYSTEM         |\n";
        cout << "+===========================================+\033[0m\n";
        cout << "|  [1] 👨‍💼  Employee Management            |\n";
        cout << "|  [2] 💰  Finance                          |\n";
        cout << "|  [3] 📦  Product Management               |\n";
        cout << "|  [4] ❌  Exit                             |\n";
        cout << "+-------------------------------------------+\n";

        char choice = getch(); // รับตัวอักษรแบบไม่ต้องกด Enter

        system("clear");

        switch (choice) {
            case '1': EmployeeMenu(); break;
            case '2': FinanceMenu(); break;
            case '3': ProductMenu(); break;
            case '4': 
                cout << "Exiting...\n";
                system("clear");
                return 0;
        }
    }
}