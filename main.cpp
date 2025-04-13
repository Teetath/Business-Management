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

//ฟังก์ชันหยุดหน้าจอ
void pause() {
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void EmployeeMenu() {
    EmployeeManager manager;
        int choice;

        while (true) {
            system("clear");
            cout << "Employee Management Menu" << endl << "-------------------------" << endl;
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
                case 5: return;
                default: cout << "Invalid choice. Try again.\n";
            }
                pause();
            }
}

void FinanceMenu() {
    // อาจจะสร้าง class finance
    int choice;

    while(true) {
        system("clear");
        cout << "Finance Menu" << endl << "-------------------------" << endl;
        cout << "1. Sell Product" << endl;
        cout << "2. Show Income Expense / Profit" << endl;
        cout << "3. Return to Main Menu" << endl;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(choice) {
            case 1: {

            }
            case 2: {

            }
            case 3: return;
            default: cout << "Invalid Choice" << endl;
        }
    }

}

void ProductMenu() {
    ProductList list;
    int choice;
    list.loadFromFile("products.txt"); //โหลดมาแค่ครั้งเดียวเพราะเป็น loop

    while(true) {
        system("clear");
        cout << "Product Management Menu" << endl << "-------------------------" << endl;
        cout << "1. Add Product" << endl;
        cout << "2. Display Products" << endl;
        cout << "3. Remove Product" << endl;
        cout << "4. Return to Main Menu" << endl;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
        switch(choice) {
            case 1: {
                string name;
                float price; int stock;
        
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
                break;
            }
            case 2: {
                list.displayAll(); break;
            }
            case 3: {
                string target;
                list.displayAll();
                cout << "Enter the name of the product you want to remove" << endl;
                getline(cin, target);
                list.removeProduct(target); 
                list.saveToFile("products.txt"); break;
            }
            case 4: return;
            default: cout << "Invalid Choice" << endl;
        }

        pause();
    }
}

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
            EmployeeMenu();

        } else if(cate == 2) {
            FinanceMenu();

        } else if(cate == 3) {
            ProductMenu();

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