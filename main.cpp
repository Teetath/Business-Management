#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include "Employee.h"
#include "Product.h"


int main() {
    while(1) {
        int cate;

        cout << "Business Management System" << endl;
        cout << "--------------------------" << endl;
        cout << "Choose Category" << endl;
        cout << "1. Employee" << endl;
        cout << "2. Finance" << endl;
        cout << "3. Products" << endl;
        cout << "4. Exit" << endl;
        cin >> cate;

        if(cate == 1) {
            int choice;
            cout << "1. Add Employee" << endl;
            cout << "2. Search Employee" << endl;
            cout << "3. Add Employee" << endl;
            cout << "4. Remove Employee" << endl;
            cin >> choice;
            if(choice) {}

        } else if(cate == 2) {
            int choice;
            cout << "1. Sell Product" << endl;
            cout << "2. Show Income Expense / Profit" << endl;
            cin >> choice;
            if(choice) {}

        } else if(cate == 3) {
            int choice;
            cout << "1. Add Product" << endl;
            cout << "2. Display Products" << endl;
            cout << "3. Remove Product" << endl;
            cin >> choice;
            if(choice) {}

        } else if(cate == 4) break;
        else cout << "Error! Please try again." << endl;;
    }
}