#ifndef PRODUCT_H
#define PRODUCT_H

class Product {
    private:
        string name, timestamp, id;
        float price;
        float cost;
        int stock;
    
    public:
        Product(string id, string name, float price, float cost, int stock, string timestamp);
        void displayProduct() const;
        string getID() const;
        string getName() const;
        float getPrice() const;
        float getCost() const; 
        float getProfitPerUnit() const;
        float getVAT() const;
        float getPriceWithVAT() const;
        int getStock() const;
        string getTimestamp() const;
        void setStock(int newStock);
        string getLine() const;
    };
    
    struct ProductNode {
        Product* product;
        ProductNode* next;
        ProductNode(Product* product) : product(product), next(nullptr) {}
    };
    
class ProductList {
    private:
        ProductNode* head;
        float totalincome;
        int size = 0;
    
    public:
        ProductList();
        ~ProductList();
        
        int getSize() const { return size; }
        bool isDuplicateID(const string& id) const;
        bool isDuplicateName(const string& name) const;
        void addProduct(Product* product);
        void add_new_product();
        void search_product();
        void removeProduct();
        void sortByNameAZ();
        void sortByNewest();
        void sortByOldest();
        void sortByHighPrice();
        void sortByLowStock();
        void displayTableHeader();
        void displayAll();
        void clearLL();
        void loadFromFile(const string& filename);
        void saveToFile(const string& filename) const;
        void comparePrice(float price);
        void compareStock(int stock);
        void sell();
        void printSalesData(const string& name,const string& targetMonth) const;
        void summaryIncome(const string& name,const string& targetMonth) const;
        void SortproductMenu(ProductList& list);
        void edit_product();
        void summaryProfitFromSales(const string& name,const string& targetMonth) const;
    };

    Product::Product(string id, string n, float p, float c, int s, string t)
    : id(id), name(n), price(p), cost(c), stock(s), timestamp(t) {}

    void Product::displayProduct() const {
        cout << fixed << setprecision(2);
        cout << left << setw(10) << id
        << "| " << setw(15) << name
        << "| " << setw(8)  << price
        << "| " << setw(8)  << cost
        << "| " << setw(8)  << getVAT()
        << "| " << setw(8)  << getPriceWithVAT()
        << "| " << setw(8)  << getProfitPerUnit();
    
        if (stock == 0) {
            cout << "| \033[1;31mOut of Stock \033[0m";
        } else {
            cout << "| " << setw(13) << stock;
        }
    
        cout << "| " << setw(20) << timestamp << endl;
    }

    string Product::getID() const { return id; }
    string Product::getName() const { return name; }
    float Product::getPrice() const { return price; }
    float Product::getCost() const { return cost; }
    float Product::getVAT() const { return price*0.07f; }
    float Product::getPriceWithVAT() const { return price + getVAT(); }
    float Product::getProfitPerUnit() const { return price - cost; }
    int Product::getStock() const { return stock; }
    string Product::getTimestamp() const { return timestamp; }

    string Product::getLine() const {
        stringstream ss;
        ss << id << "," << name << "," << price << "," << cost << "," << stock << "," << timestamp;
        return ss.str();
    }
    

    // ProductList Implementation

    ProductList::ProductList() : head(nullptr) {}

    ProductList::~ProductList() {
        ProductNode* current = head;
        while (current) {
            ProductNode* temp = current;
            current = current->next;
            delete temp->product;
            delete temp;
        }
    }

    bool ProductList::isDuplicateID(const string& id) const {
        ProductNode* current = head;
        while (current) {
            if (current->product->getID() == id) {
                return true; // พบไอดีซ้ำ
            }
            current = current->next;
        }
        return false; // ไม่ซ้ำ
    }


    bool ProductList::isDuplicateName(const string& name) const {
        ProductNode* current = head;
        while (current) {
            if (current->product->getName() == name) {
                return true; // พบชื่อซ้ำ
            }
            current = current->next;
        }
        return false; // ไม่ซ้ำ
    }

    void ProductList::addProduct(Product* product) {
        ProductNode* node = new ProductNode(product);
        node->next = head;
        head = node;
        size++;
    }

    void ProductList::removeProduct() {
        ProductNode* current = head;
        ProductNode* previous = nullptr;
        string name;
        system("clear");
        cout << "\n\033[1;36m+-------------------------------------------+\n";
        cout << "|         🗑️  Remove Product Menu            |\n";
        cout << "+-------------------------------------------+\033[0m\n";
        displayAll();
        cout << "\033[1;34mEnter the name of the product you want to remove (leave blank to return): \033[0m";
        getline(cin, name);
        if(name.empty()) { 
            cout << "\033[1;33mRemoval cancelled.\033[0m\n";
            return;
        }
        while (current) {
            if (current->product->getName() == name) {
                if (previous) {
                    previous->next = current->next;
                } else {
                    // กรณี 1 node
                    head = current->next;
                }
                delete current->product;
                delete current;
                size--;
                cout << "Product \"" << name << "\" removed successfully." << endl;

                saveToFile("products.txt");
                return;
            }
            previous = current;
            current = current->next;
        }

        cout << "Product \"" << name << "\" not found." << endl;
    }

    void ProductList::sortByNameAZ() {
        if (!head || !head->next) return;

        for (ProductNode* i = head; i != nullptr; i = i->next) {
            for (ProductNode* j = i->next; j != nullptr; j = j->next) {
                if (i->product->getName() > j->product->getName()) {
                    swap(i->product, j->product);
                }
            }
        }
    }

    void ProductList::sortByNewest() {
        ProductNode* prev = nullptr;
        ProductNode* current = head;
        ProductNode* next = nullptr;
    
        while (current) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;

        if (head == nullptr || head->next == nullptr) return;
    
        bool swapped;
        do {
            swapped = false;
            ProductNode* temp = head;
            while (temp != nullptr && temp->next != nullptr) {
                if (temp->product->getTimestamp() < temp->next->product->getTimestamp()) {

                    Product* tempProduct = temp->product;
                    temp->product = temp->next->product;
                    temp->next->product = tempProduct;
    
                    swapped = true;
                }
                temp = temp->next;
            }
        } while (swapped);
    }

    void ProductList::sortByOldest() {
        ProductNode* prev = nullptr;
        ProductNode* current = head;
        ProductNode* next = nullptr;
    
        while (current) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;

        if (head == nullptr || head->next == nullptr) return;
    
        bool swapped;
        do {
            swapped = false;
            ProductNode* temp = head;
            while (temp != nullptr && temp->next != nullptr) {
                if (temp->product->getTimestamp() > temp->next->product->getTimestamp()) {

                    Product* tempProduct = temp->product;
                    temp->product = temp->next->product;
                    temp->next->product = tempProduct;
    
                    swapped = true;
                }
                temp = temp->next;
            }
        } while (swapped);
    }

    void ProductList::sortByHighPrice() {
        if (!head || !head->next) return;

        for (ProductNode* i = head; i != nullptr; i = i->next) {
            for (ProductNode* j = i->next; j != nullptr; j = j->next) {
                if (i->product->getPrice() < j->product->getPrice()) {
                    swap(i->product, j->product);
                }
            }
        }
    }

    void ProductList::sortByLowStock() {
        if (!head || !head->next) return;

        for (ProductNode* i = head; i != nullptr; i = i->next) {
            for (ProductNode* j = i->next; j != nullptr; j = j->next) {
                if (i->product->getStock() > j->product->getStock()) {
                    swap(i->product, j->product);
                }
            }
        }
    }

    void ProductList::displayTableHeader() {
        cout << left
             << setw(10) << "ID"
             << "| " << setw(15) << "Name"
             << "| " << setw(8)  << "Price"
             << "| " << setw(8)  << "Cost"
             << "| " << setw(8)  << "VAT"
             << "| " << setw(8)  << "Total"
             << "| " << setw(8)  << "Profit"
             << "| " << setw(13) << "Stock"
             << "| " << setw(20) << "Last Updated" << endl;
    
        cout << string(115, '-') << endl;
    }

    void ProductList::displayAll() {
        displayTableHeader();
        ProductNode* current = head;
        while (current) {
            current->product->displayProduct();
            current = current->next;
        }
        cout << "\n\033[1;36m📊 Total Products: \033[1;33m" << size << "\033[0m\n";
    }

    void ProductList::clearLL() {
        ProductNode* current = head;
        while (current) {
            ProductNode* temp = current;
            current = current->next;
            delete temp->product;
            delete temp;
        }
        head = nullptr;
        size = 0;
    }

    void ProductList::loadFromFile(const string& filename) {
        clearLL();
        
        ifstream file(filename);
        string line;
    
        while (getline(file, line)) {
            stringstream ss(line);
            string id, name, priceStr, costStr, stockStr, timestamp;
    
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, priceStr, ',');
            getline(ss, costStr, ',');
            getline(ss, stockStr, ',');
            getline(ss, timestamp);
    
            float price = stof(priceStr);
            float cost = stof(costStr);
            int stock = stoi(stockStr);
    
            addProduct(new Product(id, name, price, cost, stock, timestamp));
        }
    
        file.close();
    }

    void ProductList::saveToFile(const string& filename) const {
        ofstream file(filename);
        ProductNode* current = head;

        while (current) {
            file << current->product->getLine() << endl;
            current = current->next;
        }

        file.close();
    }

    void ProductList::comparePrice(float price) {
        cout << "Products with price >= $" << price << ":" << endl;
        ProductNode* current = head;
        while (current) {
            if (current->product->getPrice() >= price)
                current->product->displayProduct();
            current = current->next;
        }
    }

    void ProductList::compareStock(int stock) {
        cout << "Products with stock >= " << stock << ":" << endl;
        ProductNode* current = head;
        while (current) {
            if (current->product->getStock() >= stock)
                current->product->displayProduct();
            current = current->next;
        }
    }

    void Product::setStock(int newStock) {
        stock = newStock;
    }

    void ProductList::SortproductMenu(ProductList& list) {
        char choice;
        while (true) {
            system("clear");
            cout << "\033[1;34m";
            cout << "+=============================================+\n";
            cout << "| 🔽           PRODUCT SORT MENU             |\n";
            cout << "+=============================================+\033[0m\n";
            cout << "| [1] 🆕 Newest to Oldest                    |\n";
            cout << "| [2] 📜 Oldest to Newest                    |\n";
            cout << "| [3] 🔤 Sort by Name A-Z                    |\n";
            cout << "| [4] 💰 Price High to Low                   |\n";
            cout << "| [5] 📦 Stock Low to High                   |\n";
            cout << "| [0] 🔙 Back to Product Menu                |\n";
            cout << "+---------------------------------------------+\n";

            choice = getch();
            system("clear");

            switch (choice) {
                case '1':
                    system("clear");
                    sortByNewest();
                    displayAll();
                    break;
                case '2':
                    system("clear");
                    sortByOldest();
                    displayAll();
                    break;
                case '3':
                    system("clear");
                    sortByNameAZ();
                    displayAll();
                    break;
                case '4':
                    system("clear");
                    sortByHighPrice();
                    displayAll();
                    break;
                case '5':
                    system("clear");
                    sortByLowStock();
                    displayAll();
                    break;
                case '0':
                    return;
                default:
                    continue;
            }
            Pause();
        }
    }
    void ProductList::add_new_product() {
        string id, name, time_added = getCurrentTimestamp();;
        float price, cost;
        int stock;

        
            system("clear");
            cout << "\033[1;36m+------------------------------------+\n";
            cout << "|        🆕 Add New Product          |\n";
            cout << "+------------------------------------+\033[0m\n";

        while (true) {
            cout << "\033[1;34m🆔 Product ID (leave blank to cancel): \033[0m ";
            getline(cin, id);

            if (id.empty() || all_of(id.begin(), id.end(), ::isspace)) {
                cout << "\033[1;33m⚠️  Product creation cancelled.\033[0m\n";
                return;
            }
    
            if (isDuplicateID(id)) {
                cout << "\033[1;31m❌ Product \'" << id << "\' already exists! Cannot add duplicate.\033[0m\n";
            } else if (!isValidID(id)) {
                cout << "\033[1;31m❌ Error: Product id must contain only English letters or digits.\033[0m\n";
            } else {
                break;
            }
        }
        while (true) {
            cout << "\033[1;34m📦 Product Name (leave blank to cancel): \033[0m ";
            getline(cin, name);
    
            if (name.empty() || all_of(name.begin(), name.end(), ::isspace)) {
                cout << "\033[1;33m⚠️  Product creation cancelled.\033[0m\n";
                return;
            }
    
            if (isDuplicateName(name)) {
                cout << "\033[1;31m❌ Product \'" << name << "\' already exists! Cannot add duplicate.\033[0m\n";
            } else if (!isValidName(name)) {
                cout << "\033[1;31m❌ Error: Product name must contain only English letters.\033[0m\n";
            } else {
                break;
            }
        }
    
        while (true) {
            cout << "\033[1;34m💲 Product Price (leave blank to cancel): \033[0m ";
            string price_input;
            getline(cin, price_input);
            if (price_input.empty() || all_of(price_input.begin(), price_input.end(), ::isspace)) {
                cout << "\033[1;33m⚠️  Product creation cancelled.\033[0m\n";
                return;
            }
    
            if (check() && tryParse(price_input, price) && price >= 0) break;
            cout << "\033[1;31m❌ Invalid price! Please enter a valid number.\033[0m\n";
        }
    
        while (true) {
            cout << "\033[1;34m💲 Product Cost (leave blank to cancel): \033[0m ";
            string cost_input;
            getline(cin, cost_input);
            if (cost_input.empty() || all_of(cost_input.begin(), cost_input.end(), ::isspace)) {
                cout << "\033[1;33m⚠️  Product creation cancelled.\033[0m\n";
                return;
            }
    
            if (check() && tryParse(cost_input, cost) && cost >= 0) break;
            else cout << "\033[1;31m❌ Invalid cost! It must be positive.\033[0m\n";
            cout << "\033[1;31m❌ Invalid cost! Please enter a valid number.\033[0m\n";

        }
    
        while (true) {
            cout << "\033[1;34m📦 Product Stock (leave blank to cancel): \033[0m";
            string stock_input;
            getline(cin, stock_input);
            if (stock_input.empty() || all_of(stock_input.begin(), stock_input.end(), ::isspace)) {
                cout << "\033[1;33m⚠️  Product creation cancelled.\033[0m\n";
                return;
            }
    
            if (check() && tryParse(stock_input, stock) && stock >= 0) break;
            cout << "\033[1;31m❌ Invalid stock! Please enter a valid number.\033[0m\n";

        }
    
        addProduct(new Product(id, name, price, cost, stock, time_added));
        saveToFile("products.txt");
    
        cout << "\n\033[1;32m✅ Product \"" << name << "\" added successfully! 🎉\033[0m\n";
    }

    void ProductList::search_product() {
        string input;
        system("clear");
    
        while (true) {
            cout << "\033[1;34mEnter product ID or name to search (leave blank to cancel): \033[0m";
            getline(cin, input);
    
            if (input.empty() || all_of(input.begin(), input.end(), ::isspace)) {
                cout << "\033[1;33mSearch cancelled.\033[0m\n";
                return;
            }
    
            if (!isValidID(input) && !isValidName(input)) {
                cout << "\033[1;31mError: Input must contain only English letters or digits.\033[0m\n";
                continue;
            } else {
                break;
            }
        }
    
        system("clear");
        ProductNode* current = head;
        bool found = false;
        displayTableHeader();
        while (current) {
            if (current->product->getName() == input) {
                current->product->displayProduct();
                found = true;
            }
            current = current->next;
        }
    
        if (!found) {
            cout << "\033[1;31mProduct not found.\033[0m\n";
        }
    }

    void ProductList::edit_product() {
        string id;
        system("clear");
        displayAll();
        cout << "\033[1;34mEnter Product ID to edit (leave blank to return): \033[0m";
        getline(cin, id);
        if (id.empty() || all_of(id.begin(), id.end(), ::isspace)) return;
        
    
        ProductNode* current = head;
        while (current) {
            if (current->product->getID() == id) {
                string productID = current->product->getID();
                string productName = current->product->getName();
                float price  = current->product->getPrice();
                float cost = current->product->getCost();
                int stock = current->product->getStock();
    
                char option;
                do {
                    system("clear");
                    cout << "\033[1;36m";
                    cout << "+---------------------------------------------+\n";
                    cout << "|         ✏️  Edit Product Information         |\n";
                    cout << "+---------------------------------------------+\033[0m\n";
    
                    cout << "\n\033[1;33mCurrent Product Info:\033[0m\n";
                    cout << left
                    << setw(10) << "ID"
                    << "| " << setw(15) << "Name"
                    << "| " << setw(8) << "Price"
                    << "| " << setw(8) << "Cost"
                    << "| " << setw(8) << "Stock" << endl;
                    cout << string(60, '-') << endl;
                    cout << fixed << setprecision(2);
    
                    cout << left << setw(10) << productID
                    << "| " << setw(15) << productName
                    << "| " << setw(8) << price
                    << "| " << setw(8) << cost;
               if (stock == 0)
                   cout << "| \033[1;31mOut of Stock\033[0m" << endl;
               else
                   cout << "| " << setw(5) << stock << endl;
    
                   cout << "\n\033[1;34mChoose the field you want to edit:\033[0m\n";
                   cout << "\033[1;36m";
                   cout << "  [1] \033[0mEdit \033[1mID\033[0m\n";
                   cout << "\033[1;36m  [2] \033[0mEdit \033[1mName\033[0m\n";
                   cout << "\033[1;36m  [3] \033[0mEdit \033[1mPrice\033[0m\n";
                   cout << "\033[1;36m  [4] \033[0mEdit \033[1mCost\033[0m\n";
                   cout << "\033[1;36m  [5] \033[0mEdit \033[1mStock\033[0m\n";
                   cout << "\033[1;32m  [S] \033[0m\033[1mSave and Exit\033[0m\n";
                   cout << "\033[1;31m  [C] \033[0m\033[1mCancel\033[0m\n";
                    option = getch();
    
                    string input;
                    switch (option) {
                        case '1': {
                            cout << "Enter new ID (leave blank to cancel): ";
                            getline(cin, input);
                            if (!(input.empty() || all_of(input.begin(), input.end(), ::isspace))) {
                                if (!isDuplicateID(input)) productID = input;
                                else {
                                    cout << "\033[1;31m❌ Duplicate ID. Keeping current.\033[0m\n";
                                    Pause();
                                }
                            }
                            break;
                        }
                        case '2': {
                            cout << "Enter new name (leave blank to cancel): ";
                            getline(cin, input);
                            if (!(input.empty() || all_of(input.begin(), input.end(), ::isspace))) {
                                if (isValidName(input) && !isDuplicateName(input)) productName = input;
                                else {
                                    cout << "\033[1;31m❌ Invalid or duplicated name. Keeping current.\033[0m\n";
                                    Pause();
                                }
                            }
                            break;
                        }
                        case '3': {
                            cout << "Enter new price (leave blank to cancel): ";
                            getline(cin, input);
                            float newPrice;
                            if (!input.empty() && tryParse(input, newPrice) && check() && newPrice >= 0) {
                                price = newPrice;
                            } else if (!input.empty()) {
                                cout << "\033[1;31m❌ Invalid price. Keeping current.\033[0m\n";
                                Pause();
                            }
                            break;
                        }
                        case '4': {
                            cout << "Enter new cost (leave blank to cancel): ";
                            getline(cin, input);
                            float newCost;
                            if (!input.empty() && tryParse(input, newCost) && check() && newCost >= 0) {
                                cost = newCost;
                            } else if (!input.empty()) {
                                cout << "\033[1;31m❌ Invalid cost. Keeping current.\033[0m\n";
                                Pause();
                            }
                            break;
                        }
                        case '5': {
                            cout << "Enter new stock (leave blank to cancel): ";
                            getline(cin, input);
                            int newStock;
                            if (!input.empty() && tryParse(input, newStock) && check() && newStock >= 0) {
                                stock = newStock;
                            } else if (!input.empty()) {
                                cout << "\033[1;31m❌ Invalid stock. Keeping current.\033[0m\n";
                                Pause();
                            }
                            break;
                        }
                        case 'S':
                        case 's': {
                            string timestamp = getCurrentTimestamp();
                            delete current->product;
                            current->product = new Product(productID, productName, price, cost, stock, timestamp);
                            saveToFile("products.txt");
                            cout << "\033[1;32m✅ Product updated successfully!\033[0m\n";
                            return;
                        }
                        case 'C':
                        case 'c':
                            cout << "\033[1;33m❌ Changes cancelled. Nothing saved.\033[0m\n";
                            return;
                        default:
                            cout << "\033[1;31m❌ Invalid option.\033[0m\n";
                            Pause();
                            break;
                    }
                } while (true);
            }
            current = current->next;
        }
    
        cout << "\033[1;31m❌ Product with ID '" << id << "' not found.\033[0m\n";
    }
#endif