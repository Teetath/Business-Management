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
    
    public:
        ProductList();
        ~ProductList();
    
        void addProduct(Product* product);
        void removeProduct(const string& name);
        void displayAll();
        void loadFromFile(const string& filename);
        void saveToFile(const string& filename) const;
        void comparePrice(float price);
        void compareStock(int stock);
        void sell();
        void clearLL();
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

void ProductList::displayAll() {
    system("clear");
    cout << "Name           | Price   | Cost    | VAT     | Total   | Profit  | Stock" << endl;
cout << "-------------------------------------------------------------------------" << endl;
    ProductNode* current = head;
    while (current) {
        current->product->displayProduct();
        current = current->next;
    }
}

void ProductList::loadFromFile(const string& filename) {
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
