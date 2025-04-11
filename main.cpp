#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <vector>
using namespace std;

#include "Employee.h"
#include "Product.h"


int main() {
    
    while(1) {
        int cate;
        system("clear");
        cout << "\033[1;35mBusiness Management System\033[0m" << endl;
        cout << "--------------------------" << endl;
        cout << "Choose Category" << endl;
        cout << "1. Employee" << endl;
        cout << "2. Finance" << endl;
        cout << "3. Products" << endl;
        cout << "4. Exit" << endl;
        cin >> cate;

        if(cate == 1) {
            EmployeeManager manager;
            int choice;

            while (true) {
                system("clear");
                cout << "1. Add Employee" << endl;
                cout << "2. Search Employee" << endl;
                cout << "3. Remove Employee" << endl;
                cout << "4. Display All Employees" << endl;
                cout << "5. Return to Main Menu" << endl;
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice) {
                    case 1: manager.add_employee(); break;
                    case 2: manager.search_employee(); break;
                    case 3: manager.remove_employee(); break;
                    case 4: manager.display_all(); break;
                    case 5: break;
                    default: cout << "Invalid choice. Try again.\n";
                }
                if(choice == 5)break;
                cout << "Press any key to continue...";
                cin.ignore();
                cin.get();
            }

        } else if(cate == 2) {
            int choice;
            system("clear");
            cout << "1. Sell Product" << endl;
            cout << "2. Show Income Expense / Profit" << endl;
            cout << "3. Exit" << endl;
            cin >> choice;
            if(choice) {}

        } else if(cate == 3) {
            ProductList list;
            int choice;
            system("clear");
            cout << "1. Add Product" << endl;
            cout << "2. Display Products" << endl;
            cout << "3. Remove Product" << endl;
            cout << "4. Exit" << endl;
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if(choice == 1) {
                string name;
                float price; int stock;
                list.loadFromFile("products.txt");

                cout << "Product Name: ";
                getline(cin, name);
                cout << "Product Price: ";
                cin >> price;
                cout << "Product Stock: ";
                cin >> stock;

                list.addProduct(new Product(name, price, stock));
                cout << "Product added Sucessfully!" << endl;
                list.displayAll();
                list.saveToFile("products.txt");
            }

            else if(choice == 2) {
                list.loadFromFile("products.txt");
                list.displayAll();
            }

            else if(choice == 3) {
                list.loadFromFile("products.txt");
                
            } else if(choice == 4) {
                system("clear");
                break;
            }

        } else if(cate == 4) {
            system("clear");
            break;
        }
        else {
            system("clear");
            cout << "Error! Please try again." << endl;;
        }
    }
return 0;
}