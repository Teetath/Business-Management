#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <vector>
#include <map>
#include <termios.h>
#include <unistd.h>
#include <ctime>
#include <algorithm>
using namespace std;

#include "Function.h"
#include "Employee.h"
#include "Finance.h"

void EmployeeMenu() {
    EmployeeManager manager;
    char choice;

    while (true) {
        system("clear");
        cout << "\033[1;32m";
        cout << "+=============================================+\n";
        cout << "| 👨‍💼       EMPLOYEE MANAGEMENT         👨‍💼 | \n";
        cout << "+=============================================+\033[0m\n";
        cout << "| ➕ \033[1;32m[1]\033[0m Add Employee                         | \n";
        cout << "| 🔍 \033[1;32m[2]\033[0m Search Employee                      | \n";
        cout << "| ✏️ \033[1;32m [3]\033[0m Edit Employee                        | \n";
        cout << "| ❌ \033[1;32m[4]\033[0m Remove Employee                      | \n";
        cout << "| 📋 \033[1;32m[5]\033[0m Display All Employees                | \n";
        cout << "| 🔙 \033[1;32m[6]\033[0m Summary of All Employees             | \n";
        cout << "| 🔙 \033[1;31m[0]\033[0m Return to Main Menu                  | \n";
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
                manager.edit_employee(); break;
                
            }case '4': {
                manager.remove_employee(); break;
            }
            case '5': {
                if(manager.display_sort_menu())continue;break;
            }
            case '6': {
                manager.getSummary(); break; //เป็น polymorphism
            }
            case '0': return;
            default : continue;
        }
        Pause();
    }
}

void FinanceMenu() {
    static ProductList list;              
    static EmployeeManager emp;           

    char choice;
    while (true) {
        system("clear");
        cout << "\033[1;32m";
        cout << "+=============================================+\n";
        cout << "|           💰 FINANCE MANAGEMENT 💰           |\n";
        cout << "+=============================================+\033[0m\n";
        cout << "| 💸 \033[1;32m[1]\033[0m Sell Product                          |\n";
        cout << "| 📅 \033[1;32m[2]\033[0m Show Income/Expense/Profit per Month  |\n";
        cout << "| 📈 \033[1;32m[3]\033[0m Show Income/Expense/Profit per Year   |\n";
        cout << "| 🔙 \033[1;31m[0]\033[0m Return to Main Menu                   |\n";
        cout << "+---------------------------------------------+\n";

        choice = getch();
        system("clear");

        switch (choice) {
            case '1': {
                list.loadFromFile("products.txt");  // โหลดใหม่เสมอ แต่ใช้ object เดิม
                list.sell();
                break;
            }
            case '2': {
                list.loadFromFile("products.txt");
                showMonthlyFinanceSummary(list, emp);
                break;
            }
            case '3': {
                list.loadFromFile("products.txt");
                showYearlyFinanceSummary(list, emp);
                break;
            }
            case '0': return;
            default: continue;
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
        cout << "| 🆕 \033[1;32m[1]\033[0m Add Product                    | \n";
        cout << "| 🔍 \033[1;32m[2]\033[0m Search Product                 | \n";
        cout << "| ✏️ \033[1;32m [3]\033[0m Edit Product                   | \n";
        cout << "| 👀 \033[1;32m[4]\033[0m Display Products               | \n";
        cout << "| 🗑  \033[1;32m[5]\033[0m Remove Product                 | \n";
        cout << "| 🔙 \033[1;31m[0]\033[0m Return to Main Menu            | \n";
        cout << "+---------------------------------------+\n";
        
        choice = getch();
        
        system("clear");
    
        switch(choice) {
            case '1': {
                list.add_new_product(); break;
            }
            case '2': {
                list.search_product(); break;
            }
            case '3': {
                list.edit_product(); break;
            }
            case '4': {
                list.SortproductMenu(list);
                continue;
                break;
            }
            case '5': {
                list.removeProduct(); break;
            }
            case '0': return;
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
        cout << "|  \033[1;32m[1]\033[0m 👨‍💼  Employee Management            |\n";
        cout << "|  \033[1;32m[2]\033[0m 💰  Finance                          |\n";
        cout << "|  \033[1;32m[3]\033[0m 📦  Product Management               |\n";
        cout << "|  \033[1;31m[0]\033[0m ❌  Exit                             |\n";
        cout << "+-------------------------------------------+\n";

        char choice = getch();
        system("clear");

        switch (choice) {
            case '1': EmployeeMenu(); break;
            case '2': FinanceMenu(); break;
            case '3': ProductMenu(); break;
            case '0': 
                cout << "Exiting...\n";
                system("clear");
                return 0;
        }
    }
}