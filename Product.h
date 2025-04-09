

class Product {
    private:
        string name;
        float price;
        int stock;
    public:
        Product(string name,float price,int stock):name(name),price(price),stock(stock) {}
        void displayProduct() {
            cout << "Product: " << name << ", Price: $" << price
             << ", Stock: " << stock << endl;
        }
    string getName() {return name; }
    float getPrice() { return price; }
    int getStock() { return stock; }

    string getLine() {
        return name + "," + to_string(price) + "," + to_string(stock);
    }
};