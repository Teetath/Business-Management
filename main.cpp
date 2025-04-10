#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

#include "Employee.h"
#include "Product.h"


int main() {
    system("clear");
    while(1) {
        int cate;

        cout << "\033[1;35mBusiness Management System\033[0m" << endl;
        cout << "--------------------------" << endl;
        cout << "Choose Category" << endl;
        cout << "1. Employee" << endl;
        cout << "2. Finance" << endl;
        cout << "3. Products" << endl;
        cout << "4. Exit" << endl;
        cin >> cate;

        if(cate == 1) {
            int choice;
            system("clear");
            cout << "1. Add Employee" << endl;
            cout << "2. Search Employee" << endl;
            cout << "3. Remove Employee" << endl;
            cout << "4. Exit" << endl;
            cin >> choice;
            if(choice) {}

        } else if(cate == 2) {
            int choice;
            system("clear");
            cout << "1. Sell Product" << endl;
            cout << "2. Show Income Expense / Profit" << endl;
            cout << "3. Exit" << endl;
            cin >> choice;
            if(choice) {}

        } else if(cate == 3) {
            int choice;
            system("clear");
            cout << "1. Add Product" << endl;
            cout << "2. Display Products" << endl;
            cout << "3. Remove Product" << endl;
            cout << "4. Exit" << endl;
            cin >> choice;
            if(choice) {}

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