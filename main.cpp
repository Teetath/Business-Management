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
        cout << "| ➕ [1] Add Employee                         | \n";
        cout << "| 🔍 [2] Search Employee                      | \n";
        cout << "| ✏️  [3] Edit Employee                        | \n";
        cout << "| ❌ [4] Remove Employee                      | \n";
        cout << "| 📋 [5] Display All Employees                | \n";
        cout << "| 🔙 [6] Summary of All Employees             | \n";
        cout << "| 🔙 [0] Return to Main Menu                  | \n";
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
    char choice;
    while(true) {
        system("clear");
        cout << "\033[1;32m";
        cout << "+=============================================+\n";
        cout << "|           💰 FINANCE MANAGEMENT 💰           |\n";
        cout << "+=============================================+\033[0m\n";
        cout << "| 💸 [1] Sell Product                          |\n";
        cout << "| 📅 [2] Show Income/Expense/Profit per Month  |\n";
        cout << "| 📈 [3] Show Income/Expense/Profit per Year   |\n";
        cout << "| 🔙 [0] Return to Main Menu                   |\n";
        cout << "+---------------------------------------------+\n";
        
        
        choice = getch();
        
        system("clear");

        switch(choice) {
            case '1': {
                // Add functionality for selling products
                ProductList list;
                list.loadFromFile("products.txt");
                list.sell();
                break;
            }
            case '2': {
                // Add functionality for showing income/expense/profit
                ProductList list;
                EmployeeManager emp;
                list.loadFromFile("products.txt");
                showMonthlyFinanceSummary(list, emp);
                break;
            }
            case '3' : {
                ProductList list;
                EmployeeManager emp;
                list.loadFromFile("products.txt");
                showYearlyFinanceSummary(list, emp);
                break;
            }
            case '0': return;
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
        cout << "| 🔍 [2] Search Product                 | \n";
        cout << "| ✏️  [3] Edit Product                   | \n";
        cout << "| 👀 [4] Display Products               | \n";
        cout << "| 🗑  [5] Remove Product                 | \n";
        cout << "| 🔙 [0] Return to Main Menu            | \n";
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
        cout << "|  [1] 👨‍💼  Employee Management            |\n";
        cout << "|  [2] 💰  Finance                          |\n";
        cout << "|  [3] 📦  Product Management               |\n";
        cout << "|  [0] ❌  Exit                             |\n";
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