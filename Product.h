class Product {
    private:
        string name;
        float price;
        float cost;
        int stock;
    
    public:
        Product(string name, float price, float cost, int stock);
        void displayProduct() const;
        string getName() const;
        float getPrice() const;
        float getCost() const; 
        float getProfitPerUnit() const;
        float getVAT() const;
        float getPriceWithVAT() const;
        int getStock() const;
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
    
    public:
        ProductList();
        ~ProductList();
        
        bool isDuplicateName(const string& name) const;
        void addProduct(Product* product);
        void add_new_product();
        void removeProduct(const string& name);
        void sortByNameAZ();
        void sortByNewest();
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
        void printSalesData(const string& name) const;
        void summaryIncome(const string& name) const;
        void SortproductMenu(ProductList& list);
        void edit_product();
    };

    Product::Product(string name, float price, float cost, int stock)
    : name(name), price(price), cost(cost), stock(stock) {}

    void Product::displayProduct() const {
        cout << fixed << setprecision(2);
        if (stock == 0) {
            cout << left << setw(15) << name
                << "| " << setw(8) << price
                << "| " << setw(8) << cost
                << "| " << setw(8) << getVAT()
                << "| " << setw(8) << getPriceWithVAT()
                << "| " << setw(8) << getProfitPerUnit()
                << "| \033[1;31mOut of Stock\033[0m" << endl;
        } else {
            cout << left << setw(15) << name
                << "| " << setw(8) << price
                << "| " << setw(8) << cost
                << "| " << setw(8) << getVAT()
                << "| " << setw(8) << getPriceWithVAT()
                << "| " << setw(8) << getProfitPerUnit()
                << "| " << setw(5) << stock << endl;
        }
    }

    string Product::getName() const { return name; }
    float Product::getPrice() const { return price; }
    float Product::getCost() const { return cost; }
    float Product::getVAT() const { return price*0.07f; }
    float Product::getPriceWithVAT() const { return price + getVAT(); }
    float Product::getProfitPerUnit() const { return price - cost; }
    int Product::getStock() const { return stock; }

    string Product::getLine() const {
        stringstream ss;
        ss << fixed << setprecision(2);  // พิมพ์ทศนิยม 2 ตำแหน่ง
        ss << name << "," << price << "," << cost << "," << stock;
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
    }

    void ProductList::removeProduct(const string& name) {
        ProductNode* current = head;
        ProductNode* previous = nullptr;

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
                cout << "Product \"" << name << "\" removed successfully." << endl;

                // หลังลบ อัพเดตไฟล์
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
            << setw(15) << "Name"
            << "| " << setw(8)  << "Price"
            << "| " << setw(8)  << "Cost"
            << "| " << setw(8)  << "VAT"
            << "| " << setw(8)  << "Total"
            << "| " << setw(8)  << "Profit"
            << "| " << setw(8)  << "Stock" << endl;
        cout << string(80, '-') << endl;
    }

    void ProductList::displayAll() {
        system("clear");
        displayTableHeader();
        ProductNode* current = head;
        while (current) {
            current->product->displayProduct();
            current = current->next;
        }
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
    }

    void ProductList::loadFromFile(const string& filename) {
        clearLL();
        
        ifstream file(filename);
        string line;

        while (getline(file, line)) {
            stringstream ss(line);
            string name, priceStr, stockStr, costStr;
            getline(ss, name, ',');
            getline(ss, priceStr, ',');
            getline(ss, costStr, ',');
            getline(ss, stockStr);

            float price = stof(priceStr);
            float cost = stof(costStr);
            int stock = stoi(stockStr);

            addProduct(new Product(name, price, cost, stock));
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
                    loadFromFile("products.txt");
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
    void ProductList::add_new_product(){
        string name;
        float price, cost;
        int stock;
        while(true){
            system("clear");
            cout << "\033[1;36m+------------------------------------+\n";
            cout << "|        🆕 Add New Product          |\n";
            cout << "+------------------------------------+\033[0m\n";
            cout << "\033[1;34m📦 Product Name   : \033[0m";
            getline(cin, name);

            if (isDuplicateName(name)) {
                cout << "\033[1;31m❌ Product \'"<< name << "\' already exists! Cannot add duplicate.\033[0m\n";
                break;
            }
        }
        

        cout << "\033[1;34m💲 Product Price  : \033[0m";
        cin >> price;

        cout << "\033[1;34m💲 Product Cost   : \033[0m";
        cin >> cost;

        cout << "\033[1;34m📦 Product Stock  : \033[0m";
        cin >> stock;

        addProduct(new Product(name, price, cost, stock));
        saveToFile("products.txt");
        
        cout << "\n\033[1;32m✅ Product \"" << name << "\" added successfully! 🎉\033[0m\n";
        return;
    }
    void ProductList::edit_product() {
        string name;
        system("clear");
        displayAll();
        cout << "\033[1;34mEnter name to edit: \033[0m";
        cin >> name;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
        ProductNode* current = head;
        while (current) {
            if (current->product->getName() == name) {
                string productName = current->product->getName();
                float price  = current->product->getPrice();
                float cost = current->product->getCost();
                int stock = current->product->getStock();
    
                char option;
                do {
                    system("clear");
                    cout << "\033[1;36m";
                    cout << "+---------------------------------------------+\n";
                    cout << "|       ✏️  Edit Employee Information          |\n";
                    cout << "+---------------------------------------------+\033[0m\n";

                    cout << "\n\033[1;33mCurrent Product Info:\033[0m\n";
                    cout << left
                        << setw(15) << "Name"
                        << "| " << setw(8)  << "Price"
                        << "| " << setw(8)  << "Cost"
                        << "| " << setw(8)  << "Stock" << endl;
                    cout << string(80, '-') << endl;
                    cout << fixed << setprecision(2);

                    if (stock == 0) {
                        cout << left << setw(15) << productName
                            << "| " << setw(8) << price
                            << "| " << setw(8) << cost
                            << "| \033[1;31mOut of Stock\033[0m" << endl;
                    } else {
                        cout << left << setw(15) << productName
                            << "| " << setw(8) << price
                            << "| " << setw(8) << cost
                            << "| " << setw(5) << stock << endl;
                    }

                    cout << "\n\033[1;34mChoose the field you want to edit:\033[0m\n";
                    cout << "\033[1;36m";
                    cout << "  [1] \033[0mEdit \033[1mName\033[0m\n";
                    cout << "\033[1;36m  [2] \033[0mEdit \033[1mPrice\033[0m\n";
                    cout << "\033[1;36m  [3] \033[0mEdit \033[1mCost\033[0m\n";
                    cout << "\033[1;36m  [4] \033[0mEdit \033[1mStock\033[0m\n";
                    cout << "\033[1;32m  [S] \033[0m\033[1mSave and Exit\033[0m\n";
                    cout << "\033[1;31m  [C] \033[0m\033[1mCancel\033[0m\n";
                    option = getch();
    
                    string input;
                    switch (option) {
                        case '1':
                            cout << "Enter new name (leave blank to keep current): ";
                            getline(cin, input);
                            if (!input.empty()) {
                                if (isValidName(input)) productName = input;
                                else cout << "\033[1;31mInvalid name. Keeping current.\033[0m\n";
                            }
                            Pause();
                            break;
                        case '2':
                            cout << "Enter new price (or type 'cancel' to skip): ";
                            getline(cin, input);
                            if (input != "cancel") {
                                try {
                                    float newPrice = stof(input);
                                    if (check() && newPrice >= 0) price = newPrice;
                                    else cout << "\033[1;31mInvalid price. Keeping current.\033[0m\n";
                                } catch (...) {
                                    cout << "\033[1;31mInvalid input. Keeping current.\033[0m\n";
                                }
                            }
                            Pause();
                            break;
                        case '3':
                            cout << "Enter new cost (or type 'cancel' to skip): ";
                            getline(cin, input);
                            if (input != "cancel") {
                                try {
                                    float newCost = stof(input);
                                    if (check() && newCost >= 0) cost = newCost;
                                    else cout << "\033[1;31mInvalid cost. Keeping current.\033[0m\n";
                                } catch (...) {
                                    cout << "\033[1;31mInvalid input. Keeping current.\033[0m\n";
                                }
                            }
                            Pause();
                            break;
                        case '4':
                            cout << "Enter new stock (or type 'cancel' to skip): ";
                            getline(cin, input);
                            if (input != "cancel") {
                                try {
                                    int newStock = stoi(input);
                                    if (check() && newStock >= 0) stock = newStock;
                                    else cout << "\033[1;31mInvalid stock. Keeping current.\033[0m\n";
                                } catch (...) {
                                    cout << "\033[1;31mInvalid input. Keeping current.\033[0m\n";
                                }
                            }
                            Pause();
                            break;
                        case 'S':
                        case 's':
                            // Update product with new info
                            delete current->product;
                            current->product = new Product(productName, price, cost, stock);
                            saveToFile("products.txt");
                            cout << "\033[1;32mProduct updated successfully!\033[0m\n";
                            return;
                        case 'C':
                        case 'c':
                            cout << "\033[1;33mChanges cancelled. Nothing was saved.\033[0m\n";
                            return;
                        default:
                            cout << "\033[1;31mInvalid option. Try again.\033[0m\n";
                            Pause();
                            break;
                    }
                } while (true);
            }
            current = current->next;
        }
    
        cout << "\033[1;31mProduct '" << name << "' not found.\033[0m\n";
    }