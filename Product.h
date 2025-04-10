class Product {
    private:
        string name;
        float price;
        int stock;
    
    public:
        Product(string name, float price, int stock);
        void displayProduct() const;
        string getName() const;
        float getPrice() const;
        int getStock() const;
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
        void displayAll();
        void loadFromFile(const string& filename);
        void saveToFile(const string& filename) const;
        void comparePrice(float price);
        void compareStock(int stock);
    };

    Product::Product(string name, float price, int stock)
    : name(name), price(price), stock(stock) {}

void Product::displayProduct() const {
    cout << "Product: " << name << ", Price: $" << price
         << ", Stock: " << stock << endl;
}

string Product::getName() const { return name; }
float Product::getPrice() const { return price; }
int Product::getStock() const { return stock; }

string Product::getLine() const {
    return name + "," + to_string(price) + "," + to_string(stock);
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

void ProductList::displayAll() {
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
        string name, priceStr, stockStr;
        getline(ss, name, ',');
        getline(ss, priceStr, ',');
        getline(ss, stockStr);

        float price = stof(priceStr);
        int stock = stoi(stockStr);

        addProduct(new Product(name, price, stock));
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