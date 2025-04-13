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
#include "Product.h"

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
    cout << "Press Enter to continue...";
    cin.get();
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
        cout << "| ➕ [1] Add Employee                        | \n";
        cout << "| 🔍 [2] Search Employee                     | \n";
        cout << "| ❌ [3] Remove Employee                     | \n";
        cout << "| 📋 [4] Display All Employees               | \n";
        cout << "| 🔙 [5] Return to Main Menu                 | \n";
        cout << "+---------------------------------------------+\n";
        
        choice = getch();  // รับตัวอักษรแบบไม่ต้องกด Enter
        
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
                manager.display_all(); break;
            }
            case '5': return;
            default: cout << "\033[1;31m❌ Invalid choice! Press any key to retry...\033[0m\n"; getch(); break;
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
                cout << "\033[1;36m💰 Selling Product...\033[0m\n";
                break;
            }
            case '2': {
                // Add functionality for showing income/expense/profit
                cout << "\033[1;36m📈 Showing Income/Expense/Profit...\033[0m\n";
                break;
            }
            case '3': return;
            default: cout << "\033[1;31m❌ Invalid choice! Press any key to retry...\033[0m\n"; getch(); break;
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
        cout << "| 🗑 [3] Remove Product                  | \n";
        cout << "| 🔙 [4] Return to Main Menu            | \n";
        cout << "+---------------------------------------+\n";
        
        choice = getch();  // รับตัวอักษรแบบไม่ต้องกด Enter
        
        system("clear");

        switch(choice) {
            case '1': {
                string name;
                float price;
                int stock;

                cout << "Product Name: ";
                getline(cin, name);
                cout << "Product Price: ";
                cin >> price;
                cout << "Product Stock: ";
                cin >> stock;

                list.addProduct(new Product(name, price, stock));
                cout << "Product added successfully! 🎉\n";
                list.displayAll();
                list.saveToFile("products.txt");
                break;
            }
            case '2': {
                list.displayAll(); break;
            }
            case '3': {
                string target;
                list.displayAll();
                cout << "Enter the name of the product you want to remove: ";
                getline(cin, target);
                list.removeProduct(target);
                list.saveToFile("products.txt");
                break;
            }
            case '4': return;
            default: cout << "\033[1;31m❌ Invalid choice! Press any key to retry...\033[0m\n"; getch(); break;
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
            default:
                cout << "\n\033[1;31mInvalid selection! Press any key to retry...\033[0m\n";
                getch();
        }
    }
}