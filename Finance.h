#ifndef FINANCE_H
#define FINANCE_H

#include "Product.h"
#include <limits>

void ProductList::sell() {
    string name;
    int amount=0;
    int stock;
    displayAll();
    
    cout << "Enter name: ";
    getline(cin, name);
    while(amount<=0) {
    cout << "Enter amount: ";
    cin >> amount;
    }
    ProductNode* current = head;
    while (current) {
        if(current->product->getName() == name) {
            stock = current->product->getStock();
            if(amount > stock) {
                cout << "Not enough stock" << endl;
            }else {
                current->product->setStock(stock-amount);
                float earned = amount * current->product->getPriceWithVAT();
                totalincome += earned;
                cout << "Sold " << amount << " of '" << name << "' Remaining in stock: " << stock - amount << endl;
                saveToFile("products.txt");

                ofstream saleoutput("sales.txt", ios::app);
                saleoutput << name << "," << amount << "," << fixed << setprecision(2) << earned << endl;
                saleoutput.close();
            }
            return;
        }
        current = current->next;
    }
    cout << "Product not found." << endl;
}

void ProductList::summaryIncome(const string& filename) const {
    ifstream file(filename);
    string line;
    float total = 0;

    while (getline(file, line)) {
        stringstream ss(line);
        string name,quan,income_string;

        getline(ss, name, ',');
        getline(ss, quan, ',');
        getline(ss, income_string);

        float income = stof(income_string);
        total += income;
    }
    file.close();
    cout << "Total income : " << fixed << setprecision(2) << total << " Bath" << endl;
}

void ProductList::printSalesData(const string& filename) const {
    ifstream file(filename);
    if(!file) {
        cout << "Can't open file" << endl;
        return;
    }
    
    string line;
    bool Printed = false;
    system("clear");
    while(getline(file, line)) {
        stringstream ss(line);
        string name, quan, earned;

        if(!Printed) {
            Printed = true;
            cout << left << setw(20) << "Product Name" << setw(10) << "|Quantity" << setw(15) << "|Earned (Baht)" << endl;
            cout << string(55, '-') << endl; 
        }
        getline(ss, name, ',');
        getline(ss, quan, ',');
        getline(ss, earned);

        cout << left << setw(20) << name
             << setw(10) << quan
             << setw(15) << earned << endl;
    }
    file.close();
}

#endif