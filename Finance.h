#ifndef FINANCE_H
#define FINANCE_H

#include "Product.h"

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

                string timestamp = getCurrentTimestamp();

                ofstream saleoutput("sales.txt", ios::app);
                if (saleoutput.tellp() == 0) {
                    saleoutput << left << setw(20) << "Product Name"
                               << setw(10) << "Qty"
                               << setw(15) << "Earned (Baht)"
                               << "Date & Time" << endl;
                    saleoutput << string(65, '-') << endl;
                }

                saleoutput << left << setw(20) << name
                           << setw(10) << amount
                           << setw(15) << fixed << setprecision(2) << earned
                           << timestamp << endl;

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
        string name, quan, income_string, time_String;

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
    map<string, pair<int, double>> salesData;
    system("clear");

    while(getline(file, line)) {
         stringstream ss(line);
         string name, quan, earned;
 
         getline(ss, name, ',');
         getline(ss, quan, ',');
         getline(ss, earned);

        int quantity = stoi(quan);
        double earnedValue = stod(earned);

        salesData[name].first += quantity;
        salesData[name].second += earnedValue;
     }
     file.close();

     if (!salesData.empty()) {
        cout << "\n=========== Sales Log ===========" << endl;
        cout << left << setw(20) << "Product Name"
             << setw(10) << "|Quantity"
             << setw(15) << "|Earned (Baht)" << endl;
        cout << string(55, '-') << endl;

        for (const auto& entry : salesData) {
            cout << left << setw(20) << entry.first
                 << setw(10) << entry.second.first
                 << fixed << setprecision(2)
                 << setw(15) << entry.second.second << endl;
        }
    } else cout << "No Sales Data!!" << endl;
}

#endif