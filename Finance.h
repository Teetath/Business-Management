#ifndef FINANCE_H
#define FINANCE_H

#include "Product.h"
#include "Employee.h"

void ProductList::sell() {
    string id, input;
    int amount;

    if (!head) {
        cout << "⚠️ No product data loaded.\n";
        return;
    }

    displayAll();

    while (true) {
        cout << "\033[1;34m🆔 Enter Product ID (leave blank to cancel): \033[0m ";
        getline(cin, id);

        if (id.empty() || all_of(id.begin(), id.end(), ::isspace)) {
            cout << "\033[1;33m⚠️  Sale cancelled.\033[0m\n";
            return;
        }

        if (!isValidID(id)) {
            cout << "\033[1;31m❌ Error: Product ID must contain only letters or digits.\033[0m\n";
        } else {
            break;
        }
    }

    ProductNode* current = head;
    while (current) {
        if (current->product->getID() == id) {
            while (true) {
                cout << "\033[1;34mEnter amount to sell (leave blank to cancel):\033[0m ";
                getline(cin, input);
        
                if (input.empty() || all_of(input.begin(), input.end(), ::isspace)) {
                    cout << "\033[1;33m⚠️  Sale cancelled.\033[0m\n";
                    return;
                }
                if (check() && tryParse(input, amount) && amount > 0) {
                    cout << amount;
                    if(amount > current->product->getStock()) {
                        cout << "\033[1;31m❌ Not enough stock.\033[0m\n";
                        continue;
                    }
                    else break;
                }
                cout << "\033[1;31m❌ Invalid amount! Please enter a positive number.\033[0m\n";
    
            }

            int stock = current->product->getStock();

            current->product->setStock(stock - amount);
            float earned = amount * current->product->getPriceWithVAT();
            totalincome += earned;
            saveToFile("products.txt");

            string timestamp = getCurrentTimestamp();
            ofstream saleoutput("sales.txt", ios::app);
            saleoutput << current->product->getName() << "," << amount << "," << fixed << setprecision(2) << earned << "," << timestamp << endl;
            saleoutput.close();

            cout << "✅ Sold " << amount << " of product '" << current->product->getName() << "' (ID: " << id << ")\n";
            cout << "📦 Remaining in stock: " << current->product->getStock() << endl;
            return;
        }
        current = current->next;
    }
    cout << "\033[1;31m❌ Product with ID '" << id << "' not found.\033[0m\n";
}


void ProductList::summaryIncome(const string& filename, const string& targetMonth) const {
    float total = getMonthlyIncome(filename, targetMonth);
    cout << "💰 Total income : \033[32m" << fixed << setprecision(2) << total << "\033[0m Bath" << endl;
}

void ProductList::printSalesData(const string& filename, const string& targetMonth) const {
    ifstream file(filename);
    if (!file) {
        cout << "Can't open file" << endl;
        return;
    }

    string line;
    map<string, pair<int, double>> salesData;

    while (getline(file, line)) {
        stringstream ss(line);
        string name, quan, earned, timestamp;

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
        cout << "\033[1;36m================= 📊 Sales Log for " << targetMonth << " =================\033[0m" << endl;
        cout << left << setw(20) << "Product Name"
             << setw(15) << "Quantity"
             << setw(25) << "Earned (Baht)" << endl;
        cout << "\033[1;36m" << string(60, '=') << "\033[0m" << endl;

        for (const auto& entry : salesData) {
            cout << left << setw(20) << entry.first
                 << setw(15) << entry.second.first
                 << fixed << setprecision(2)
                 << setw(25) << entry.second.second << endl;
        }
    } else {
        cout << "\033[1;31mNo Sales Data for " << targetMonth << "!!\033[0m" << endl;
    }
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

struct MonthlyFinanceData {
    string month;
    float income;
    float salary;
    float sso;
    float profit;
};

MonthlyFinanceData calculateMonthlyFinance(ProductList& products, EmployeeManager& empManager, const string& targetMonth) {
    float income = products.getMonthlyIncome("sales.txt", targetMonth);
    float totalSalary = 0, totalSSO = 0;

    for (Node* curr = empManager.getHead(); curr; curr = curr->next) {
        string timestamp = curr->data.getTimestamp();  // YYYY-MM-DD

        // ถ้าเริ่มงานหลังเดือนเป้าหมาย ไม่ต้องนับ
        if (timestamp.substr(0, 7) > targetMonth) continue;

        float baseSalary = curr->data.getSalary();
        float baseSSO = curr->data.getSocialSecurity();
        float netBaseSalary = baseSalary - baseSSO;

        totalSalary += netBaseSalary;
        totalSSO += baseSSO;
    }

    float profit = income - totalSalary - totalSSO;
    return { targetMonth, income, totalSalary, totalSSO, profit };
}

void printFinanceRow(const MonthlyFinanceData& data) {
    string incomeColor = data.income > 0 ? "\033[32m" : "\033[0m";
    string profitColor = data.profit < 0 ? "\033[31m" : "\033[32m";
    string salaryColor = "\033[31m"; 
    string ssoColor = "\033[31m";
    string reset = "\033[0m";

    cout << "║ " << setw(10) << right << data.month << " ║ "
         << incomeColor << setw(23) << fixed << setprecision(2) << data.income << reset << " ║ "
         << salaryColor << setw(23) << data.salary << reset << " ║ "
         << ssoColor << setw(18) << data.sso << reset << " ║ "
         << profitColor << setw(18) << data.profit << reset << " ║\n";
}

void showMonthlyFinanceSummary(ProductList& products, EmployeeManager& empManager) {
    string targetMonth = getTargetMonthInput();
    if (targetMonth.empty()) return;

    system("clear");
    cout << "\033[1;36m"
    << string(38, '=')
    << " 📈 Monthly Summary for " << targetMonth << " "
    << string(38, '=') << "\n\033[0m" << endl;

    products.printSalesData("sales.txt", targetMonth);
    cout << endl;

    products.summaryIncome("sales.txt", targetMonth);
    cout << endl;

    MonthlyFinanceData data = calculateMonthlyFinance(products, empManager, targetMonth);

    cout << "╔════════════╦═════════════════════════╦═════════════════════════╦════════════════════╦════════════════════╗\n";
    cout << "║   Month    ║     Total Income (฿)    ║     Total Salary (฿)    ║     SSO TAX (฿)    ║  Total Profit (฿)  ║\n";
    cout << "╠════════════╬═════════════════════════╬═════════════════════════╬════════════════════╬════════════════════╣\n";
    printFinanceRow(data);
    cout << "╚════════════╩═════════════════════════╩═════════════════════════╩════════════════════╩════════════════════╝\n";
}

void showYearlyFinanceSummary(ProductList& products, EmployeeManager& empManager) {
    string targetYear = getTargetYearInput();
    if (targetYear.empty()) return;

    system("clear");
    cout << "\033[1;36m"
        << string(35, '=')
        << " 📊 Yearly Financial Summary for " << targetYear << " "
        << string(35, '=') << "\n\033[0m" << endl;
    cout << "╔════════════╦═════════════════════════╦═════════════════════════╦════════════════════╦════════════════════╗\n";
    cout << "║   Month    ║     Total Income (฿)    ║     Total Salary (฿)    ║     SSO TAX (฿)    ║  Total Profit (฿)  ║\n";
    cout << "╠════════════╬═════════════════════════╬═════════════════════════╬════════════════════╬════════════════════╣\n";

    float totalIncomeYear = 0, totalSalaryYear = 0, totalSSOYear = 0, totalProfitYear = 0;

    for (int m = 1; m <= 12; ++m) {
        stringstream ss;
        ss << targetYear << "-" << (m < 10 ? "0" : "") << m;
        string targetMonth = ss.str();

        MonthlyFinanceData data = calculateMonthlyFinance(products, empManager, targetMonth);

        totalIncomeYear += data.income;
        totalSalaryYear += data.salary;
        totalSSOYear += data.sso;
        totalProfitYear += data.profit;

        printFinanceRow(data);
    }

    cout << "╠════════════╬═════════════════════════╬═════════════════════════╬════════════════════╬════════════════════╣\n";

    MonthlyFinanceData totalData = { "Total", totalIncomeYear, totalSalaryYear, totalSSOYear, totalProfitYear };
    printFinanceRow(totalData);

    cout << "╚════════════╩═════════════════════════╩═════════════════════════╩════════════════════╩════════════════════╝\n";
}

#endif