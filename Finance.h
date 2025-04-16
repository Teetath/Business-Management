#ifndef FINANCE_H
#define FINANCE_H

#include "Product.h"
#include "Employee.h"

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
                saleoutput << name << "," << amount << "," << fixed << setprecision(2) << earned << "," << timestamp << endl;
                saleoutput.close();
            }
            return;
        }
        current = current->next;
    }
    cout << "Product not found." << endl;
}

void ProductList::summaryIncome(const string& filename,const string& targetMonth) const {
    ifstream file(filename);
    string line;
    float total = 0;

    while (getline(file, line)) {
        stringstream ss(line);
        string name, quan, income_string, timestamp;

        getline(ss, name, ',');
        getline(ss, quan, ',');
        getline(ss, income_string, ',');
        getline(ss, timestamp);

        if (timestamp.substr(0, 7) != targetMonth) continue;

        float income = stof(income_string);
        total += income;
    }
    file.close();
    cout << "💰 Total income : " << "\033[32m" << fixed << setprecision(2) << total << "\033[0m" << " Bath" << endl;
}

void ProductList::printSalesData(const string& filename,const string& targetMonth) const {
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
         string name, quan, earned,timestamp;
 
         getline(ss, name, ',');
         getline(ss, quan, ',');
         getline(ss, earned, ',');
         getline(ss, timestamp);


         if (timestamp.substr(0, 7) != targetMonth) continue;

        int quantity = stoi(quan);
        double earnedValue = stod(earned);

        salesData[name].first += quantity;
        salesData[name].second += earnedValue;
     }
     file.close();

     if (!salesData.empty()) {
        cout << "====================== Sales Log ====================== " << endl;
        cout << left << setw(20) << "Product Name"
             << setw(20) << "|Quantity"
             << setw(20) << "|Earned (Baht)" << endl;
        cout << string(55, '-') << endl;

        for (const auto& entry : salesData) {
            cout << left << setw(20) << entry.first
                 << setw(20) << entry.second.first
                 << fixed << setprecision(2)
                 << setw(20) << entry.second.second << endl;
        }
    } else cout << "No Sales Data!!" << endl;
}

void ProductList::summaryProfitFromSales(const string& filename, const string& targetMonth) const {
    ifstream file(filename);
    if (!file) {
        cerr << "❌ Failed to open sales.txt" << endl;
        return;
    }

    string line;
    float totalProfit = 0.0f;
    float totalSSO = 0.0f;
    float net = 0.0f;

    while (getline(file, line)) {

        stringstream ss(line);
        string name, quantityStr, earnedStr, timestamp;
        getline(ss, name, ',');
        getline(ss, quantityStr, ',');
        getline(ss, earnedStr, ',');
        getline(ss, timestamp);

        if (timestamp.substr(0, 7) != targetMonth) continue;

        int quantity = stoi(quantityStr);
        
        ProductNode* current = head;
        while (current) {
            if (current->product->getName() == name) {
                float profitPerUnit = current->product->getProfitPerUnit();
                float profit = quantity * profitPerUnit;
                totalProfit += profit;
                break;
            }
            current = current->next;
        }
    }

    file.close();
    
    EmployeeManager EmpManager;
    Node* currentEmp = EmpManager.getHead();
    float totalSalaries = 0.0f;
    while (currentEmp) {
        totalSalaries += currentEmp->data.getSalary() - currentEmp->data.getSocialSecurity();
        totalSSO += currentEmp->data.getSocialSecurity();
        currentEmp=currentEmp->next;

    }
    cout << "🫂  Total Salary : " << "\033[31m" << fixed << setprecision(2) << totalSalaries << "\033[0m" << " Baht " << "(Withholding tax)" << endl;
    cout << "🧾 SSO TAX      : " <<"\033[31m" << fixed << setprecision(2) << totalSSO << "\033[0m" << " Baht" << endl;
    cout << "-------------------------------------------------------" << endl;
    net = totalProfit - (totalSalaries + totalSSO);
    if (net < 0) {
        cout << "📊 Total Profit : " << "\033[31m" << fixed << setprecision(2) << net << "\033[0m" << " Baht" << endl;    //loss
    }else {
        cout << "📊 Total Profit : " << "\033[32m" << fixed << setprecision(2) << net << "\033[0m" << " Baht" << endl;    //profit
    }
    return;
}

#endif